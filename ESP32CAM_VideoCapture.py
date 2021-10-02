# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import urllib.request
import cv2
import numpy as np

face_cascade=cv2.CascadeClassifier("haarcascade_frontalface_default.xml")

url = 'http://10.62.228.40:8080'
cv2.namedWindow("Feed", cv2.WINDOW_AUTOSIZE)

while True:
    imgResponse=urllib.request.urlopen(url)
    imgnp = np.array(bytearray(imgResponse.read()), dtype=np.uint8)
    img = cv2.imdecode(imgnp, -1)
   # gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
 #   face = face_cascade.detectMultiScale(gray, 1.1, 4)
#    for x,y,w,h in face:
#        img = cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,255),3)
    cv2.imshow("Feed", img)
    key = cv2.waitKey(5)
    if key==ord('q'):
        break

cv2.destroyAllWindows()