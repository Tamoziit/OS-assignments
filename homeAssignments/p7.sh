#!/bin/bash

if [ $# -ne 3 ]; then
  echo "Usage: $0 <word> <input_file> <output_file>"
  exit 1
fi

word=$1
input_file=$2
output_file=$3

# Using grep with -v to invert match, which excludes lines containing the word
grep -v "$word" "$input_file" > "$output_file"

echo "Lines not containing '$word' have been written to $output_file"

