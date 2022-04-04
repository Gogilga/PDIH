#include<ncurses.h>
#include<unistd.h>

#define DELAY 30000

void inicio(){                                                      // pantalla de inicio de partida
    initscr();
    keypad(stdscr,true);                                            //Para obtener entrada de teclado
    noecho();
    curs_set(FALSE);                                                // quitar el cursor
    mvprintw(5,10,"JUGADOR 1. CONTROLES: W arriba, S abajo");       // instrucciones del juego por pantalla
    mvprintw(6,10,"JUGADOR 2. CONTROLES: I arriba, K abajo");       // instrucciones del juego por pantalla
    mvprintw(7,10,"PULSA P PARA PAUSA");                            // instrucciones del juego por pantalla
    mvprintw(8,10,"PULSA Q PARA PARA TERMINAR LA PARTIDA");         // instrucciones del juego por pantalla
    box(stdscr,'|','-');                                            // crea la caja recuadro
    getch();
    nodelay(stdscr,1);
    clear();
}

void pausa(int x1, int x2){                                         // pantalla de pausa
    clear();
    mvprintw(5,5,"PAUSA. PULSA CUALQUIER TECLA PARA CONTINUAR");    // mensaje por pantalla
    mvprintw(6,5,"RESUMEN: %i -- %i",x1,x2);                        // mensaje por pantalla
    box(stdscr,'|','-');                                            // crea la caja recuadro
    nodelay(stdscr,0);
    getch();
}

void fin(int x1, int x2){                                                   // pantalla de fin de partida
    nodelay(stdscr,0);
    clear();
    mvprintw(1,0,"\n\n\n\n\n" "\t\tFIN DE LA PARTIDA: %i - %i",x1,x2);      // resultado del juego por pantalla
    box(stdscr,'|','-');                                                    // crea la caja recuadro
    if (x1 > x2){                                                           // si la puntuacion del primer jugador es mayor a la del segundo jugador
        mvprintw(10,0,"\t\tGANADOR: JUGADOR 1\n");                          // el ganador seria el jugador 1
    }
    else if(x1 < x2){                                                       // si no (puntuacion del jugador 1 menor que del jugador 2)
        mvprintw(10,0,"\t\tGANADOR: JUGADOR 2\n");                          // el ganador seria el jugador 2
    }
    else{                                                                   // si no (puntuacion del jugador 1 igual que del jugador 2)
        mvprintw(10,0,"\t\tEMPATE\n");                                      // empatan
    }
    refresh();
    getch();
}

void palas(int columnas, int pos1, int pos2){       // dibujamos las palas a distancia 10 de los bordes de la pantalla
    int i;
    for (i = 0; i < 5; i++){                        // las palas van a estar formadas por 5 palos verticales: |
	    mvprintw(pos1+i, 2, "|");                   // pala jugador 1
	    mvprintw(pos2+i, columnas-2, "|");          // pala jugador 2
    }
}


int main (){
    int i;                              // variable entera que usaremos en los bucles
    int x = 35, y = 10;                 // posiciones iniciales de la bola
    bool quit = false;                  // variable para terminar la partida al presionar q
    int pause = 0;                      // variable para entrar en pausa al presionar p
    int j1 = 0;                         // puntuacion del jugador 1, inicialmente a 0
    int j2 = 0;                         // puntuacion del jugador 2, inicialmente a 0
    int puntuacion_ganadora = 10;       // puntuacion a la que tienen que llegar los jugadores para ganar
    int fils, cols;                     // variables para saber las dimensiones de la pantalla
    int y1= 10, y2= 10;                 // posicion en y de las palas de los jugadores
    
    //Variables para gestionar el movimiento de la bola
    int next_x = 0;
    int directionx = 1;
    int next_y = 0;
    int directiony = 1;

    int ch = 0;                         //Para comprobar la tecla pulsada

    inicio();                           // mostramos la pantalla de inicio
    getmaxyx(stdscr,fils,cols);         // dimensiones de la pantalla
    int max_y = fils, max_x = cols; 

    while(quit == false){                           // mientras no se termine la partida       
        clear();
        nodelay(stdscr,1);
        mvprintw(y,x,"o");                          // colocar la bola
        mvprintw(0,cols/2,"%i vs %i",j1,j2);        // puntuacion actual de la partida
        palas(cols, y1, y2);                        // se sibujan las palas en la pantalla
        refresh();

        // decidir que hacer en funcion de la tecla pulsada
        ch = getch();
        switch(ch){
            case 'q':       // Salir del juego
                fin(j1,j2);
                quit = true;
                break;
            case 's':       // Mover la pala del jugador 1 para abajo
                if(y1 + 5 == fils){
                    y1 = fils - 5;
                }
                else{
                    y1 += 1;
                }
                break;
            case 'w':       // Mover la pala del jugador 1 para arriba
                if(y1 == 0){
                    y1 = 0;
                }
                else{
                    y1 -= 1;
                }
                break;
            case 'k':       // Mover la pala del jugador 2 para abajo
                if(y2 + 5 == fils){
                    y2 = fils - 5;
                }
                else{
                    y2 += 1;
                }
                break;
            case 'i':       // Mover la pala del jugador 2 para arriba
                if(y2 == 0){
                    y2 = 0;
                }
                else{
                    y2 -= 1;
                }
                break;
            case 'p':       // Poner en pausa
                pausa(j1,j2);
                break;
            //default:
        }

        // movimiento de la bola
        usleep(DELAY);

        next_x = x + directionx;
        next_y = y + directiony;

        // Comprobar cuando choca con las palas para que rebote y no haya recuento de puntos
        if(next_x == max_x-2 || next_x == 2){
            if(next_y == y1 || next_y == y1+1 || next_y == y1+2 || next_y == y1+3 || next_y == y1+4){
                directionx *= -1;
            }
            if(next_y == y2 || next_y == y2+1 || next_y == y2+2 || next_y == y2+3 || next_y == y2+4){
                directionx *= -1;
            }
        }

        // Comprobar cuando llega al borde y dar los puntos a los jugadores
        if(next_x >= max_x || next_x <= 0) {
            directionx *= -1;
            
            //Colcocar la pelota en el centro para que salga de nuevo
            x = cols/2, y = fils/2;

            // Para dar los puntos a cada uno de los jugadores
            if(next_x == max_x){
                j1 += 1;
            }else if(next_x == 0){
                j2 += 1;
            }
        } else {
            x += directionx;
        }

        if (next_y >= max_y || next_y < 0) {
            directiony *= -1;
        } else {
            y += directiony;
        }

        if(j1 == puntuacion_ganadora || j2 == puntuacion_ganadora){        // si uno de los dos jugadores ha llegado a la puntuacion maxima
            fin(j1,j2);                 // se muestra el jugador ganador
            quit = true;                // se termina la partida
        }
    }

    endwin();       // fin ncurses
    return 0;
}
