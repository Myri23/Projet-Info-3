#!/bin/bash

#gcc -o exe prog.c

#./exe/

cat data.csv

#mettre verification c

tmp="temp"
img="images"


if [ -d "$tmp" ]; then
  echo "Le dossier $tmp existe"
  rm -r "$tmp"
fi
mkdir "$tmp"


if [ -d "$img" ]; then
  echo "Le dossier $img existe"
else
  mkdir "$img"
fi



chmod -R u=rwx $tmp
chmod -R u=rwx $img

# Fonction pour afficher l'aide
afficher_aide() {
    echo "Usage: $0 FICHIER [OPTIONS]"
    echo "Options:"
    echo "  -d1, Activer l'option d1"
    echo "  -d2, Activer l'option d2"
    echo "  -l, Activer l'option l"
    echo "  -t, Activer l'option t"
    echo "  -s, Activer l'option s"
}

# Vérifier si au moins un argument (le chemin du fichier) est fourni
if [ $# -eq 0 ]; then
    echo "Erreur : Chemin du fichier manquant."
    afficher_aide
    exit 1
fi

# Récupérer le chemin du fichier (premier argument)
fichier=$1
shift  # Supprimer le premier argument pour ne laisser que les options

# Vérifier si l'argument -h est présent
if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    afficher_aide
    exit 0  # Quitter le script après avoir affiché l'aide
fi

# Vérifier si au moins une option est fournie
if [ $# -eq 0 ]; then
    echo "Erreur : Aucune option spécifiée."
    afficher_aide
    exit 1
fi

# Traitement des options
while [ $# -gt 0 ]; do
    case "$1" in
        -d1|--optiond1)
            echo "Traitement avec l'option d1 pour le fichier $fichier"
            ;;
        -d2|--optiond2)
            echo "Traitement avec l'option d2 pour le fichier $fichier"
            ;;
        -l|--optionl)
            echo "Traitement avec l'option l pour le fichier $fichier"
            ;;
        -t|--optiont)
            echo "Traitement avec l'option t pour le fichier $fichier"
            ;;
        -s|--options)
            echo "Traitement avec l'option s pour le fichier $fichier"
            ;;
        *)
            echo "Option inconnue : $1"
            afficher_aide
            exit 1
            ;;
    esac
    shift  # Passer à l'option suivante
done
