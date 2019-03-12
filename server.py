import socket
import cv2
import numpy as np
import time

server = socket.socket()

server.bind(("127.0.0.1", 6969))    #地址和端口号

server.listen(5) #监听

print("监听开始..")

conn, addr = server.accept()
print("conn:", conn, "\naddr:", addr)

while True:
	cap = cv2.VideoCapture(2)
	ret,frame = cap.read()
	cap.release()
	print(frame.shape,frame.itemsize)
	frame_raw_num=frame.shape[0]
	frame_column_num=frame.shape[1]
	conn.send(str(frame_raw_num).encode("utf-8"))
	conn.send(str(frame_column_num).encode("utf-8"))
	frame=frame[:,:,0]
	frame_bytes=frame.tostring()
	conn.sendall(frame_bytes)
	time.sleep(10)

		
