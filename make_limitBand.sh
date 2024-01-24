#!/bin/bash

# Input file
input_file="limits.txt"

# Check if the file exists
if [ ! -f "$input_file" ]; then
    echo "File not found: $input_file"
    exit 1
fi

# Process each line in the file
while IFS= read -r line; do
    # Check if the line is empty
    if [ -z "$line" ]; then
        # Empty line, start a new row
        echo "],"; echo -n "["
    else
        # Non-empty line, extract and print the last number
        last_number=$(echo "$line" | awk '{print $NF}')
        echo -n "$last_number, "
    fi
done < "$input_file"

