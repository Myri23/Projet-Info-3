#!/bin/bash

# Vérification du nombre de paramètres
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 data.csv"
    exit 1
fi
 
cut -d";" -f1,3 data.csv | paste -d '\n'-<(cut -d";" -f1,4 data.csv) | sort | uniq -c > tempT3.txt 


head -10 resultatsTc.txt > resultatsT1.csv

cut -d";" -f1,3,4 data.csv > tempTbis.csv

# Assignation des noms de fichiers aux variables
data_csv="tempTbis.csv"
villes_a_rechercher="resultatsT1.csv"

# Création d'un fichier temporaire pour stocker les résultats
temp_file=$(mktemp)

# Boucle pour chaque ville dans le fichier contenant la liste de 10 villes
while IFS= read -r ville; do
    compteur=0
    # Parcours du fichier CSV et comptage des occurrences
    compteur=$(awk -v ville="$ville" -F',' '$2 == ville && !($3 ~ ville) {count++} END {print count}' "$data_csv")
    echo "$ville,$compteur" >> "$temp_file"
done < "$villes_a_rechercher"

# Ajout de la troisième colonne au fichier des villes
paste -d',' "$villes_a_rechercher" "$temp_file" > resultatsTfinal.csv

# Nettoyage du fichier temporaire
rm "$temp_file"


