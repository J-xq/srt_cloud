import socket
import os
import hashlib
import time
import cv2
import numpy as np

client = socket.socket()

ip_port =("192.168.1.102", 6969)  #地址和端口号

client.connect(ip_port)  #连接

print("服务器已连接")

if not os.path.exists("photo"):
	os.mkdir("photo")
while True:
	filename='photo/'+time.strftime("%Y%m%d-%H%M%S",time.localtime(time.time())) + '.png'
	frame_raw_num=int(client.recv(1024).decode("utf-8"))
	frame_column_num=int(client.recv(1024).decode("utf-8"))
	print(frame_raw_num,frame_column_num)
	frame_bytes=b""
	recv_size=0
	while recv_size<frame_raw_num*frame_column_num:
		frame_bytes+=client.recv(1024)
		recv_size+=1024
	frame=np.fromstring(frame_bytes,dtype=np.uint8).reshape(frame_raw_num,frame_column_num)
	cv2.imwrite(filename,frame)
	time.sleep(10)
