#Program uses openCV to change the resolution of images and write their data to a text file

import numpy as np
import cv2, pygame

#Colors
green = (0,255,0)
blue = (0,0,255)
black = (0,0,0)
white = (255,255,255)

def changeRes(file_name,mode,width,height,res_x,res_y):

    assert(0<=-width/height+res_x/res_y<=0.1)
    
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
        file.write('{')
        for j in range(len(img_arr[i])):
            if j == len(img_arr[i])-1:
                file.write(str(img_arr[i][j]))
            else:
                file.write(str(img_arr[i][j])+',')

        if i == len(img_arr)-1:
            file.write('}')
        else:
            file.write('},\n')
            
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

def rotatePlane(plane,angle,direction):
    direction = direction.lower()
    
    horiz = True
    skip = 0
    countOn = False
    direct = 1
    
    x = 0
    y = 0
    
    
    if direction == 'ccw':
        horiz = False
    
    for rev in range(angle%45+1):
        for diag in range(len(plane)-2,int(len(plane)/2),-1):

            perimeter = 2**diag
            x = 0
            y = 0
            
            for i in range(perimeter):
                
                if not i%diag and i != 0:
                    horiz = horiz ^ 1
                    
                if x == diag and y == diag:
                    direct = -1
                    
                if direction == 'cw':
                    if horiz:
                        if plane[x][y] and skip == (diag-2):
                            plane[x][y] = 0
                            plane[x+(diag-2)*direct][y] = 1
                        x += direct
                        if countOn:
                            skip += 1

                            
                    else:
                        if plane[x][y] and skip == (diag-2):
                            plane[x][y] = 0
                            plane[x][y+(diag-2)*direct] = 1
                        y += direct
                        if countOn:
                            skip += 1
                        
                elif direction == 'ccw':
                    if horiz:
                        if plane[x][y] and skip == (diag-2):
                            plane[x][y] = 0
                            plane[x-(diag-2)*direct][y] = 1
                            
                        x -= direct
                        if countOn:
                            skip += 1
                    else:
                        if plane[x][y] and skip == (diag-2):
                            plane[x][y] = 0
                            plane[x][y-(diag-2)*direct] = 1
                        y -= direct
                        if countOn:
                            skip += 1
            
    return plane;
            
        
##Main Program
    
def main():
    
    arr = changeRes('worldmap.png','grayscale',1024,512,64,32)
    #   drawMonocolor(1024,512,blue,green,arr)
    arr2 = changeRes('plane.jpg','grayscale',615,512,5,4)
    arr2.append([0,0,0,0,0])
    arr3 = rotatePlane(arr2,45,'cw')
    printimgArray(arr3)
    
 
 #printimgArray(plane)
 #recordData('plane.txt',plane)
 #recordData('map.txt',arr)
 #drawMonocolor(512,512,white,black,plane)


main()
