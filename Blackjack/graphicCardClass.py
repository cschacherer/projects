import pygame, sys
from pygame.locals import *

pygame.init()


class gCard:

    def __init__(self, size, surf, suit, value):
        self.SIZE = size
        self.RADIUS = self.SIZE // 10
        self.HALFRAD = self.RADIUS // 2
        self.cardSURF = pygame.Surface((self.SIZE * 3, self.SIZE * 3), flags=SRCALPHA, depth=32)
        TRANSP = (0, 0, 0, 0)
        self.cardSURF.fill(TRANSP)
        self.suit = suit
        self.value = value


    #setting suit
    def __makeCard(self):

        DKBLUE = (24, 32, 188)
        LTBLUE = (141, 234, 251)
        DKYELLOW = (255, 198, 0)
        LTYELLOW = (252, 241, 150)
        DKGREEN = (10, 136, 0)
        LTGREEN = (104, 207, 97)
        CRIMSON = (149, 3, 3)
        LTRED = (255, 65, 65)
        BLACK = (0, 0, 0)
        WHITE = (255, 255, 255)
              
        if (self.suit == "air"):
            color1 = LTYELLOW
            color2 = DKYELLOW
            self.suitImage = 'air.tga'
            self.fontcolor = DKYELLOW
        elif (self.suit == "water"):
            color1 = LTBLUE
            color2 = DKBLUE
            self.suitImage = 'water.tga'
            self.fontcolor = DKBLUE
        elif (self.suit == "earth"):
            color1 = LTGREEN
            color2 = DKGREEN
            self.suitImage = 'earth.tga'
            self.fontcolor = DKGREEN
        elif (self.suit == "fire"):
            color1 = LTRED
            color2 = CRIMSON
            self.suitImage = 'fire.tga'
            self.fontcolor = CRIMSON

        elif (self.suit == 'background'):
            color1 = BLACK
            color2 = WHITE
        

        #make card
        pygame.draw.circle(self.cardSURF, color1,(int(self.SIZE * 0.1), int(self.SIZE * 0.1)), self.RADIUS)
        pygame.draw.circle(self.cardSURF, color1,(self.SIZE, int(self.SIZE * 0.1)), self.RADIUS)
        pygame.draw.circle(self.cardSURF, color1,(int(self.SIZE * 0.1), int(self.SIZE * 1.5)), self.RADIUS)
        pygame.draw.circle(self.cardSURF, color1,(self.SIZE, int(self.SIZE * 1.5)), self.RADIUS)

        pygame.draw.rect(self.cardSURF, color1, ((int(self.SIZE * 0.1), 0), (int(self.SIZE*0.9), int(self.SIZE * 1.6))))
        pygame.draw.rect(self.cardSURF, color1, ((0, int(self.SIZE * 0.1)), (int(self.SIZE*1.1), int(self.SIZE * 1.4))))

        #card border
        pygame.draw.circle(self.cardSURF, color2,(int(self.SIZE * 0.1), int(self.SIZE * 0.1)), self.HALFRAD)
        pygame.draw.circle(self.cardSURF, color2,(self.SIZE, int(self.SIZE * 0.1)), self.HALFRAD)
        pygame.draw.circle(self.cardSURF, color2,(int(self.SIZE * 0.1), int(self.SIZE * 1.5)), self.HALFRAD)
        pygame.draw.circle(self.cardSURF, color2,(self.SIZE, int(self.SIZE * 1.5)), self.HALFRAD)

        pygame.draw.rect(self.cardSURF, color2, ((int(self.SIZE * 0.1), int(self.SIZE * 0.05)), (int(self.SIZE * 0.9), int(self.SIZE * 0.10))))
        pygame.draw.rect(self.cardSURF, color2,((int(self.SIZE * 0.05), int(self.SIZE * 0.1)), (int(self.SIZE * 0.1), int(self.SIZE * 1.4))))
        pygame.draw.rect(self.cardSURF, color2, ((int(self.SIZE * 0.1), int(self.SIZE * 1.45)), (int(self.SIZE *0.9), int(self.SIZE * 0.1))))
        pygame.draw.rect(self.cardSURF, color2, ((int(self.SIZE * 0.95), int(self.SIZE * 0.1)), (int(self.SIZE * 0.1), int(self.SIZE * 1.4))))


                
    def __cardImage(self):
        #suitSURF = pygame.Surface((170, 170), flags=SRCALPHA, depth=32)
        imageSURF = pygame.image.load(self.suitImage)
        suitSURF = pygame.transform.scale(imageSURF, (int(self.SIZE * 0.75), int(self.SIZE * 0.75)))

        self.cardSURF.blit(suitSURF, (int(self.SIZE * 0.170), int(self.SIZE * 0.4)))
        


    def __cardFont(self):
        suitNum = str(self.value)

        cardFont = pygame.font.SysFont("Elephant", int(self.SIZE * 0.25))
        textSURF = cardFont.render(suitNum, True, self.fontcolor, None)

        self.cardSURF.blit(textSURF, (int(self.SIZE * 0.2), int(self.SIZE * 0.135)))
        self.cardSURF.blit(textSURF, (int(self.SIZE * 0.7), int(self.SIZE * 1.15)))
        
    def __constructCard(self):
        self.__makeCard()
        self.__cardImage()
        self.__cardFont()

    def __constructBG(self):
        self.__makeCard()


    def showCard(self, surf, position):
        self.__constructCard()
        surf.blit(self.cardSURF, position)

    def showBG(self, surf, position):
        self.__constructBG()
        surf.blit(self.cardSURF, position)
##
##GREY = (150, 150, 150)
##
##
##DISPLAYSURF = pygame.display.set_mode((800, 600))
##pygame.display.set_caption('Cards')
##DISPLAYSURF.fill(GREY)
##
##
##
##SIZE = 200
##A2 = gCard(SIZE, DISPLAYSURF, "air", 2)
##
##        
##def main():
##    while True:
##        for event in pygame.event.get():
##            if event.type == QUIT:
##                pygame.quit()
##                sys.exit()
##        A2.POSITION = (100, 100)
##        A2.showCard(DISPLAYSURF)
##        
##        pygame.display.update()
##
##main()

