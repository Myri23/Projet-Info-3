#!/bin/bash

# Début du chronomètre
start=$(date +%s)

# Vérification du nombre de paramètres
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 data.csv"
    exit 1
fi

#cut -d";" -f1,5 data.csv > tempS.txt

# Trie et extrait les distances maximales et minimales pour chaque routeID

awk -F ';' '{
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


# Mise ne pause du chronomètre jusqu'à ce que le fichier exécutable généré par la compilation existe
while [ ! -f progc/execS ]; do
    sleep 1
done

# Compilation avec make
make -C progc/ 


# Vérification de la compilation
if [ $? -ne 0 ]; then
    echo "Erreur lors de la compilation."
    exit 1
else
    echo "Compilation réussie."
fi


# Chemin d'accès à l'exécutable
executable="progc/execS"

# Exécution du programme c avec les arguments fournis pour trier le fichier temp_resultat_T.txt dans l'ordre décroissant
"$executable" "$@"

head -50 temp/resultatsSc.txt > demo/result_S.txt



# Appeler le script Gnuplot pour générer le graphique
gnuplot -persist << GNU_CMD

# Spécifier le terminal de sortie
set terminal png

# Spécifier le nom du fichier de sortie
set output "images/graphique_S.png"

# Titre du graphique
set title "Option -s"

# Étiquettes des axes
set xlabel "Identifiant des trajets" #On n'a pas pu mettre les identifiants des trajets sur l'axe des x, notre programme fait apparaitre la différence entre les distances max et min à la place.
set ylabel "Distances en km"
set xtics rotate by 90 right


# Charger les données depuis le fichier
plot "demo/result_S.txt" using 5:2 with lines title "Distance Min", \
     "demo/result_S.txt" using 5:4 with lines title "Distance Max", \
     "demo/result_S.txt" using 5:2:4 with filledcurves notitle lt rgb "#CCCCCC", \
     "demo/result_S.txt" using 5:3 with lines title "Distance Moyenne", \
     


GNU_CMD



# Fin du chronomètre
end=$(date +%s)

# Calcul de la durée d'exécution en secondes
duration=$((end - start))

# Affichage de la durée
echo "Durée d'exécution : $duration secondes"


