# TD 2 à 5 simulation équation de diffusion : résolution d'une équation de Laplace

Contexte et objectifs du TD : voir [Intro TD simulation équation de diffusion](TD2-5_intro.md)

Nous proposons d'utiliser ce contexte comme fil rouge de nos séances de TD.

# TD 3 Mise en place de l'équation et du schéma numérique

Nous allons maintenant résoudre numériquement l'équation de Laplace :
$\Delta u = 0$ en calculant notre solution discrète sur notre discrétisation en espace créée au TD2, $(x_i)_{i=0..N_x}$ : $u_i\approx u(x_i)$. En revanche nous augmenterons le nombre de point en espace par rapport au premier TD, nous passerons à une discrétisation avec **100 points d'espace**.
Nous aurons trois étapes pour pouvoir réaliser cette résolution :

- créer une classe pour stocker la solution discrète $u_i$
- calculer une condition initiale et les conditions aux limites pour notre problème
- coder notre schéma numérique (une méthode de Jacobi pour commencer) dans notre classe `Equation`

Dans un premier temps le schéma numérique sera directement intégré dans la classe `Equation`.

Dans un deuxième temps, afin de rendre le code plus générique, nous pourrons le rendre indépendant.

## 3.1 Classe `Variable` pour stocker les $u_i$

Pour la discrétisation en espace, vous créerez une classe `Variable` qui vous permettra de stocker et d'accéder au tableau des valeurs de $u_i$. Vous utiliserez par exemple un `std::vector` pour stocker les valeurs dans cette classe. Cette classe nous permettra d'accéder à $u_i$ à partir de l'index $i$ : `u_i = variable[i]`. Cette classe aura besoin de stocker un pointeur vers `IMesh`.

- Le `std::vector` doit être dimensionné et initialisé dans le constructeur de `Variable`. Pour connaître la taille du maillage en $x$, vous ajouterez une méthode `IMesh::x_size()`.
- Afin de pouvoir écrire `u_i = variable[i]`, vous créerez un `operator[]` dans la classe qui prendra en argument l'index $i$ et  vous retournera une référence vers le $i^{ème}$ élément du tableau.

Pour la méthode itérative de résolution du solveur linéaire, nous n'avons besoin que de stocker les itérés $k$ et $k+1$, nous créerons pour cela deux variables `u_k` et `u_kp1` ; `u_kp1` étant recopié dans `u_k` en fin d'itération. Dans la méthode `solve` de votre `Problem`, vous instancierez ces deux variables `u_k` et `u_kp1`, instances de la classe `Variable`.

## 3.2 Calcul de la condition initiale et des conditions aux limites

Nous allons calculer la diffusion de la chaleur dans un milieu contenant initialement deux zones à des températures différentes. Vous initialiserez donc la première moitié du domaine à une température $T_1 = 30$ et la seconde à une température $T_2 = 15$.

Afin de calculer la condition initiale, vous créerez une méthode `compute_initial_condition` dans `Equation`. Cette méthode prendra en argument la classe `Variable` ainsi que le maillage `IMesh`. Vous aurez besoin de connaître la position $x_i$ pour chaque index $i$. Pour ce faire, vous ajouterez une nouvelle méthode dans `IMesh` qui retourne la valeur de $x_i$ en fonction de $i$ : `IMesh::x_i(int i)`.

Vous appellerez cette méthode juste avant votre boucle en temps, dans la méthode `solve` de votre `Problem`, en lui passant votre maillage et votre variable `u_k`.

Vous devrez également créer une méthode `compute_boundary_conditions` pour imposer les conditions aux limites dans votre variable `u_kp1`. Vous imposerez une condition de Dirichlet aux deux bords : $u(0) = T_1$ et $u(1) = T_2$.

## 3.3 Intégration du schéma numérique dans la classe `Equation`

Nous allons faire une première version de notre solveur itératif avec une méthode de Jacobi dont je vous rappelle la formule :
$$u_i^{k+1} = \frac{u_{i-1}^k + u_{i+1}^k}{2} $$

Cette résolution se fera dans la méthode `Equation::compute` où il faudra donc rajouter en argument les variables `u_k` et `u_kp1`.

Cette méthode calculera votre solution au temps $t_{n+1}$. Vous n'oublierez pas de remettre à jour `u_k` avec les valeurs de `u_kp1` à la fin de l'itération.

