import numpy as np
import cv2, pygame

#Colors
green = (0,255,0)
blue = (0,0,255)

#Screen Parameters
SCREEN_WIDTH,SCREEN_HEIGHT = 1024,512
pygame.init()
##screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
##screen.fill((0,0,0))

#pygame.display.update()

#Load Image
img = cv2.imread('worldmap.png',cv2.IMREAD_GRAYSCALE)
img = cv2.resize(img,(1024,512))
pixelated_img = [[] for i in range(32)]

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
            #pixelated_img[int(i/16)][int(j/16)] = green
            pixelated_img[int(i/16)].append(1)
        else:
            #pixelated_img[int(i/16)][int(j/16)] = blue
            pixelated_img[int(i/16)].append(0)
            
##for i in range (32):
##    for j in range (64):
##        print(pixelated_img[i][j],end='')
##    print('')

def recordData(fname, img_arr):
    file = open(fname,'w')
    file.write('{')
    
    for i in range(len(img_arr)):
        for j in range(len(img_arr[i])):
            if i == len(img_arr)-1 and j == len(img_arr[i])-1:
                file.write(str(img_arr[i][j]))
            else:
                file.write(str(img_arr[i][j])+',')
        file.write('\n')
    file.write('}')
    file.close()

recordData('map_array.txt',pixelated_img)
#print(count/4096*100,"% is land")
##while True:
##    for i in range(32):
##        for j in range(64):
##            for event in pygame.event.get():
##                if event.type == pygame.QUIT:
##                    pygame.quit()
##                    quit()
##                    
##                if pixelated_img[i][j]:
##                    pygame.draw.rect(screen,green, (j*16,i*16,16,16))
##                else:
##                    pygame.draw.rect(screen,blue, (j*16,i*16,16,16))
##
##  #              pygame.draw.rect(screen,(255,255,255), (randint(0,512),randint(0,1024),16,16))
##                pygame.display.update()
##
pygame.time.delay(5000)
pygame.quit()
quit()
