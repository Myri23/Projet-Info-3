#!/bin/bash 

# Début du chronomètre
start=$(date +%s)

cut -d";" -f1,5 data.csv | awk -F';' '{ distances[$1]+=$2 } END { for (trajet in distances) print trajet " " distances[trajet] }' > temp/result_L2.txt

sort -nr -t' ' -k2 temp/result_L2.txt | head -10 | sort -rn -t' ' -k1 > demo/result_L.txt




# Appeler le script Gnuplot pour générer le graphique
gnuplot -persist << GNU_CMD
# Spécifier le terminal de sortie
set terminal png

# Spécifier le nom du fichier de sortie
set output "images/histogramme_L.png"

# Style de remplissage des barres
set style fill solid

# Largeur des barres
set boxwidth 1

# Titre du graphique
set title "Les 10 trajets les plus longs (option -l)"

# Étiquettes des axes
set xlabel "Route ID"
set ylabel "Distances (km)"
set xtics rotate by 90 right


# Tracer l'histogramme horizontal à partir d'un fichier de données
plot "./demo/result_L.txt" using 2:xticlabels(1) with histograms notitle
GNU_CMD



#Fin du chronomètre
end=$(date +%s)

# Calcul de la durée d'exécution en secondes
duration=$((end - start))

# Affichage de la durée
echo "Durée d'exécution : $duration secondes"


