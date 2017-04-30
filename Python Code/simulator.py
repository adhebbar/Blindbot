#Delegated to pratyusha
#simulator.py
import matplotlib.pyplot as plt
import numpy as np

class Simulator:
	def __init__(self,cox_len, femur_len, tibia_len,
		         cox_angle, femur_angle, tibia_angle):
		self.cox_len = cox_len
		self.femur_len = femur_len
		self.tibia_len = tibia_len
		self.cox_angle = cox_angle
		self.tibia_angle = tibia_angle
		self.femur_angle = femur_angle
		self.cox_y = 0,0
		self.calculate_coords()

	def IK(self,x,y,z):
		self.cox_angle = np.degrees(np.arctan2(z,x))
		leg_length = np.sqrt(x**2 + z**2);
		HF = np.sqrt((leg_length - self.cox_len)**2 + y**2)
		#print(self.tibia_len**2 -self.femur_len**2 - HF**2)
		#print(-2.0*self.femur_len*HF)
		alpha_1 = np.arctan2((leg_length-self.cox_len),y)
		alpha_2 = np.arccos((self.tibia_len**2 -self.femur_len**2 - HF**2)/
			                 (-2.0*self.femur_len*HF))
		self.femur_angle = 90 - np.degrees((alpha_1 + alpha_2)) 
		beta = np.degrees(np.arccos((HF**2 - self.tibia_len**2 - self.femur_len**2)/
			                        (-2.0 * self.femur_len * self.tibia_len)))
		print(beta)
		self.tibia_angle = 90 - beta 

	def FK(self):
		pass

	def calculate_coords(self):
		self.cox_x = 0,self.cox_len#*np.cos(self.cox_angle)
		self.cox_z = 0,self.cox_len*np.sin(self.cox_angle)
		self.cox_y = 0, 0
		self.femur_x = self.cox_x[1], \
		               self.cox_x[1] + self.femur_len*np.cos(np.radians(self.femur_angle))
		self.femur_y = 0, \
		               self.cox_y[1] - self.femur_len*np.sin(np.radians(self.femur_angle))
		#self.femur_z = self.cox_z[1], self.cox_z[1]
		self.tibia_x = self.femur_x[1],\
					   self.femur_x[1] - self.tibia_len*np.sin(np.radians(self.tibia_angle))
		self.tibia_y = self.femur_y[1], \
					   self.femur_y[1] - self.tibia_len*np.cos(np.radians(self.tibia_angle))
	    #self.tibia_z = self.femur_z[1], \
	    #               self.femur_z[1]

	def plot(self):
		print(self.cox_angle, self.femur_angle, self.tibia_angle)
		x_points = np.array([self.cox_x,self.femur_x,self.tibia_x])
		#x_points = x_points.flatten('C')
		y_points = np.array([self.cox_y, self.femur_y, self.tibia_y])
		#y_points = y_points.flatten()
		print(x_points, y_points)
		plt.scatter(x_points, y_points)
		plt.plot(x_points, y_points)
		plt.show()

sim = Simulator(60.0,83.0,93.0,60.0,30.0,30.0)
sim.IK(150.0,70.0,0.0)
sim.calculate_coords()
sim.plot()
user = "Yes"
"""
while user != "no":
	user = input("input coords separated by spaces or no to quit")
	if user.lower() == "no":
		break
	x = (map(user.split,int))
"""
