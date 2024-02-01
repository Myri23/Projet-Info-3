#!/bin/bash

# Début du chronomètre
start=$(date +%s)


# Vérification du nombre de paramètres
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 data.csv"
    exit 1
fi

cut -d";" -f1,5 data.csv > tempS.txt

# Trie et extrait les distances maximales et minimales pour chaque routeID

awk -F ';' '{
    if (!($1 in minDistances) || $2 < minDistances[$1]) {
        minDistances[$1] = $2;
    }
    if (!($1 in maxDistances) || $2 > maxDistances[$1]) {
        maxDistances[$1] = $2;
    }
    distancesSomme[$1] += $2;  
    compteur[$1]++;  
}
END {
    for (routeID in maxDistances) {
        difference = maxDistances[routeID] - minDistances[routeID];
        moyenne = distancesSomme[routeID] / compteur[routeID];
        print routeID ";" minDistances[routeID] ";" moyenne ";" maxDistances[routeID] ";" difference;
    }
}' tempS.txt > tempS2.txt

#tri des donnees par le programme c

# Compilation du programme C 
make

# Mise ne pause du chronomètre jusqu'à ce que le fichier exécutable généré par la compilation existe
while [ ! -f prog ]; do
    sleep 1
done

# Exécution du programme C
./prog

head -50 result_S1.txt > result_S.txt


# Fin du chronomètre
end=$(date +%s)

# Calcul de la durée d'exécution en secondes
duration=$((end - start))

# Affichage de la durée
echo "Durée d'exécution : $duration secondes"

