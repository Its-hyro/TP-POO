# TD simulation équation de diffusion

les équations de diffusion sont omniprésentes dans tous les domaines de la simulation numérique. Elles permettent par exemple de simuler les problèmes thermiques, les problèmes d'écoulement en milieu poreux dispersion ou encore d'autres problèmes de mécaniques des fluides. Elles sont donc au coeur de très nombreux travaux de R&D passés ou actuels.

![Temperature evolution](Heat_eqn.gif)

*Evolution de la température dans une plaque métallique (source Wikipédia)*

## Equation de la chaleur

Dans le cadre de ce TP, nous focaliserons sur une équation de la chaleur de la forme :
$$ \partial_t u - \alpha \Delta u = 0$$

Nous allons nous restreindre au cas stationnaire, et donc résoudre une équation de Laplace :
$$ \Delta u = 0$$

Pour simplifier les développement, nous nous restreindrons à une résolution en une dimension de l'espace, sur $\Omega=[0,1]$.
Pour discrétiser cette équation, nous introduisons une grille 1-D, de pas éventuellement variable $\Delta x(i)=\Delta x_i$. Pour résoudre cette équation, nous allons discrétiser le Laplacien avec une une méthode des différences finies centrées :
$$\partial_{x^2} u(x_i) \approx  \frac{u_{i-1} - 2 u_i + u_{i+1}}{\Delta x_i^2}  $$

$$u_i = \frac{u_{i-1} + u_{i+1}}{2} $$

ou encore
$$2u_i-u_{i-1} - u_{i+1} = 0$$

Avec $u_i = u(x_i)$ solution discrète du problème au point $x_i$. Nous avons donc à résoudre un système linéaire de la forme :

$$AU = 0$$

avec U le vecteur des solutions $U=(u_i)_{i=0..N_x}$ et A la matrice tridiagonale :

$$ A = \begin{bmatrix} 2 &-1 &0 &...& &&0\\
 -1 & 2& -1& 0& ... && 0 \\
 0& -1 & 2& -1& 0& ... &0 \\
 & & & ...& & & \\
 0&... & & 0& -1& 2 &-1 \\
 0&... & & &0 & -1 &2\end{bmatrix}$$

Lors du TP, nous résoudrons ce système par des méthodes itératives, de Jacobi dans un premier temps, puis de Gauss-Seidel. Si l'on introduit $k$ comme index d'itération de la méthode, on peut écrire la solution à l'itération $k+1$ au point $x_i$ :
- pour la méthode Jacobi, en fonction de la solution à l'itéré $k$ uniquement :
$$u_i^{k+1} = \frac{u_{i-1}^k + u_{i+1}^k}{2} $$
- pour la méthode de Gauss-Seidel, en fonction des itérés $k$ et $k+1$ :
$$u_i^{k+1} = \frac{u_{i-1}^{k+1} + u_{i+1}^k}{2} $$

## Objectifs du TP

L'objectif du TP n'est pas la seule construction d'un simulateur de cette équation de Laplace. Il s'agit de mettre en oeuvre les concepts orientés objets vus en cours dans le contexte d'une application calcul scientifique.
Vous serez donc guidés, au fil des séances 2 à 5, pour construire l'architecture de cette application orienté objet. Nous suivrons les étapes suivantes :

- TD2 : création de l'architecture du simulateur (classes de base) ;
- TD3 : implémentation de la discrétisation d'une équation de Laplace 1D ;
- TD4 : validation des résultats et parallélisation ;
- TD5 : extension du parallélisme pour la portabilité des performances.
