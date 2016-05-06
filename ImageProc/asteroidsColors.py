# import the necessary packages
import numpy as np
import imutils
import cv2
from matplotlib import pyplot as plt
 

cyanLower = (64, 86, 6)
cyanUpper = (100, 255, 255)

yellowLower = (15, 195,80)
yellowUpper = (20, 255, 255)

img = cv2.imread("a1.jpg")

frame = imutils.resize(img, width=600)
# blurred = cv2.GaussianBlur(frame, (11, 11), 0)
hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
 
# construct a mask for the color "green", then perform
# a series of dilations and erosions to remove any small
# blobs left in the mask
mask = cv2.inRange(hsv, cyanLower, cyanUpper)
mask = cv2.erode(mask, None, iterations=2)
mask = cv2.dilate(mask, None, iterations=7)

mask2 = cv2.inRange(hsv, yellowLower, yellowUpper)
mask2 = cv2.erode(mask2, None, iterations=2)
mask2 = cv2.dilate(mask2, None, iterations=7)
#mask = cv2.GaussianBlur(mask, (5,5), 0)
# find contours in the mask and initialize the current
# (x, y) center of the ball
#cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
cnts, hier = cv2.findContours(
				mask.copy(), 
				cv2.RETR_EXTERNAL, 
				cv2.CHAIN_APPROX_SIMPLE
				)
cnts2, hier = cv2.findContours(
				mask2.copy(), 
				cv2.RETR_EXTERNAL, 
				cv2.CHAIN_APPROX_SIMPLE
				)
center = None
rects = [cv2.boundingRect(ctr) for ctr in cnts] 
rects2 = [cv2.boundingRect(ctr) for ctr in cnts2] 
index = 0
for rect in rects:
		#dibuja los rectangulos
		momentos = cv2.moments(cnts[index])
		masa = momentos["m00"]/100
		cv2.rectangle(
			frame, 
			(rect[0], rect[1]), 					#esquina superior
			(rect[0] + rect[2], rect[1] + rect[3]), #esquina inferior
			(0, 255, 0), 							#color
			2
			)
		cv2.putText(
					frame, 
					str(int(masa)),
					(rect[0], rect[1]),
					cv2.FONT_HERSHEY_DUPLEX,
					1,
					(0, 255, 255),
					1
					)
		index += 1

index = 0
for rect in rects2:
		#dibuja los rectangulos
		momentos = cv2.moments(cnts2[index])
		masa = momentos["m00"]/100
		cv2.rectangle(
			frame, 
			(rect[0], rect[1]), 					#esquina superior
			(rect[0] + rect[2], rect[1] + rect[3]), #esquina inferior
			(0, 255, 255), 							#color
			2
			)
		cv2.putText(
					frame, 
					str(int(masa)),
					(rect[0], rect[1]),
					cv2.FONT_HERSHEY_DUPLEX,
					1,
					(0, 255, 0),
					1
					)
		index += 1
# only proceed if at least one contour was found
if len(cnts) > 0:
	# find the largest contour in the mask, then use
	# it to compute the minimum enclosing circle and
	# centroid
	c = max(cnts, key=cv2.contourArea)
	((x, y), radius) = cv2.minEnclosingCircle(c)
	M = cv2.moments(c)
	center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
 
	# only proceed if the radius meets a minimum size
	if radius > 10:
		# draw the circle and centroid on the frame,
		# then update the list of tracked points
		cv2.circle(frame, (int(x), int(y)), int(radius),
			(0, 0, 255), 3)
		#cv2.circle(frame, center, 5, (0, 0, 255), -1)


#plt.hist(mask.ravel(), 256, [0,256])
#plt.show()


# show the frame to our screen
cv2.imshow("Frame", frame)
cv2.imshow("th", mask)
cv2.imshow("th2", mask2)
color = ('b', 'g', 'r')
for i,col in enumerate(color):
	histr = cv2.calcHist([frame],[i],None,[256],[5,240])
	plt.plot(histr,color = col)
	plt.xlim([0,256])
plt.show() 
while True:
	key = cv2.waitKey(1) & 0xFF

# cleanup the camera and close any open windows

cv2.destroyAllWindows()