#!/bin/bash
direc='/home/alejandro/Desktop/src/*'
output='/home/alejandro/Desktop/os-labs/Lab1.5/linux_source_structure.txt'

for dir in $direc; do
    if [ -d "$dir" ]; then
        echo 'Directory: '$dir >> $output
        echo 'Files with .c' >> $output
        find $dir -name '*.c'  >> $output
        echo 'Files with .h'  >> $output
        find $dir -name '*.h' >> $output
    fi
done

