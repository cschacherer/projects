
import pygame
import pygame, sys
from pygame.locals import *
from random import *

pygame.init()
class score:

    def __init__(self, surf, height, width, bgcolor, textcolor):
        self.MAINSURF = surf
        self.MAINHEIGHT = height
        self.MAINWIDTH = width
        self.BGCOLOR = bgcolor
        self.TEXTCOLOR = textcolor

    def showPoints(self, points):
        pygame.draw.rect(self.MAINSURF, self.BGCOLOR, ((int(self.MAINWIDTH * 0.1), int(self.MAINHEIGHT * 0.1)),
                             (int(self.MAINWIDTH * 0.15), int(self.MAINHEIGHT * 0.025))))
        
        scoreFont = pygame.font.SysFont("Walkway, Walkway_Black.ttf", 30)
        textSURF = scoreFont.render("SCORE: " + str(points), True, self.TEXTCOLOR, None)
        
        self.MAINSURF.blit(textSURF, (int(self.MAINWIDTH * 0.1),int(self.MAINHEIGHT * 0.1)))
