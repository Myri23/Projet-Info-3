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

# Appeler le script Gnuplot pour générer le graphique
gnuplot -persist << GNU_CMD
# Spécifier le terminal de sortie
set terminal png

# Spécifier le nom du fichier de sortie
set output "histogramme_horizontal_D1.png"

# Style de remplissage des barres
set style fill solid

# Largeur des barres
set boxwidth 2

# Titre du graphique
set ylabel "Conducteurs avec le plus de trajets (option -d1)"

# Étiquettes des axes
set y2tics
set xlabel "Noms des Conducteurs"
set y2label "Nombre de Trajets"
set xtics rotate by 90 right
set ytics rotate by 90 right

# Définir une plage pour l'axe y2
set y2range [0:0]

# Tracer l'histogramme horizontal à partir d'un fichier de données
plot "temp/result_D1.txt" using 1:xtic(3) with histograms title "Nombre de Trajets"
GNU_CMD
