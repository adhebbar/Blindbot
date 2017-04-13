#sensor.py
import serial
import pygame
from multiprocessing import Event, Process

class SerialPort():
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
    def __init__(self, port, legs, packet_ending = '\n', baud = 115200):
        super().__init__(baud, port, packet_ending)
        self.legs = legs
        self.running = True
        self.listening = True
        self.data_q = []
        self.joystick = RoboJoystick([1,2,3])
        self.state = self.LEGS

    def run():
        coords_available = False
        while self.running:
            if self.listening:
                self.data_q = self.data_q + self.receive_message()
            while (len(self.data_q) > 0):
                current_data = data_q.pop(0)
                #TODO Take decisions based on actions
            if self.joystick.button_updated("A"):
                self.send_message("SetA")
                self.state = self.GAIT
            elif self.joystick.button_updated("B"):
                self.send_message("SetB")
                self.state = self.GAIT_AUTO
            elif self.joystick.button_udpated("X"):
                self.send_message("SetX")
                self.state = self.BODY
            elif self.joysick.button_udpated("Y"):
                self.send_message("SetY")
                self.state = self.LEGS
            else:
                self.send_message("SetLB")
                self.state = self.LOCK
            elif self.joystick.axis_updated("RA_X") or
                self.joystick.axis_updated("RA_Y"):
                coords_available = True
                if self.state == self.GAIT:
                    self.send_message("MOVE")
                elif self.state == self.LEGS:
                    pass
                elif self.state == self.BODY:
                    pass
                else
            return


            if self.joystick.axis_updated("LA_X") or
               self.joystick.axis_updated("LA_Y"):
               pass #move forward backward to the left or right
            


