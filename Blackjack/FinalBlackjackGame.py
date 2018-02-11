#Blackjack Game

import pygame
import pygame, sys
from pygame.locals import *
from random import *
import random
from buttonClass import simpleButton
from graphicCardClass import gCard
from cardShufflingClass import cards


pygame.init()

#SIZE AND COLORS
SIZE = 150

GREY = (150, 150, 150)
WHITE = (255, 255, 255)
LTGREY = (207, 207, 207)
BLACK = (0, 0, 0)
RED = (255, 0, 0, 150)
DKRED = (100, 0, 0)
TRANSP = (0, 0, 0, 0)
DKBLUE = (24, 32, 188)
LTBLUE = (141, 234, 251)
DKYELLOW = (255, 198, 0)
LTYELLOW = (252, 241, 150)
DKGREEN = (10, 136, 0)
LTGREEN = (104, 207, 97)
CRIMSON = (149, 3, 3)
LTRED = (255, 65, 65)

#DISPLAY
DISPLAYHEIGHT = 1100
DISPLAYWIDTH = 650
DISPLAYSURF = pygame.display.set_mode((DISPLAYHEIGHT, DISPLAYWIDTH))
pygame.display.set_caption('Blackjack Game')
DISPLAYSURF.fill(GREY)


class dealCards:
    
    def __init__(self, surf, size):
        self.MAINSURF = surf
        self.SIZE = size
        self.DECK = cards()
        self.SHUFFLEDDECK = self.DECK.shuffleCARDS()
