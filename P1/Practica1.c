#include <stdio.h>
#include <dos.h>

unsigned char cfondo= 3;
unsigned char ctexto= 0;

/*Funcion para poner una pausa en el programa*/
void pausa(){
   union REGS inregs, outregs;
	 inregs.h.ah = 8;
	 int86(0x21, &inregs, &outregs);
}

/*Funcion para ir a un punto x y de la pantalla*/
void xy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.bh = 0x00;
	inregs.h.dh = y;
	inregs.h.dl = x;
	int86(0x10,&inregs,&outregs);
	return;
}

/*Funcion para cambiar el tipo de cursor*/
void setcursortype(int tipo_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(tipo_cursor){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case 2: //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}
	int86(0x10, &inregs, &outregs);
}

/*Funcion para cambiar el modo de video de la pantalla*/
void set_modovideo(unsigned char modo){
	union REGS inregs, outregs; 
	inregs.h.ah = 0x00; 
	inregs.h.al = modo; 
	int86(0x10,&inregs,&outregs); 
	return;
}

/*Funcion que obtiene el modo de video actual*/
void get_modovideo(){
    union REGS inregs, outregs;
    unsigned char modo;

    inregs.h.ah= 0x0f;
    int86(0x10,&inregs,&outregs);

    modo= outregs.h.al;

    if(modo == 0 || modo == 1 || modo == 2 || modo == 3 || modo == 7){
        printf("\nEstamos en modo texto");
    }
    else{
        printf("\nEstamos en modo grafico");
    }
}

/*Funcion que obtiene el caracter de teclado*/
int get_char(){
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
	 return caracter;
}

/*Funcion para borrar la pantalla*/
void borrar() {
    union REGS regs;
	regs.h.ah = 15; 
	int86(0x10,&regs,&regs);
	regs.h.ah = 0; 
	int86(0x10,&regs,&regs);
}

/*Funcion para escribir un caracter*/
void put_char(char c){
	 union REGS inregs, outregs;

	 inregs.h.ah = 2;
	 inregs.h.dl = c;
	 int86(0x21, &inregs, &outregs);
}

/*Funcion para cambiar el color de un caracter*/
void put_char_color(char letra){
    union REGS inregs, outregs;

    inregs.h.ah= 0x09;
    inregs.h.al= letra;
	inregs.h.bl= cfondo << 4 | ctexto;
    inregs.h.bh= 0x00;
	inregs.x.cx = 1;
    int86(0x10, &inregs, &outregs);
}

//---------------- REQUISITOS AMPLIADOS -------------------
// Funcion pixel, pone un pixel en color
void pixel(int x, int y, unsigned char color){
    union REGS inregs, outregs;
    inregs.x.cx = x;
    inregs.x.dx = y;
    inregs.h.al = color;
    inregs.h.ah = 0x0C;
    int86(0x10,&inregs,&outregs);
}

// Funcion que dibuja un cuadrado
void cuadrado(int xi, int yi, int xd, int yd, char letra){
    int i;
	//set_modovideo(4);

    for (i = xi; i <= xd; i++){
		xy(i,yi);
		put_char_color(letra);
    }
    for (i = xi; i <= xd; i++){
		xy(i,yd);
		put_char_color(letra);
    }
    for (i = yi; i <= yd; i++){
		xy(xi,i);
		put_char_color(letra);
    }
    for (i = yi; i <= yd; i++){
		xy(xd,i);
		put_char_color(letra);
    }
}

// Funcion que dibuja una carita sonriente
void carita_feliz(){
    int i;

    // Circunferencia (lineas rectas)
    // Izquierda
    for (i = 35; i < 75; i++){
        pixel(40,i,2);
    }
    // Derecha
    for (i = 35; i < 75; i++){
        pixel(130,i,2);
    }
    // Arriba
    for (i = 65; i < 105; i++){
        pixel(i,10,2);
    }
    // Abajo
    for (i = 65; i < 105; i++){
        pixel(i,100,2);
    }

    // Circunferencia (lineas diagonales)
    // Arriba, derecha
    for (i = 0; i < 25; i++){
        pixel(105+i,10+i,2);
    }
    // Abajo, izquierda
    for (i = 0; i < 25; i++){
        pixel(40+i,75+i,2);
    }
    // Arriba, izquierda
    for (i = 0; i < 25; i++){
        pixel(65-i,10+i,2);
    }
    // Abajo, derecha
    for (i = 0; i < 26; i++){
        pixel(130-i,75+i,2);
    }

    // Ojos
    for (i = 0; i < 30; i++){
        pixel(71,30+i,1);
        pixel(99,30+i,1);
    }

    // Boca
    for (i = 70; i < 100; i++){
        pixel(i,80,1);
    }
    for (i = 0; i < 20; i++){
        pixel(100+i,80-i,1);
    }
    for (i = 0; i < 20; i++){
        pixel(70-i,80-i,1);
    }

}


/*#################################################################################*/
int main(){
	
	int tmp;
    char letra;
	int x, y;
	int x1,y1,x2,y2;
    unsigned char c1,c2;

	//Borro primero la pantalla para mostrar todo bien
	borrar();

	/*Vamos a mover el cursor*/
	x= 23; y= 4;
	printf("Primero vamos a mover el cursor al punto x= %d y= %d", x, y);
	xy(x,y);
	printf("x= %d y= %d", x, y);
	pausa();

	//Vamos a cambiar el color de caracter
    printf("\nPulsa un numero para elegir color de fondo...  ");
	cfondo = get_char();
	pausa();
    printf("\nPulsa un numero para elegir color de letra...  ");
	ctexto = get_char();
	pausa();
    printf("\nEscribe la letra que quieres mostrar...  ");
	letra = get_char();
    pausa();
    printf("\n");
    put_char_color(letra);

	pausa();

	//Vamos a cambiar los tipos de cursor
    printf("\nCursor invisible: ");
   	setcursortype(0);
   	pausa();
   	printf("\nCursor grueso: ");
   	setcursortype(2);
   	pausa();
   	printf("\nCursor normal: ");
   	setcursortype(1);
   	pausa();

	//Vamos a leer un caracter de teclado
	printf("\nPulsa una tecla...  ");
	tmp = get_char();

	printf("\nHas pulsado: ");
    put_char( (char)tmp );

	pausa();

	//Vamos a borrar la pantalla
	printf("\nVamos a borrar la pantalla...");
	pausa();
	borrar();

    pausa();
	set_modovideo(3);  // modo 3 -> 80x25 (letras pequenias)

	// ---------- REQUISITOS ADICIONALES ----------
	//Pasos para dibujar un cuadrado
    printf("\nVamos a dibujar un cuadrado.");
    printf("\nColor de texto: ");
    ctexto= get_char();
    //c1= get_char();
    pausa();
    printf("\nColor de fondo: ");
    cfondo= get_char();
    //c2= get_char();
	pausa();

    // Borramos toda la pantalla para mostrar un cuadrado en modo texto
    pausa();
    borrar();

    //Obtenemos el modo de video
    get_modovideo();
    // Cuadrado en modo texto
    x1= 2; y1= 2; x2= 52; y2= 14; 
    cuadrado(x1,y1,x2,y2,letra);
    pausa();

    //Cambiamos el modo de video
	set_modovideo(4);  // modo 4 -> 320x200 (letras grandes, en modo grafico)


   	//Volvemos a obtener el modo de video 
    get_modovideo();

    // Borramos toda la pantalla para mostrar un dibujo en modo grafico
    printf("\n\n\nPulsa una tecla para ver el dibujo");
    pausa();
    borrar();

    carita_feliz();
    pausa();

	/*Vuelvo a poner el modo de video por defecto para salir del programa*/
	set_modovideo(3);  // modo 3 -> 80x25 (letras pequenias)


	return 0;
}
