#!/bin/bash

# Compile the C code
make

# Run the program and capture the output
output=$(./wildfire )

# Expected output
expected="5"

# Check if the output matches the expected result
if [ "$output" == "$expected" ]; then
    echo "Test passed!"
else
    echo "Test failed! Expected '$expected', but got '$output'."
fi
