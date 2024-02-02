#!/bin/bash


start=$(date +%s)  #Début du chronomètre

cut -d";" -f1,6 data.csv | sort | uniq | cut -d";" -f2 | sort | uniq -c | sort -r -k1 | head -10 > demo/result_D1.txt


gnuplot -persist << GNU_CMD  #Appeler le script Gnuplot pour générer le graphique

set terminal png  #Spécifier le terminal de sortie

set output "images/histogramme_horizontal_D1.png"  #Spécifier le nom du fichier de sortie


set style fill solid  #Style de remplissage des barres


set boxwidth 2  #Largeur des barres


set ylabel "Conducteurs avec le plus de trajets (option -d1)"  #Titre du graphique


set y2tics # Étiquettes des axes
set xlabel "Nombre de Trajets"
set y2label "Noms des Conducteurs"
set xtics rotate by 90 right
set y2tics rotate by 90 right
unset ytics

stats "demo/result_D1.txt" using 1 nooutput # Obtenir la valeur maximale de la colonne 1
max_value = STATS_max + 50


set y2range [0:max_value] # Définir une plage pour l'axe y

plot "demo/result_D1.txt" using 1:xticlabels(strcol(2) . " " . strcol(3)) with histograms title "Nombre de Trajets" # Tracer l'histogramme horizontal à partir d'un fichier de données



GNU_CMD



end=$(date +%s) # Fin du chronomètre


duration=$((end - start)) # Calcul de la durée d'exécution en secondes


echo "Durée d'exécution : $duration secondes" # Affichage de la durée
