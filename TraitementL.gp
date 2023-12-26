# Spécifier le terminal de sortie
set terminal png

# Spécifier le nom du fichier de sortie
set output "histogramme_L.png"

# Style de remplissage des barres
set style fill solid

# Largeur des barres
set boxwidth 0.5

# Titre du graphique
set title "Les 10 trajets les plus longs"

# Étiquettes des axes
set xlabel "Route ID"
set ylabel "Distances (km)"

# Tracer l'histogramme horizontal à partir d'un fichier de données
plot "result_L2.txt" using 1:xtic(2) with histograms notitle