# TP-POO - Master 1 CHPS

Ce projet a été développé et testé sur macOS (Apple Silicon).

## Prérequis

Avant de compiler le programme, assurez-vous d'avoir installé les éléments suivants :

- CMake (version 3.10 minimum)
- Un compilateur C++ compatible C++17
- Make
- VSCode (recommandé)

### Extensions VSCode recommandées

- C/C++ Extension Pack
- CMake Tools
- CMake Language Support

## Compilation du programme

1. Ouvrez un terminal et placez-vous dans le répertoire du projet
2. Créez un dossier build et compilez le projet :

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j
```

## Exécution du programme

Une fois la compilation terminée, vous pouvez exécuter le programme depuis le dossier `build` :

```bash
./Simulator
./UnitTests
```


## Notes

- Si vous rencontrez des problèmes de compilation, vérifiez que vous avez bien installé tous les prérequis
- Le programme a été développé et testé sur macOS, des adaptations peuvent être nécessaires pour d'autres systèmes d'exploitation
