# Tournoi du dilemme du prisonnier itéré

Projet de POA (Master Imagine, Université de Montpellier), réalisé seul.

Le programme simule un tournoi d'Axelrod : des stratégies s'affrontent dans le dilemme du
prisonnier itéré, et on observe laquelle obtient le meilleur score total. Le moteur du tournoi
est écrit en C++.

À chaque tour, les deux joueurs choisissent C (coopérer) ou D (trahir) en même temps. Les gains
sont ceux du cours :

| | j joue C | j joue D |
|---|---|---|
| **i joue C** | 3, 3 | 0, 5 |
| **i joue D** | 5, 0 | 2, 2 |

## Compilation

```
make          # compile et crée bin/tp
make clean    # supprime les fichiers compilés
```

## Utilisation

```
bin/tp <s>              les deux joueurs utilisent la stratégie s
bin/tp <sA> <sB>        joueur A contre joueur B
bin/tp all              tournoi tous contre tous (200 tours par partie)
bin/tp all inconnu      tous contre tous avec horizon inconnu
bin/tp all bruit        tous contre tous avec bruit
```

Les stratégies sont désignées par leur numéro :

| Numéro | Stratégie |
|---|---|
| 0 | ALL_D |
| 1 | RANDOM |
| 2 | TIT_FOR_TAT |
| 3 | TESTER |
| 4 | JOSS |
| 5 | TIT_FOR_TWO_TATS |
| 6 | GRUDGER |
| 7 | NONE (une stratégie tirée au hasard) |

Exemples :

```
bin/tp 4          # JOSS contre JOSS
bin/tp 2 3        # TIT_FOR_TAT contre TESTER
bin/tp all        # tournoi complet
```

Pour chaque confrontation, le programme affiche les points de chaque partie. À la fin d'un
tournoi `all`, il affiche le classement par total de points, du plus grand au plus petit.

## Paramètres

Les paramètres se règlent par des constantes au début de `src/main.cpp` :

- `TOURS` : nombre de parties par confrontation (5)
- `ROUNDS` : nombre de tours par partie (200)
- `CONTINUE_PROBABILITY` : probabilité de continuer après chaque tour en mode `inconnu` (0,995)
- `NOISE_PROBABILITY` : probabilité d'inverser un coup en mode `bruit` (0,05)
- `SEED` : graine du générateur pseudo-aléatoire (42), pour obtenir les mêmes résultats à
  chaque exécution

## Les stratégies

- **ALL_D** : joue toujours D.
- **RANDOM** : joue C ou D au hasard, une chance sur deux.
- **TIT_FOR_TAT** : joue C au premier tour, puis rejoue le coup de l'adversaire au tour précédent.
- **TESTER** : joue D au premier tour. Si l'adversaire riposte, joue TIT_FOR_TAT ; sinon répète
  C, C, D.
- **JOSS** : joue TIT_FOR_TAT, mais remplace C par D une fois sur dix.
- **TIT_FOR_TWO_TATS** : joue C, sauf si l'adversaire a joué D aux deux tours précédents.
- **GRUDGER** : joue C jusqu'à ce que l'adversaire joue D une fois, puis joue D jusqu'à la fin
  de la partie.

## Organisation du code

```
src/main.cpp              lecture des arguments, tournoi tous contre tous
src/core/tournament.*     moteur du tournoi (parties, scores, horizon inconnu, bruit)
src/core/strategy.*       les stratégies
src/shared/player.h       joueur, coups (C / D) et historique
src/shared/strategyName.h liste des stratégies
```