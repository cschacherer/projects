#Yahtzee Game
#Conner Schacherer

import pygame, sys
from pygame.locals import *
import random

pygame.init()

class gDie:

    def __init__(self, surf, size, value):
        self.SIZE = size
        self.RADIUS = SIZE//10
        self.dieSURF = surf
        self.dieSURF = pygame.Surface((SIZE, SIZE), flags=SRCALPHA, depth=32)#put SIZE in for the 200, 200
        self.dieSURF.fill(TRANSP)
        self.LOCKED = False
        self.VALUE = value

        pygame.draw.circle(self.dieSURF, BLACK, (int(self.SIZE * 0.1), int(self.SIZE * 0.1)), self.RADIUS)
        pygame.draw.circle(self.dieSURF, BLACK, (int(self.SIZE * 0.9), int(self.SIZE * 0.1)), self.RADIUS)
        pygame.draw.circle(self.dieSURF, BLACK, (int(self.SIZE * 0.9), int(self.SIZE * 0.9)), self.RADIUS)
        pygame.draw.circle(self.dieSURF, BLACK, (int(self.SIZE * 0.1), int(self.SIZE * 0.9)), self.RADIUS)

        pygame.draw.rect(self.dieSURF, BLACK, Rect((int(self.SIZE * 0.1), 0), (int(self.SIZE * 0.8), self.SIZE)))
        pygame.draw.rect(self.dieSURF, BLACK, Rect((0, int(self.SIZE * 0.1)), (SIZE, int(self.SIZE * 0.8))))

    def setValue(self, value):
        self.VALUE = value
        pygame.draw.circle(self.dieSURF, BLACK, (int(self.SIZE * 0.1), int(self.SIZE * 0.1)), self.RADIUS)
        pygame.draw.circle(self.dieSURF, BLACK, (int(self.SIZE * 0.9), int(self.SIZE * 0.1)), self.RADIUS)
        pygame.draw.circle(self.dieSURF, BLACK, (int(self.SIZE * 0.9), int(self.SIZE * 0.9)), self.RADIUS)
        pygame.draw.circle(self.dieSURF, BLACK, (int(self.SIZE * 0.1), int(self.SIZE * 0.9)), self.RADIUS)

        pygame.draw.rect(self.dieSURF, BLACK, Rect((int(self.SIZE * 0.1), 0), (int(self.SIZE * 0.8), self.SIZE)))
        pygame.draw.rect(self.dieSURF, BLACK, Rect((0, int(self.SIZE * 0.1)), (SIZE, int(self.SIZE * 0.8))))
        
        if (value == 1):
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.5)), (int(SIZE * 0.5))), self.RADIUS)
        elif (value == 2):
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.25)), (int(SIZE * 0.25))), self.RADIUS)#2
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.75)), (int(SIZE * 0.75))), self.RADIUS)
        elif (value == 3):
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.5)), (int(SIZE * 0.5))), self.RADIUS) #1
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.25)), (int(SIZE * 0.25))), self.RADIUS)#2
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.75)), (int(SIZE * 0.75))), self.RADIUS) #7
        elif (value == 4):
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.25)), (int(SIZE * 0.25))), self.RADIUS)#2
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.25)), (int(SIZE * 0.75))), self.RADIUS)#4
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.75)), (int(SIZE * 0.25))), self.RADIUS) #5
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.75)), (int(SIZE * 0.75))), self.RADIUS) #7
        elif (value == 5):
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.5)), (int(SIZE * 0.5))), self.RADIUS) #1
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.25)), (int(SIZE * 0.25))), self.RADIUS)#2
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.25)), (int(SIZE * 0.75))), self.RADIUS)#4
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.75)), (int(SIZE * 0.25))), self.RADIUS) #5
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.75)), (int(SIZE * 0.75))), self.RADIUS)
        elif (value == 6):
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.25)), (int(SIZE * 0.25))), self.RADIUS)#2
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.25)), (int(SIZE * 0.5))), self.RADIUS) #3
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.25)), (int(SIZE * 0.75))), self.RADIUS) #4
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.75)), (int(SIZE * 0.25))), self.RADIUS) #5
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.75)), (int(SIZE * 0.5))), self.RADIUS) #6
            pygame.draw.circle(self.dieSURF, WHITE, ((int(SIZE * 0.75)), (int(SIZE * 0.75))), self.RADIUS) #7


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
        self.THEIGHT  = int(self.HEIGHT * .60)

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


