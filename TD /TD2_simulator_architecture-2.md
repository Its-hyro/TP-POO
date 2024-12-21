# TD 2 à 5 simulation équation de diffusion : résolution d'une équation de Laplace

Contexte et objectifs du TD : voir [Intro TD simulation équation de diffusion](TD2-5_intro.md)

# TD 2 Mise en place de l'infrastructure

## 2.1 Structure du simulateur

Le but de cette première partie est de créer le programme principal et l'architecture objet de notre simulateur.

Le simulateur sera constitué de deux classes principales :

- Une classe `Problem` permettant de résoudre nos équations,
- une classe `Equation`, contenant les paramètres de notre équation à résoudre.

Vous créerez des fichiers .cpp et .h pour chacune de ces classes.
La classe `Problem` contiendra un membre de type `Equation`.

Le programme principal se limitera pour l'instant à créer une instance de la classe `Problem` et à appeler sa méthode `solve`. Cette méthode lancera la méthode `compute` de l'`Equation` contenue dans le `Problem`.

Le programme sera configuré par un projet CMake, voir partie 2.3. Ce TD va vous servir à remplir le squelette de votre projet. Les méthodes numériques seront ajoutés dans le TD suivant, TD-3.

## 2.2 Méthode itérative et discrétisation en espace

Nous allons maintenant créer l'outillage pour itérer jusqu'à convergence sur la résolution en espace du problème. C'est dans la méthode `Problem::solve()` que vous allez mettre en place les itérations.
Vous stockerez comme donnée membre de la class Problem le nombre d'itérations et vous créerez une méthode qui permet d'indiquer si la résolution a convergé. Pour l'instant cette méthode ne prendra pas d'argument et retournera systématiquement vrai.

Pour chaque itération du problème vous appellerez le calcul de la résolution spatiale, qui sera contenu dans la méthode `Equation::compute()`;

Afin de permettre de la souplesse dans le choix de cette discrétisation (uniforme ou non par exemple), nous allons avoir recours au polymorphisme. Nous utiliserons une classe de base `IMesh` qui proposera des méthodes pour accéder aux informations de discrétisations nécessaires :

- position initiale, position finale
- nombre de points et pas d'espace.

Vous créerez cette classe de base ainsi qu'une classe dérivée `UniformMesh` qui implémentera les méthodes de la classe parent pour un pas d'espace constant. Vous donnerez à la construction de cette classe les valeurs `x_min`, `x_max`, `dx`. On choisira les valeurs :

- `x_min` = 0
- `x_max` = 1
- `dx` = 0.2

Une fois ces deux classes créées, vous stockerez un pointeur de `IMesh` dans `Problem` et vous le passerez en argument de la méthode `Equation::compute`. Vous l'utiliserez au sein de cette méthode `compute` pour boucler sur tous les points de l'espace. Pour l'instant, cette boucle en espace se contentera d'afficher la valeur de la position $x_i$ pour chaque point courant. L'exécution du programme devrait donc donner l'affichage suivant :

```shell
--- Solve problem ---
--- Iterative methode iteration : 1 ---
-- at x_i = 0
-- at x_i = 0.2
-- at x_i = 0.4
-- at x_i = 0.6
-- at x_i = 0.8
-- at x_i = 1
```

Pour créer notre `Problem` dans le programme principal, nous lui passerons à la construction un pointeur de `UniformMesh` qu'il stockera dans son pointeur de `IMesh`. Il sera responsable de la mémoire de ce pointeur, ce sera donc à lui d'appeler le `delete`. Vous veillerez à ce que le pointeur ne puisse pas être nul, en bloquant les constructions ou affectations par copie.

## 2.3 Compiler avec CMake

La compilation du projet utilisera un projet CMake qui créera une cible de type exécutable qui compilera votre programme principal en utilisant toutes les classes que vous aurez définies. Pour compiler votre projet depuis vos sources, il faudra simplement exécuter les commandes suivantes :

```shell
mkdir build
cd build
cmake .. 
make
```

Vous référer au TD1 pour cette partie.

## 2.4 Tester avec CTest

Grâce à la commande `add_test(test_name target_name)`, vous ajouterez votre exécutable à la base de test. Vous n'oublierez pas la commande `enable_testing` avant d'ajouter `add_test` dans le CMakeLists.txt.

Vous pouvez maintenant lancer votre exécutable via la commande `ctest` :

```shell
$ ctest
    Start 1: structure_test
1/1 Test #1: structure_test ...................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1
```

**Le livrable de ce TD doit être configurable via CMake, compilable et avoir une base de tests ok.**

### Bonus 1 : créez des tests unitaires avec GTest

Vous avez créé un test d'intégration (qui utilise tous les éléments de votre projet), il est également nécessaire de créer des test unitaires pour chaque brique (classe) du projet. GTest est un bon outil pour les réaliser.

- Vous créerez un nouvel exécutable de test, utilisant GTest (revoir TD1), qui vous permettra, à l'aide de la macro `TEST`, de tester vos différentes classes.
- Grâce à la commande CMake `gtest_discover_tests`, prenant en argument le nom de la target exécutable que vous venez de créer, ces tests seront lancés également via la commande `ctest`.

```c++
TEST(UnitaryTest,MeshTest){
  // construction et test d'une instance de UniformMesh
}

TEST(UnitaryTest,ProblemTest){
  // construction et test d'une instance de Problem
}

TEST(MainFunctionTest,EquationTest){
  // construction et test d'une instance de Equation
}
...
```

Pour le test de `Problem` vous pourrez tester le comportement de la classe si on lui fournit un pointeur nul pour le maillage. L'appel de `Problem::solve` ne devra pas planter. Vous pourrez de la même façon tester pour `Equation` le comportement lorsque la méthode `Equation::compute` est appelée avec un `IMesh*=nullptr` et faire en sorte que ce test passe.

### Bonus 2 : choix dynamique de la configuration de calcul

- Pour l'instant la configuration du problème était réalisée statiquement dans votre programme, à la création de la classe `UniformMesh`. Vous allez maintenant permettre à l'utilisateur de préciser les paramètres d'espace (`x_min`, `x_max` et pas d'espace `dx`) dans la ligne de commande. Votre programme prendra donc en paramètres trois arguments, que vous récupérerez grâce aux arguments `(int argc, char** argv)` de la fonction `main`. Vous pourrez utiliser `std::stof` pour convertir une chaîne de caractère en flottant.  
- Finalement afin de pouvoir choisir le type de maillage au runtime, vous prendrez en argument d'entrée supplémentaire le type de maillage (via une chaîne de caractère : "uniform" ou "non-uniform"). Vous utiliserez ensuite une fabrique, qui en prenant cette argument d'entrée sera capable de créer l'instance souhaitée de la classe `Problem`. Cette fabrique utilisera une `enum class` définissant les types de maillage possibles ```Uniform, NonUniform```. Pour pouvoir prévoir le cas ```NonUniform``` vous créerez une classe ```NonUniformMesh``` qui héritera de ```IMesh``` mais avec des méthodes vides. Votre fabrique assurera, grâce à un dictionnaire, la conversion entre la chaîne de caractère donnée en entrée et l'enum.

