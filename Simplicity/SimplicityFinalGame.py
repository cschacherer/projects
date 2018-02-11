#Steven Malecki
#SIMPLICITY GAME

import pygame
import pygame, sys
from pygame.locals import *
from random import *
from random import randint
from WallClass import wall
from shapeRandomizer import randomizer
from makeShapesClass import makeShapes
from playerClass import player
from scoreClass import score
from textClass import text

pygame.init()
pygame.mixer.init(frequency=22050, size=-16, channels=2, buffer=4096)

GREEN = (0,255,0)
DGREEN = (0, 100, 0)
BLUE = (50,50,255)
DBLUE = (0,0,100)
RED = (255,50,50)
DRED = (100,0,0)
BLACK = (50,50,50)
WHITE = (255, 255, 255)
GREY = (126, 126, 126)
PURPLE = (70,0,70)
TRNSP = (0, 0, 0, 0)

SWIDTH = 1080
SHEIGHT = 720
ShapeSize = 50
WWIDTH = SWIDTH // 8
FPS = 120

#StartMenu = pygame.image.load('simplicitystart.png')
#gameOver = pygame.image.load('simplicitygameover.png')

LanePos = [20, 100, 180, 260, 340, 420, 500, 580, 660]


DISPLAYSURF = pygame.display.set_mode((SWIDTH, SHEIGHT), 0, 32)
pygame.display.set_caption('SIMPLICITY')

#Define class shortcuts
w = wall(SWIDTH, SHEIGHT)
p = player(DISPLAYSURF, RED)
s = randomizer(ShapeSize, DISPLAYSURF, SHEIGHT, SWIDTH, RED)
score = score(DISPLAYSURF, SHEIGHT, SWIDTH, WHITE, BLACK)
text = text(DISPLAYSURF)

#Sound
music = pygame.mixer.Sound("music.wav")
pickupSound = pygame.mixer.Sound("pickupSound.wav")


def main():
    
    RoundNum = 0
    wNum = 0
    pNum = 0
    points = 0
    GAMESTATE = 0
    key = 0
    clock = pygame.time.Clock()
    WX = SWIDTH
    WY = 0

    a = 0

    PPOS = SWIDTH #PICKUP STARTING POINT
    WX = SWIDTH + 400 #WALL STARTING POINT

    s.shuffleShapes(pNum)#MAKE PICKUP
    s.secondShuffle(wNum) #MAKE WALL SHAPES

    music.play(loops = -1)
    
    while True:
        
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
                
        if GAMESTATE == 0:
            DISPLAYSURF.fill(WHITE)
            startGame = pygame.Surface((SWIDTH, SHEIGHT), flags=0, depth=32)
            startGame.fill(WHITE)
            title = text.title(BLACK)
            startGame.blit(title, (300, 300))
            cred, names = text.credits(BLACK)
            startGame.blit(cred, (50, 50))
            startGame.blit(names, (50, 85))
            inst1, inst2, inst3 = text.gameInstruc(BLACK)
            startGame.blit(inst2, (350, 430))
            startGame.blit(inst3, (350, 475))
            startGame.blit(inst1, (400, 530))
            menuInst = text.menuInstruc(BLACK)
            startGame.blit(menuInst, (400, 580))
            startGame.set_alpha(a)
            a += 1
            DISPLAYSURF.blit(startGame, (0,0))
            if event.type == KEYDOWN:
                if event.key == K_RETURN: #Start Game
                    GAMESTATE += 1
            
        
        if GAMESTATE == 1:        
            DISPLAYSURF.fill(WHITE)
            DISPLAYSURF.blit(w.wallSURF, (WX, WY))
            DISPLAYSURF.blit(p.playerSURF, (p.pX, p.pY))
            score.showPoints(points)
            clock.tick(FPS)
            if (PPOS <= -200): #REMAKE PICKUPS
                PPOS = SWIDTH
                s.shuffleShapes(pNum)
            elif (WX <= -200): #REMAKE WALL SHAPES
                WX = SWIDTH
                s.secondShuffle(wNum)
                
            s.showShuffledShapes(PPOS)#SHOW PICKUP
            s.showSecondShuffle(WX)#SHOW WALL

            PPOS -= 2.5 + (wNum * 0.025) #INCREASING PICKUP SPEED
            WX -= 2.5 + (wNum * 0.025) #INCREASING WALL SPEED
            points += 1
            
            if p.pX >= PPOS and p.pX < PPOS + 50:
                p.pickupCollision(s)
                pNum += 0.25
                if not s.getShape(str(p.pY), "pickup") == "none":
                    pickupSound.play(loops=0)
                    points += 500
                    pointText = text.pointBurst(500, BLACK)
                    x = p.pX - 25
                    y = p.pY - 25
                    DISPLAYSURF.blit(pointText, (x,y))
            if p.pX >= WX and p.pX < WX + 50:
                result = p.wallCollision(s)
                if result == "pass":
                    pickupSound.play(loops=0)
                    wNum += 0.25
                    points += 1000
                    pointText = text.pointBurst(1000, BLACK)
                    x = p.pX - 25
                    y = p.pY - 25
                    DISPLAYSURF.blit(pointText, (x,y))
                if result == "fail": #Lose and send to End Game
                    a = 0
                    GAMESTATE += 1

            if event.type == KEYDOWN and key == 0:
                if event.key == K_UP:
                    p.positionUp()
                    key += 1
                elif event.key == K_DOWN:
                    p.positionDown()
                    key += 1
            if event.type == KEYUP and key == 1:
                if event.key == K_UP:
                    key -= 1
                elif event.key == K_DOWN:
                    key -= 1

        if GAMESTATE == 2:
            endGame = pygame.Surface((SWIDTH, SHEIGHT), flags=0, depth=32)
            endGame.fill((255,255,255))
            gameOver = text.gameOver(BLACK)
            endGame.blit(gameOver, (300, 400))
            instructions = text.instructions(BLACK)
            endGame.blit(instructions, (300, 550))
            finalScore = text.finalScore(points, BLACK)
            endGame.blit(finalScore, (100, 300))
            endGame.set_alpha(a)
            a += 1
            DISPLAYSURF.blit(endGame, (0,0))
            if event.type == KEYDOWN:
                if event.key == K_SPACE: #Go back to Start Menu
                    RoundNum = 0
                    wNum = 0
                    pNum = 0
                    GAMESTATE = 0
                    WX = SWIDTH
                    WY = 0
                    p.pY = 340
                    p.changeShape("circle")

                    a = 0
    
                    PPOS = SWIDTH #PICKUP STARTING POINT
                    WX = SWIDTH + 400 #WALL STARTING POINT

                    s.shuffleShapes(pNum)#MAKE PICKUP
                    s.secondShuffle(wNum) #MAKE WALL SHAPES
                
                if event.key == K_RETURN: 
                    RoundNum = 0
                    wNum = 0
                    pNum = 0
                    GAMESTATE = 0
                    WX = SWIDTH
                    WY = 0
                    p.pY = 340
                    p.changeShape("circle")

                    a = 0
                    
                    PPOS = SWIDTH #PICKUP STARTING POINT
                    WX = SWIDTH + 400 #WALL STARTING POINT

                    s.shuffleShapes(pNum)#MAKE PICKUP
                    s.secondShuffle(wNum) #MAKE WALL SHAPES
            
        pygame.display.update()

if __name__ == "__main__": main()
