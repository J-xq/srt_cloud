import cv2
import numpy as np
i=240+50
j=360-30
I=cv2.imread("2019-04-19 17:30:45.png")
print(I[i:i+10,j:j+10,0])
print(np.sum(I[i:i+10,j:j+10,0])/100)
#print(I[100:105,360:365,0])
print("///////////////////////")

I[i:i+10,j:j+10,0]=0
I[i:i+10,j:j+10,1]=0
I[i:i+10,j:j+10,2]=255

cv2.imwrite("position.png",I)
