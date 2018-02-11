#Shape Class

import pygame, sys
from pygame.locals import *
import random

pygame.init()


class makeShapes:
    def __init__(self, size, surf, shape, color):
        self.SIZE = size
        self.RADIUS = self.SIZE//2
        self.TRANSP = (0, 0, 0, 0)
        self.MSURF = surf
        self.SHAPESURF = pygame.Surface((self.SIZE, self.SIZE), flags=SRCALPHA, depth=32)
        self.SHAPESURF.fill(self.TRANSP)
        self.SHAPE = shape
        self.COLOR = color
        
    def constructShape(self):
        if self.SHAPE == "circle":
            pygame.draw.circle(self.SHAPESURF, self.COLOR, (self.SIZE//2, self.SIZE//2), self.RADIUS)

        elif self.SHAPE == "triangle":
            pygame.draw.polygon(self.SHAPESURF, self.COLOR, [(self.SIZE//2, 0), (0, self.SIZE), (self.SIZE, self.SIZE)])

        elif self.SHAPE == "square":
            pygame.draw.rect(self.SHAPESURF, self.COLOR, ((0, 0), (self.SIZE, self.SIZE)))

        elif self.SHAPE == "pentagon":
            pygame.draw.polygon(self.SHAPESURF, self.COLOR, [(self.SIZE//2, 0), (0, self.SIZE//2.5), (self.SIZE//4, self.SIZE), (self.SIZE//4, self.SIZE),
                                                          (int(self.SIZE * 0.75), self.SIZE), (self.SIZE, self.SIZE//2.5)])

        elif self.SHAPE == "star":
            pygame.draw.polygon(self.SHAPESURF, self.COLOR, [(self.SIZE//2, 0), (int(self.SIZE * 0.36), int(self.SIZE * 0.33)),
                                                          (int(self.SIZE * 0.63), int(self.SIZE * 0.33))])
            pygame.draw.polygon(self.SHAPESURF, self.COLOR, [(0, int(self.SIZE * 0.33)), (int(self.SIZE * 0.33), int(self.SIZE * 0.33)),
                                                          (int(self.SIZE * 0.33), int(self.SIZE * 0.66))])
            pygame.draw.polygon(self.SHAPESURF, self.COLOR, [(int(self.SIZE * 0.66), int(self.SIZE * 0.33)), (int(self.SIZE * 0.66), int(self.SIZE * 0.66)),
                                                          (self.SIZE, int(self.SIZE * 0.33))])
            pygame.draw.polygon(self.SHAPESURF, self.COLOR, [(int(self.SIZE * 0.1), self.SIZE), (self.SIZE//2, int(self.SIZE * 0.73)),
                                                          (int(self.SIZE * 0.26), int(self.SIZE * 0.53))])
            pygame.draw.polygon(self.SHAPESURF, self.COLOR, [(self.SIZE//2, int(self.SIZE * 0.73)),(int(self.SIZE * 0.9), self.SIZE),
                                                           (int(self.SIZE * 0.73), int(self.SIZE * 0.53))])
            pygame.draw.rect(self.SHAPESURF, self.COLOR, [(int(self.SIZE * 0.33), int(self.SIZE * 0.33)), (int(self.SIZE * 0.33), int(self.SIZE * 0.40))])

            pygame.draw.rect(self.SHAPESURF, self.COLOR, [(int(self.SIZE * 0.5), int(self.SIZE * 0.33)), (int(self.SIZE * 0.25), int(self.SIZE * 0.3))])
                                                           
    def showShape(self, position):
        self.constructShape()
        self.MSURF.blit(self.SHAPESURF, position)