class holdDie:

    def __init__(self, color, size, surf, position):
        self.COLOR = color
        self.HOLDSIZE = size * 1.05
        self.SURF = surf
        self.RADIUS = size//10
        self.POSITION = position

        self.HOLDSURF = pygame.Surface((self.HOLDSIZE, self.HOLDSIZE), flags=SRCALPHA, depth=32)#put SIZE in for the 200, 200
        self.HOLDSURF.fill(TRANSP)

        pygame.draw.circle(self.HOLDSURF, self.COLOR, (int(self.HOLDSIZE * 0.1), int(self.HOLDSIZE * .1)), self.RADIUS)
        pygame.draw.circle(self.HOLDSURF, self.COLOR, (int(self.HOLDSIZE * 0.9), int(self.HOLDSIZE * 0.1)), self.RADIUS)
        pygame.draw.circle(self.HOLDSURF, self.COLOR, (int(self.HOLDSIZE * 0.9), int(self.HOLDSIZE * 0.9)), self.RADIUS)
        pygame.draw.circle(self.HOLDSURF, self.COLOR, (int(self.HOLDSIZE * 0.1), int(self.HOLDSIZE * 0.9)), self.RADIUS)
        

        pygame.draw.rect(self.HOLDSURF, self.COLOR, Rect((int(self.HOLDSIZE * 0.1), 0), (int(self.HOLDSIZE * 0.8), self.HOLDSIZE)))
        pygame.draw.rect(self.HOLDSURF, self.COLOR, Rect((0, int(self.HOLDSIZE * 0.1)), (self.HOLDSIZE, int(self.HOLDSIZE * 0.8))))


        self.SURF.blit(self.HOLDSURF, self.POSITION)
  

#set up colors
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

#GLOBAL VARIABLES
SIZE = 150

displayWIDTH = 1300
displayHEIGHT = 600

DISPLAYSURF = pygame.display.set_mode((displayWIDTH, displayHEIGHT))
pygame.display.set_caption('Yahtzee')
DISPLAYSURF.fill(DKGREEN)

dieSURF = pygame.Surface((SIZE, SIZE), flags=SRCALPHA, depth=32)
dieSURF.fill(TRANSP)

#create die
d1 = gDie(dieSURF, SIZE, random.randint(1,6))
d2 = gDie(dieSURF, SIZE, random.randint(1,6))
d3 = gDie(dieSURF, SIZE, random.randint(1,6))
d4 = gDie(dieSURF, SIZE, random.randint(1,6))
d5 = gDie(dieSURF, SIZE, random.randint(1,6))

dieList = []

#create hold buttons
diceHOLD1 = simpleButton(SIZE, SIZE, TRANSP, TRANSP, " ", DISPLAYSURF, (int(displayWIDTH * 0.07),int(displayHEIGHT * 0.25)))
diceHOLD2 = simpleButton(SIZE, SIZE, TRANSP, TRANSP, " ", DISPLAYSURF, (int(displayWIDTH * 0.25),int(displayHEIGHT * 0.25)))
diceHOLD3 = simpleButton(SIZE, SIZE, TRANSP, TRANSP, " ", DISPLAYSURF, (int(displayWIDTH * 0.42),int(displayHEIGHT * 0.25)))
diceHOLD4 = simpleButton(SIZE, SIZE, TRANSP, TRANSP, " ", DISPLAYSURF, (int(displayWIDTH * 0.60),int(displayHEIGHT * 0.25)))
diceHOLD5 = simpleButton(SIZE, SIZE, TRANSP, TRANSP, " ", DISPLAYSURF, (int(displayWIDTH * 0.77),int(displayHEIGHT * 0.25)))

