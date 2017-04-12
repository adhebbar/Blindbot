#Robot_joystick.py
#TODO IMPLEMENT THIS
import pygame
import time
from copy import copy
from pygame.locals import *

#some ideas taken from http://www.nerdparadise.com/programming/pygamejoystick
#It allows both keyboard and controller inputs
class RoboJoystick():
    LINUX = 0
    WINDOWS = 1
    MAC = 2
    def __init__(self, axes_dead_zone = 0.15, os_num = 0):
        pygame.init()
        self.init_joystick()
        self.dead_zone = axes_dead_zone
        self.dpad = (0,0)
        self.prev_dpad = (0,0)
        self.buttons, self.axes_map = create_button_map(os_num)
        self.key_map = {
            K_UP : 'up',
            K_DOWN : 'down',
            K_LEFT : 'left',
            K_RIGHT : 'right',
            K_RETURN : 'START',
            K_a : 'A',
            K_b : 'B',
            K_x : 'X',
            K_y : 'Y',
            K_l : 'LB',
            K_r : 'RB'
        }
        self.keys_pressed = {}
        self.axes = {}
        self.axes_changed = {}
        for button in self.buttons:
            self.keys_pressed[self.buttons[button]] = False
        for axis in self.axes:
            self.axes[self.axes_map[axis]] = 0.0
            self.axes_chaged[self.axes_map[axis]] = False
        self.prev_keys = copy(keys_pressed)

        self.running = False

    def button_updated(self, button):
        prev_state = self.prev_keys[button]
        state = self.keys_pressed[button]
        if prev_state != state:
            self.prev_keys[button] = state
            return True
        return False

    def dpad_updated(self):
        if (self.prev_dpad != self.dpad):
            self.prev_dpad = self.dpad
            return True
        return False

    def axis_updated(self, name):
        if self.axes_changed[name]:
            self.axes_changed[name] = False
            return True
        return False

    def get_events(self):
        for event in pygame.event.get():
            if event.type == QUIT or (event.key == K_ESCAPE):
                self.running = False
                return None

            elif event.type == KEYDOWN or event.type == KEYUP:
                key_pushed_down = event.type == KEYDOWN
                button = self.key_map.get(event.key) #uses get to prevent unsafe accesses
                if button is not None:
                    self.keys_pressed[button] = key_pushed_down

            if event.type == JOYBUTTONDOWN:
                button = self.buttons.get(event.button)
                if button is None: 
                    print ("Unregistered button pressed!")
                    return
                self.keys_pressed[button] = True

            if event.type == JOYBUTTONUP:
                button = self.buttons.get(event.button)
                if button is None: 
                    print ("Unregistered button pressed!")
                    return
                self.keys_pressed[button] = False
                
            if event.type == pygame.JOYHATMOTION:
                self.dpad = event.value

            if event.type == pygame.JOYAXISMOTION:
                if abs(event.value > self.dead_zone):
                    value = event.value
                else:
                    value = 0.0

                if self.axes[self.axes_map[event.axis]] != value:
                    self.axes[self.axes_map[event.axis]] = value
                    self.axes_changed[self.axes_map[event.axis]] = True

    def init_joystick(self):
        pygame.joystick.init()
        self.joystick = pygame.joystick.Joystick(0)
        self.joystick_name = self.joystick.get_name()

    @staticmethod
    def create_button_map(os_num):
        if os_num == RoboJoystick.LINUX:
            result_buttons = {
                0: "A",
                1: "B",
                2: "X",
                3: "Y",
                4: "LB",
                5: "RB",
                6: "BACK",
                7: "START",
                9: "LS",
                10: "RS",}
            result_axes = {
                0: "LS_X",
                1: "LS",
                3: "RS_X",
                4: "RS_Y"}
        elif os_num == RoboJoystick.WINDOWS:
            result_buttons = {
                0: "A",
                1: "B",
                2: "X",
                3: "Y",
                4: "LB",
                5: "RB",
                6: "BACK",
                7: "START",
                8: "LS",
                9: "RS",}
            result_axes = {
                0: "LA_X",
                1: "LA_Y",
                4: "RA_X",
                3: "RA_Y"}      
        return result_buttons, result_axes
