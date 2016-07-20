/********************************
 * TEAM 5401 - 2016 Summer Program
 * Simple code for Tim
********************************/
#include "WPILib.h"

const int MOTOR_FPS     = 200;
const int LBumper_ID	=	5; //Button channels
const int RBumper_ID	=	6;
const int XboxB_ID		=	2;
const int XboxA_ID		=	1;
const int XboxX_ID		=	3;
const int Start_ID		=	8;
const int XboxR3_ID		=	10;
const int Back_ID		=	7;
const int XboxL3_ID		=	9;
const int MOHStartID	=	10;
const int MOHL3_ID		= 	11;
const int LTrigger		= 	2;
const int RTrigger		=	3;
const double Thresh		=	0.1;
const double Sensitivity	= .5;

class Robot : public SampleRobot{
	Joystick OpController;

	Victor RightDrive1;
	Victor RightDrive2;
	Victor LeftDrive1;
	Victor LeftDrive2;

public:
	Robot() :
		OpController(1),

		RightDrive1(0),
		RightDrive2(1),
		LeftDrive1(2),
		LeftDrive2(3)
	{
	}

	void SetMotors(double LeftDriveDesired, double RightDriveDesired){
		LeftDrive1  .Set(LeftDriveDesired);
		LeftDrive2  .Set(LeftDriveDesired);
		RightDrive1 .Set(RightDriveDesired);
		RightDrive2 .Set(RightDriveDesired);
	}

	void RobotInit() override{
	}

	void Autonomous(){
	}

	void OperatorControl(){
		double Left;
		double Right;
		while(IsOperatorControl() && IsEnabled()){

			double Slew     	= 	OpController.GetRawAxis(0);
			double Throttle 	= 	OpController.GetRawAxis(RTrigger);
//			double Twist    	= 	OpController.GetRawAxis(2);
			double 	Reverse 	=	OpController.GetRawAxis(LTrigger);
			bool 	Brake		=	OpController.GetRawButton(RBumper_ID);

	// -----Begin block of drive code
		if (Brake){		//brake, Bracket level 1
			Left = 0;
			Right = 0;
			} else if (Slew > Thresh){	//If Slew is positive (Thumbstick pushed right), go Right, new bracket L2
					Left = (Throttle - Reverse) * Sensitivity;			//Send Left full power
					Right = (Throttle - Reverse) * Sensitivity * (1 - Slew);	//Send Right partial power, tempered by how hard the thumbstick is being pushed
					} else if (Slew < (-1 * Thresh)){	//If Slew is negative (Thumbstick pushed left), go Left, end bracket L2, new bracket L2 ***020516 KJM - added an else here.  May be unnecessary
						Left = (Throttle - Reverse) * Sensitivity * (1 + Slew);		//Send Left partial power, tempered by how hard thumbstick is being pushed left
						Right = (Throttle - Reverse) * Sensitivity; 			//Send Right full power
							} else //if (Slew < Thresh && Slew > (-1 * Thresh))
								{
									Left = (Throttle - Reverse) * Sensitivity;
									Right = (Throttle - Reverse) * Sensitivity;
								}//end bracket L2
			//} 			}//end bracket L1
	//------End block of spin in place code


			SetMotors(Left, Right);


/*
			if(OpController.GetRawButton(5)){
				LeftFeedWheel.Set(FEED_WHEEL_IN);
			}else{
				LeftFeedWheel.Set(-OpController.GetRawAxis(2) * FEED_WHEEL_OUT);
			}

			if(OpController.GetRawButton(6)){
				RightFeedWheel.Set(-FEED_WHEEL_IN);
			}else{
				RightFeedWheel.Set(OpController.GetRawAxis(3) * FEED_WHEEL_OUT);
			}

*/

			Wait(1 / MOTOR_FPS);
		}
	}
};

START_ROBOT_CLASS(Robot);

