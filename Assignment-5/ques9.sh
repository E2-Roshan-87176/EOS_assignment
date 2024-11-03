#!/bin/bash


factorial() {
    local num=$1
    local fact=1

    if [ "$num" -lt 0 ]; then
        echo "Factorial is not defined for negative numbers."
        return
    fi

    for ((i=1; i<=num; i++)); do
        fact=$((fact * i))
    done

    echo "The factorial of $num is: $fact"
}


read -p "Enter a non-negative integer to calculate its factorial: " number


if ! [[ "$number" =~ ^[0-9]+$ ]]; then
    echo "Invalid input. Please enter a valid non-negative integer."
    exit 1
fi

factorial "$number"
