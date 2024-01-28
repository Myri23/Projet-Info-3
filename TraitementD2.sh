#!/bin/bash

#cat data.csv | cut -d";" -f5,6 | awk -F ';' '{noms[$1] += $2; sommes[$1] = $2} END {for (k in noms) print k ";" noms[k] ";" sommes[k]}' | sort -rn | head -10 > temp/result_D2.txt

awk -F ';' '
  { noms[$6] += $5 }
  END {
    for (k in noms) {
      print k ";" noms[k]
    }
  }
' data.csv | sort -t';' -k2 -rn | awk -F ';' '{print $1 ";" $2}' | tr ";" " " | head -10 > temp/result_D2.txt