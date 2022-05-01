import cv2
import os
import numpy as np

dataPath = 'Data'
peopleList = os.listdir(dataPath)
print('Lista de personas: ', peopleList)

labels = []
facesData = []
label = 0

for nameDir in peopleList:
    personPath = dataPath + '/' + nameDir
    print('\nLeyendo las imágenes de ' + nameDir)

    for fileName in os.listdir(personPath):
        print('Rostros: ', nameDir + '/' + fileName)
        labels.append(label)
        facesData.append(cv2.imread(personPath+'/'+fileName,0))

        #Para ver las imágenes a la vez que se etiquetan
        image = cv2.imread(personPath+'/'+fileName,0)
        cv2.imshow('image',image)
        cv2.waitKey(10)
    label = label + 1

#print('\nlabels= ',labels)
for i in range(label):
    print('Número de etiquetas ' + str(i) + ' para ' + peopleList[i] + ':\t',np.count_nonzero(np.array(labels)==i))


# Método para entrenar el reconocedor
face_recognizer = cv2.face.LBPHFaceRecognizer_create()

# Entrenando el reconocedor de rostros
print("Entrenando...")
face_recognizer.train(facesData, np.array(labels))

# Almacenando el modelo obtenido
face_recognizer.write('modeloLBPHFace.xml')
print("Modelo almacenado...")

