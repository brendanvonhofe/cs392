// Compute the sum of a file full of binary 16-bit integer data,
// parallel version.

// TODO: parallelize this program!

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

struct mmap_region {
	int fd;
	void *addr;
	size_t size;
};

struct thread_info {
	int elem_ind;
	int last;
	int result;
};

uint16_t *data;
size_t num_elements;
int elems_per_thread;

size_t get_file_size(const char *filename);
void map_file_region(const char *filename, size_t size, struct mmap_region *region);
void unmap_file_region(struct mmap_region *region);
void *thread_count(struct thread_info *info) {
	int sum = 0;
	if(info->last == 0) {
		for(int i = info->elem_ind; i < info->elem_ind+elems_per_thread; i++) {
			sum += data[i];
		}
	}
	else {
		for(int i = info->elem_ind; i < num_elements; i++) {
			sum += data[i];
		}
	}
	printf("result: %d\n", sum);
	info->result = sum;
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	size_t size;
	uint64_t sum;
	struct mmap_region region;
	int num_threads;

	if (argc != 3) {
		fprintf(stderr, "Usage: sumu16 <input file>\n");
		exit(1);
	}

	// Find out how large the file is.
	size = get_file_size(argv[1]);
	printf("File is %lu bytes in size\n", size);

	// Each element (datum) is 16 bits.
	// Find out how many elements there are overall.
	num_elements = size / sizeof(uint16_t);

	// Map the file data into memory
	map_file_region(argv[1], size, &region);
	data = region.addr;

	num_threads = atoi(argv[2]);
	elems_per_thread = num_elements / num_threads;
	pthread_t threads[num_threads];
	struct thread_info thread_infos[num_threads];


	for(int i = 0; i < num_threads; i++) {
		thread_infos[i].elem_ind = elems_per_thread * i;
		thread_infos[i].last = 0;
		if(i == num_threads -1) {
			thread_infos[i].last = 1;
		}
		//printf("thread %d: %d,%d\n", i, tuple[0], tuple[1]);
		if(pthread_create(&threads[i], NULL, (void * (*) (void*))thread_count, &thread_infos[i]) < 0) {
			printf("Thread create error");
		}
	}

	sum = 0ULL;

	for(int i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
		sum += thread_infos[i].result;
	}

	printf("Sum is %lu\n", sum);

	unmap_file_region(&region);

	return 0;
}

size_t get_file_size(const char *filename)
{
	struct stat file_info;

	if (stat(filename, &file_info) < 0) {
		fprintf(stderr, "Could not stat %s: %s\n", filename, strerror(errno));
		exit(1);
	}
	return (size_t)file_info.st_size;
}

void map_file_region(const char *filename, size_t size, struct mmap_region *region)
{
	region->size = size;

	// Open the file
	region->fd = open(filename, O_RDONLY);
	if (region->fd < 0) {
		fprintf(stderr, "Could not open %s: %s\n", filename, strerror(errno));
		exit(1);
	}

	// Map the file into memory.
	region->addr = mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, region->fd, (off_t)0);
	if (region->addr == MAP_FAILED) {
		fprintf(stderr, "Could not map %s: %s\n", filename, strerror(errno));
		exit(1);
	}
}

void unmap_file_region(struct mmap_region *region)
{
	munmap(region->addr, region->size);
	close(region->fd);
}