#roll buttons
r1 = simpleButton(250, 75, BLACK, WHITE, "First Roll", DISPLAYSURF, (int(displayWIDTH * 0.385), int(displayHEIGHT * 0.633)))
r2 = simpleButton(250, 75, BLACK, WHITE, "Second Roll", DISPLAYSURF, (int(displayWIDTH * 0.385), int(displayHEIGHT * 0.633)))
r3 = simpleButton(250, 75, BLACK, WHITE, "Third Roll", DISPLAYSURF, (int(displayWIDTH * 0.385), int(displayHEIGHT * 0.633)))





def title():   
    titleFont = pygame.font.SysFont("Sylfaen", 100)
    textSURF = titleFont.render("YAHTZEE", True, WHITE, None)
    DISPLAYSURF.blit(textSURF, (int(displayWIDTH * 0.308),int(displayHEIGHT * 0.058)))

    
def scoreText(points, color):
    scoreFont = pygame.font.SysFont("Sylfaen", 50)
    scoreSURF = scoreFont.render("Score: " + str(points), True, color, None)
    DISPLAYSURF.blit(scoreSURF, (500, 500))

def valueText(value):
    valueFont = pygame.font.SysFont("Sylfaen", 50)
    valueSURF = valueFont.render(str(value), True, WHITE, None)
    DISPLAYSURF.blit(valueSURF, (630, 500))

def holdText():
    holdFont = pygame.font.SysFont("Sylfaen", 25)
    holdSURF = holdFont.render("Click on die to hold it", True, WHITE, None)
    DISPLAYSURF.blit(holdSURF, (int(displayWIDTH * 0.4),int(displayHEIGHT * 0.53)))
    
  


        
def score(dice, points):
    counts = [0]*7 
    for value in dice:
         counts[value] = counts[value] + 1 
         #print (counts)

    if 5 in counts:
        points += 30
        #print(points)
        return (str(points) + "    Five of a Kind" )
    elif 4 in counts:
        points += 20
        #print(points)
        return (str(points) + "    Four of a Kind")
    elif (3 in counts) and (2 in counts):
        points += 15
        #print(points)
        return (str(points) + "    Full House")
    elif 3 in counts:
        points += 10
        #print(points)
        return (str(points) + "    Three of a Kind")
    elif not (2 in counts):
        points += 25
        #print(points)
        return (str(points) + "    Straight")
    elif (counts.count(2) == 2):
        points += 8
        #print(points)
        return (str(points) + "    Two Pairs")
    else:
        #print(points)
        return (str(points) + "    No Score")


def roll(d1, d2, d3, d4, d5):  
    if d1.LOCKED == False:
        d1.setValue(random.randint(1,6))
    if d2.LOCKED == False:
        d2.setValue(random.randint(1,6))
    if d3.LOCKED == False:
        d3.setValue(random.randint(1,6))
    if d4.LOCKED == False:
        d4.setValue(random.randint(1,6))
    if d5.LOCKED == False:
        d5.setValue(random.randint(1,6))

    global dieList
    dieList = [d1.VALUE, d2.VALUE, d3.VALUE, d4.VALUE, d5.VALUE]
    

def green():
    pygame.draw.rect(DISPLAYSURF, DKGREEN, Rect((625, 500), (650, 550)))


