#!/bin/bash

#gcc -o exe prog.c

#./exe/

cat data.csv

#mettre verification c

tmp="temp"
img="images"


if [ -d "$tmp" ]; then
  echo "Le dossier $tmp existe"
  rm -r "$tmp"
fi
mkdir "$tmp"


if [ -d "$img" ]; then
  echo "Le dossier $img existe"
else
  mkdir "$img"
fi



chmod -R u=rwx $tmp
chmod -R u=rwx $img


