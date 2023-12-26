#!/bin/bash 

cat data.csv | cut -d";" -f1,5 | awk -F';' '{ distances[$1]+=$2 } END { for (trajet in distances) print trajet ";" distances[trajet] }' > result_L.txt

cat result_L.txt | sort -nr -t';' -k2 | head -10 | sort -rn -t';' -k1 > result_L2.txt