Il vous faudra également implémenter une méthode `has_converged` dans la classe `Problem` qui contrôlera la convergence de votre méthode itérative. Pour tester la convergence, dans un premier temps nous vérifierons simplement que la méthode converge et donc que l'écart entre `u_k` et `u_kp1` tend vers 0. Vous pourrez évaluer la norme infinie de la différence entre ces deux quantités :
$$||u^{k+1}-u^k||_\infty = \max_{i=0...N_x}( | u_i^{k+1}-u_i^k|)$$

Vous afficherez le nombre d'itérations nécessaire pour que cette norme soit en dessous d'un epsilon, que vous pouvez prendre à $1e-5$.

## 3.4 Bonus

### 3.4.1 Fonction d'initialisation en paramètre

Afin de pouvoir changer la fonction utilisée en condition initiale, nous allons maintenant la passer en paramètre de la méthode `Equation::compute_initial_condition`. Vous allez modifier votre initialisation : la boucle sur les points d'espace va maintenant appeler une fonction générique `initial_condition(x_i)` qui retournera la valeur de la température initiale pour le point d'espace considéré.

Pour ce faire, vous pourrez coder la fonction d'initialisation dans une $\lambda$-fonction que vous passerez dans un argument template de `compute_initial_condition`. Vous pourrez alors créer deux lambdas fonctions :

- celle qui correspondait à votre initialisation actuelle avec $T_1$ et $T_2$ pour chaque moitié du domaine ;
- une nouvelle fonction d’initialisation uniforme qui retournera une même température $T_3=\frac{T_1+T_2}{2}$ en tout point.

Vous pourrez constater l'effet sur le nombre d'itérations de cette seconde initialisation.

### 3.4.2 Séparation de l'équation et du solveur linéaire

Nous allons maintenant découpler le solveur linéaire de l'`Equation` afin de pouvoir tester plusieurs solveurs itératifs pour la même équation. Pour cela nous allons créer une nouvelle méthode `compute_for_solver` qui prendra en paramètre template le solveur linéaire utilisé.

Il faudra donc maintenant créer une classe `Jacobi` pour définir notre solveur itératif Jacobi. Cette classe n'aura pas besoin de contenir de données, elle peut simplement avoir une méthode statique `compute_iteration` qui prendrait en argument le maillage `IMesh*` ainsi que les variables `u_k` et `u_kp1`. La méthode `Equation::compute_for_solver` sera template et prendra en argument template le type du solveur linéaire :

```c++
m_equation.compute_for_solver<Jacobi>(u_k,u_kp1);
```

### 3.4.3 Ajout d'un solveur de Gauss-Seidel

Nous allons maintenant pouvoir ajouter une nouveau solveur itératif de Gauss-Seidelsans modifier la classe `Equation`. Il vous faudra ajouter une classe `GaussSeidel`, sur le même modèle que la classe `Jacobi`. La méthode `compute_iteration` de cette nouvelle classe devra permettre de calculer l'itération de Gauss-Seidel dont nous rappelons la formule :

$$u_i^{k+1} = \frac{u_{i-1}^{k+1} + u_{i+1}^k}{2} $$

### 3.4.4 Calculer le résidu pour vérifier la solution obtenue

Dans la partie 3.3, nous avons uniquement vérifié que la méthode convergeait, sans vérifier qu'elle convergeait vers une solution du problème. Pour ce faire, nous allons maintenant calculer le résidu de notre solveur $R = A U^{k+1}$ où $U^{k+1}$ est la solution à convergence. Si $U^{k+1}$ est bien solution de notre équation alors $R\approx 0$, cf. [Intro des TDs](TD2-5_intro.md). Vous vérifierez que la norme infinie du résidu est inférieur à votre epsilon.

### 3.4.5 Rendre le code plus robuste via les concepts

Il est enfin possible de rendre votre code plus robuste en vérifiant, là où vous utilisez des paramètres template, que les objets donnés en paramètre template remplissent le bon contrat, grâce aux **`concept`** introduit en C++20. Vous pouvez vérifier que la classe donnée comme solveur linéaire de la méthode `compute_for_solver` possède bien une méthode `compute_iteration` et que la fonction passée en argument de la méthode `Equation::compute_initial_condition` possède bien un `operator()`. Pour réaliser cet item il vous faudra un compilateur récent (GCC >= 10 ; Clang >= 10). Voir sur  [cpp reference](https://en.cppreference.com/w/cpp/concepts).
