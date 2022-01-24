# getting function from library
import pygame
import time
import os

from pygame.constants import FULLSCREEN
from Block_farhan import Block
from shape_farhan import Shape
from gameboard_farhan import *
import sys

from pynput.keyboard import Key, Controller

keyboard = Controller()

cmd2='python3 blu_key.py &'
os.system(cmd2)
    
# colours
#BLACK = (0, 0, 0)
#WHITE = (255, 255, 255)
#RED = (255, 0, 0)
#GREEN = (0, 255, 0)
#BLUE = (0, 0, 255)
#ORANGE = (255, 128, 0)
#YELLOW = (255, 255, 0)
#PINK = (255, 0, 127)

BLACK = (40, 42, 54)
WHITE = (255, 255, 255)
RED = (255, 85, 85)
GREEN = (80, 250, 123)
BBLUE = (98, 114, 164)
BLUE = (139, 233, 253)
ORANGE = (255, 184, 108)
YELLOW = (241, 250, 140)
PINK = (255, 121, 198)
NBLEU = (0, 128, 255)
PURPLE = (189, 147, 249)


if __name__ == "__main__":
# initalize the game engine
    
    pygame.init()
    
    started = False
    # playing music
    pygame.mixer.init()
    pygame.mixer.music.load('tetris_trance.mp3')
    pygame.mixer.music.play(-1)
    pygame.mixer.music.set_volume(0.05)
# making window
    size = (800, 600)
    screen = pygame.display.set_mode(size)
    #screen = pygame.display.set_mode((800,600), pygame.FULLSCREEN,32)
# setting caption
    pygame.display.set_caption('TETRIS^3')
    shape = Shape()
    nextshape = Shape()
    gameboard = Gameboard(WHITE, 25)
    done = False
    delay = 0
    score = 0
    myfont = pygame.font.SysFont('Early GameBoy', 20)     # modification police interface
    myfont1 = pygame.font.SysFont('Fira Mono', 50)  # modification police nom du joueur
    myfont3 = pygame.font.SysFont('Early GameBoy', 100)
    slowtimedelay = 0
    leftKey = False
    rightKey = False
    downKey = False
    name = ""
    namelist = [0 for i in range(5)]
    scorelist = [0 for y in range(5)]
    HSFile = open("highscores.txt", "r")
    for i in range(5):
        namelist[i] = HSFile.readline().rstrip("\n")
    for y in range(5):
        scorelist[y] = HSFile.readline().rstrip('\n')
    HSFile.close()
    paused = False
    holding = False
    changehold = False
    holdshape = None


def checkhighscores():
    newHS = False
    tempnamelist = [0 for y in range(5)]
    tempscorelist = [0 for y in range(5)]
    for i in range(5):
        if gameboard.score > int(scorelist[i]) and newHS == False:
            newHS = True
            tempscorelist[i] = gameboard.score
            tempnamelist[i] = name
        elif newHS == True:
            tempscorelist[i] = scorelist[i -1]
            tempnamelist[i] = namelist[i -1]
        else:
            tempscorelist[i] = scorelist[i]
            tempnamelist[i] = namelist[i]

    for i in range(5):
        scorelist[i] = tempscorelist[i]
        namelist[i] = tempnamelist[i]

    HSFile = open("highscores.txt", "w")

    for i in range(5):
        HSFile.write(str(namelist[i]) + "\n")
    for i in range(5):
        HSFile.write(str(scorelist[i]) + "\n")
    HSFile.close()

def Drawscreen():
    screen.fill(BBLUE)

    if gameboard.shakescreen:
        gameboard.drawshake(screen)
    else:
        gameboard.draw(screen)

    shape.drawShadow(screen)
    shape.draw(screen)

    scoreText = myfont.render('S C O R E : ' + str(gameboard.score), True, BLUE)
    screen.blit(scoreText, (330, 400))
    linesText = myfont.render('L I N E S : ' + str(gameboard.lines), True, BLUE)
    screen.blit(linesText, (330, 350))
    LevelText = myfont.render('S P E E D  x ' + str(gameboard.levelTracker), True, BLUE)
    screen.blit(LevelText, (330, 300))
    nextshapetext = myfont.render('N E X T : ', True, BLUE)
    pygame.draw.rect(screen, WHITE, [330, 100, 6 * shape.blocklist[0].size, 6 * shape.blocklist[0].size], 1)
    screen.blit(nextshapetext, (330, 50))
    nextshape.drawNewShape(screen)
    #poweruptext = myfont.render("P O W E R U P S : ", True, PINK)
    #screen.blit(poweruptext, (50, 525))
    #numslowtimestext = myfont.render(" X   " + str(gameboard.numslowtime), True, PINK)
    #screen.blit(numslowtimestext, (310, 525))
    #slowtime_image = pygame.image.load('clock.png')
    #screen.blit(slowtime_image, (250, 515))
    #numswaptext = myfont.render('   X ' + str(gameboard.numswap), True, PINK)
    #screen.blit(numswaptext, (435, 525))
    #swap_image = pygame.image.load("swap.png")
    #screen.blit(swap_image, (375, 515))
    highscoretext = myfont.render("H I G H S C O R E S : ", True, BLUE)
    screen.blit(highscoretext, (575, 50))
    pygame.draw.rect(screen, WHITE, [575, 100, 200, 400], True)
    playernametext = myfont1.render(name, True, BLUE)
    screen.blit(playernametext,(600, 525))
    for i in range(5):
        highscoreplayertext = myfont.render(str(namelist[i]) + "        " + str(scorelist[i]), True, BLUE)
        screen.blit(highscoreplayertext, (600, 100 + 30 * i))
    pygame.display.flip()

