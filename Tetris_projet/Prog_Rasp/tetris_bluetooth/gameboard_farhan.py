import pygame
import random
#BLACK = (0, 0, 0)
#WHITE = (255, 255, 255)
# RED = (255, 0, 0)
# GREEN = (0, 255, 0)
#BLUE = (0, 0, 255)
# ORANGE = (255, 128, 0)
# YELLOW = (255, 255, 0)
# PINK = (255, 0, 127)

BLACK = (40, 42, 54)
WHITE = (248, 248, 242)
RED = (255, 85, 85)
GREEN = (80, 250, 123)
BLUE = (139, 233, 253)
BBLUE = (98, 114, 164)
ORANGE = (255, 184, 108)
YELLOW = (241, 250, 140)
PINK = (255, 121, 198)
GREY = (68, 71, 90)
NBLEU = (0, 128 ,255)

AllColours = [BLUE, BLUE, BLUE, BLUE, WHITE, WHITE, WHITE, WHITE]
pygame.init()
linesound = pygame.mixer.Sound('clearline.wav')
#line = pygame.mixer.Sound('ligne.mp3')
#yahoo = pygame.mixer.Sound('yeahoo.mp3')
#wow = pygame.mixer.Sound('wow.mp3')
#wow2 = pygame.mixer.Sound('wow_2.mp3')
#applause = pygame.mixer.Sound('applause.mp3')
pygame.mixer.music.set_volume(2)
gameboard_width = 12
gameboard_height = 20
activeBoardSpot = [[0 for y in range(gameboard_height)] for x in range(gameboard_width)]
activeBoardColour = [[0 for y in range(gameboard_height)] for x in range(gameboard_width)]

class Gameboard():
    def __init__(self, colour, blocksize):
        self.colour = colour
        self.multiplier = blocksize
        self.score = 0
        self.lines = 0
        self.tempTracker = 0
        self.levelTracker = 1
        self.numslowtime = 0
        self.numslowtimeon = False
        self.numswap = 0
        self.swapshape = False
        self.linescounter = 0
        self.shakescreen = False
        for i in range(gameboard_width):
            for j in range(gameboard_height):
                activeBoardSpot[i][j] = False
                activeBoardColour[i][j] = BLACK

    def draw(self, screen):
        pygame.draw.rect(screen, GREY, [0, 0, gameboard_width * self.multiplier, gameboard_height * self.multiplier], 0)
        for i in range(gameboard_width):
            for j in range(gameboard_height):
                if activeBoardSpot[i][j]:
                    pygame.draw.rect(screen, activeBoardColour[i][j], [i * self.multiplier, j * self.multiplier, self.multiplier -1, self.multiplier -1], 0)



    def checkLoss(self):
        for i in range(gameboard_width):
            if activeBoardSpot[i][0]:
                return True
        return False

    def isCompleteLine(self, rownum):
        for i in range(gameboard_width):
            if activeBoardSpot[i][rownum] == False:
                return False
        return True
    def drawshake(self, screen):
        normalwidth = gameboard_width * self.multiplier
        normalheight = gameboard_height * self.multiplier
        shakeamount = 10
        shakecounter = 0
        while self.shakescreen:
            pygame.draw.rect(screen, GREY,[0, 0, normalwidth+ shakeamount, normalheight + shakeamount], 5)
            for i in range(gameboard_width):
                for j in range(gameboard_height):
                    Colour = AllColours[random.randrange(7)]
                    pygame.draw.rect(screen, Colour, [i * self.multiplier, j *self.multiplier, self.multiplier -1, self.multiplier -1], 0)
            pygame.display.flip()
            if shakeamount%5 == 0:
                if shakeamount == 10:
                    shakeamount = -shakeamount

            if shakecounter > 100:
                self.shakescreen = False

            shakecounter += 1


    def clearLine(self):
        for j in range(gameboard_height):
            if self.isCompleteLine(j): # is a row is complete
                self.linescounter += 1
                #linesound.play()
                #line.play()
                self.lines += 1
                self.tempTracker += 1
                if self.tempTracker == 5:
                    self.numswap += 1
                if self.tempTracker%4 == 0:
                    self.shakescreen = True
                    #wow.play()
                if self.tempTracker == 10:
                    self.numswap += 1
                    self.levelTracker += 1
                    self.numslowtime += 1
                    self.tempTracker = 0
                for c in range(j, 1, -1):
                    for i in range(gameboard_width): # giving current fow the same value as above
                        activeBoardSpot[i][c] = activeBoardSpot[i][c - 1]
                        activeBoardColour[i][c] = activeBoardColour[i][c -1]
                for r in range(gameboard_width):
                    activeBoardSpot[r][0] = False
                    activeBoardColour[r][0] = BLACK
        if self.isCompleteLine:
            if self.linescounter == 1:
                self.score += 50
                #line.play()
                linesound.play()
                self.linescounter = 0
            elif self.linescounter == 2:
                self.score += 100
                #wow.play()
                linesound.play()
                self.linescounter = 0
            elif self.linescounter == 3:
                self.score += 150
                #wow2.play()
                linesound.play()
                self.linescounter = 0
            elif self.linescounter == 4:
                self.score += 200
                #yahoo.play()
                self.linescounter = 0
                linesound.play()

