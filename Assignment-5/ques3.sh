#!/bin/bash

# Prompt the user to enter a name (file or directory)
read -p "Enter the name of file or directory: " name

# Check if the entered name is a file
if [ -f "$name" ]; 
then
    # If it's a file, display its size
    echo "The entered name is a file."
    echo "File Size: $(stat -c%s "$name") bytes"
    
# Check if the entered name is a directory
elif [ -d "$name" ]; 
then
    # If it's a directory, display its contents
    echo "The entered name is a directory."
    echo "Contents:"
    ls -l "$name"
    
else
    # If neither, display an error message
    echo "The entered name is neither a file nor a directory."
fi
