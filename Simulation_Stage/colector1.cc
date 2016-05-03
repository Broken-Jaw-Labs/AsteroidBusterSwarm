#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <libplayerc++/playerc++.h>
#define PI 3.14159265
#include "args.h"

#define RAYS 32
using namespace PlayerCc;

/**
Randomly assigns new speeds into the given addresses.
This function will always write to the given addresses.
@param *forwardSpeed the address of the forward speed
variable you want this function to change.
@param *turnSpeed the address of the turn speed variable
you want this function to change.
*/
void Moveto(double *forwardSpeed, double *turnSpeed, int *goDone, player_pose2d_t target, SimulationProxy &sim)
{
	double dist, angle;
	double robotX, robotY, robotYaw;
	double newturnrate = 0;
	double newspeed = 0;
	
	//find the robot...
	sim.GetPose2d((char*)"bob2", robotX, robotY, robotYaw);
	robotYaw = int(robotYaw*180/PI);
	printf("X=%f, ", robotX);
	printf("Y=%f, ", robotY);
	printf("Yaw=%f, ", robotYaw);
	dist = int(sqrt((target.px - robotX)*(target.px - robotX) + (target.py - robotY)*(target.py - robotY)));
	angle = atan2(target.py - robotY, target.px - robotX);
	angle = int(angle*180/PI);
	printf("dist=%f, ", dist);
	printf("angle=%f\n", angle);
	
	
	
	if(abs(angle-robotYaw)!=0)
	{
		newspeed = 0;
		if(angle-robotYaw>0)
		{
			newturnrate = 10;
		} else
		{
			newturnrate = -10;
		}
		
	} else {
		if(dist != 0)
		{
			newturnrate = 0;
			newspeed = 3;
		} else {
			newturnrate = 0;
			newspeed = 0;
			*goDone = 1;
			//printf("Setting search mode\n");
		}
	}

	printf("speed=%f, ", newspeed);
	printf("turnrate=%f\n", newturnrate);
	
	
	*forwardSpeed = newspeed;
	*turnSpeed = newturnrate;
}

/**
Randomly assigns new speeds into the given addresses.
This function will always write to the given addresses.
@param *forwardSpeed the address of the forward speed
variable you want this function to change.
@param *turnSpeed the address of the turn speed variable
you want this function to change.
*/
void Returnto(double *forwardSpeed, double *turnSpeed, int *goDone, player_pose2d_t target, SimulationProxy &sim)
{
	double dist, angle;
	double robotX, robotY, robotYaw;
	double newturnrate = 0;
	double newspeed = 0;
	
	//find the robot...
	sim.GetPose2d((char*)"bob2", robotX, robotY, robotYaw);
	robotYaw = int(robotYaw*180/PI);
	printf("X=%f, ", robotX);
	printf("Y=%f, ", robotY);
	printf("Yaw=%f, ", robotYaw);
	dist = int(sqrt((target.px - robotX)*(target.px - robotX) + (target.py - robotY)*(target.py - robotY)));
	angle = atan2(target.py - robotY, target.px - robotX);
	angle = int(angle*180/PI);
	printf("dist=%f, ", dist);
	printf("angle=%f\n", angle);
	
	
	
	if(abs(angle-robotYaw)!=0)
	{
		newspeed = 0;
		if(angle-robotYaw>0)
		{
			newturnrate = 10;
		} else
		{
			newturnrate = -10;
		}
		
	} else {
		if(dist != 0)
		{
			newturnrate = 0;
			newspeed = 3;
		} else {
			newturnrate = 0;
			newspeed = 0;
			*goDone = 0;
			//printf("Setting search mode\n");
		}
	}
	
	printf("speed=%f, ", newspeed);
	printf("turnrate=%f\n", newturnrate);
	
	
	*forwardSpeed = newspeed;
	*turnSpeed = newturnrate;
}


int main(int argc, char *argv[])
{
	parse_args(argc,argv);
	
	/*need to do this line in c++ only*/
	using namespace PlayerCc;
	player_pose2d_t gTarget, rTarget;
	PlayerClient    robot("localhost",gPort);
	Position2dProxy p2dProxy(&robot,gIndex);
	SonarProxy      sonarProxy(&robot,gIndex);
	BlobfinderProxy blobProxy(&robot,gIndex);
	LaserProxy      laserProxy(&robot,gIndex);
	SimulationProxy simProxy(&robot,0);
	int go = 0;
	double forwardSpeed, turnSpeed;
	if(gIndex == 10){
		player_pose2d_t gTarget = {-2, 0, 0};
		player_pose2d_t rTarget = {-24, -3, 0};
	}
	
	if(gIndex == 11){
		player_pose2d_t gTarget = {-1.2, -1.2, 0};
		player_pose2d_t rTarget = {-24, -6, 0};
	}
	
	if(gIndex == 12){
		player_pose2d_t gTarget = {-0.5, -2.5, 0};
		player_pose2d_t rTarget = {-21, -11, 0};
	}
	
	
	//enable motors
	p2dProxy.SetMotorEnable(true);
	//request geometries
	p2dProxy.RequestGeom();
	sonarProxy.RequestGeom();
	laserProxy.RequestGeom();
	//blobfinder doesn't have geometry
	/*here so that laserProxy[90] doesn't segfault on first loop*/
	robot.Read();

	while(true)
	{
		// read from the proxies
		robot.Read();
		//if(blobProxy.GetCount() == 0)
		
		if(go == 0)
		{
			//wander
			printf("going to the area of gathering\n");
			Moveto(&forwardSpeed, &turnSpeed, &go, gTarget, simProxy);
			//Wander(&forwardSpeed, &turnSpeed);
		} else {
			//printf("returning\n");
			
			if(go == 1){
				printf("returning to the launch area\n");
				Returnto(&forwardSpeed, &turnSpeed, &go, rTarget, simProxy);
			}
		}
		
		p2dProxy.SetSpeed(forwardSpeed, dtor(turnSpeed));
		sleep(0.1);
	}
}