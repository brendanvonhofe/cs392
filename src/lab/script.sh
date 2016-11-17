#! /bin/bash

var=echo $PATH | tr ":" " "

for dir in var; do
    echo ls $dir | grep -$1
done
