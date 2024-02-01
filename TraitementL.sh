#!/bin/bash 

# Début du chronomètre
start=$(date +%s)

cat data.csv | cut -d";" -f1,5 | awk -F';' '{ distances[$1]+=$2 } END { for (trajet in distances) print trajet ";" distances[trajet] }' > result_L.txt

cat result_L.txt | sort -nr -t';' -k2 | head -10 | sort -rn -t';' -k1 > result_L2.txt

# Appeler le script Gnuplot pour générer le graphique
gnuplot -persist << GNU_CMD
# Spécifier le terminal de sortie
set terminal png

# Spécifier le nom du fichier de sortie
set output "histogramme_L.png"

# Style de remplissage des barres
set style fill solid

# Largeur des barres
set boxwidth 1

# Titre du graphique
set title "Les 10 trajets les plus longs"

# Étiquettes des axes
set xlabel "Route ID"
set ylabel "Distances (km)"
set xtics rotate by 90 right

# Tracer l'histogramme horizontal à partir d'un fichier de données
plot "./temp/result_L2.txt" using 2:xtic(1) with histograms notitle
GNU_CMD

# Fin du chronomètre
end=$(date +%s)

# Calcul de la durée d'exécution en secondes
duration=$((end - start))

# Affichage de la durée
echo "Durée d'exécution : $duration secondes"
