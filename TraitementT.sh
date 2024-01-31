#!/bin/bash
 
# Vérification du nombre de paramètres
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 data.csv"
    exit 1
fi

awk -F';' '{
    data[$3][$1] = 1; 
    data[$4][$1] = 1; 
    if ($2 == 1) departures[$3]++;
} 
END { 
    for (city in data) {
        count = 0;
        for (id in data[city]) {
            count++;
        }
        print count, city, departures[city];
    }
}' data.csv > combined_result.txt

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

head -10 resultatsTcombined.txt | sort -t ';' -k2> result_T.txt



