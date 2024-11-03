#!/bin/bash


read -p "Enter the name of file or directory: " name


if [ -f "$name" ]; 
then
  
    echo "The entered name is a file."
    echo "File Size: $(stat -c%s "$name") bytes"
    

elif [ -d "$name" ]; 
then

    echo "The entered name is a directory."
    echo "Contents:"
    ls -l "$name"
    
else
    
    echo "The entered name is neither a file nor a directory."
fi
