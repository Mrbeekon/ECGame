#!/usr/bin/env python

from core.screen import Screen

WIDTH = 800
HEIGHT = 600
FPS = 600

screen = Screen(WIDTH, HEIGHT, FPS)

i = 0
while screen.next():
    i += 1
    # clean up
    screen.clear(0)

    # Frame by frame processing here
    colour = -1
    screen.draw_line((i % WIDTH), 1, (i % WIDTH), HEIGHT, colour)
    screen.draw_line(1, (i % HEIGHT), WIDTH,(i % HEIGHT), colour)



