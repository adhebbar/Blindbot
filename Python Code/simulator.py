#simulator.py
import matplotlib.pyplot as plt
import numpy as np

class Simulator:
	def __init__(cox_len, femur_len, tibia_len,
		         cox_angle, femur_angle, tibia_angle):
		self.cox = cox_len
		self.femur_len = femur_len
		self.tibia_len = tibia_len
		self.cox_angle = cox_angle
		self.tibia_angle = tibia_angle
		self.femur_angle = femur_angle
		self.cox_y = 0,0
		calculate_coords()

	def IK(x,y,z):
		self.cox_angle = np.arctan2(z,x)*180/np.pi
		leg_length = np.sqrt(x**2 + x**2);
		HF = np.sqrt((leg_length - self.cox_len)**2 + y**2)
		alpha_1 = np.arctan2((leg_length-self.cox_len)/y)
		alpha_2 = np.arccos((self.tibia_len**2 -self.femur_len**2 - HF**2)/
			                 (-2*self.femur_len*HF))
		self.femur_angle = (alpha_1 + alpha_2)*180/np.pi - 90
		self.beta = np.arccos((HF**2 - self.tibia_len**2 - self.femur_len)/
			                   (-2 * self.femur_len * self.tibia_len))

	def FK():
		pass

	def calculate_coords():
		self.cox_x = 0,self.cox_len*np.cos(self.cox_angle)
		self.cox_z = 0,self.cox_len*np.sin(self.cox_angle)
		self.femur_x = self.cox_x[1], \
		               self.cox_x[1] + self.femur_len*np.cos(np.radians(self.femur_angle))
		self.femur_y = 0, \
		               self.cox_z[1] + self.femur_len*np.sin(np.radians(self.femur_angle))
		self.tibia_x = self.femur_x[1],\
					   self.femur_x[1]
		self.tibia_y = self.femur_y[1]