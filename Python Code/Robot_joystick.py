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
        self.buttons, self.axes_map = self.create_button_map(os_num)
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
        self.prev_keys = copy(self.keys_pressed)

        self.running = False

    def get_button(self, button):
        return self.keys_pressed[button]


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
        if self.axes_changed.get(name):
            self.axes_changed[name] = False
            return True
        return False

    def get_events(self):
        for event in pygame.event.get():
            if event.type == QUIT:
                self.running = False
                return None
            elif event.type == KEYDOWN or event.type == KEYUP:
                key_pushed_down = event.type == KEYDOWN
                button = self.key_map.get(event.key) #uses get to prevent unsafe accesses
                if button is not None:
                    self.keys_pressed[button] = key_pushed_down
                if event.key == K_P:
                    self.running = False
                    return None

            if event.type == JOYBUTTONDOWN:
                print(event.button)
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
                if button == "BACK":
                    self.running = False
                    return None
                self.keys_pressed[button] = False


            if event.type == pygame.JOYHATMOTION:
                self.dpad = event.value



            if event.type == pygame.JOYAXISMOTION:
                if abs(event.value) > self.dead_zone:
                    value = event.value
                else:
                    value = 0.0
                print(value)
                prev_value = self.axes.get(self.axes_map.get(event.axis))
                if prev_value != value and self.axes_map.get(event.axis) is not None:
                    self.axes[self.axes_map.get(event.axis)]= value
                    self.axes_changed[self.axes_map[event.axis]] = True

    def init_joystick(self):
        joysticks = [pygame.joystick.Joystick(x) for x in
                     range(pygame.joystick.get_count())]
        for joystick in joysticks:
            joystick.init()

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

joystick = RoboJoystick(os_num = 1)
joystick.running = True
while (joystick.running):
    joystick.get_events()
    if joystick.button_updated("A") and not joystick.get_button("A"):
        print("A")
    elif joystick.button_updated("B") and not joystick.get_button("B"):
        print("B")
    elif joystick.button_updated("X") and not joystick.get_button("X"):
        print("X")
    elif joystick.button_updated("Y") and not joystick.get_button("Y"):
        print("Y")
    elif joystick.button_updated("LB") and not joystick.get_button("LB"):
        print("LB")
    elif joystick.button_updated("RB") and not joystick.get_button("RB"):
        print("RB")
    elif joystick.button_updated("START") and not joystick.get_button("START"):
        print("START")
    # elif joystick.button_updated("BACK") and not joystick.get_button("BACK"):
    #     print("BACK")        
    # elif joystick.axis_updated("RA_X"):
    #     print("RA_X")
    # elif joystick.axis_updated("RA_Y"):
    #     print("RA_Y")
    elif joystick.axis_updated("LA_X"):
        print("LA_X")
    elif joystick.axis_updated("LA_Y"):
        print("LA_Y")
    elif joystick.dpad_updated() and joystick.dpad != (0,0):
        print(joystick.dpad)
