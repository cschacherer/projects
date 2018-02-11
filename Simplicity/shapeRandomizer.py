#randomization

import pygame
import pygame, sys
from pygame.locals import *
from random import *
import random
from makeShapesClass import makeShapes
from WallClass import wall

pygame.init()

class randomizer:
    def __init__(self, size, surf, height, width, color):        
        self.SIZE = size
        self.DISPLAYSURF = surf
        
        self.DISPLAYHEIGHT = height
        self.DISPLAYWIDTH = width

        self.GREY = (125, 125, 125)
        self.GREEN = (255,255,255)
        self.PURPLE = (70, 0, 70)
        self.DKBLUE = (24, 32, 188)
        self.TRANSP = (0, 0, 0, 0)

        #PICKUP SURFACE
        self.MAINSURF = pygame.Surface(((self.SIZE + int(self.SIZE * 0.1)), self.DISPLAYHEIGHT), flags=SRCALPHA, depth=32)
        self.MAINSURF.fill(self.TRANSP)
        self.COLOR = color

        #MAKE WALL
        self.WALL = wall(self.DISPLAYWIDTH, self.DISPLAYHEIGHT) 
        
        #PICK UP DICTIONARY
        self.SHAPEDICT = {'S1':makeShapes(self.SIZE, self.MAINSURF, "circle", self.COLOR),
                          'S2':makeShapes(self.SIZE, self.MAINSURF, "triangle", self.COLOR),
                          'S3':makeShapes(self.SIZE, self.MAINSURF, "square", self.COLOR),
                          'S4':makeShapes(self.SIZE, self.MAINSURF, "star", self.COLOR),
                          'S5':makeShapes(self.SIZE, self.MAINSURF, "pentagon", self.COLOR)}

        #WALL DICTIONARY
        self.RANDDICT = {'S1':makeShapes(self.SIZE, self.WALL.wallSURF, "circle", self.GREEN),
                          'S2':makeShapes(self.SIZE, self.WALL.wallSURF, "triangle", self.GREEN),
                          'S3':makeShapes(self.SIZE, self.WALL.wallSURF, "square", self.GREEN),
                          'S4':makeShapes(self.SIZE, self.WALL.wallSURF, "star", self.GREEN),
                          'S5':makeShapes(self.SIZE, self.WALL.wallSURF, "pentagon", self.GREEN)}

        self.RETURNDICT = {'S1':"circle",
                          'S2':"triangle",
                          'S3':"square",
                          'S4':"star",
                          'S5':"pentagon"}
        
        self.SHAPELIST = ['S1', 'S2', 'S3', 'S4', 'S5']


    #MAKE PICKUPS
    def shuffleShapes(self, score):
        self.MAINSURF.fill(self.TRANSP) 
        y = 0 #RANDOM VARIABLE THAT MANAGES HOW MANY SHAPES THERE WILL BE 

        #THE LIST WHERE THE SHAPES WILL BE PUT IN ORDER
        self.RANDOMLIST = []
        self.RANDRANGE = 0

        #THIS IS THE DICTIONARY THAT HELPS THE PLAYER'S COLLISON TEST
        self.RETURNLIST = ['none','none','none','none','none','none','none','none','none',] 

        #THE STARTING POSITION OF THE SHAPES DEPENDING ON WHAT THE SCORE IS
        if (score <= 2):#two shapes
            self.YPOS = 260 
        elif (score > 2) and (score <= 6):#three shapes
            self.YPOS = 180 
        elif (score > 6) and (score <= 10):#four shapes
            self.YPOS = 100 
        elif (score > 10) and (score <= 15):#five shapes 
            self.YPOS = 20
        elif (score > 15) and (score <= 25): #six shapes
            self.YPOS = 100
        elif (score > 25) and (score <= 35): #seven shapes
            self.YPOS = 100
        elif (score > 35) and (score <= 45): #eight shapes
            self.YPOS = 20
        elif (score > 45): #nine shapes
            self.YPOS = 20

        
        while True:       
            shapeCount = random.randrange (0, 5) 
            self.RANDOMLIST.append(self.SHAPELIST[shapeCount])
            SHAPE = self.RANDOMLIST[y] #CHOOSES A RANDOM SHAPE TO BE PUT IN THE PICKUPS
            
            RETURN = self.RETURNDICT[SHAPE]
            self.RETURNLIST[y] = RETURN #THIS HELPS THE COLLISION TEST, SO IF IT IS A CIRCLE, IT WILL RETURN 'CIRCLE'
            
            
            GSHAPE = self.SHAPEDICT[SHAPE] 
            GSHAPE.showShape((0, self.YPOS))#BLITS THE SHAPE IN THE PICKUPS    
            
            y += 1 

            #DEPENDING ON THE SCORE, THE SPACES IN BETWEEN THE SHAPES HAVE TO BE BIGGER OR SMALLER
            #THE YDICTIONARY HELPS THE COLLISION TEST, RETURNING A STRING OF NONE OR THE SHAPE FOR THE PLAYER TO TURN INTO
            #IF Y EQUALS THE NUMBER OF PICKUPS THERE SHOULD BE, THEN THE YPOS IS SET TO ZERO TO FOR THE NEXT PICKUP LIST
            #THE SELF.RANDRANGE IS FOR THE WALL CLASS, SO IT KNOWS HOW MANY NUMBER OF SHAPES IT CAN CHOOSE FROM
            if (score <= 2): #two shapes
                self.YPOS += 160
                self.YDICT = {'20': "none", '100': "none", '180': "none",
                         '260': self.RETURNLIST[0], '340': "none", '420': self.RETURNLIST[1],
                         '500': "none", '580': "none" , '660': "none"}
                if (y == 2):
                    self.YPOS = 0
                    self.RANDRANGE = 2
                    break
                
            elif (score > 2) and (score <= 6): #three shapes
                self.YPOS += 160
                self.YDICT = {'20': "none", '100': "none", '180': self.RETURNLIST[0],
                         '260': "none", '340': self.RETURNLIST[1], '420': "none",
                         '500': self.RETURNLIST[2], '580': "none", '660': "none"}
                if (y == 3):
                    self.YPOS = 0
                    self.RANDRANGE = 3
                    break
                
            elif (score > 6) and (score <= 10): #four shapes
                self.YPOS += 160
                self.YDICT = {'20': "none", '100': self.RETURNLIST[0], '180': "none",
                         '260': self.RETURNLIST[1], '340': "none", '420': self.RETURNLIST[2],
                         '500': "none", '580': self.RETURNLIST[3] , '660': "none"}
                if (y == 4):
                    self.YPOS = 0
                    self.RANDRANGE = 4
                    break
                
            elif (score > 10) and (score <= 15): #five shapes
                self.YPOS += 160
                self.YDICT = {'20': self.RETURNLIST[0], '100': "none", '180': self.RETURNLIST[1],
                         '260': "none", '340': self.RETURNLIST[2], '420': "none",
                         '500': self.RETURNLIST[3], '580': "none" , '660': self.RETURNLIST[4]}
                if (y == 5):
                    self.YPOS = 0
                    self.RANDRANGE = 5
                    break
                
            elif (score > 15) and (score <= 25): #six shapes
                self.YPOS += 80          
                self.YDICT = {'20': "none", '100': self.RETURNLIST[0], '180': self.RETURNLIST[1],
                         '260': self.RETURNLIST[2], '340': self.RETURNLIST[3], '420': self.RETURNLIST[4],
                         '500': self.RETURNLIST[5], '580': "none" , '660': "none"}
                if (y == 6):
                    self.YPOS = 0
                    self.RANDRANGE = 5
                    break
                
            elif (score > 25) and (score <= 35): #seven shapes
                self.YPOS += 80
                self.YDICT = {'20': "none", '100': self.RETURNLIST[0], '180': self.RETURNLIST[1],
                         '260': self.RETURNLIST[2], '340': self.RETURNLIST[3], '420': self.RETURNLIST[4],
                         '500': self.RETURNLIST[5], '580': self.RETURNLIST[6] , '660': "none"}
                if (y == 7):
                    self.YPOS = 0
                    self.RANDRANGE = 5
                    break
                
            elif (score > 35) and (score <= 45): #eight shapes
                self.YPOS += 80
                self.YDICT = {'20': self.RETURNLIST[0], '100': self.RETURNLIST[1], '180': self.RETURNLIST[2],
                         '260': self.RETURNLIST[3], '340': self.RETURNLIST[4], '420': self.RETURNLIST[5],
                         '500': self.RETURNLIST[6], '580': self.RETURNLIST[7] , '660': "none"}
                if (y == 8):
                    self.YPOS = 0
                    self.RANDRANGE = 5
                    break
                
            elif (score > 45): #nine shapes
                self.YPOS += 80
                self.YDICT = {'20': self.RETURNLIST[0], '100': self.RETURNLIST[1], '180': self.RETURNLIST[2],
                         '260': self.RETURNLIST[3], '340': self.RETURNLIST[4], '420': self.RETURNLIST[5],
                         '500': self.RETURNLIST[6], '580': self.RETURNLIST[7] , '660': self.RETURNLIST[8]}
                if (y == 9):
                    self.YPOS = 0
                    self.RANDRANGE = 5
                    break

        
    #SHOW PICKUPS
    def showShuffledShapes(self, XPOS):
        self.DISPLAYSURF.blit(self.MAINSURF, (XPOS, 0))


    #MAKE WALL SHAPES
    def secondShuffle(self, score):
        self.WALL.wallSURF.fill(self.GREY)

        y = 0
        
        self.RANDLIST2 = []

        self.RETURNLIST = ['none','none','none','none','none','none','none','none','none',]

        if (score <= 2):#two shapes
            self.YPOS = 100 
        elif (score > 2) and (score <= 6):#three shapes
            self.YPOS = 100 
        elif (score > 6) and (score <= 10):#four shapes
            self.YPOS = 100 
        elif (score > 10) and (score <= 15):#five shapes 
            self.YPOS = 20
        elif (score > 15) and (score <= 25): #six shapes
            self.YPOS = 100
        elif (score > 25) and (score <= 35): #seven shapes
            self.YPOS = 100
        elif (score > 35) and (score <= 45): #eight shapes
            self.YPOS = 20
        elif (score > 45): #nine shapes
            self.YPOS = 20
            


        while True:       
            shapeCount = random.randrange (0, (self.RANDRANGE))
            self.RANDLIST2.append(self.RANDOMLIST[shapeCount])
            SHAPE = self.RANDLIST2[y]
            
            RETURN = self.RETURNDICT[SHAPE]
            self.RETURNLIST[y] = RETURN
            #print(self.RETURNLIST)
            
            GSHAPE = self.RANDDICT[SHAPE]
            GSHAPE.showShape((28, self.YPOS))           

            y += 1

            if (score <= 2): #two shapes
                self.YPOS += 480
                self.WYDICT = {'20': "none", '100': self.RETURNLIST[0], '180': "none",
                         '260': "none", '340': "none", '420': "none",
                         '500': "none", '580': self.RETURNLIST[1], '660': "none"}
                if (y == 2):
                    self.YPOS = 0
                    break
                
            elif (score > 2) and (score <= 6): #three shapes
                self.YPOS += 240
                self.WYDICT = {'20': "none", '100': self.RETURNLIST[0], '180': "none",
                         '260': "none", '340': self.RETURNLIST[1], '420': "none",
                         '500': "none", '580': self.RETURNLIST[2], '660': "none"}
                if (y == 3):
                    self.YPOS = 0
                    break
            elif (score > 6) and (score <= 10): #four shapes
                self.YPOS += 160
                self.WYDICT = {'20': "none", '100': self.RETURNLIST[0], '180': "none",
                         '260': self.RETURNLIST[1], '340': "none", '420': self.RETURNLIST[2],
                         '500': "none", '580': self.RETURNLIST[3] , '660': "none"}
                if (y == 4):
                    self.YPOS = 0
                    break
            elif (score > 10) and (score <= 15): #five shapes
                self.YPOS += 160
                self.WYDICT = {'20': self.RETURNLIST[0], '100': "none", '180': self.RETURNLIST[1],
                         '260': "none", '340': self.RETURNLIST[2], '420': "none",
                         '500': self.RETURNLIST[3], '580': "none" , '660': self.RETURNLIST[4]}
                if (y == 5):
                    self.YPOS = 0
                    break
            elif (score > 15) and (score <= 25): #six shapes
                self.YPOS += 80
                self.WYDICT = {'20': "none", '100': self.RETURNLIST[0], '180': self.RETURNLIST[1],
                         '260': self.RETURNLIST[2], '340': self.RETURNLIST[3], '420': self.RETURNLIST[4],
                         '500': self.RETURNLIST[5], '580': "none" , '660': "none"}
                if (y == 6):
                    self.YPOS = 0
                    break
            elif (score > 25) and (score <= 35): #seven shapes
                self.YPOS += 80
                self.WYDICT = {'20': "none", '100': self.RETURNLIST[0], '180': self.RETURNLIST[1],
                         '260': self.RETURNLIST[2], '340': self.RETURNLIST[3], '420': self.RETURNLIST[4],
                         '500': self.RETURNLIST[5], '580': self.RETURNLIST[6] , '660': "none"}
                if (y == 7):
                    self.YPOS = 0
                    break
            elif (score > 35) and (score <= 45): #eight shapes
                self.YPOS += 80
                self.WYDICT = {'20': self.RETURNLIST[0], '100': self.RETURNLIST[1], '180': self.RETURNLIST[2],
                         '260': self.RETURNLIST[3], '340': self.RETURNLIST[4], '420': self.RETURNLIST[5],
                         '500': self.RETURNLIST[6], '580': self.RETURNLIST[7] , '660': "none"}
                if (y == 8):
                    self.YPOS = 0
                    break
            elif (score > 45): #nine shapes
                self.YPOS += 80
                self.WYDICT = {'20': self.RETURNLIST[0], '100': self.RETURNLIST[1], '180': self.RETURNLIST[2],
                         '260': self.RETURNLIST[3], '340': self.RETURNLIST[4], '420': self.RETURNLIST[5],
                         '500': self.RETURNLIST[6], '580': self.RETURNLIST[7] , '660': self.RETURNLIST[8]}
                if (y == 9):
                    self.YPOS = 0
                    break
        
                
        
        #PUTS ONE PICKUP SHAPE INTO THE WALL   
        randCount = random.randrange (0, self.RANDRANGE)
        r = random.randrange(0, self.RANDRANGE)
        
        rSHAPE = self.RANDOMLIST[randCount]
        
        del self.RANDLIST2[r]
        self.RANDLIST2.insert(r, rSHAPE)


    #SHOW WALL SHAPES
    def showSecondShuffle(self, XPOS2):
        self.DISPLAYSURF.blit(self.WALL.wallSURF, (XPOS2, 0))

    def getShape(self, yPOS, itemType):
        if itemType == "pickup":
            return self.YDICT[yPOS]
        elif itemType == "wall":
            return self.WYDICT[yPOS]

