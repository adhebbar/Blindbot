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
    joystick_map = {}
    def __init__(self, port, legs, packet_ending = '\n', baud = 115200):
        super().__init__(baud, port, packet_ending)
        self.legs = legs
        self.running = True
        self.listening = True
        self.data_q = []

    def run():
        while self.running:
            if self.listening:
                self.data_q = self.data_q + self.receive_message()
            while (len(self.data_q) > 0):
                current_data = data_q.pop(0)
                #TODO Take decisions based on actions
            read_joystick()

