#Program uses openCV to change the resolution of images and write their data to a text file

import numpy as np
import cv2, pygame

#Colors
green = (0,255,0)
blue = (0,0,255)
black = (0,0,0)

def changeRes(file_name,mode,width,height,res_x,res_y):
    
    mode = mode.lower()
    
    if mode == 'grayscale':
        
        img = cv2.imread(file_name,cv2.IMREAD_GRAYSCALE)
        img = cv2.resize(img,(width,height))
        
        pixelated_img = [[] for i in range(res_y)]

        scale_x = int(width/res_x)
        scale_y = int(height/res_y)
        
        for i in range(0,height,scale_y):
            for j in range(0,width,scale_x):

                num_black = 0
                num_white = 0
                
                for k in range(scale_y):
                    for l in range(scale_x):
                        if img[i+k][j+l]>= 127:
                            num_white+=1
                        else:
                            num_black+=1
                                              
                if num_black >= num_white:            
                    pixelated_img[int(i/scale_y)].append(1)
                else:
                    pixelated_img[int(i/scale_y)].append(0)

    return pixelated_img

def printimgArray(array):
    for i in range(len(array)):
        for j in range(len(array[i])):
            print(array[i][j],end='')
        print('')

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

def drawMonocolor(width,height,col0,col1,array):
    assert(len(col0) == 3 and len(col1) == 3)
    
    pygame.init()

    screen = pygame.display.set_mode((width, height))
    screen.fill(black)

    scale_x = int(width/len(array[0]))
    scale_y = int(height/len(array))

    for i in range(len(array)):
        for j in range(len(array[i])):
            
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    quit()
                    
            if array[i][j]:
                pygame.draw.rect(screen,col1, (j*scale_x,i*scale_y,16,16))
            else:
                pygame.draw.rect(screen,col0, (j*scale_x,i*scale_y,16,16))
                    
            pygame.display.update()
            
    pygame.display.update()
    pygame.time.delay(5000)
    pygame.quit()

##Main Program
    
def main():
    
    arr = changeRes('worldmap.png','grayscale',1024,512,64,32)
    drawMonocolor(1024,512,blue,green,arr)


main()
