# ESN12 - marimoutou_lab3
## Introduction


## Architecture du système

![lab3](https://github.com/ESN2024/marimoutou_lab3/assets/97475510/0bf8a712-ad1c-4987-96b6-7ebd02fd16e2)

Le système est composé de l'architecture basique vu en cours dans laquelle on retrouve :

* Un processeur Nios II
* Une mémoire RAM
* Une clock
* Un port JTAG

A cela on ajoute :

* Un PIO 4 bits pour le premier afficheur 7 segments.
* Un PIO 4 bits pour le deuxième afficheur 7 segments.
* Un PIO 4 bits pour le troisième afficheur 7 segments.
* Un PIO 4 bits pour le quatrième afficheur 7 segments.
* Un PIO 4 bits pour le cinquième afficheur 7 segments qiu affichera le signe.
* Un PIO 1 bits pour le bouton poussoir (KEY1).
* Un Timer 32 bits réglé sur une période de 500 ms.
* Un OpenCores I2C.
  
## Platform Designer
L'architecture sous Platform Designer (**QSYS**) est donc la suivante :
![qsys_lab3a](https://github.com/ESN2024/marimoutou_lab3/assets/97475510/8aede823-c162-4c98-b972-ea7923b36dc9)
![qsys_lab3b](https://github.com/ESN2024/marimoutou_lab3/assets/97475510/f812668e-f963-47e8-9d19-cd00a333582e)


### Quartus

Sous quartus on vient dans un premier temps récuperer le fichier `BCD7SEG.vhd` écrit lors du lab2 afin d'y rajouter une condition et d'afficher le signe **-**. On décrit ensuite notre fichier `toplevel.vhd` ou nous relions notre composants créer sou qsys à nos 7 segments.
On réaliser ensuite le pin assignements de nos 7 segments et de notre bouton poussoir dans le pin planner ou en modifiant le fichier *.qsf* . 
On réalise ensuite la compilation compléte de notre design et si il n'y a aucune erreur nous pouvons flasher l'architecture sur notre carte.

### Nios2 Flow
A partir du terminal Nios2 on vient alors créer notre **Makefile** et générer notre **bsp**.
Une fois cela fait, nous pouvons écrire nos scripts C, les compiler et les téléverser sur notre carte.

## Travail effectué
Nous avons ensuite créer un fichier `main.c` et  `main_timer.c` qui contiennent les fonctions qui nous permettent de lire et écrire dans les registres en I2C.
Ensuite nous avons permis l'affichage des données en UART avec une prise des données cadencé par le timer.
Enfin on calibre la carte pour avoir des valeurs plausibles.


### Les fonctions I2C


### Calibration

Nous allons calibrer la carte à l'aide des registre OFSX(0x1E), OFSY(0x1F),(OFSZ 0x20)

Calibrage X            |  Calibrage Y              | Calibrage Z
:-------------------------:|:-------------------------:|:-------------------------:
![IMG_4945](https://github.com/ESN2024/marimoutou_lab3/assets/97475510/6da766cf-8351-4b12-bbea-982b0d9a50b5)|![IMG_4943](https://github.com/ESN2024/marimoutou_lab3/assets/97475510/2947f5d2-5703-43b9-9727-bf8ab1df75b6)|![IMG_4944](https://github.com/ESN2024/marimoutou_lab3/assets/97475510/886e0c26-2672-4503-8e52-95e323692c57)


#### Demonstration




## Conclusion


