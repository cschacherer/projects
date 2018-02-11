#simple button class
import pygame
from pygame.locals import *

class simpleButton:
    # class that creates button objects
    def __init__(self, width, height, color, textColor, label, surf, position):
        # define and assign some self values
        self.ACTIVE = True
        self.LABEL = label
        self.SURF = surf
        self.POS = position
        self.BUTCOLOR  = color
        self.TEXTCOLOR = textColor

        # Generate a greyed-out version of color and a highlighted version of color
        self.BUTGREYED   = (color[0] * .25, color[1] * .25, color[2] * .25)
        self.HIGHLIGHTCOLOR = (color[0] + ((255 - color[0])//2),
                               color[1] + ((255 - color[1])//2),
                               color[2] + ((255 - color[2])//2))

        # Assign and calulate some size values 
        self.HEIGHT   = height
        self.WIDTH    = width
        self.HWIDTH   = self.WIDTH//2
        self.RADIUS   = self.HEIGHT//2
        self.THEIGHT  = int(self.HEIGHT * .5)

        # Create BUTTONSURF
        self.BUTTONSURF = pygame.Surface((self.WIDTH, self.HEIGHT), flags=SRCALPHA, depth=32)
        self.BUTTONSURF.fill((0, 0, 0, 0))

    def __buttonBG(self, color):

        # Helper Method to create button background
        # create square with rounded corners
       
        pygame.draw.circle(self.BUTTONSURF, color,(self.RADIUS, self.RADIUS),self.RADIUS)
        pygame.draw.circle(self.BUTTONSURF, color,(self.WIDTH - self.RADIUS, self.RADIUS), self.RADIUS)

        pygame.draw.rect(self.BUTTONSURF, color, Rect((self.RADIUS, 0), (self.WIDTH - 2 * self.RADIUS, self.HEIGHT)))

    def __buttonText(self):

        # helper funtion to make text surface and blit on BUTTONSURF

        # Set up the Font Object and how to Change Fonts
        BUTFONT = pygame.font.SysFont("Sylfaen", self.THEIGHT)
        
        # Render a Text Surface
        self.TEXTSURF = BUTFONT.render(self.LABEL, True, self.TEXTCOLOR, None)
        w, h   = self.TEXTSURF.get_size()
        XPOS = (self.WIDTH - w)//2
        YPOS = (self.HEIGHT - h)//2

        # Draw Text
        self.BUTTONSURF.blit(self.TEXTSURF, (XPOS, YPOS))

    def clicked(self, MOUSEXY):
        yesORno = False
        P1 = self.POS
        P2 = (P1[0] + self.WIDTH, P1[1] + self.HEIGHT)
        yesORno = (self.ACTIVE and P1[0] <= MOUSEXY[0] <= P2[0] and
                   P1[1] <= MOUSEXY[1] <= P2[1])

        return yesORno

    def active(self):
        self.ACTIVE = True

    def inActive(self):
        self.ACTIVE = False

    def changePos(self, X, Y):
        self.POS = (X, Y)
        return self.POS

    def displayhighlighted(self):
        self.__buttonBG(self.HIGHLIGHTCOLOR)
        self.__buttonText()
        self.SURF.blit(self.BUTTONSURF, self.POS)

    def displayBut(self):
        
        self.__buttonBG(self.BUTCOLOR)
        self.__buttonText()
        self.SURF.blit(self.BUTTONSURF, self.POS)
