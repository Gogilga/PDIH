# S-LKM

Para la realización de esta actividad he usado una máquina virtual con el sistema operativo ``Zorin OS`` instalado.

Primero tenemos que tener preparado el código kernel para compilar un LKM, y para ello instalamos las cabeceras de Linux:
~~~
sudo apt-get update
sudo apt-cache search linux-headers-$(uname -r)
sudo apt-get install linux-headers-$(uname -r)
~~~

Aquí podemos ver la instalación:

![Imagen de la instalación](img/InstalarCosas.jpg)
