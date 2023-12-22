#!/bin/bash
 
cut -d";" -f1,3 data.csv > tempT1.txt
cut -d";" -f1,4 data.csv > tempT2.txt
paste -d '\n' tempT1.txt tempT2.txt > tempT3.txt
uniq -c tempT3.txt > tempT4.txt