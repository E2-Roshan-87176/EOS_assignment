#!/bin/bash

read -p "Enter first number: " num1
read -p "Enter second number: " num2
read -p "Enter third number: " num3


greatest=$num1


if [ "$num2" -gt "$greatest" ]; then
    greatest=$num2
fi


if [ "$num3" -gt "$greatest" ]; then
    greatest=$num3
fi

echo "The greatest number is: $greatest"
