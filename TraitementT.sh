#!/bin/bash
 
cut -d";" -f1,3 data.csv > tempT1.txt
cut -d";" -f1,4 data.csv > tempT2.txt
cut -d";" -f1,3,4 data.csv > tempTbis.txt
paste -d '\n' tempT1.txt tempT2.txt > tempT3.txt
uniq -c tempT3.txt > tempT4.txt

head -10 resultatsTc.txt > resultatsT.txt