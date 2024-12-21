#!/usr/bin/gnuplot

# Configuration générale
set terminal png size 1200,800 enhanced font 'Arial,12'
set grid lw 1
set key right top box

# Définition des styles de lignes avec des couleurs plus distinctes
set style line 1 lc rgb '#000000' lt 1 lw 3   # noir pour solution exacte
set style line 2 lc rgb '#FF0000' lt 1 lw 3   # rouge vif pour Jacobi
set style line 3 lc rgb '#00FF00' lt 1 lw 3   # vert vif pour Gauss-Seidel
set style line 4 lc rgb '#0000FF' lt 1 lw 3   # bleu vif pour condition initiale
set style line 5 lc rgb '#FF00FF' lt 1 lw 3   # magenta pour iter 100
set style line 6 lc rgb '#00FFFF' lt 1 lw 3   # cyan pour iter 500

# Création du répertoire results s'il n'existe pas
system('mkdir -p results')

# Configuration des bornes fixes pour tous les graphiques
set xrange [0:1]
set yrange [10:35]
set xtics 0,0.1,1
set ytics 10,5,35

# Graphique de comparaison des solutions
set output 'results/solutions_comparison.png'
set title 'Comparaison des solutions numeriques avec la solution exacte' font 'Arial,14'
set xlabel 'Position x' font 'Arial,12'
set ylabel 'Temperature u(x)' font 'Arial,12'
set label 1 "T1 = 30 C" at 0.02,30 font 'Arial,10'
set label 2 "T2 = 15 C" at 0.85,15 font 'Arial,10'
plot 'build/initial_condition.dat' using 1:2 with lines ls 4 title 'Condition initiale', \
     'build/exact_solution.dat' using 1:2 with lines ls 1 title 'Solution exacte', \
     'build/jacobi_final.dat' using 1:2 with lines ls 2 title 'Solution Jacobi', \
     'build/gauss_final.dat' using 1:2 with lines ls 3 title 'Solution Gauss-Seidel'

# Graphique de l'evolution de Jacobi
unset label 1
unset label 2
set output 'results/jacobi_evolution.png'
set title 'Evolution de la methode de Jacobi' font 'Arial,14'
set xlabel 'Position x' font 'Arial,12'
set ylabel 'Temperature u(x)' font 'Arial,12'
set label 1 "Convergence progressive" at 0.1,25 font 'Arial,10'
plot 'build/initial_condition.dat' using 1:2 with lines ls 4 title 'Condition initiale (t=0)', \
     'build/exact_solution.dat' using 1:2 with lines ls 1 title 'Solution exacte', \
     'build/jacobi_iter_100.dat' using 1:2 with lines ls 5 title 'Iteration 100', \
     'build/jacobi_iter_500.dat' using 1:2 with lines ls 6 title 'Iteration 500', \
     'build/jacobi_final.dat' using 1:2 with lines ls 2 title 'Solution finale'

# Graphique de l'evolution de Gauss-Seidel
unset label 1
set output 'results/gauss_evolution.png'
set title 'Evolution de la methode de Gauss-Seidel' font 'Arial,14'
set xlabel 'Position x' font 'Arial,12'
set ylabel 'Temperature u(x)' font 'Arial,12'
set label 1 "Convergence plus rapide" at 0.1,25 font 'Arial,10'
plot 'build/initial_condition.dat' using 1:2 with lines ls 4 title 'Condition initiale (t=0)', \
     'build/exact_solution.dat' using 1:2 with lines ls 1 title 'Solution exacte', \
     'build/gauss_iter_100.dat' using 1:2 with lines ls 5 title 'Iteration 100', \
     'build/gauss_iter_500.dat' using 1:2 with lines ls 6 title 'Iteration 500', \
     'build/gauss_final.dat' using 1:2 with lines ls 3 title 'Solution finale'

# Graphique de comparaison des vitesses de convergence
unset label 1
set output 'results/convergence_comparison.png'
set title 'Comparaison des vitesses de convergence' font 'Arial,14'
set xlabel 'Position x' font 'Arial,12'
set ylabel 'Temperature u(x)' font 'Arial,12'
unset logscale y
set yrange [10:35]
set xrange [0:1]

plot 'build/initial_condition.dat' using 1:2 with lines ls 4 title 'Condition initiale', \
     'build/exact_solution.dat' using 1:2 with lines ls 1 title 'Solution exacte', \
     'build/jacobi_iter_100.dat' using 1:2 with lines ls 5 dt 2 title 'Jacobi (100)', \
     'build/gauss_iter_100.dat' using 1:2 with lines ls 5 dt 3 title 'Gauss-Seidel (100)', \
     'build/jacobi_iter_500.dat' using 1:2 with lines ls 6 dt 2 title 'Jacobi (500)', \
     'build/gauss_iter_500.dat' using 1:2 with lines ls 6 dt 3 title 'Gauss-Seidel (500)'