##        self.PLAYERSCARDS = []
##        self.PLAYERSSCORE = 0
##        self.DEALERSCARDS = []
##        self.DEALERSSCORE = 0


        self.GRAPHICDICT = {'A2': gCard(self.SIZE, self.MAINSURF, "air", 2),
        'A3': gCard(self.SIZE, self.MAINSURF, "air", 3),
        'A4': gCard(self.SIZE, self.MAINSURF, "air", 4),
        'A5': gCard(self.SIZE, self.MAINSURF, "air", 5),
        'A6': gCard(self.SIZE, self.MAINSURF, "air", 6),
        'A7': gCard(self.SIZE, self.MAINSURF, "air", 7),
        'A8': gCard(self.SIZE, self.MAINSURF, "air", 8),
        'A9': gCard(self.SIZE, self.MAINSURF, "air", 9),
        'A10': gCard(self.SIZE, self.MAINSURF, "air", 10),
        'AJ': gCard(self.SIZE, self.MAINSURF, "air", "J"),
        'AQ': gCard(self.SIZE, self.MAINSURF, "air", "Q"),
        'AK': gCard(self.SIZE, self.MAINSURF, "air", "K"),
        'AA': gCard(self.SIZE, self.MAINSURF, "air", "A"),

        #water
        'W2': gCard(self.SIZE, self.MAINSURF, "water", 2),
        'W3': gCard(self.SIZE, self.MAINSURF, "water", 3),
        'W4': gCard(self.SIZE, self.MAINSURF, "water", 4),
        'W5': gCard(self.SIZE, self.MAINSURF, "water", 5),
        'W6': gCard(self.SIZE, self.MAINSURF, "water", 6),
        'W7': gCard(self.SIZE, self.MAINSURF, "water", 7),
        'W8': gCard(self.SIZE, self.MAINSURF, "water", 8),
        'W9': gCard(self.SIZE, self.MAINSURF, "water", 9),
        'W10': gCard(self.SIZE, self.MAINSURF, "water", 10),
        'WJ': gCard(self.SIZE, self.MAINSURF, "water", "J"),
        'WQ': gCard(self.SIZE, self.MAINSURF, "water", "Q"),
        'WK': gCard(self.SIZE, self.MAINSURF, "water", "K"),
        'WA': gCard(self.SIZE, self.MAINSURF, "water", "A"),

        #earth
        'E2': gCard(self.SIZE, self.MAINSURF, "earth", 2),
        'E3': gCard(self.SIZE, self.MAINSURF, "earth", 3),
        'E4': gCard(self.SIZE, self.MAINSURF, "earth", 4),
        'E5': gCard(self.SIZE, self.MAINSURF, "earth", 5),
        'E6': gCard(self.SIZE, self.MAINSURF, "earth", 6),
        'E7': gCard(self.SIZE, self.MAINSURF, "earth", 7),
        'E8': gCard(self.SIZE, self.MAINSURF, "earth", 8),
        'E9': gCard(self.SIZE, self.MAINSURF, "earth", 9),
        'E10': gCard(self.SIZE, self.MAINSURF, "earth", 10),
        'EJ': gCard(self.SIZE, self.MAINSURF, "earth", "J"),
        'EQ': gCard(self.SIZE, self.MAINSURF, "earth", "Q"),
        'EK': gCard(self.SIZE, self.MAINSURF, "earth", "K"),
        'EA': gCard(self.SIZE, self.MAINSURF, "earth", "A"),

        #fire
        'F2': gCard(self.SIZE, self.MAINSURF, "fire", 2),
        'F3': gCard(self.SIZE, self.MAINSURF, "fire", 3),
        'F4': gCard(self.SIZE, self.MAINSURF, "fire", 4),
        'F5': gCard(self.SIZE, self.MAINSURF, "fire", 5),
        'F6': gCard(self.SIZE, self.MAINSURF, "fire", 6),
        'F7': gCard(self.SIZE, self.MAINSURF, "fire", 7),
        'F8': gCard(self.SIZE, self.MAINSURF, "fire", 8),
        'F9': gCard(self.SIZE, self.MAINSURF, "fire", 9),
        'F10': gCard(self.SIZE, self.MAINSURF, "fire", 10),
        'FJ': gCard(self.SIZE, self.MAINSURF, "fire", "J"),
        'FQ': gCard(self.SIZE, self.MAINSURF, "fire", "Q"),
        'FK': gCard(self.SIZE, self.MAINSURF, "fire", "K"),
        'FA': gCard(self.SIZE, self.MAINSURF, "fire", "A")}


        self.CARDLIST = ['A2', 'W2', 'E2', 'F2',
                         'A3', 'W3', 'E3', 'F3',
                         'A4', 'W4', 'E4', 'F4',
                         'A5', 'W5', 'E5', 'F5',
                         'A6', 'W6', 'E6', 'F6',
                         'A7', 'W7', 'E7', 'F7',
                         'A8', 'W8', 'E8', 'F8',
                         'A9', 'W9', 'E9', 'F9',
                         'A10', 'W10', 'E10', 'F10',
                         'AJ', 'WJ', 'EJ', 'FJ',
                         'AQ', 'WQ', 'EQ', 'FQ',
                         'AK', 'WK', 'EK', 'FK',
                         'AA', 'WA', 'EA', 'FA']
        
        self.CARDPOINTS = {'A2': 2, 'W2': 2, 'E2': 2, 'F2': 2,
                         'A3': 3, 'W3': 3, 'E3': 3, 'F3': 3,
                         'A4': 4, 'W4': 4, 'E4': 4, 'F4': 4,
                         'A5': 5, 'W5': 5, 'E5': 5, 'F5': 5,
                         'A6': 6, 'W6': 6, 'E6': 6, 'F6': 6,
                         'A7': 7, 'W7': 7, 'E7': 7, 'F7': 7,
                         'A8': 8, 'W8': 8, 'E8': 8, 'F8': 8,
                         'A9': 9, 'W9': 9, 'E9': 9, 'F9': 9,
                         'A10': 10, 'W10': 10, 'E10': 10, 'F10': 10,
                         'AJ': 10, 'WJ': 10, 'EJ': 10, 'FJ': 10,
                         'AQ': 10, 'WQ': 10, 'EQ': 10, 'FQ': 10,
                         'AK': 10, 'WK': 10, 'EK': 10, 'FK': 10,
                         'AA': 11, 'WA': 11, 'EA': 11, 'FA': 11}


    def dealPCard(self, position):
        newCard = self.SHUFFLEDDECK.pop(0)
        self.PLAYERSCARDS.append(newCard)
        self.PLAYERSSCORE += self.CARDPOINTS[newCard]
        #print("adding score", self.CARDPOINTS[newCard])
        self.PLAYERSSCORE = self.fixAces(self.PLAYERSCARDS, self.PLAYERSSCORE)##############################################################################
        GCARD = self.GRAPHICDICT[newCard]
        GCARD.showCard(self.MAINSURF, position)

        return (self.PLAYERSSCORE)




    def dealDCard(self, position):
        newCard = self.SHUFFLEDDECK.pop(0)
        self.DEALERSCARDS.append(newCard)
        self.DEALERSSCORE += self.CARDPOINTS[newCard]

        GCARD = self.GRAPHICDICT[newCard]
        GCARD.showCard(self.MAINSURF, position)
        

        return (self.DEALERSSCORE)

    
    def fixAces(self, hand, score):
        #print(score)
        aceNum = 0
        if score > 21:
            aceNum += hand.count('EA')
            aceNum += hand.count('WA')
            aceNum += hand.count('AA')
            aceNum += hand.count('FA')

            for c in range(aceNum + 1):
                if aceNum == 0:
                    return score
                elif aceNum == 1:
                    return score - 10
                elif aceNum == c:
                    if score <= (c * 11 + 10 - c + 1):
                        score = (score - (c * 10 - 10))
                    else:
                        score = (score - (c * 10))

            return score

        else:
            return score




    def startDealerHand(self):
        self.DEALERSCARDS = []
        self.DEALERSSCORE = 0
        self.dealDCard((350, 100))
        self.dealDCard((550, 100))

        #self.fixAces(self.DEALERSCARDS, self.DEALERSSCORE)
        return (self.DEALERSCARDS, self.DEALERSSCORE)


    def startPlayerHand(self):
        self.PLAYERSCARDS = []
        self.PLAYERSSCORE = 0
        self.dealPCard((350, 375))
        self.dealPCard((550, 375))

        #self.fixAces(self.PLAYERSCARDS, self.PLAYERSSCORE)
        return (self.PLAYERSCARDS, self.PLAYERSSCORE)

