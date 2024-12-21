# TD 2 à 5 simulation équation de diffusion : résolution d'une équation de Laplace

Contexte et objectifs du TD : voir [Intro TD simulation équation de diffusion](TD2-5_intro.md)

# TD 4 Validation des résultats

## 4.1 Calcul de la solution exacte

L'équation de Laplace que nous étudions dans ces TDs, pour rappel :

$\Delta u = 0$,

admet une solution exacte sur $[0,1]$ pour les conditions initiales et aux limites données. Nous allons donc pouvoir l'utiliser pour vérifier nos résultats.
Pour calculer la solution exacte, vous créerez une nouvelle méthode `Equation::compute_exact_solution`. Cette fonction pourra prendre en argument un objet `Variable` et le maillage `IMesh*`. Elle devra calculer la solution exacte en chaque point d'espace du maillage. Pour les conditions initiales et aux limites que nous avons données, et pour $x$ dans $[0,1]$ la solution exacte est de la forme :

$u_{exacte}(x) = (T_2 - T_1) * x + T_1$,

celle-ci étant simplement une droite définie par les conditions aux limites sur $[0,1]$ :

$u_{exacte}(0) = T_1, u_{exacte}(1) = T_2$,

Vous pourrez appeler cette fonction au sein de votre méthode `Problem::solve` avant ou après votre méthode itérative. Vous stockerez la solution exacte dans une nouvelle variable `u_ref`.

## 4.2 Validation : affichage des résultats

Tout d'abord afin de pouvoir vous y retrouver lors de l'affichage des variables, vous ajouterez un champ `m_name` dans la classe `Variable`.
Ajoutez à votre classe `Variable` une méthode `print` qui vous permette d'afficher à l'écran les valeurs de votre variable ainsi que son nom. Vous appellerez cette méthode à la fin de de votre méthode itérative dans `Problem::solve` pour les variables `u_kp1` et `u_ref`. Les valeurs de `u_kp1` doivent converger vers celles de `u_ref`.

Afin de pouvoir tracer votre solution et la solution exacte sur un graphique (avec gnuplot par exemple), vous ajouterez dans la méthode `print` un export dans un fichier, en utilisant par exemple un `std::ofstream`. Vous utiliserez le nom de la variable pour créer le nom du fichier : *Variable_u_kp1.data*, *Variable_u_ref.data*...

## 4.3 Validation : comparaison des résultats

Nous rappelons les valeurs des paramètres du maillage :

- `x_min` = 0
- `x_max` = 1
- `dx` = 0.01

L'objectif est maintenant de tracer sur une même courbe l'évolution de votre solution `u_kp1` obtenue avec la méthode de Jacobi et celle de la solution exacte `u_ref`. Vous exporterez dans un fichier la condition initiale (en exportant `u_k` avant de démarrer les calculs) ainsi que `u_kp1` et `u_ref` en fin de calcul. Vous tracerez, avec gnuplot par exemple, la courbe d'évolution de ces trois variables en fonction de l'espace, pour obtenir une figure du type de celle ci-dessous:
![solution Jacobi](Jacobi.png)

## 4.4 Bonus

### 4.4.1 Export de la méthode Gauss-Seidel

Si vous avez ajouté la méthode de Gauss-Seidel (bonus du TD3), vous allez maintenant pouvoir l'ajouter à la courbe pour vérifier que vous obtenez bien toujours une solution convergée vers la solution exacte. Vous calculerez dans deux nouvelles variables `u_k_gs` et `u_kp1_gs` la solution pour ce nouveau solveur et vous l'exporterez dans un fichier en fin de calcul afin de pouvoir l'ajouter à la courbe de comparaison. Vous devriez obtenir une figure identique à celle de la méthode Jacobi :
![solution Gauss-Seidel](Gauss-Seidel.png)

### 4.4.2 Utilisation des algorithmes de la STL

Afin de prévoir la future parallélisation de votre code, il serait intéressant d'utiliser au maximum des algorithmes de la STL à chaque fois que cela est possible. En effet la parallélisation de ces algorithmes est assez directe. Par exemple un algorithme de type :

```c++
#include <algorithm>
int main() {
    std::for_each(container.begin(),container.end(),[](auto current_element) {
      // your function
    });
}
```

se parallélise simplement avec la notion de contexte d'exécution :

```c++
#include <execution>
#include <algorithm>
int main() {
    std::for_each(std::execution::par,container.begin(),container.end(),[](auto current_element) {
      // your function
    });
}
```

Vous pourrez introduire des algorithmes STL dans les éléments suivants de votre code :

- méthode `Equation::compute_initial_solution()` ;
- méthode `Equation::compute_exact_solution()`, où vous pourrez alors écrire votre fonction exacte sous la forme d'une $\lambda$-fonction, comme vous l'aviez fait pour la solution initiale ;
- méthode `Equation::has_converged()`, éventuellement pour les différentes versions que vous avez pu faire : norme de la différence entre `u_k` et `u_kp1` et norme du résidu ;
- méthode `Equation::compute()`, pour la méthode Jacobi. Vous pouvez mettre en place un algorithme STL pour la boucle de la méthode Gauss-Seidel mais il ne sera pas parallélisable ;
- méthode `Variable::print()`.

Globalement toutes les boucles sur le maillage doivent être remplacées par un algorithme de la STL.

Vous vérifierez la non régression de vos résultats après ce portage, par exemple en retraçant les courbes demandées en partie 4.3. S'il vous reste du temps, vous pourrez ajouter des tests de non régression qui comparent les résultats avec une boucle et avec un algorithme STL.

Ces algorithmes pourront être parallélisés lors du prochain TD sur la performance.

### 4.4.3 Import des résultats dans Paraview

Dans cette dernière partie, vous allez étoffer votre export fichier pour ajouter l'écriture d'un fichier de résultat lisible dans Paraview, au format VTK. Vous pourrez utiliser le data set VTK `STRUCTURED_GRID` et exporter en CELL_DATA vos variables `u_kp1` et `u_ref`, ainsi que la condition initiale.
Cela devrait vous donner une image de ce type :
![Import Paraview](Import_paraview.png)
