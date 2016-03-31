#!/bin/bash

if [[ $# -ne 2 ]]; then
    echo "Usage: $0 matrixSize numberOfTests"
else
#./bin& 128 1&
    for (( i = 1; i <= $2; i++ ))
    do
        ./bin $1 1 > $1x$1_test_$i&
    done
fi
