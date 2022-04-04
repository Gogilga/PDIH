# Práctica 2. USO DE BIBLIOTECAS DE PROGRAMACIÓN DE INTERFACES DE USUARIO EN MODO TEXTO.

Estudiantes:

- :bust_in_silhouette:  **Santiago Gil Legaza** :octocat: [Repositorio PDIH](https://github.com/Gogilga/PDIH)
- :bust_in_silhouette:  **Victoria Dueñas Salcedo** :octocat: [Repositorio PDIH](https://github.com/vduesal/PDIH)

## Instalación librería ncurses.
---

Para la realización de esta práctica, necesitamos tener instalada la librería ncurses en nuestra máquina. Para ello, tenemos que ejecutar en la terminal:

~~~
$ sudo apt-get install libncurses5-dev libncursesw5-dev
~~~

Además, en el código que realicemos en lenguage C tenemos que incluir al principio ``#include <ncurses.h>``.

## Implementación juego Pong.

A partir de los programas de ejemplo mostrados en clase sobre el funcionamiento de la librería *ncurses*, implementaremos el juego *Pong*. Nuestro juego mostrará por pantalla dos palas con las que los jugadores tendrán que parar la bola que está en movimiento para no chocar contra los laterales. El choque de con los laterales implicaría un punto para el jugador de la pared contraria. Ganaría el jugador que llegue antes al máximo de puntos definido. Por otro lado, también vamos a implementar una pantalla para el inicio y otra para el final de la partida, y una pantalla más para poner el juego en pausa.
