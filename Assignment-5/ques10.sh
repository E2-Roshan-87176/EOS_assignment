#!/bin/bash


fibonacci() {
    local terms=$1
    local a=0
    local b=1

    echo "Fibonacci Series up to $terms terms:"

    for ((i=0; i<terms; i++)); do
        echo -n "$a "
     
        local next=$((a + b))
        a=$b
        b=$next
    done

    echo 
}


read -p "Enter the number of terms in the Fibonacci series: " number


if ! [[ "$number" =~ ^[0-9]+$ ]]; then
    echo "Invalid input. Please enter a valid positive integer."
    exit 1
fi

fibonacci "$number"
