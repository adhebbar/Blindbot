#sensor.py
import serial
import pygame
from multiprocessing import Event, Process

class SerialPort(Process):
    def __init__(self, baud, port, packet_ending):
        self.start_time = 0.0
        self.packet_ending = packet_ending
        self.port = port
        self.baud = baud
        self.serial_ref = serial.Serial(port=self.port, baudrate=self.baud)
        self.buffer = ""
        self.packets = []
        self.joystick = XboxJoystick()

    def receive_message(self):
        if (self.serial_ref.in_waiting > 0):
            message = self.serial_ref.read(self.serial_ref.in_waiting).decode("utf-8")
            recovered_packet = ""
            if self.buffer != "":
                recovered_packet = self.buffer
            if message[-1] != self.packet_ending:
                last_ending = message.rfind(self.packet_ending)
                self.buffer = message[last_ending:]
                message = message[:last_ending+1]
            packets = message.split(self.packet_ending)
            if recovered_packet != "": packets.insert(0,recovered_packet)
            self.packets = self.packets + packets
            return packets
        else 
            return []

    def send_message(self, message):
        message.encode("utf-8")
        result = self.serial_ref.write(message)
        return result;

class Robot(SerialPort):
    LEGS = 1
    GAIT = 2
    BODY = 3
    LOCK = 4
    GAIT_AUTO = 5
    def __init__(self, port, legs, packet_ending = '\n', baud = 115200,
                 txt_file = ""):
        super().__init__(baud, port, packet_ending)
        self.legs = legs
        self.running = True
        self.listening = True
        self.data_q = []
        self.joystick = RoboJoystick([1,2,3])
        self.state = self.LEGS
        self.leg_coords = []
        self.leg_forces = []
        self.COM = (,) #2d view from top
        self.triangle_centroid = (,) #2d view from top
        self.update_received = False
        self.num_legs
        self.txt_file = txt_file

    def joystick_read(self):
        if self.joystick.button_updated("A") and not self.joystick.get_button("A"):
            self.send_message("SA")
            self.state = self.GAIT
        elif self.joystick.button_updated("B") and not self.joystick.get_button("B"):
            self.send_message("SB")
            self.state = self.GAIT_AUTO
        elif self.joystick.button_updated("X") and not self.joystick.get_button("X"):
            self.send_message("SX")
            self.state = self.BODY
        elif self.joystick.button_updated("Y") and not self.joystick.get_button("Y"):
            self.send_message("SY")
            self.state = self.LEGS
        elif self.joystick.button_updated("LB") and not self.joystick.get_button("LB"):
            self.send_message("SLB")
            self.state = self.LOCK
        elif self.joystick.button_update("RB") and not self.joystick.get_button("RB"):
            self.send_message("SRB")
        elif self.joystick.dpad_updated():
            self.send_message(str(self.dpad))
        elif self.joystick.axis_updated("RA_X") or
            self.joystick.axis_updated("RA_Y"):
            axis_x, axis_y = joystick.get_axes("RA")
            axis_angle = joystick.get_axis_angle("RA")
            if self.state == self.GAIT:
                self.send_message("R A {0f}".format(angle))
            elif self.state == self.LEGS:
                self.send_message("M Z {0f}".format(axis_x))
            elif self.state == self.BODY:
                self.send_message("R A {0f}".format(angle))
        if self.joystick.axis_updated("LA_X") or
           self.joystick.axis_updated("LA_Y"):
            axis_x, axis_y = joystick.get_axes("LA");
            axis_angle = joystick.get_axis_angle("LA");
            if self.state = self.GAIT:
                self.send_message("MD{},{:0f}".format(axis_x,axis_y))
            elif self.state == self.LEGS:
                self.send_message("MX{0f}".format(axis_x))
            elif self.state == self.BODY:
                self.send_message("TA{0f}".format(angle))


    def write_txt(self):
        pass


    def run(self):
        coords_available = False
        while self.running:
            if self.listening:
                self.data_q = self.data_q + self.receive_message()
            while (len(self.data_q) > 0):
                current_data = data_q.pop(0)
                instructions = current_data.split()
                for i in range(1,len(instructions)):
                    if instructions[0] == "C":
                        self.write_txt()
                        self.coords[i-1] = tuple(map(instruction[i].split("\t"), float))
                    if instructions[0] == "F":
                        self.leg_forces[i-1] = tuple(map(instructions[i].split("\t"), float))
                #TODO Take decisions based on actions
            self.joystick_read()


            