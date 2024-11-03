#!/bin/bash


read -p "Enter your basic salary: " basic_salary


if ! [[ "$basic_salary" =~ ^[0-9]+([.][0-9]+)?$ ]]; then
    echo "Invalid input. Please enter a valid numeric value for basic salary."
    exit 1
fi


da=$(echo "$basic_salary * 0.40" | bc)
hra=$(echo "$basic_salary * 0.20" | bc)


gross_salary=$(echo "$basic_salary + $da + $hra" | bc)


printf "Gross Salary: %.2f\n" "$gross_salary"
