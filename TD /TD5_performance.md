# TD 2 à 5 simulation équation de transport : résolution d'une équation de Laplace

Contexte et objectifs du TD : voir [Intro TD simulation équation de diffusion](TD2-5_intro.md)

# TD 5 Optimisation

## 5.1 Analyse de performances

Afin de mesurer les performances de votre code, vous construirez une classe `Timer` qui grâce à des méthodes `start`, `stop` et `print` vous permettra de calculer le temps passé entre les appels à `start` et `stop` et de l'afficher avec la méthode `print`. A l'intérieur de cette classe vous utiliserez les outils du standard `std::chrono` pour effectuer ces mesures. Vous pourrez par exemple stocker dans la classe deux `time_point`, l'un affecté lors du `start` et l'autre lors du `stop`.
Vous créerez plusieurs `Timer`, l'un pour calculer le temps total du calcul et l'autre pour calculer celui de chaque méthode itérative que vous avez implémentée. Vous afficherez ces résultats à l'écran en millisecondes. Ces mesures doivent être faites en faisant tourner le code en mode **Release**. Vous pourrez laisser CMake choisir les options de compilation adaptées, il vous suffira alors de le lancer avec l'option : ```cmake -DCMAKE_BUILD_TYPE=Release```. Il vous faudra également désactiver tous les affichages à l'écran que vous pouviez avoir mis pour le debug et qui sont très consommateurs de temps CPU. Afin de pouvoir faire des mesures significatives, vous réaliserez un calcul pour une discrétisation fine, un $\delta x = 10^-6$.

## 5.2 Amélioration des performances

Vous devriez constater que la majeure partie du temps de calcul est consommée dans la méthode itérative. Afin de rendre plus visible l'amélioration des performances, nous allons **imposer le nombre d'itérations maximal à une valeur de 100**. Nous sommes bien loin de la convergence, mais cela permettra de mettre en évidence le gain de performance apporté par les deux niveaux de parallélisation.

Un premier travail d'optimisation à grain grossier pourra consister à exécuter dans des threads distincts les différents noyaux de calcul de votre applications. Ainsi vous pourrez isoler dans des threads différents les deux méthodes itératives (Jacobi et Gauss-Seidel) que vous avez implémentées pour résoudre le système. Afin de pouvoir comparer vos performances séquentielles et parallèles vous créerez une nouvelle méthode `Problem::solve_parallel()` dans laquelle vous recopierez le contenu de `Problem::solve()`. C'est dans cette nouvelle méthode que vous ferez la parallélisation.

### 5.2.1 Utilisation de `std::thread`

Depuis C++11, il est assez facile d'introduire des processus légers (threads). En effet vous avez accès à la classe `thread` depuis le header `<thread>`. Cette classe prend à la construction une $\lambda$-fonction qui sera exécutée par le processus. Ainsi, l'exemple de code suivant exécutera en parallèle deux threads :

```c++
#include <thread>

int main(){
    std::thread first_thread([](){
        //  do something : compute exact solution
    });
    std::thread second_thread([](){
        //  do something : compute approximate solution
    });
    first_thread.join();
    second_thread.join();
    return 0;
}
```

Pour pouvoir exécuter un programme avec des `std::thread` il faudra embarquer la bibliothèque de threads de votre système d'exploitation à l'édition des liens. CMake est là pour vous aider dans ce travail : il faudra ajouter les lignes suivantes dans votre CMakeLists.txt, en remplaçant `MyExe` par le nom de la target CMake associée à votre exécutable :

```cmake
find_package(Threads)
target_link_libraries(MyExe Threads::Threads)
```

Comme vous le voyez dans l'exemple, les opérations effectuées dans le thread, sont passées sous la forme d'une $\lambda$-fonction. Vous pouvez accéder à la mémoire du thread principal en capturant des variables dans les $\lambda$ mais attention aux accès concurrents. Dans notre exemple, c'est surtout le calcul de la méthode itérative qui va consommer du CPU, vous pourrez donc séparer dans des threads différents :

- le calcul de la solution avec Jacobi ;
- le calcul de la solution avec Gauss-Seidel.

Vous comparerez ensuite les temps de calcul au temps séquentiel, toujours en mode Release.

## 5.3 Bonus

### 5.3.1 **Parallélisation des boucles** de calcul grâce aux algorithmes de la STL

Nous allons maintenant réaliser un parallélisme à grain plus fin, au niveau des boucles de calcul.
Le plus simple pour paralléliser nos boucles tout en restant sur du C++ standard sera d'utiliser les algorithmes parallèles de la STL. En effet dans la partie 4.4.2 du TD4, vous avez introduit des algorithmes de la STL dans la quasi-totalité des boucles sur le maillage. Nous allons pouvoir introduire assez simplement du parallélisme.
Dans cette partie, nous lancerons **uniquement la méthode de Jacobi**, la méthode de Gauss-Seidel n'étant pas parallélisable simplement, le calcul du point $i$ nécessitant la connaissance du point $i-1$.

#### Préparation

Tout d'abord il faut un compilateur suffisamment moderne (GCC >= 9.1). Ensuite pour pouvoir faire fonctionner les algorithmes parallèles de la STL, il est nécessaire d'embarquer Intel TBB à l'édition des liens. Pour l'installer sur votre machine Linux, vous pouvez le faire via le paquet :

```shell
sudo apt install libtbb-dev
```

Il faudra donc modifier votre CMakeLists.txt, comme d'habitude en remplaçant `MyExe` par le nom de la target CMake associée à votre exécutable :

```cmake
find_package(Threads)
find_package(TBB)
target_link_libraries(MyExe Threads::Threads TBB::tbb)
```

#### Mise en oeuvre

La parallélisation de votre algorithme se fera maintenant très simplement, en ajoutant en paramètre l'environnement d'exécution :

```c++
#include <execution>
#include <algorithm>
int main() {
    std::for_each(std::execution::par,times.begin(),times.end(),[](auto time) {
      // your function
    });
}
```

Vous pourrez regarder sur https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag_t le sens des différentes valeurs dans std::execution pour choisir la plus adaptée. Vous pourrez comparer avec le séquentiel grâce à la valeur `std::execution::seq`.

Vous utiliserez cette syntaxe dans la boucle de calcul de l'itéré de Jacobi, qui représente le point chaud en terme de performance dans votre application.

### 5.3.2 Remplacer `std::thread` par `std::async`

L'utilisation de `std::async` peut être assez intéressante. En effet cette fonction va créer le thread pour vous, encapsuler son éventuel résultat dans une classe `std::future`, et vous permettre de choisir entre une exécution séquentielle ou parallèle. Si nous reprenons l'exemple donné en 5.2.1 et que nous le réécrivons à base d'`async` cela donnera :

```c++
#include <future>

int main(){
    std::future first_task = std::async(std::launch::async,[](){
        //  do something : compute exact solution
    });
    std::future second_task = std::async(std::launch::async,[](){
        //  do something : compute approximate solution
    });
    first_task.wait();
    second_task.wait();
    return 0;
}
```

Il est également possible de mettre comme premier argument `std::launch::deferred` ; il n'y aura alors pas de création de thread et la tâche sera exécutée séquentiellement à l'appel du `wait()`. Vous pourrez alors facilement comparer les performances en séquentiel ou parallèle. Vous pourrez aussi comparer les performances de la solution à base d'`async` avec celles de la solution à base de `thread`.
