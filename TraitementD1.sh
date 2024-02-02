#!/bin/bash

# Début du chronomètre
start=$(date +%s)

cut -d";" -f1,6 data.csv | sort | uniq | cut -d";" -f2 | sort | uniq -c | sort -r -k1 | head -10 > demo/result_D1.txt

# Appeler le script Gnuplot pour générer le graphique
gnuplot -persist << GNU_CMD
# Spécifier le terminal de sortie
set terminal png

# Spécifier le nom du fichier de sortie
set output "images/histogramme_horizontal_D1.png"

# Style de remplissage des barres
set style fill solid

# Largeur des barres
set boxwidth 2

# Titre du graphique
set ylabel "Conducteurs avec le plus de trajets (option -d1)"

# Étiquettes des axes
set y2tics
set xlabel "Nombre de Trajets"
set y2label "Noms des Conducteurs"
set xtics rotate by 90 right
set y2tics rotate by 90 right
unset ytics

# Obtenir la valeur maximale de la colonne 1
stats "demo/result_D1.txt" using 1 nooutput
max_value = STATS_max + 50

# Définir une plage pour l'axe y
set y2range [0:max_value]

# Tracer l'histogramme horizontal à partir d'un fichier de données
plot "demo/result_D1.txt" using 1:xticlabels(strcol(2) . " " . strcol(3)) with histograms title "Nombre de Trajets"



GNU_CMD


# Fin du chronomètre
end=$(date +%s)

# Calcul de la durée d'exécution en secondes
duration=$((end - start))

# Affichage de la durée
echo "Durée d'exécution : $duration secondes"