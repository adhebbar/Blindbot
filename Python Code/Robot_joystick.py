#Robot_joystick.py
#TODO IMPLEMENT THIS
import pygame
import time
from pygame.local import *

#some ideas taken from http://www.nerdparadise.com/programming/pygamejoystick
#It allows both keyboard and controller inputs
class RoboJoystick():
	def __init__(self, axes_dead_zones):
		pygame.init()
		self.init_joystick()
		self.dpad = (0,0)
		self.prev_dpad = (0,0)
		self.buttons = ['up', 'down', 'left', 'right', 'start', 'A', 'B', 'X', 'Y', 'L', 'R']
        self.key_map = {
            K_UP : 'up',
            K_DOWN : 'down',
            K_LEFT : 'left',
            K_RIGHT : 'right',
            K_RETURN : 'start',
            K_a : 'A',
            K_b : 'B',
            K_x : 'X',
            K_y : 'Y',
            K_l : 'L',
            K_r : 'R'
        }
        self.axes = []
        self.keys_pressed = {}
        self.prev_buttons = []
        for button in self.buttons:
        	self.keys_pressed[button] = False
         self.running = False

    def button_pressed(self, button):
    	return self.keys_pressed[button]

    def dpad_updated(self):
    	if ()

    def get_events(self):
    	events = []
    	for event in pygame.event.get():
    		if event.type == QUIT or (event.key == K_ESCAPE):
    			self.running = False
    			return None

    		elif event.type == KEYDOWN or event.type == KEYUP:
    			key_pushed_down = event.type == KEYDOWN
    			button = self.key_map.get(event.key) #uses get to prevent unsafe accesses
    			if button != None:
    				events.append(InputEvent(button, key_pushed_down))
    				self.keys_pressed[button] = key_pushed_down

    		if event.type == JOYBUTTONDOWN:
    			if event.button < len(self.buttons):
    				button = self.buttons[event.button]
    				self.keys_pressed[button] = True
    			else
    				print ("Unregistered button pressed!")

    		if event.type == JOYBUTTONUP:
    			if event.button < len(self.buttons):
    				button = self.buttons[event.button]
    				self.keys_pressed[button] = False
    			else:
    				print ("Unregistered button pressed!")

    		if event.type == pygame.JOYHATMOTION:
    			self.dpad = event.value

    		if event.type == pygame.JOYAXISMOTION:
    			if event.axis < len(self.axes):
    				if abs(event.value > self.dead_zones[event.axis]):
    					value = self.axis_flipped[event.axis] * event.value 



	def init_joystick(self):
		pygame.joystick.init()
		self.joystick = pygame.joystick.Joystick(0)
		self.joystick_name = self.joystick.get_name()