#############################################################################################################################################
    #############################################################################################################################################3
    ####################################################################################################################################3
    ##############################################################################################################################3
    #####################################################################################################################################


    

class gameDisplay:
    def __init__(self, surf, width, height, cardsize):
        #DISPLAY
        self.MAINSURF = surf
        self.MAINWIDTH = width
        self.MAINHEIGHT = height
        self.CARDSIZE = cardsize
        self.SIZE = SIZE
        self.HIT = 0
        self.XLOOP = True
        self.YLOOP = False
        self.CARDBG = gCard(SIZE, self.MAINSURF, 'background', 2)

        self.CARDS = dealCards(self.MAINSURF, self.CARDSIZE)
        
        #colors
        self.GREY = (150, 150, 150)
        self.WHITE = (255, 255, 255)
        self.LTGREY = (207, 207, 207)
        self.BLACK = (0, 0, 0)
        self.RED = (255, 0, 0, 150)
        self.DKRED = (100, 0, 0)
        self.TRANSP = (0, 0, 0, 0)
        self.DKBLUE = (24, 32, 188)
        self.LTBLUE = (141, 234, 251)
        self.DKYELLOW = (255, 198, 0)
        self.LTYELLOW = (252, 241, 150)
        self.DKGREEN = (10, 136, 0)
        self.LTGREEN = (104, 207, 97)
        self.CRIMSON = (149, 3, 3)
        self.LTRED = (255, 65, 65)

        self.GRAPHICDICT = {'A2': gCard(self.SIZE, self.MAINSURF, "air", 2),
                            'A3': gCard(self.SIZE, self.MAINSURF, "air", 3),
                            'A4': gCard(self.SIZE, self.MAINSURF, "air", 4),
                            'A5': gCard(self.SIZE, self.MAINSURF, "air", 5),
                            'A6': gCard(self.SIZE, self.MAINSURF, "air", 6),
                            'A7': gCard(self.SIZE, self.MAINSURF, "air", 7),
                            'A8': gCard(self.SIZE, self.MAINSURF, "air", 8),
                            'A9': gCard(self.SIZE, self.MAINSURF, "air", 9),
                            'A10': gCard(self.SIZE, self.MAINSURF, "air", 10),
                            'AJ': gCard(self.SIZE, self.MAINSURF, "air", "J"),
                            'AQ': gCard(self.SIZE, self.MAINSURF, "air", "Q"),
                            'AK': gCard(self.SIZE, self.MAINSURF, "air", "K"),
                            'AA': gCard(self.SIZE, self.MAINSURF, "air", "A"),

                            #water
                            'W2': gCard(self.SIZE, self.MAINSURF, "water", 2),
                            'W3': gCard(self.SIZE, self.MAINSURF, "water", 3),
                            'W4': gCard(self.SIZE, self.MAINSURF, "water", 4),
                            'W5': gCard(self.SIZE, self.MAINSURF, "water", 5),
                            'W6': gCard(self.SIZE, self.MAINSURF, "water", 6),
                            'W7': gCard(self.SIZE, self.MAINSURF, "water", 7),
                            'W8': gCard(self.SIZE, self.MAINSURF, "water", 8),
                            'W9': gCard(self.SIZE, self.MAINSURF, "water", 9),
                            'W10': gCard(self.SIZE, self.MAINSURF, "water", 10),
                            'WJ': gCard(self.SIZE, self.MAINSURF, "water", "J"),
                            'WQ': gCard(self.SIZE, self.MAINSURF, "water", "Q"),
                            'WK': gCard(self.SIZE, self.MAINSURF, "water", "K"),
                            'WA': gCard(self.SIZE, self.MAINSURF, "water", "A"),

                            #earth
                            'E2': gCard(self.SIZE, self.MAINSURF, "earth", 2),
                            'E3': gCard(self.SIZE, self.MAINSURF, "earth", 3),
                            'E4': gCard(self.SIZE, self.MAINSURF, "earth", 4),
                            'E5': gCard(self.SIZE, self.MAINSURF, "earth", 5),
                            'E6': gCard(self.SIZE, self.MAINSURF, "earth", 6),
                            'E7': gCard(self.SIZE, self.MAINSURF, "earth", 7),
                            'E8': gCard(self.SIZE, self.MAINSURF, "earth", 8),
                            'E9': gCard(self.SIZE, self.MAINSURF, "earth", 9),
                            'E10': gCard(self.SIZE, self.MAINSURF, "earth", 10),
                            'EJ': gCard(self.SIZE, self.MAINSURF, "earth", "J"),
                            'EQ': gCard(self.SIZE, self.MAINSURF, "earth", "Q"),
                            'EK': gCard(self.SIZE, self.MAINSURF, "earth", "K"),
                            'EA': gCard(self.SIZE, self.MAINSURF, "earth", "A"),

                            #fire
                            'F2': gCard(self.SIZE, self.MAINSURF, "fire", 2),
                            'F3': gCard(self.SIZE, self.MAINSURF, "fire", 3),
                            'F4': gCard(self.SIZE, self.MAINSURF, "fire", 4),
                            'F5': gCard(self.SIZE, self.MAINSURF, "fire", 5),
                            'F6': gCard(self.SIZE, self.MAINSURF, "fire", 6),
                            'F7': gCard(self.SIZE, self.MAINSURF, "fire", 7),
                            'F8': gCard(self.SIZE, self.MAINSURF, "fire", 8),
                            'F9': gCard(self.SIZE, self.MAINSURF, "fire", 9),
                            'F10': gCard(self.SIZE, self.MAINSURF, "fire", 10),
                            'FJ': gCard(self.SIZE, self.MAINSURF, "fire", "J"),
                            'FQ': gCard(self.SIZE, self.MAINSURF, "fire", "Q"),
                            'FK': gCard(self.SIZE, self.MAINSURF, "fire", "K"),
                            'FA': gCard(self.SIZE, self.MAINSURF, "fire", "A")}

    def startScreen(self):
        self.MAINSURF.fill(self.DKGREEN)
        
        titleFont = pygame.font.SysFont("Sylfaen", 75)
        textSURF = titleFont.render("BLACKJACK", True, self.BLACK, None)
        self.MAINSURF.blit(textSURF, (int(self.MAINWIDTH * 0.5),int(self.MAINHEIGHT * 0.15)))
        
        self.startButton = simpleButton (250, 70, self.BLACK, self.WHITE, "START GAME",
                           self.MAINSURF, (int(self.MAINWIDTH * 0.63), int(self.MAINHEIGHT * 0.3)))
        self.startButton.displayBut()
        self.startButton.active()

    def gameBackground(self):
        self.MAINSURF.fill(self.DKGREEN)
        titleFont = pygame.font.SysFont("Sylfaen", 75)
        textSURF = titleFont.render("BLACKJACK", True, self.BLACK, None)
        self.MAINSURF.blit(textSURF, (int(self.MAINWIDTH * 0.5),int(self.MAINHEIGHT * 0.01)))

    def showPlayersCards(self):
        self.PHAND, self.PSCORE = self.CARDS.startPlayerHand()


    def showDealersCards(self):
        self.DHAND, self.DSCORE = self.CARDS.startDealerHand()

    def coverDealer(self):
        self.CARDBG.showBG(self.MAINSURF, (550, 100))
        
    def showDeck(self):
        self.CARDBG.showBG(self.MAINSURF, (825, 100))
        

    def showCards(self):
        self.showDealersCards()
        self.showPlayersCards()
        self.showDeck()

    def showScore(self):
        pygame.draw.rect(self.MAINSURF, self.DKGREEN, ((int(self.MAINWIDTH * 0.35), int(self.MAINHEIGHT * 0.1)),
                             (int(self.MAINWIDTH * 0.1), int(self.MAINHEIGHT * 0.05))))
        scoreFont = pygame.font.SysFont("Sylfaen", 45)
        textSURF = scoreFont.render("SCORE: " + str(self.PSCORE), True, self.BLACK, None)
        self.MAINSURF.blit(textSURF, (int(self.MAINWIDTH * 0.1),int(self.MAINHEIGHT * 0.1)))

    def hitButton(self):
        self.HITBUTTON = simpleButton(180, 60, self.WHITE, self.BLACK, "HIT", self.MAINSURF, (int(self.MAINWIDTH * 0.1), int(self.MAINHEIGHT * 0.16)))
        self.HITBUTTON.displayBut()
        self.HITBUTTON.active()
        

    def holdButton(self):
        self.HOLDBUTTON = simpleButton(180, 60, self.WHITE, self.BLACK, "HOLD", self.MAINSURF, (int(self.MAINWIDTH * 0.1), int(self.MAINHEIGHT * 0.24)))
        self.HOLDBUTTON.displayBut()
        self.HOLDBUTTON.active()

    def hitOrHold(self):
        self.hitButton()
        self.holdButton()

    def showDealerScore(self):
        pygame.draw.rect(self.MAINSURF, self.DKGREEN, ((int(self.MAINWIDTH * 0.08), int(self.MAINHEIGHT * 0.14)),
                        (int(self.MAINWIDTH * 0.35), int(self.MAINHEIGHT * 0.18))))
        DEALERscoreFont = pygame.font.SysFont("Sylfaen", 45)
        textSURF = DEALERscoreFont.render("DEALER: " + str(self.DSCORE), True, self.BLACK, None)
        self.MAINSURF.blit(textSURF, (int(self.MAINWIDTH * 0.1),int(self.MAINHEIGHT * 0.16)))

    def showWin(self):
        winFont = pygame.font.SysFont("Sylfaen", 45)
        textSURF = winFont.render("You Win!", True, self.CRIMSON, None)
        self.MAINSURF.blit(textSURF, (int(self.MAINWIDTH * 0.1),int(self.MAINHEIGHT * 0.23)))

    def showLose(self):
        loseFont = pygame.font.SysFont("Sylfaen", 45)
        textSURF = loseFont.render("You Lose!", True, self.CRIMSON, None)
        self.MAINSURF.blit(textSURF, (int(self.MAINWIDTH * 0.1),int(self.MAINHEIGHT * 0.23)))

    def showTie(self):
        tieFont = pygame.font.SysFont("Sylfaen", 45)
        textSURF = tieFont.render("You Tied!", True, self.CRIMSON, None)
        self.MAINSURF.blit(textSURF, (int(self.MAINWIDTH * 0.1),int(self.MAINHEIGHT * 0.23)))

    def restartButton(self):
        pygame.draw.rect(self.MAINSURF, self.DKGREEN, ((825, 100), (250, 250)))
        self.RESTARTBUTTON = simpleButton(250, 60, self.WHITE, self.BLACK, "RESTART GAME", self.MAINSURF, (int(self.MAINWIDTH * 1.2), int(self.MAINHEIGHT * 0.17)))
        self.RESTARTBUTTON.displayBut()
        self.RESTARTBUTTON.active()
        self.XLOOP = False
        self.YLOOP = True



    def moveCards(self):
        if (self.HIT == 1):
            pygame.draw.rect(self.MAINSURF, self.DKGREEN, ((0, 360),(1100, 300)))
            
            GCARD0 = self.GRAPHICDICT[self.PHAND[0]]
            GCARD0.showCard(self.MAINSURF, (250, 375))

            GCARD1 = self.GRAPHICDICT[self.PHAND[1]]
            GCARD1.showCard(self.MAINSURF, (450, 375))

            GCARD2 = self.GRAPHICDICT[self.PHAND[2]]
            GCARD2.showCard(self.MAINSURF, (650, 375))

        elif (self.HIT == 2):
            pygame.draw.rect(self.MAINSURF, self.DKGREEN, ((0, 360),(1100, 300)))
            
            GCARD0 = self.GRAPHICDICT[self.PHAND[0]]
            GCARD0.showCard(self.MAINSURF, (150, 375))

            GCARD1 = self.GRAPHICDICT[self.PHAND[1]]
            GCARD1.showCard(self.MAINSURF, (350, 375))

            GCARD2 = self.GRAPHICDICT[self.PHAND[2]]
            GCARD2.showCard(self.MAINSURF, (550, 375))

            GCARD3 = self.GRAPHICDICT[self.PHAND[3]]
            GCARD3.showCard(self.MAINSURF, (750, 375))

        elif (self.HIT == 3):
            pygame.draw.rect(self.MAINSURF, self.DKGREEN, ((0, 360),(1100, 300)))
            
            GCARD0 = self.GRAPHICDICT[self.PHAND[0]]
            GCARD0.showCard(self.MAINSURF, (50, 375))

            GCARD1 = self.GRAPHICDICT[self.PHAND[1]]
            GCARD1.showCard(self.MAINSURF, (250, 375))

            GCARD2 = self.GRAPHICDICT[self.PHAND[2]]
            GCARD2.showCard(self.MAINSURF, (450, 375))

            GCARD3 = self.GRAPHICDICT[self.PHAND[3]]
            GCARD3.showCard(self.MAINSURF, (650, 375))

            GCARD4 = self.GRAPHICDICT[self.PHAND[4]]
            GCARD4.showCard(self.MAINSURF, (850, 375))

        elif (self.HIT == 4):
            pygame.draw.rect(self.MAINSURF, self.DKGREEN, ((0, 360),(1100, 300)))
            
            GCARD0 = self.GRAPHICDICT[self.PHAND[0]]
            GCARD0.showCard(self.MAINSURF, (0, 375))

            GCARD1 = self.GRAPHICDICT[self.PHAND[1]]
            GCARD1.showCard(self.MAINSURF, (160, 375))

            GCARD2 = self.GRAPHICDICT[self.PHAND[2]]
            GCARD2.showCard(self.MAINSURF, (320, 375))

            GCARD3 = self.GRAPHICDICT[self.PHAND[3]]
            GCARD3.showCard(self.MAINSURF, (480, 375))

            GCARD4 = self.GRAPHICDICT[self.PHAND[4]]
            GCARD4.showCard(self.MAINSURF, (640, 375))

            GCARD5 = self.GRAPHICDICT[self.PHAND[5]]
            GCARD5.showCard(self.MAINSURF, (800, 375))

        elif (self.HIT == 5):
            pygame.draw.rect(self.MAINSURF, self.DKGREEN, ((0, 360),(1100, 300)))
            
            GCARD0 = self.GRAPHICDICT[self.PHAND[0]]
            GCARD0.showCard(self.MAINSURF, (0, 375))

            GCARD1 = self.GRAPHICDICT[self.PHAND[1]]
            GCARD1.showCard(self.MAINSURF, (160, 375))

            GCARD2 = self.GRAPHICDICT[self.PHAND[2]]
            GCARD2.showCard(self.MAINSURF, (320, 375))

            GCARD3 = self.GRAPHICDICT[self.PHAND[3]]
            GCARD3.showCard(self.MAINSURF, (480, 375))

            GCARD4 = self.GRAPHICDICT[self.PHAND[4]]
            GCARD4.showCard(self.MAINSURF, (640, 375))

            GCARD5 = self.GRAPHICDICT[self.PHAND[5]]
            GCARD5.showCard(self.MAINSURF, (800, 375))

            GCARD6 = self.GRAPHICDICT[self.PHAND[6]]
            GCARD6.showCard(self.MAINSURF, (960, 375))

                  
    def hitStart(self):
        while (self.XLOOP == True):
            for event in pygame.event.get():
                if event.type == QUIT:
                    pygame.quit()
                    sys.exit()
                if event.type == MOUSEBUTTONDOWN:
                    mouseXY = pygame.mouse.get_pos()
                    if self.startButton.clicked(mouseXY):
                        self.startButton.inActive()
                        self.gameBackground()
                        self.showCards()
                        self.coverDealer()
                        self.showScore()
                        self.hitOrHold()                        
                    elif self.HITBUTTON.clicked(mouseXY):
                        if (self.PSCORE <= 21):
                            #print (self.HIT)
                            self.HIT = self.HIT + 1
                            #print (self.HIT)
                            self.PSCORE = self.CARDS.dealPCard((0, 375))
                            #print (self.PHAND)
                            #print ("hit")
                            self.showScore()
                            self.moveCards()
                            if(self.PSCORE > 21):
                                self.HIT = 0
                                self.HITBUTTON.inActive()
                                self.showDealerScore()
                                GDCARD = self.GRAPHICDICT[self.DHAND[1]]
                                GDCARD.showCard(self.MAINSURF, (550, 100))
                                self.showLose()
                                
