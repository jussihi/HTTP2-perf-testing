#!/bin/bash

echo "testing ${1} for 1000 iterations"

for (( i=0; i<1000; i++ ))
do  
   ./${1} >> ${1}-results
done