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
        print routeID ";" minDistances[routeID] ";" moyenne ";" maxDistances[routeID] ";" difference;
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

# Fin du chronomètre
end=$(date +%s)

# Calcul de la durée d'exécution en secondes
duration=$((end - start))

# Affichage de la durée
echo "Durée d'exécution : $duration secondes"
