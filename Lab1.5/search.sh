#!/bin/bash
direc='/home/alejandro/Desktop/src/*'
juanito='/home/alejandro/Desktop/os-labs/Lab1.5/linux_source_structure.txt'

for dir in $direc; do
    if [ -d "$dir" ]; then
        echo 'Directory: '$dir >> $juanito
        echo 'Files with .c' >> $juanito
        find $dir -name '*.c'  >> $juanito
        echo 'Files with .h'  >> $juanito
        find $dir -name '*.h' >> $juanito
    fi
done

