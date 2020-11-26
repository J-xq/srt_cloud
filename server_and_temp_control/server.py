#coding:utf-8
import socket
import hashlib
import cv2
import numpy
import threading
import time
import RPi.GPIO as GPIO
import os
from ctypes import *

def temp_control():
	GPIO.setmode(GPIO.BOARD)
	GPIO.setwarnings(False)
	GPIO.setup(11,GPIO.OUT,initial=0)

	p=os.getcwd()+'/libgettemp.so'
	f=cdll.LoadLibrary(p)

	f.gettemp.restype=c_float #key point

	while(1):
		temp=f.gettemp()
		print('The temperature of FPA is '+'%.2f' % temp +' °C')
		if(temp>45.0):
			while(temp>39.0):
				GPIO.output(11,1)
				time.sleep(1)
				temp=f.gettemp()
		time.sleep(1)
		

thread1 = threading.Thread(target = temp_control, args = ())
thread1.setDaemon(True)
thread1.start()



server = socket.socket()

server.bind(("192.168.4.1", 6964))    #地址和端口号

server.listen(5) #监听

print("监听开始..")

while True:
    conn, addr = server.accept()

    print("conn:", conn, "\naddr:", addr)

    while True:
        data = conn.recv(1024)
        if not data:
            print("客户端断开连接")
            break
            
        cap = cv2.VideoCapture(2)
        frame = cap.read()[1]
        cap.release()
        frame_enc = frame[:,:,0].tostring()
        print("开始发送")
        #发送时间
        t = time.time()
        t_str = time.strftime("%Y-%m-%d %H:%M:%S",time.localtime(t))
        print(t_str)
        conn.send(t_str.encode("utf-8"))
        conn.recv(1024)
        #发送大小
        size = len(frame_enc)
        conn.send(str(size).encode("utf-8"))
        print("发送的大小：", size)
        conn.recv(1024)
        #发送长宽
        frame_raw_num=frame.shape[0]
        frame_column_num=frame.shape[1]
        conn.send(str(frame_raw_num).encode("utf-8"))
        conn.recv(1024)
        conn.send(str(frame_column_num).encode("utf-8"))
        conn.recv(1024)

        #发送文件内容
        m = hashlib.md5()
        conn.send(frame_enc)
        m.update(frame_enc)
        conn.recv(1024)

        #md5校验
        md5 = m.hexdigest()
        conn.send(md5.encode("utf-8"))
        print("md5:", md5)
    
    conn.close()
    print("监听开始..")	
