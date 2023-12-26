# Spécifier le terminal de sortie
set terminal png

# Spécifier le nom du fichier de sortie
set output "histogramme_horizontal.png"

# Style de remplissage des barres
set style fill solid

# Largeur des barres
set boxwidth 0.5

# Titre du graphique
set title "Top 10 des conducteurs avec le plus de trajets"

# Étiquettes des axes
set xlabel "Noms des Conducteurs"
set y2label "Nombres de Trajets"
set yrange [ 0 : * ]
set y2range [ 0 : * ]
set y2tics
set ytics rotate by 90 right
set xtics rotate by 90 right

# Tracer l'histogramme horizontal à partir d'un fichier de données
plot "result.txt" using 1:xtic(2) with histograms notitle