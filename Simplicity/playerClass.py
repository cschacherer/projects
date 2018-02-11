#Alex Koumandarakis
#playerClass.py

import pygame, sys
from pygame.locals import *
from makeShapesClass import makeShapes
from shapeRandomizer import randomizer

pygame.init()

class player:

    def __init__(self, surf, color):

        #Colors
        self.TRNSP = (0,0,0,0)
        self.WHITE = (255,255,255)
        self.pCOLOR = color

        #Sizes and ratios
        self.pSIZE = 50
        self.pHSIZE = self.pSIZE//2

        #Surface
        self.playerSURF = pygame.Surface((self.pSIZE, self.pSIZE), flags=SRCALPHA, depth=32)
        pygame.draw.circle(self.playerSURF, self.pCOLOR, (self.pHSIZE, self.pHSIZE), self.pHSIZE)

        self.DISPLAYSURF = surf

        #Shape
        self.CIRCLE = makeShapes(self.pSIZE, self.playerSURF, "circle", self.pCOLOR)
        self.TRIANGLE = makeShapes(self.pSIZE, self.playerSURF, "triangle", self.pCOLOR)
        self.SQUARE = makeShapes(self.pSIZE, self.playerSURF, "square", self.pCOLOR)
        self.PENTAGON = makeShapes(self.pSIZE, self.playerSURF, "pentagon", self.pCOLOR)
        self.STAR = makeShapes(self.pSIZE, self.playerSURF, "star", self.pCOLOR)
        self.SHAPE = "circle"

        #Positions
        self.LaneList = [20, 100, 180, 260, 340, 420, 500, 580, 660]

        self.LANE = 4
        self.pX = 70
        self.pY = 340

    def positionUp(self):
        if not self.LANE == 0:
            self.LANE -= 1
            self.pY -= 80
            #print(self.LANE)

    def positionDown(self):
        if not self.LANE == 8:
            self.LANE += 1
            self.pY += 80
            #print(self.LANE)

    def changeShape(self, shape):
        if shape == "circle":
            self.playerSURF.fill(self.WHITE)
            self.CIRCLE.showShape((0,0))
            self.SHAPE = "circle"
        elif shape == "star":
            self.playerSURF.fill(self.WHITE)
            self.STAR.showShape((0,0))
            self.SHAPE = "star"
        elif shape == "square":
            self.playerSURF.fill(self.WHITE)
            self.SQUARE.showShape((0,0))
            self.SHAPE = "square"
        elif shape == "triangle":
            self.playerSURF.fill(self.WHITE)
            self.TRIANGLE.showShape((0,0))
            self.SHAPE = "triangle"
        elif shape == "pentagon":
            self.playerSURF.fill(self.WHITE)
            self.PENTAGON.showShape((0,0))
            self.SHAPE = "pentagon"

    #checks what the interaction should be between the player and the object it hits
    def pickupCollision(self, pickup):
        self.changeShape(pickup.getShape(str(self.pY), "pickup"))
        '''
        print(pickup.getShape(self.LANE, "pickup"))
        print()
        print(self.SHAPE)
        print()
        print()
        '''

    def wallCollision(self, wall):
        '''
        print(wall.getShape(self.LANE, "wall"))
        print()
        print(self.SHAPE)
        '''
        if wall.getShape(str(self.pY), "wall") == self.SHAPE:
            return "pass"
        else:
            return "fail"

    def displayPlayer(self):
        self.DISPLAYSURF.fill(self.GREEN)
        self.DISPLAYSURF.blit(self.playerSURF, (self.pX, self.pY))
