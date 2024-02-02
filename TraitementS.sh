#!/bin/bash

start=$(date +%s) # Début du chronomètre

if [ "$#" -ne 1 ]; then # Vérification du nombre de paramètres
    echo "Usage: $0 data.csv"
    exit 1
fi


awk -F ';' '{ # Trie et extrait les distances maximales et minimales pour chaque routeID
    if (!($1 in minDistances) || $5 < minDistances[$1]) {
        minDistances[$1] = $5;
    }
    if (!($1 in maxDistances) || $5 > maxDistances[$1]) {
        maxDistances[$1] = $5;
    }
    distancesSomme[$1] += $5;  
    compteur[$1]++;  
}
END {
    for (routeID in maxDistances) {
        difference = maxDistances[routeID] - minDistances[routeID];
        moyenne = distancesSomme[routeID] / compteur[routeID];
        print routeID " " minDistances[routeID] " " moyenne " " maxDistances[routeID] " " difference;
    }
}' data.csv > temp/temp_resultat_S.txt

#tri des donnees par le programme c


while [ ! -f progc/execS ]; do # Mise ne pause du chronomètre jusqu'à ce que le fichier exécutable généré par la compilation existe
    sleep 1
done


make -C progc/  # Compilation avec make


if [ $? -ne 0 ]; then # Vérification de la compilation
    echo "Erreur lors de la compilation."
    exit 1
else
    echo "Compilation réussie."
fi


executable="progc/execS" # Chemin d'accès à l'exécutable


"$executable" "$@" # Exécution du programme c avec les arguments fournis pour trier le fichier temp_resultat_T.txt dans l'ordre décroissant

head -50 temp/resultatsSc.txt > demo/result_S.txt


gnuplot -persist << GNU_CMD # Appeler le script Gnuplot pour générer le graphique


set terminal png # Spécifier le terminal de sortie


set output "images/graphique_S.png" # Spécifier le nom du fichier de sortie


set title "Option -s" # Titre du graphique

# Étiquettes des axes
set xlabel "Identifiant des trajets" #On n'a pas pu mettre les identifiants des trajets sur l'axe des x, notre programme fait apparaitre la différence entre les distances max et min à la place.
set ylabel "Distances en km"
set xtics rotate by 90 right



plot "demo/result_S.txt" using 5:2 with lines title "Distance Min", \ # Charger les données depuis le fichier result_S.txt
     "demo/result_S.txt" using 5:4 with lines title "Distance Max", \
     "demo/result_S.txt" using 5:2:4 with filledcurves notitle lt rgb "#CCCCCC", \
     "demo/result_S.txt" using 5:3 with lines title "Distance Moyenne", \
     


GNU_CMD


end=$(date +%s) # Fin du chronomètre

duration=$((end - start)) # Calcul de la durée d'exécution en secondes


echo "Durée d'exécution : $duration secondes" # Affichage de la durée


