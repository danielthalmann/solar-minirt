# Solar minirt

Solar minirt est un raystracer réalisé dans le cadre de l'école 42 Lausanne
, débuté au mois de mai 2022. 

C'est une collaboration entre Tanguy Rossel et Daniel Thalmann.

Le projet contient trois librairies utilitaires qui sont disponibles avec leurs
sources :

* MiniLibX : librairie graphique permettant l'affichage d'une image dans une fenêtre
* glmath : librairie mathématique utilisé pour les calculs de l'image.
* libft : librairie de fonction standard C

## Prérequis

MiniLibX pour  Linux requière les librairie xorg, x11 and zlib.

installation pour Ubuntu :

```bash
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```

## Installation

Pour installer solar-minirt, il faut clôner le présent dépôt git dans un répertoire
de son choix. 

Puis, entrée dans la ligne de commande :

```bash
make
```
Pour executer solar-minirt tappez dans la ligne de commande :

```bash
./minirt scenes/plane.rt
```

Le première paramètre indique le nom du fichier qui sera utilisé pour indiquer
les éléments à dessiner dans le raytracer.
