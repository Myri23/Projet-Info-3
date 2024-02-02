#!/bin/bash 

start=$(date +%s) # Début du chronomètre

cut -d";" -f1,5 data.csv | awk -F';' '{ distances[$1]+=$2 } END { for (trajet in distances) print trajet " " distances[trajet] }' > temp/result_L2.txt

sort -nr -t' ' -k2 temp/result_L2.txt | head -10 | sort -rn -t' ' -k1 > demo/result_L.txt


gnuplot -persist << GNU_CMD # Appeler le script Gnuplot pour générer le graphique

set terminal png # terminal de sortie

set output "images/histogramme_L.png" # le nom du fichier de sortie

set style fill solid # Style de remplissage des barres

set boxwidth 1 # Largeur des barres

set title "Les 10 trajets les plus longs (option -l)" # Titre du graphique


set xlabel "Route ID" # Étiquettes des axes
set ylabel "Distances (km)"
set xtics rotate by 90 right

plot "./demo/result_L.txt" using 2:xticlabels(1) with histograms notitle # Tracer l'histogramme horizontal à partir de result_L.txt
GNU_CMD


end=$(date +%s) #Fin du chronomètre

duration=$((end - start)) # Calcul de la durée d'exécution en secondes

echo "Durée d'exécution : $duration secondes" # Affichage de la durée


