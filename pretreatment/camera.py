import cv2
import time

cap = cv2.VideoCapture(0)
ret,frame = cap.read()

t = time.time()
t_str = time.strftime("%Y-%m-%d %H:%M:%S",time.localtime(t))

cv2.imwrite("%s.png"%t_str,frame)
cap.release()
