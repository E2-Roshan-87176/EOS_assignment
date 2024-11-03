#!/bin/bash

is_leap_year() {
    local year=$1
    if (( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) )); then
        echo "$year is a leap year."
    else
        echo "$year is not a leap year."
    fi
}


read -p "Enter a year: " year


is_leap_year "$year"
