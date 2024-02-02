#!/bin/bash

tmp="temp"
img="images"
dem="demo"
dat="data"
prc="progc"





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

if [ ! -d "$dem" ]; then
  mkdir "$dem"
fi


if [ ! -d "$dat" ]; then
  mkdir "$dat"
fi


if [ ! -d "$prc" ]; then
  mkdir "$prc"
fi


chmod -R u=rwx $tmp
chmod -R u=rwx $img
chmod -R u=rwx $dem
chmod -R u=rwx $dat
chmod -R u=rwx $prc

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
            source TraitementD1.sh
            ;;
        -d2|--optiond2)
            echo "Traitement avec l'option d2 pour le fichier $fichier"
            source TraitementD2.sh
            ;;
        -l|--optionl)
            echo "Traitement avec l'option l pour le fichier $fichier"
            source TraitementL.sh
            ;;
        -t|--optiont)
            echo "Traitement avec l'option t pour le fichier $fichier"
            source TraitementT.sh
            ;;
        -s|--options)
            echo "Traitement avec l'option s pour le fichier $fichier"
            source TraitementS.sh
            ;;
        *)
            echo "Option inconnue : $1"
            afficher_aide
            exit 1
            ;;
    esac
    shift  # Passer à l'option suivante
done
