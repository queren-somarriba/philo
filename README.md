# Philosopher

Philosopher est un projet en C inspiré du problème classique des philosophes, mettant en œuvre la gestion des threads et des ressources partagées à l'aide des mutex.

## Installation

Pour compiler `philosopher`, utilisez la commande suivante :

```sh
gcc -Wall -Wextra -Werror philosopher.c utils/*.c -lpthread -o philosopher
```

## Utilisation

La syntaxe de `philosopher` est la suivante :

```sh
./philosopher number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` : Nombre de philosophes autour de la table.
- `time_to_die` : Temps (en ms) avant qu'un philosophe meure s'il ne mange pas.
- `time_to_eat` : Temps (en ms) nécessaire pour manger.
- `time_to_sleep` : Temps (en ms) que le philosophe passe à dormir.
- `number_of_times_each_philosopher_must_eat` *(optionnel)* : Nombre minimum de repas qu'un philosophe doit consommer avant la fin de la simulation.

Exemple :

```sh
./philosopher 5 800 200 200
```

## Principe du problème

- Chaque philosophe est assis autour d'une table avec une fourchette entre lui et son voisin.
- Pour manger, un philosophe doit prendre les deux fourchettes adjacentes.
- Un philosophe passe par trois états : *penser*, *manger*, *dormir*.
- Si un philosophe ne mange pas dans le temps imparti (`time_to_die`), il meurt et la simulation se termine.

## Gestion des threads et des mutex

- Chaque philosophe est un thread indépendant.
- Les fourchettes sont représentées par des mutex pour éviter les conflits d’accès.
- Un philosophe ne peut prendre une fourchette que si elle est disponible.
- La gestion des accès synchronisés permet d’éviter les *deadlocks* et *race conditions*.
