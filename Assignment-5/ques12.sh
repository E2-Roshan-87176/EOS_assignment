#!/bin/bash


if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename="$1"


if [ -f "$filename" ]; then
   
    mod_time=$(stat -c %y "$filename")
    echo "The last modification time of '$filename' is: $mod_time"
else
    
    echo "File '$filename' does not exist."
fi
