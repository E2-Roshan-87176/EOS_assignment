#!/bin/bash

while true; do
    echo "Please select an option:"
    echo "1. Date"
    echo "2. Cal"
    echo "3. Ls"
    echo "4. Pwd"
    echo "5. Exit"
    
    read -p "Enter your choice [1-5]: " choice
    
    case $choice in
        1)
            echo "Current Date and Time: $(date)"
            ;;
        2)
            echo "Current Month Calendar:"
            cal
            ;;
        3)
            echo "Listing files in the current directory:"
            ls -l
            ;;
        4)
            echo "Current Working Directory: $(pwd)"
            ;;
        5)
            echo "Exiting..."
            exit 0
            ;;
        *)
            echo "Invalid option selected. Please try again."
            ;;
    esac
    
    echo 
done
