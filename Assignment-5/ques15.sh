#!/bin/bash


read -p "Enter the name of the first file: " first_file
read -p "Enter the name of the second file: " second_file


if [[ ! -f "$first_file" ]]; then
    echo "Error: $first_file does not exist."
    exit 1
fi

{
    while IFS= read -r line; do
        
        echo "$line" | tr '[:lower:][:upper:]' '[:upper:][:lower:]'
    done < "$first_file"
} >> "$second_file"

echo "Appended reversed case content from $first_file to $second_file."
