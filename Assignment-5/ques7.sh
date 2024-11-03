#!/bin/bash


read -p "Enter a number: " number

if ! [[ "$number" =~ ^-?[0-9]+$ ]]; then
    echo "Invalid input. Please enter a valid number."
    exit 1
fi

if [ "$number" -gt 0 ]; then
    echo "$number is a positive number."
elif [ "$number" -lt 0 ]; then
    echo "$number is a negative number."
else
    echo "$number is zero."
fi
