#!/bin/bash

# Vérification du nombre de paramètres
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 data.csv"
    exit 1
fi

cut -d";" -f1,5 data.csv > tempS.csv
#cherche un moyen de recuperer en shell ou en c que les distances max et min pour un route ID unique 
#diff = distance max - distance min en shell ou en c
#avl qui trie dans l'ordre decroissant le diff par rapport au route ID
