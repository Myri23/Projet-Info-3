#!/bin/bash

# Début du chronomètre
start=$(date +%s)

# Vérification du nombre de paramètres
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 data.csv"
    exit 1
fi

# Trie du fichier data.csv pour obtenir le nombre de fois où chaque ville est traversée et le nombre de fois où ce sont des villes de départ
awk -F';' '{
    tableau[$3][$1] = 1; 
    tableau[$4][$1] = 1; 
    if ($2 == 1) departs[$3]++;
} 
END { 
    for (ville in tableau) {
        compte = 0;
        for (id in tableau[ville]) {
            compte++; 
        }
        print compte " " departs[ville] " " ville;
    }
}' data.csv > temp/temp_resultat_T.txt

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
executable="progc/execT"

# Exécution du programme c avec les arguments fournis pour trier le fichier temp_resultat_T.txt dans l'ordre décroissant
"$executable" "$@"


# Affichage des premières lignes triées
head -10 temp/resultatsTc.txt | sort -t ' ' -k3 > demo/result_T.txt


# Tracer l'histogramme horizontal à partir d'un fichier de données
gnuplot -persist << GNU_CMD
# Spécifier le terminal de sortie
set terminal png

# Spécifier le nom du fichier de sortie
set output "images/histogramme_T.png"

# Style de remplissage des barres
set style fill solid

# Largeur des barres
set boxwidth 2

# Titre du graphique
set ylabel "option -t"

# Étiquettes des axes
set xlabel "Villes"
set y2label "Nombre de Routes"
set xtics rotate by 90 right


# Tracer l'histogramme horizontal à partir d'un fichier de données
plot "demo/result_T.txt" using 1:xtic(3) with histograms title "Colonne 2", \
     '' using 2:xtic(strcol(3) . " " . strcol(4)) with histograms title "Colonne 3"
GNU_CMD






















# Fin du chronomètre
end=$(date +%s)

# Calcul de la durée d'exécution en secondes
duration=$((end - start))

# Affichage de la durée
echo "Durée d'exécution : $duration secondes"
 







