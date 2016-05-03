# drill.inc
# model for the robot "Bigbob"
# Author: Jennifer Owen
# Date: 16/04/2010

# drill’s body
define drillbase position
(
# actual size
size [1 1 1.2]
# Bigbob’s centre of rotation is offset from its centre of area
# origin [0.125 0 0 0]
# the shape of Bigbob
block
(
points 4
point[3] [-1 -1]
point[2] [-1 1]
point[1] [1 1]
point[0] [1 -1]
z [1.05 1.1]
)

block
(
points 4
point[3] [-0.5 -0.5]
point[2] [-0.5 0.5]
point[1] [0.5 0.5]
point[0] [0.5 -0.5]
z [1.15 1.9]
)

block
(
points 4
point[3] [-1 -1]
point[2] [-1 -0.9]
point[1] [-0.9 -0.9]
point[0] [-0.9 -1]
z [0 1.05]
)

block
(
points 4
point[3] [1 -1]
point[2] [0.9 -1]
point[1] [0.9 -0.9]
point[0] [1 -0.9]
z [0 1.05]
)

block
(
points 4
point[3] [1 1]
point[2] [1 0.9]
point[1] [0.9 0.9]
point[0] [0.9 1]
z [0 1.05]
)

block
(
points 4
point[3] [-1 1]
point[2] [-0.9 1]
point[1] [-0.9 0.9]
point[0] [-1 0.9]
z [0 1.05]
)

# differential steering model
drive "diff"
# sensors attached to drill
obstacle_return 1 # Can hit things.
laser_return 1 # reflects laser beams
ranger_return 1 # reflects sonar beams

)