def keypressed():
#     
    if event.key == pygame.K_LEFT :
        shape.MoveLeft()
    elif event.key == pygame.K_RIGHT :
        shape.MoveRight()
    elif event.key == ord('d'):
        global downKey
        downKey = True
    elif event.key == pygame.K_UP or event.key == ord('w'):
        shape.RotateCW() # tourne la piece dans le sens des aiguilles d'une montre
    elif event.key == pygame.K_DOWN or event.key == ord('s'):
        shape.RotateCCW() # tourne la piece dans le sens inverse des aiguilles d'une montre
    elif event.key == pygame.K_SPACE or event.key == ord('h') :
        gameboard.score += (gameboard_height - shape.blocklist[0].gridy)
        shape.fall()
    elif event.key == ord('t') and gameboard.numslowtime > 0:
        gameboard.numslowtimeon = True
        gameboard.numslowtime -= 1
    elif event.key == ord('f') and gameboard.numswap > 0:
        gameboard.swapshape = True
        gameboard.numswap -= 1
    elif event.key == ord('p'):
        global paused
        paused = True
    elif event.key == ord('p'):
        paused = False


def keyReleased():
    if event.key == pygame.K_d:
        global downKey
        downKey = False


def keycheck():
    
    if downKey:
        shape.MoveDown()
    




while not started:  # Title screen
    titlescreen = pygame.image.load('background1.png')
    nametext = myfont.render(name, True, WHITE)
    screen.blit(titlescreen, (0, 0))
    pygame.display.flip()
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
            started = True
        if event.type == pygame.KEYDOWN:
            if event.key >= 33 and event.key <= 126 and len(name) < 10:
                name += chr(event.key)
            if event.key == pygame.K_BACKSPACE:
                name = name[: - 1]
            if event.key == pygame.K_RETURN:
                if name == "":
                    name = "Player"
                started = True



# quit function
while not done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
        elif event.type == pygame.KEYDOWN:
            keypressed()
        elif event.type == pygame.KEYUP:
            keyReleased()

    keycheck()

    if gameboard.swapshape:
        shape = nextshape
        nextshape = Shape()
        gameboard.swapshape = False
    if gameboard.numslowtimeon:
        slowtimedelay += 1
        if slowtimedelay > 100:
            slowtimeelay = 0
            slowtimeon = False

    delay += 1
    if delay > 10:
        shape.falling()
        delay = 0
    if shape.active == False:
        shape = nextshape
        nextshape = Shape()
        gameboard.clearLine()

    Drawscreen()
    time.sleep(0.11 - gameboard.levelTracker * 0.02 + gameboard.numslowtimeon * 0.1)
    if changehold:
        changehold = False
        if holding:
            nextshape = shape
            holdshape.reposition()
            shape = holdshape
            holdshape = None
            holding = False
        else:
            holdshape = shape
            shape = nextshape
            nextshape = Shape()
            holding = True



    while paused:
        pausedscreen = myfont3.render("P A U S E D ", True, BBLUE)
        screen.blit(pausedscreen, (200, 200))
        pygame.display.flip()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                paused = False
                done = False
            if event.type == pygame.KEYDOWN:
                if event.key == ord('p'):
                    paused = False




    if gameboard.checkLoss():
        checkhighscores()
        gameboard = Gameboard(WHITE, 25)
        shape = Shape
        continueGame = True
        while continueGame == True:
            endscreen = pygame.image.load('go_screen.png')
            endscreen = pygame.transform.scale(endscreen, (800, 600))
            scoretext = myfont.render(str(name) + '  l o s t ,  y o u r  s c o r e  w a s  ' + str(score), True, WHITE)
            screen.blit(endscreen, (0, 0))
            screen.blit(scoretext, (0, 550))
            quitend = myfont.render('P R E S S  Q  T O  Q UI T ', True, WHITE)
            playagaintext = myfont.render('P R E S S  E N T E R  T O  P L A Y  A G A I N', True, WHITE)
            screen.blit(playagaintext,(400, 0 ))
            screen.blit(quitend, (0, 0))
            pygame.display.flip()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    done = True
                    continueGame = False
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_RETURN:
                        gameboard = Gameboard(WHITE, 25)
                        shape = Shape()
                        nextshape = Shape()
                        holdshape = None
                        continueGame = False
                    if event.key == ord('q'):
                        done = True
                        continueGame= False

