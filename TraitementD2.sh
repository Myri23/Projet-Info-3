#!/bin/bash

# Début du chronomètre
start=$(date +%s)


awk -F ';' '
  { noms[$6] += $5 }
  END {
    for (k in noms) {
      print k ";" noms[k]
    }
  }
' data.csv | sort -t';' -k2 -rn | awk -F ';' '{print $1 ";" $2}' | tr ";" " " | head -10 > demo/result_D2.txt


# Appeler le script Gnuplot pour générer le graphique
gnuplot -persist << GNU_CMD
# Spécifier le terminal de sortie
set terminal png

# Spécifier le nom du fichier de sortie
set output "images/histogramme_horizontal_D2.png"

# Style de remplissage des barres
set style fill solid

# Largeur des barres
set boxwidth 2

# Titre du graphique
set ylabel "Conducteurs avec plus longue distance (option -d2)"

# Étiquettes des axes
set y2tics
set xlabel "Noms des Conducteurs"
set y2label "Nombre de Trajets"
set xtics rotate by 90 right
set y2tics rotate by 90 right
unset ytics

# Obtenir la valeur maximale de la colonne 1
stats "demo/result_D2.txt" using 3 nooutput
max_value = STATS_max + 10000

# Définir une plage pour l'axe y
set y2range [0:max_value]

# Style de police pour les étiquettes de l'axe y
set y2tics font ",8"

# Tracer l'histogramme horizontal à partir d'un fichier de données
plot "demo/result_D2.txt" using 3:xticlabels(strcol(1) . " " . strcol(2)) with histograms title "Nombre de Trajets"
GNU_CMD



# Fin du chronomètre
end=$(date +%s)

# Calcul de la durée d'exécution en secondes
duration=$((end - start))

# Affichage de la durée
echo "Durée d'exécution : $duration secondes"