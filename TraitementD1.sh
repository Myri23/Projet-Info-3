#!/bin/bash

# Début du chronomètre
start=$(date +%s)

cat data.csv | cut -d";" -f1,6 | sort | uniq > tempD1.txt
 
cat tempD1.txt | cut -d";" -f2 | sort | uniq -c | sort -r -k1 | head -10 > resultD1.txt

# Fin du chronomètre
end=$(date +%s)

# Calcul de la durée d'exécution en secondes
duration=$((end - start))

# Affichage de la durée
echo "Durée d'exécution : $duration secondes"
