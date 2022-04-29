# Práctica 3. EXPERIMENTACIÓN CON ARDUINO

Estudiantes:

- :bust_in_silhouette:  **Santiago Gil Legaza** :octocat: [Repositorio PDIH](https://github.com/Gogilga/PDIH)
- :bust_in_silhouette:  **Victoria Dueñas Salcedo** :octocat: [Repositorio PDIH](https://github.com/vduesal/PDIH)

## 1. Parpadeo led

Implementar el programa de parpadeo de LED, ampliándolo para que encienda y apague alternativamente tres LEDs (uno rojo, otro amarillo y otro verde), conectados a las salidas digitales 11, 12 y 13 del Arduino, a un intervalo de 1.5 segundos. Crear el esquema con Fritzing y cargar el programa en Arduino para comprobar que funciona correctamente.

Componentes eléctricos utilizados: 
- Un LED rojo
- Un LED amarillo
- Un LED verde
- Tres resistencias de 220Ω
- Una placa Arduino Uno R3

Esquema de conexiones eléctricas:

![Circuito 1](img/Circuito1.png)

![Esquema circuito 1](img/EsquemaCircuito1.png)

Código fuente:

```
void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(11, HIGH);
  delay(1500); // Wait for 1500 millisecond(s)
  digitalWrite(11, LOW);
  delay(1500); // Wait for 1500 millisecond(s)
  digitalWrite(12, HIGH);
  delay(1500); // Wait for 1500 millisecond(s)
  digitalWrite(12, LOW);
  delay(1500); // Wait for 1500 millisecond(s)
  digitalWrite(13, HIGH);
  delay(1500); // Wait for 1500 millisecond(s)
  digitalWrite(13, LOW);
  delay(1500); // Wait for 1500 millisecond(s)
}
```

Los pines 11, 12 y 13 son de salida y hacen referencia a los tres LEDs verde, amarillo y rojo, respectivamente.

Imágenes demostrativas del funcionamiento: 

![Muestra circuito 1](img/Muestra1.jpg)

![Video circuito 1](img/Video1.gif)

## 2. Parpadeo led con pulsador

Partir del programa de parpadeo de LEDs anterior y ampliarlo con las modificaciones necesarias para que se encienda el LED rojo solo cuando se pulse un interruptor conectado a la entrada 7, y en ese momento se apaguen los LEDs amarillo y verde.

Componentes eléctricos utilizados: 
- Un LED rojo
- Un LED amarillo
- Un LED verde
- Cuatro resistencias de 220Ω
- Una placa Arduino Uno R3
- Un pulsador

Esquema de conexiones eléctricas:

![Circuito 2](img/Circuito2.png)

![Esquema circuito 2](img/EsquemaCircuito2.png)

Código fuente:

```
void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
}

void loop()
{
  if (digitalRead(7) == HIGH){
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }
}
```

Al igual que antes, los pines 11, 12 y 13 son de salida y corresponden con los LEDs en el mismo orden que en el primer circuito. Por otro lado, en este circuito hemos añadido el pin 7, en este caso de entrada, para el pulsador que hará el cambio de bombillas encendidas.

Imágenes demostrativas del funcionamiento: 

![Muestra circuito 2](img/Muestra2.1.jpg)

![Muestra circuito 2](img/Muestra2.2.jpg)

![Video circuito 2](img/Video2.gif)

## 3. Coche fantástico

Secuencia de LEDs, encendiendo y apagando 4 LEDs secuencialmente, de forma similar a las lucecitas de “_El coche fantástico_”.

Componentes eléctricos utilizados: 
- Cuatro LEDs rojos
- Cuatro resistencias de 220Ω
- Una placa Arduino Uno R3

Esquema de conexiones eléctricas:

![Circuito 3](img/Circuito3.png)

![Esquema circuito 3](img/EsquemaCircuito3.png)

Código fuente:

```
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW);
  delay(300); // Wait for 300 millisecond(s)
  
  digitalWrite(12, LOW);
  delay(300); // Wait for 300 millisecond(s)
  
  digitalWrite(12, HIGH);
  digitalWrite(10, LOW);
  delay(300); // Wait for 300 millisecond(s)
  digitalWrite(11, HIGH);
  digitalWrite(13, LOW);
  delay(300); // Wait for 300 millisecond(s)
  digitalWrite(10, HIGH);
  digitalWrite(12, LOW);
  delay(300); // Wait for 300 millisecond(s)
  
  digitalWrite(11, LOW);
  delay(300); // Wait for 300 millisecond(s)
  
  digitalWrite(11, HIGH);
  digitalWrite(13, LOW);
  delay(300); // Wait for 300 millisecond(s)
  digitalWrite(12, HIGH);
  digitalWrite(10, LOW);
  delay(300); // Wait for 300 millisecond(s)
}
```

En esta ocasión tenemos 4 LEDs rojos conectados a los pines 10, 11, 12 y 13, todos de salida.

Imágenes demostrativas del funcionamiento: 

![Muestra circuito 3](img/Muestra3.jpg)

![Video circuito 3](img/Video3.gif)

## 4. Alarma por detección de presencia.

Componentes eléctricos utilizados: 
- Un LED rojo
- Cuatro resistencias de 220Ω
- Un sensor PIR
- Un buzzer
- Una placa Arduino Uno R3

Esquema de conexiones eléctricas:

![Circuito 4](img/Circuito4.png)

![Esquema circuito 4](img/EsquemaCircuito4.png)

Código fuente:

```
int pir_pin = 2;
int led_pin = 3;
int val= 0;

void setup() {
  pinMode(pir_pin, INPUT);
  pinMode(led_pin, OUTPUT);
}
void loop() {
  val = digitalRead(pir_pin);
  if(val == HIGH)
  {
    digitalWrite(led_pin, HIGH);
    delay(100);
  }
  else{
    digitalWrite(led_pin, LOW);
    delay(100);
  }
}
```

Utilizamos variables globales en este último circuito para definir los pines de los componentes que tenemos. El pin 2 lo utilizamos para el sensor PIR, y será de entrada. El pin 3 corresponde con el LED, que como ya hemos dicho anteriormente es de salida. Por último, el buzzer estará en el pin 4, y también será de salida porque emitirá un zumbido cuando detecte presencia con el sensor PIR.

Imágenes demostrativas del funcionamiento: 

![Muestra circuito 4](img/Muestra4.jpg)

