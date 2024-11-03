#!/bin/bash


echo "Hidden files in the current directory:"
ls -d .[^.]* 2>/dev/null


if [ $? -ne 0 ]; then
    echo "No hidden files found."
fi
