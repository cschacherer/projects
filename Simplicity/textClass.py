#textClass.py

import pygame, sys
from pygame.locals import *

pygame.init()

class text:

    def __init__(self, surf):

        self.DISPLAYSURF = surf

        self.FONT = pygame.font.SysFont("Sylfaen", 40)#####

    def pointBurst(self, points, color):
        pointstxt = "+" + str(points)
        pointText = self.FONT.render(pointstxt, True, color, None)
        return pointText

    def gameOver(self, color):
        font = pygame.font.SysFont("Sylfaen", 120)
        text = font.render("Game Over", True, color, None)
        return text

    def instructions(self, color):
        font = pygame.font.SysFont("Sylfaen", 35)
        text = font.render("Enter: Try Again   Space: Main Menu", True, color, None)
        return text

    def finalScore(self, score, color):
        font = pygame.font.SysFont("Sylfaen", 35)
        text = font.render("Final Score: " + str(score), True, color, None)
        return text

    def title(self, color):
        font = pygame.font.SysFont("Sylfaen", 120)
        text = font.render("Simplicity", True, color, None)
        return text

    def credits(self, color):
        font = pygame.font.SysFont("Sylfaen", 35)
        text = font.render("Created By:", True, color, None)
        text2 = font.render("Steven Malecki: Conner Schacherer: Alex Koumandarakis", True, color, None)
        return text, text2

    def menuInstruc(self, color):
        font = pygame.font.SysFont("Sylfaen", 35)
        text = font.render("Enter: Play", True, color, None)
        return text

    def gameInstruc(self, color):
        font = pygame.font.SysFont("Sylfaen", 35)
        text = font.render("Up and Down Arrows: Move", True, color, None)
        text2 = font.render("-Collect pickups to change shape", True, color, None)
        text3 = font.render("-Make it through the holes in the wall", True, color, None)
        return text, text2, text3

    
        


        
            
            
