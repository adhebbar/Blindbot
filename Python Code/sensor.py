#sensor.py
import serial
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

    def receive_message():
    	if (self.serial_ref.in_waiting > 0):
    		message = self.serial_ref.read(self.serial_ref.in_waiting).decode("utf-8")
    		recovered_packet = ""
            if self.buffer != "":
                recovered_packet = self.buffer
    		if message[-1] != self.packet_ending:
    			self.buffer = 
    		packets = message.split(self.packet_ending)
            if recovered_packet != "": packets.insert(0,recovered_packet)
            self.packets = self.packets + packets
    		return packets
    	else 
    		return None

    def send_message(message):
    	message.encode("utf-8")
    	result = self.serial_ref.write(message)
    	return result;

   	def run():
   		