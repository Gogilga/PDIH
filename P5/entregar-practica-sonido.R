
library(tuneR)
library(seewave)
library(soundgen)
library(audio)

# establecer el path concreto en cada caso a la carpeta de trabajo
setwd("C:/Users/santi/Documents/Universidad/SextoAnio/SegundoCuatrimestre/PDIH/Practicas/Practica5")

# cargar archivos de sonido (wav/mp3):
nombre <- readWave('NombreSantiago.wav')
nombre
apellidos <- readWave('ApellidosSantiago.wav')
apellidos

# mostrar los campos del archivo de sonido
str(nombre)
str(apellidos)

# calcular la duración exacta del sonido (con tres decimales)
round(length(nombre@left) / nombre@samp.rate, 3)
f <- nombre@samp.rate    #44100

# escuchar un sonido:
listen(nombre,f=f)

# escuchar un sonido:
listen(apellidos,f=f)

# mostrar la onda del sonido:
plot( extractWave(nombre, from = 1, to = 393984) )

# mostrar la onda del sonido:
plot( extractWave(apellidos, from = 1, to = 393984) )

# uno ambos sonidos:
mezcla <- pastew(apellidos, nombre, output="Wave")
mezcla
plot( extractWave(mezcla, from = 1, to=393984) )
listen(mezcla)
writeWave(mezcla, file.path("mezcla.wav"))

# filtro de frecuencia 
filtrofrec <- bwfilter(mezcla,f=44100, channel=1, n=1, from=10000, to=20000, bandpass=TRUE, listen = FALSE, output = "Wave")
listen(filtrofrec,f=f)
plot(extractWave(filtrofrec, from = 1, to=393984))

# se guarda la señal en el fichero mezcla.wav
writeWave(filtrofrec, file.path("mezclafiltro.wav"))

# aplicar eco a un nuevo sonido y darle la vuelta
# guardar la señal en el fichero alreves.wav
nuevo <- readWave('oveja.wav')
str(nuevo)
nuevoconeco <- echo(nuevo, f=22050, amp=c(0.8,0.4,0.2), delay=c(1,2,3), output="Wave")
alreves <- revw(nuevoconeco, output="Wave")
listen(alreves)
writeWave(alreves, file.path("alreves.wav"))


