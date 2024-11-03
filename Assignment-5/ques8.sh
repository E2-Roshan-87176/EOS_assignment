#!/bin/bash


read -p "Enter a number to print its multiplication table: " number


if ! [[ "$number" =~ ^-?[0-9]+$ ]]; then
    echo "Invalid input. Please enter a valid integer."
    exit 1
fi

echo "Multiplication Table of $number:"
for ((i=1; i<=10; i++)); do
    result=$((number * i))
    echo "$number x $i = $result"
done
