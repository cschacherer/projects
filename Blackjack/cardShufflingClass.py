#Conner Schacherer

import pygame
from pygame.locals import *
from random import *
import random

pygame.init()

class cards:

    def __init__(self):
     
        self.DECK = 3

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

        

    def shuffleCARDS(self):

        numcards = self.CARDLIST * self.DECK

        cardlength = len(numcards) 
        shuffled_cards =[]

        while(cardlength > 0):
            cardCount = random.randrange (0, (cardlength))
            shuffled_cards.append(numcards[cardCount])
            
            del numcards [cardCount]
            cardlength = len(numcards)

        return (shuffled_cards)
