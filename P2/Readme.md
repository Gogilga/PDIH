# Práctica 2. USO DE BIBLIOTECAS DE PROGRAMACIÓN DE INTERFACES DE USUARIO EN MODO TEXTO

Estudiantes:

- :bust_in_silhouette:  **Santiago Gil Legaza** :octocat: [Repositorio PDIH](https://github.com/Gogilga/PDIH)
- :bust_in_silhouette:  **Victoria Dueñas Salcedo** :octocat: [Repositorio PDIH](https://github.com/vduesal/PDIH)

## Instalación librería ncurses
---

Para la realización de esta práctica, necesitamos tener instalada la librería ncurses en nuestra máquina. Para ello, tenemos que ejecutar en la terminal:

~~~
$ sudo apt-get install libncurses5-dev libncursesw5-dev
~~~

Además, en el código que realicemos en lenguage C tenemos que incluir al principio ``#include <ncurses.h>``.

## Implementación juego Pong

A partir de los programas de ejemplo mostrados en clase sobre el funcionamiento de la librería *ncurses*, implementaremos el juego *Pong*. Nuestro juego mostrará por pantalla dos palas con las que los jugadores tendrán que parar la bola que está en movimiento para no chocar contra los laterales. El choque de con los laterales implicaría un punto para el jugador de la pared contraria. Ganaría el jugador que llegue antes al máximo de puntos definido. Por otro lado, también vamos a implementar una pantalla para el inicio y otra para el final de la partida, y una pantalla más para poner el juego en pausa.

### Controles del juego
---

- w: arriba pala del jugador 1
- s: abajo pala del jugador 1
- i: arriba pala jugador 2
- k: abajo para jugador 2
- p: pausa de la partida
- q: terminar la partida

### Funciones de la librería ncurses utilizadas
---

- ``initscr()``: determina el tipo de terminal e inicializa las estructuras de datos de ncurses.
- ``edwin()``: finaliza el modo ncurses, restaura los modos de tty a como estuvieran cuando se llamó por primera vez a initscr() y mueve el cursor abajo a la esquina izquierda.
- ``noecho()``: no hacer el eco de entrada.
- ``curs_set(FALSE)``: hace que el cursor desaparezca y luego vuelva a aparecer.
- ``mvprintw(x,y,”mensaje”)``: imprime por pantalla el mensaje en las coordenadas indicadas x,y.
- ``box(stdscr,‘|’, ‘-’)``: crea una caja por el borde de la pantalla.
- ``getch()``: espera una pulsación de una sola tecla.
- ``nodelay(stdscr,1)``: hace que getch() sea una llamada sin bloqueos; si no hay ninguna entrada lista getch() devuelve error.
- ``clear()``: borra todo o parte de una ventana ncurses.
- ``getmaxyx(stdscr,fils,cols)``: halla las dimensiones de la pantalla.
- ``refresh()``: actualiza el aspecto de la pantalla.
- ``usleep(DELAY)``: suspende un proceso por un número determinado de segundos.
- ``keypad(stdscr,true)``: activa y desactiva la función de procesado de caracteres especiales.
