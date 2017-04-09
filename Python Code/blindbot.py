import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

def getHeight(theta1, legHeight, link1, link2): #in mm
	endEffectorHeight = link1*np.sin(theta1) + link2
	return legHeight-endEffectorHeight

def getAngle(theta): #in radians
	return (theta-512)*2*np.pi/1024

#FK for the legs
def getCoordinates(theta0, theta1, theta2):
	link0 = 90 #hardcode
	link1 = 70 #hardcode;
	link2 = 90 #hardcode;
	legHeight = 100 #hardcode
	theta0, theta1= getAngle(theta0), getAngle(theta1)
	z = getHeight(theta1, legHeight, link1, link2)
	radius = link0 + link1*np.cos(theta1)
	y = radius*np.sin(theta0) 
	x = radius*np.cos(theta0)
	return (x,y,z)

def plot(coordinateArray): #of form [[x1, y1, z1],[x2,y2,z2]]
	temp = np.array(coordinateArray).transpose()
	xs, ys, zs = temp[0], temp[1], temp[2]
	fig = plt.figure()
	ax = fig.add_subplot(111, projection='3d')
	ax.scatter(xs, ys, zs, c='r', marker='o')
	ax.plot_wireframe(xs, ys, zs)
	ax.set_xlabel('X Label')
	ax.set_ylabel('Y Label')
	ax.set_zlabel('Z Label')
	plt.show()

plot([[1,1,1],[1,3,4],[2,2,2],[2,3,4],[2,1,3]])