def main():
    r1.displayBut()
    
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == MOUSEBUTTONDOWN:
                mouseXY = pygame.mouse.get_pos()
                if r1.clicked(mouseXY):
                    POINTS = 100
                    r1.active()
                    roll(d1, d2, d3, d4, d5)
                    POINTS -= 10
                    #print(POINTS)
                    scoreText(POINTS, WHITE)
                elif r2.clicked(mouseXY):
                    green()
                    POINTS = 100
                    r2.active()
                    roll(d1, d2, d3, d4, d5)
                    POINTS -= 20
                    #print(POINTS)
                    scoreText(POINTS, WHITE)
                elif r3.clicked(mouseXY):
                    green()
                    POINTS = 100
                    r3.active()
                    roll(d1, d2, d3, d4, d5)
                    POINTS -= 30
                    #print(POINTS)
                    #scoreText(POINTS, WHITE)
                    
                    diceHOLD1.inActive()
                    diceHOLD2.inActive()
                    diceHOLD3.inActive()
                    diceHOLD4.inActive()
                    diceHOLD5.inActive()
                    
                    #print(score(dieList, POINTS))
                    valueText(score(dieList, POINTS))
                    
                elif diceHOLD1.clicked(mouseXY):
                    diceHOLD1.active() 
                    if d1.LOCKED == True:
                        d1.LOCKED = False
                        holdDie(DKGREEN, (int(SIZE * 1.1)), DISPLAYSURF, (int(displayWIDTH * 0.062), int(displayHEIGHT * 0.23)))
                    else:
                        d1.LOCKED = True
                        holdDie(RED, (int(SIZE * 1.1)), DISPLAYSURF, (int(displayWIDTH * 0.062), int(displayHEIGHT * 0.23)))    
                    
                elif diceHOLD2.clicked(mouseXY):
                    diceHOLD2.active()
                    if d2.LOCKED == True:
                        d2.LOCKED = False
                        holdDie(DKGREEN, (int(SIZE * 1.1)), DISPLAYSURF, (int(displayWIDTH * 0.242), int(displayHEIGHT * 0.23)))
                    else:
                        d2.LOCKED = True
                        holdDie(RED, (int(SIZE * 1.1)), DISPLAYSURF, (int(displayWIDTH * 0.242), int(displayHEIGHT * 0.23)))
                        
                elif diceHOLD3.clicked(mouseXY):
                    diceHOLD3.active()
                    if d3.LOCKED == True:
                        d3.LOCKED = False
                        holdDie(DKGREEN, (int(SIZE * 1.1)), DISPLAYSURF, (int(displayWIDTH * 0.412), int(displayHEIGHT * 0.23)))
                    else:
                        d3.LOCKED = True
                        holdDie(RED, (int(SIZE * 1.1)), DISPLAYSURF, (int(displayWIDTH * 0.412), int(displayHEIGHT * 0.23)))

                elif diceHOLD4.clicked(mouseXY):
                    diceHOLD4.active()
                    if d4.LOCKED == True:
                        d4.LOCKED = False
                        holdDie(DKGREEN, (int(SIZE * 1.1)), DISPLAYSURF, (int(displayWIDTH * 0.592), int(displayHEIGHT * 0.23)))
                    else:
                        d4.LOCKED = True
                        holdDie(RED, (int(SIZE * 1.1)), DISPLAYSURF, (int(displayWIDTH * 0.592), int(displayHEIGHT * 0.23)))
                        
                elif diceHOLD5.clicked(mouseXY):
                    diceHOLD5.active()
                    if d5.LOCKED == True:
                        d5.LOCKED = False
                        holdDie(DKGREEN, (int(SIZE * 1.1)), DISPLAYSURF, (int(displayWIDTH * 0.762), int(displayHEIGHT * 0.23)))
                    else:
                        d5.LOCKED = True
                        holdDie(RED, (int(SIZE * 1.1)), DISPLAYSURF, (int(displayWIDTH * 0.762), int(displayHEIGHT * 0.23)))

            if event.type == MOUSEBUTTONUP:
                if r1.clicked(mouseXY):
                    r2.displayBut()
                    r1.inActive()
                    r2.active()
                elif r2.clicked(mouseXY):
                    r3.displayBut()
                    r2.inActive()
                    r3.active()
                elif r3.clicked(mouseXY):
                    r3.inActive()
                   
        title()
        holdText()

        
        DISPLAYSURF.blit(d1.dieSURF, (int(displayWIDTH * 0.07),int(displayHEIGHT * 0.25)))
        DISPLAYSURF.blit(d2.dieSURF, (int(displayWIDTH * 0.25),int(displayHEIGHT * 0.25)))
        DISPLAYSURF.blit(d3.dieSURF, (int(displayWIDTH * 0.42),int(displayHEIGHT * 0.25)))
        DISPLAYSURF.blit(d4.dieSURF, (int(displayWIDTH * 0.60),int(displayHEIGHT * 0.25)))
        DISPLAYSURF.blit(d5.dieSURF, (int(displayWIDTH * 0.77),int(displayHEIGHT * 0.25)))


        
        pygame.display.update()



#RUNNING GAME        
main()

                    
                    
                  
                    
        
        
    

