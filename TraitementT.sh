#!/bin/bash
 
# Vérification du nombre de paramètres
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 data.csv"
    exit 1
fi
 
cut -d";" -f1,3 data.csv > tempT1.txt
cut -d";" -f1,4 data.csv > tempT2.txt
paste -d '\n' tempT1.txt tempT2.txt > tempT3.txt
 
sort tempT3.txt | uniq -c > tempBis.txt
 
uniq -u tempT3.txt > tempT4.txt
cut -d";" -f2 tempT4.txt | sort > tempT.txt
 
uniq -c tempT.txt > result_T.txt