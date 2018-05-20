import numpy as np
import cv2, pygame

green = (0,255,0)
blue = (0,0,255)

img = cv2.imread('worldmap.png',cv2.IMREAD_GRAYSCALE)
img = cv2.resize(img,(1024,512))
pixelated_img = [[]]

print(img[350][842])

for i in range(0,1009,16):
    for j in range(0,1009,16):
        print(i,j)
        num_black = 0
        num_white = 0
        
        for k in range(16):
            for l in range(16):
                if img[k][l]>= 127:
                    num_white+=1
                else:
                    num_black+=1
                    
        if num_black >= num_white:
            pixelated_img[i/16][j/16] = green
        else:
            pixelated_img[i/16][j/16] = blue
