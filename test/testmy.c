#include "../include/my.h"

#define TEST(code) { \
    my_str(#code); \
    my_str(": "); \
    code; }

int main(int argc, char **argv) {
    /*
    TEST(my_int(0));
    TEST(my_int(1));
    my_int(-1);
    my_int(2147483647);
    my_int(-2147483648);
    my_int(102);
    my_int(94);
    my_int(my_strlen("harrow"));
    my_int(my_strlen(""));
    my_int(my_strlen(NULL));
    my_num_base(9, "RTFM");
    my_num_base(-9, "RTFM");
    my_num_base(12, "P");
    my_num_base(-2147483648, "0123");
    my_num_base(2147483647, "0123");
    my_num_base(0, "wtf");
    my_alpha();
    my_digits();
    my_int(my_strindex("", 'u'));
    my_int(my_strrindex("aoxomoxoa", 'c'));
    char str[] = "A";
    my_str(str);
    my_char('\n');
    my_int(my_revstr(str));
    my_str(str);
    my_char('\n');
    */
    my_str("~~~~~~~~~~~TESTS~~~~~~~~~~~~");
    my_char('\n');

    TEST(my_char(*(my_strfind("hello", 'o'))));
    my_char('\n');
    TEST(my_char(*(my_strrfind("hello", 'l'))));
    my_char('\n');

    TEST(my_int(my_strcmp("hello", "hello")));
    my_char('\n');
    TEST(my_int(my_strcmp("hello", "hell")));
    my_char('\n');
    TEST(my_int(my_strcmp("", "")));
    my_char('\n');
    TEST(my_int(my_strcmp(NULL, NULL)));
    my_char('\n');
    TEST(my_int(my_strcmp("please", "thankyou")));
    my_char('\n');
    TEST(my_int(my_strcmp("woot", "")));
    my_char('\n');

    TEST(my_int(my_strncmp("wootang", "woot", 4)));
    my_char('\n');
    TEST(my_int(my_strncmp("hello", "hello", 3)));
    my_char('\n');
    TEST(my_int(my_strncmp("hello", "hell", 0)));
    my_char('\n');
    TEST(my_int(my_strncmp("", "", 4)));
    my_char('\n');
    TEST(my_int(my_strncmp(NULL, NULL, 0)));
    my_char('\n');
    TEST(my_int(my_strncmp("please", "thankyou", -7)));
    my_char('\n');
    TEST(my_int(my_strncmp("woot", "", 3)));
    my_char('\n');

    char hello[] = "hello";
    char ding[] = "ding";
    char prance[] = "prance";
    char yo[] = "yo";
    char empty[] = "";

    TEST(my_str(my_strcpy(hello, ding)));
    my_char('\n');
    TEST(my_str(my_strcpy(prance, yo)));
    my_char('\n');
    TEST(my_str(my_strcpy(empty, empty)));
    my_char('\n');
    TEST(my_str(my_strcpy(NULL, NULL)));
    my_char('\n');

    TEST(my_str(my_strncpy(hello, ding, 3)));
    my_char('\n');
    TEST(my_str(my_strncpy(prance, yo, 7)));
    my_char('\n');
    TEST(my_str(my_strncpy(empty, empty, 4)));
    my_char('\n');

    char razer[] = "razer";
    char blade[] = "blade";
    char key[] = "key";
    char make[] = "make";
    char a[] = "a";
    char b[] = "b";
    char c[] = "c";

    TEST(my_str(my_strcat(razer, blade)));
    my_char('\n');
    TEST(my_str(my_strcat(key, empty)));
    my_char('\n');
    TEST(my_str(my_strcat(NULL, NULL)));
    my_char('\n');
    TEST(my_str(my_strcat(empty, empty)));
    my_char('\n');
    TEST(my_str(my_strcat(key, make)));
    my_char('\n');
    TEST(my_str(my_strcat(blade, NULL)));
    my_char('\n');
    TEST(my_str(my_strcat(a, b)));
    my_char('\n');

    TEST(my_str(my_strdup(razer)));
    my_char('\n');
    TEST(my_str(my_strdup(empty)));
    my_char('\n');
    TEST(my_str(my_strdup(NULL)));
    my_char('\n');
    TEST(my_str(my_strdup(blade)));
    my_char('\n');
    TEST(my_str(my_strdup(c)));
    my_char('\n');

    TEST(my_str(my_strconcat("hello", "world")));
    my_char('\n');
    TEST(my_str(my_strconcat("", "")));
    my_char('\n');
    TEST(my_str(my_strconcat(NULL, NULL)));
    my_char('\n');
    TEST(my_str(my_strconcat(blade, make)));
    my_char('\n');
    TEST(my_str(my_strconcat("b", "j")));
    my_char('\n');

    TEST(my_str(my_strnconcat("hello", "world", 3)));
    my_char('\n');
    TEST(my_str(my_strnconcat("", "", 4)));
    my_char('\n');
    TEST(my_str(my_strnconcat(NULL, NULL, -10)));
    my_char('\n');
    TEST(my_str(my_strnconcat(blade, make, 10)));
    my_char('\n');
    TEST(my_str(my_strnconcat("b", "j", 0)));
    my_char('\n');

    TEST(my_int(my_atoi("5")));
    my_char('\n');
    TEST(my_int(my_atoi("-5")));
    my_char('\n');
    TEST(my_int(my_atoi("--5")));
    my_char('\n');
    TEST(my_int(my_atoi("a-b54sc7-d")));
    my_char('\n');
    TEST(my_int(my_atoi("abcd")));
    my_char('\n');
    TEST(my_int(my_atoi("")));
    my_char('\n');
    TEST(my_int(my_atoi("hhee--asb67kk4432--kgfbmk")));
    my_char('\n');

    return 0;
}
