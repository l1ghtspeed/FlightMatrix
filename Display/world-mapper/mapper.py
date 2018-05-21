import numpy as np
import cv2, pygame

#Colors
green = (0,255,0)
blue = (0,0,255)

#Screen Parameters
SCREEN_WIDTH,SCREEN_HEIGHT = 1024,512
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
screen.fill((0,0,0))

#pygame.display.update()

#Load Image
img = cv2.imread('worldmap.png',cv2.IMREAD_GRAYSCALE)
img = cv2.resize(img,(1024,512))
pixelated_img = [[] for i in range(32)]
count = 0
for i in range(0,497,16):
    for j in range(0,1009,16):

        num_black = 0
        num_white = 0
        
        for k in range(16):
            for l in range(16):
                if img[i+k][j+l]>= 127:
                    num_white+=1
                else:
                    num_black+=1
                    
        #print("---",int(i/16),"     ",int(j/16),"---")                   
        if num_black >= num_white:
            count += 1
            print(count/4096,"% is land")
            #pixelated_img[int(i/16)][int(j/16)] = green
            pixelated_img[int(i/16)].append(green)
        else:
            #pixelated_img[int(i/16)][int(j/16)] = blue
            pixelated_img[int(i/16)].append(blue)

print("sdjik")
for i in range(32):
    for j in range(64):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
                
            pygame.draw.rect(screen,pixelated_img[i][j], (i*16,j*16,16,16))

            pygame.display.update()

