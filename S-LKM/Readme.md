# S-LKM

Primero tenemos que tener preparado el código kernel para compilar un LKM, y para ello instalamos las cabeceras de Linux:
~~~
sudo apt-get update
sudo apt-cache search linux-headers-$(uname -r)
sudo apt-get install linux-headers-$(uname -r)
~~~

![Esta es una imagen](img/InstalarCosas.jpg)

<img align="center" src="img/InstalarCosas.jpg" alt="Imagen de la instalación"/>