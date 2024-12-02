#!/usr/bin/gnuplot

# Configuration générale
set terminal png size 1200,800 enhanced font 'Arial,12'
set grid lw 1
set key left top box
set style line 1 lc rgb '#0060ad' lt 1 lw 2   # bleu pour solution exacte
set style line 2 lc rgb '#dd181f' lt 1 lw 2   # rouge pour Jacobi
set style line 3 lc rgb '#00A000' lt 1 lw 2   # vert pour Gauss-Seidel
set style line 4 lc rgb '#9400D3' lt 1 lw 2   # violet pour condition initiale

# Création du répertoire results s'il n'existe pas
system('mkdir -p ../results')

# Graphique de comparaison des solutions
set output '../results/solutions_comparison.png'
set title 'Comparaison des solutions numériques avec la solution exacte' font 'Arial,14'
set xlabel 'Position x' font 'Arial,12'
set ylabel 'Température u(x)' font 'Arial,12'
plot 'exact_solution.dat' using 1:2 with lines ls 1 title 'Solution exacte', \
     'jacobi_final.dat' using 1:2 with lines ls 2 title 'Solution Jacobi', \
     'gauss_final.dat' using 1:2 with lines ls 3 title 'Solution Gauss-Seidel'

# Graphique de l'évolution de Jacobi
set output '../results/jacobi_evolution.png'
set title 'Évolution de la méthode de Jacobi' font 'Arial,14'
set xlabel 'Position x' font 'Arial,12'
set ylabel 'Température u(x)' font 'Arial,12'
plot 'initial_condition.dat' using 1:2 with lines ls 4 title 'Condition initiale (t=0)', \
     'jacobi_iter_100.dat' using 1:2 with lines ls 2 dt 2 title 'Itération 100', \
     'jacobi_iter_500.dat' using 1:2 with lines ls 2 dt 3 title 'Itération 500', \
     'jacobi_final.dat' using 1:2 with lines ls 2 title 'Solution finale', \
     'exact_solution.dat' using 1:2 with lines ls 1 dt 4 title 'Solution exacte'

# Graphique de l'évolution de Gauss-Seidel
set output '../results/gauss_evolution.png'
set title 'Évolution de la méthode de Gauss-Seidel' font 'Arial,14'
set xlabel 'Position x' font 'Arial,12'
set ylabel 'Température u(x)' font 'Arial,12'
plot 'initial_condition.dat' using 1:2 with lines ls 4 title 'Condition initiale (t=0)', \
     'gauss_iter_100.dat' using 1:2 with lines ls 3 dt 2 title 'Itération 100', \
     'gauss_iter_500.dat' using 1:2 with lines ls 3 dt 3 title 'Itération 500', \
     'gauss_final.dat' using 1:2 with lines ls 3 title 'Solution finale', \
     'exact_solution.dat' using 1:2 with lines ls 1 dt 4 title 'Solution exacte' 