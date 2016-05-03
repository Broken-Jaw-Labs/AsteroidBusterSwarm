#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <libplayerc++/playerc++.h>
#define PI 3.14159265
#include "args.h"

#define RAYS 32
using namespace PlayerCc;

int main(int argc, char *argv[])
{
	parse_args(argc,argv);
	
	/*need to do this line in c++ only*/
	using namespace PlayerCc;
	PlayerClient    robot("localhost",gPort);
	Position2dProxy p2dProxy(&robot,gIndex);
	SimulationProxy simProxy(&robot,0);
	int go = 0;
	double forwardSpeed, turnSpeed;
	//enable motors
	p2dProxy.SetMotorEnable(true);
	//request geometries
	p2dProxy.RequestGeom();
	robot.Read();

	while(true)
	{
		// read from the proxies
		robot.Read();
		p2dProxy.SetSpeed(0, dtor(30));
		sleep(0.1);
	}
}