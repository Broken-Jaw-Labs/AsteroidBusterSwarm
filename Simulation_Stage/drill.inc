# drill.inc
# model for the robot "Bigbob"
# Author: Jennifer Owen
# Date: 16/04/2010

# drill’s body
define drill position
(
# actual size
size [0.25 0.25 1]
# Bigbob’s centre of rotation is offset from its centre of area
# origin [0.125 0 0 0]
# the shape of Bigbob
block
(
points 8
point[7] [0.25 0]
point[6] [0 0.25]
point[5] [0 0.75]
point[4] [0.25 1]
point[3] [0.75 1]
point[2] [1 0.75]
point[1] [1 0.25]
point[0] [0.75 0]
z [0 1]
)

# differential steering model
drive "diff"
# sensors attached to drill
obstacle_return 1 # Can hit things.
laser_return 1 # reflects laser beams
ranger_return 1 # reflects sonar beams

)