#                                print(self.HIT)
                                self.restartButton()
                                
                                

                    elif self.HOLDBUTTON.clicked(mouseXY):
                        self.HITBUTTON.inActive()
                        self.HOLDBUTTON.inActive()
                        self.showDealerScore()
                        GDCARD = self.GRAPHICDICT[self.DHAND[1]]
                        GDCARD.showCard(self.MAINSURF, (550, 100))
                        self.restartButton()
                        if (self.PSCORE <= 21) and (self.PSCORE > self.DSCORE):
                            self.showWin()      
                            self.restartButton()
                        elif (self.PSCORE <= 21) and (self.PSCORE < self.DSCORE):
                            self.showLose()
                            self.restartButton()
                        elif (self.PSCORE > 21):
                            self.showLose()
                            self.restartButton()
                        elif (self.PSCORE == self.DSCORE):
                            self.showTie()
                            self.restartButton()

            pygame.display.update()

            

    def restartGame(self):#######################################################################################################3
        while (self.YLOOP == True):
            for event in pygame.event.get():
                if event.type == QUIT:
                    pygame.quit()
                    sys.exit()
                elif event.type == MOUSEBUTTONDOWN:
                    mouseXY = pygame.mouse.get_pos()
                    if self.RESTARTBUTTON.clicked(mouseXY):
                        pygame.draw.rect(self.MAINSURF, self.RED, ((825, 100), (250, 250)))
                        self.startScreen()
                        self.hitStart()
                        self.YLOOP = False

            pygame.display.update()
                        




def main():
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()

        game = gameDisplay(DISPLAYSURF, DISPLAYWIDTH, DISPLAYHEIGHT, SIZE)
        game.startScreen()
        game.hitStart()
        game.restartGame()

        
        pygame.display.update()

main()



