import cv2

I=cv2.imread("2019-03-15 12:22:11.803.png")
print(I.shape)
print(I[220:260,340:380,:])
B=cv2.imread("2019-04-12 12:38:09.png")
print(B.shape)
print(B[220:260,340:380,:])
I=I-B

cv2.imwrite("after_pretreatment.png",I)
