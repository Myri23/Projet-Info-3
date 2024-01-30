#!/bin/bash
 
# Vérification du nombre de paramètres
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 data.csv"
    exit 1
fi

#1 
awk -F';' '{ data[$3][$1] = 1; data[$4][$1] = 1 } 
END { 
    for (city in data) {
        count = 0;
        for (id in data[city]) {
            count++;
        }
        print count, city;
    }
}' data.csv > result_T.txt

#execution du programme c pour trier le fichier result_T.txt dans l'ordre croissant

# Chemins d'accès aux fichiers source
mainT="/chemin/vers/mainT.c"
avlT="/chemin/vers/avlT.c"

# Chemin d'accès à l'exécutable
executable="/chemin/vers/prog"

# Vérifier si l'exécutable existe
if [ ! -x "$executable" ]; then
    echo "L'exécutable n'existe pas. Compilation en cours..."
    
    # Compiler le programme
    gcc "$mainT" "$avlT" -o "$executable"
    
    # Vérifier si la compilation s'est bien déroulée
    if [ $? -ne 0 ]; then
        echo "Erreur lors de la compilation."
        echo $?
        exit 1
    else
        echo "Compilation réussie."
    fi
fi

# Exécuter le programme avec les arguments fournis
"$executable" "$@"

rm result_T.txt

head -10 resultatsTc.txt > result_T.txt


#2
#sort tempT3.txt | uniq -c > tempBis.txt

awk -F";" '$2 == 1 {print $4}' data.csv > villesDeDepart.csv
awk -F";" '$2 == 1 {print $4}' data.csv | sort | uniq -c > villesDeDepart.csv


# Fichier contenant les 10 villes de référence
villes_reference="villes_reference.txt"

# Fichier contenant les données
donnees="villesDeDepart.csv"

# Nom du fichier de sortie
fichier_sortie="resultat_villes_trouvees.txt"

# Effacer le fichier de sortie s'il existe déjà
> "$fichier_sortie"

# Parcours des villes de référence
oldIFS=$IFS
while IFS= read -r ville_reference; do
    # Recherche de la ville dans les données et copie de la ligne dans le fichier de sortie
    grep -i "$ville_reference" "$donnees" >> "$fichier_sortie"
done < "$villes_reference"
IFS=$oldIFS

