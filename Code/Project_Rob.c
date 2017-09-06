/*
 *File Description:
 *this program is prototype 1 for Automatic1.
*/

//=====================================================================//
//////////////////////// Strategy Description ///////////////////////////
//=====================================================================//
/*	On Automatic 1 the gripper of the candle light flame will be on the front and
	the lifter of the flower and petal will be on the right side of the robot
				(( in case of blue court ))
/////////////////////////////////////////////////////////////////////////
	the lifter of the flower and petal will be on the left side of the robot
				(( in case of red court ))
/////////////////////////////////////////////////////////////////////////
	on line 1 for 4 lines till it’s exactly between lines G & F;
	it will then pick up the 1st petal and flower, using Lifter;
	after that it will turn 90 deg. CCW;
	it will move on line F for 3 lines till it’s between 9 & 10
	((the 2nd preparation point));
	then it will put the flower and the petal.
*/

//=====================================================================//
/////////////////////////// HW Description //////////////////////////////
//=====================================================================//
/*Description of the pins used:

	//C0 & (C1) for the Left motor, C1 is the pin that control
	//the speed of Left motor by the PWM
	//(C2) & C3 for the Right motor, C2 is the pin that control
	//the speed of Right motor by the PWM
	
	//C4 is the pin the Pve pole of the Lifter motor.
	//C5 is the pin the Nve pole of the Lifter motor.
	
	//C6 is the pin the Pve pole of the horizontal motor.
	//C7 is the pin the Nve pole of the horizontal motor.
	
	//B1 is the input from the left sensor of the line sensors
	//B2 is the input from the middle sensor of the line sensors
	//B3 is the input from the right sensor of the line sensors
	
	//B4 is the input from the front sensor of horizontal sensors
	//B5 is the input from the back sensor of horizontal sensors
	
	//B6 is the input from the upper sensor of Lifter sensors
	//B7 is the input from the lower sensor of Lifter sensors
	
*/
////////////////////////////////////////////////////////////////////////////
//============================ Definitions =================================//
////////////////////////////////////////////////////////////////////////////
#define Left_Motor_Pve PORTC.f1
#define Left_Motor_Nve PORTC.f0
#define Right_Motor_Pve PORTC.f2
#define Right_Motor_Nve PORTC.f3

#define Lifter_Pve PORTC.F4
#define Lifter_Nve PORTC.F5

#define horizontal_Pve PORTC.F6
#define horizontal_Nve PORTC.F7

#define Left_Sensor PORTB.f1
#define Mid_Sensor PORTB.f2
#define Right_Sensor PORTB.f3

#define front_sensor PORTB.F4
#define back_sensor PORTB.F5

#define upper_sensor PORTB.F6
#define lower_sensor PORTB.F7
////////////////////////////////////////////////////////////////////////////
//============================ Functions =================================//
////////////////////////////////////////////////////////////////////////////

//============================ PWM =================================//
/////////////////////////////////////////////////
//PWM registers configuration:
 /* Fosc = 4000000 Hz
 * Fpwm = 15625.00 Hz (Requested : 15625.00 Hz)
 * Resolution is 8 bits
 * Prescaler is 1*/
////////////////////////////////////////////////
void PWM_C1(const unsigned short duty_Percent)
{
////////////////////////////////////////
//this function set the PWM for PORTC.f1
////////////////////////////////////////
	if(duty_Percent == 100)
	{
		CCPR2L = 0b00111111;
		//Set Duty by 255.
		CCP2CON = 0b00111100;
		//Enable PWM
	}
	else if(duty_Percent == 75)
	{
		CCPR2L = 0b00101111;
		//Set Duty by 191.
		CCP2CON = 0b00111100;
		//Enable PWM
	}
	else if(duty_Percent == 50)
	{
		CCPR2L = 0b00011111;
		//Set Duty by 127.
		CCP2CON = 0b00111100;
		//Enable PWM
	}
	else if(duty_Percent == 25)
	{
		CCPR2L = 0b00001111;
		//Set Duty by 63
		CCP2CON = 0b00111100;
		//Enable PWM
	}
	else
	{
		CCPR2L = 0b00000000;
		//Set Duty by 0
		CCP2CON = 0b00001100;
		//Enable PWM
	}
}

void PWM_C2(const unsigned short duty_Percent)
{
////////////////////////////////////////
//this function set the PWM for PORTC.f2
////////////////////////////////////////
	if(duty_Percent == 100)
	{
		CCPR1L = 0b00111111;
		//Set Duty by 255.
		CCP1CON = 0b00111100;
		//Enable PWM
	}
	else if(duty_Percent == 75)
	{
		CCPR1L = 0b00101111;
		//Set Duty by 191.
		CCP1CON = 0b00111100;
		//Enable PWM
	}
	else if(duty_Percent == 50)
	{
		CCPR1L = 0b00011111;
		//Set Duty by 127.
		CCP1CON = 0b00111100;
		//Enable PWM
	}
	else if(duty_Percent == 25)
	{
		CCPR1L = 0b00001111;
		//Set Duty by 63
		CCP1CON = 0b00111100;
		//Enable PWM
	}
	else
	{
		CCPR1L = 0b00000000;
		//Set Duty by 0
		CCP1CON = 0b00001100;
		//Enable PWM
	}
}

void Init_PWM()
{
//////////////////////////////////////////////////
//this function initialize Timer2 & PWM registers.
//////////////////////////////////////////////////
	PR2 = 0b00111111;
	//set the Timer 2 Period
	T2CON = 0b00000100;
	//Enable Timer 2.
	//Prescale is 1.
	PIE1 = 0;
	PIR1 = 0;
	PIE2 = 0;
	PIR2 = 0;
	//disable all interrupts from the timers & other devices.
    PIE1.TMR1IE = 1;        // Enable Timer 1 interrupts
	delay_ms(100);
}

void Reset_PWM()
{
///////////////////////////////////////////
//this function reset the PWM configuration
///////////////////////////////////////////
  	T2CON = 0;
	//disable timer 2.
	TMR2 = 0;
	//clear TMR2 register.
	delay_ms(100);
  	Init_PWM();
	//reinitialize the PWM
}
//============================ PWM =================================//

//========================== Movement ==============================//
void Track_Line_forward(const unsigned short Lines)
{
//////////////////////////////////////////////////////////////////////////////////
/*this program is used to detect a line and move forward on it and detect any
 *deflection in the movement and debug it, and moving backward if there is no line,
 *and stop after detecting "Lines" number of lines, then exit the function.
 *using Manual PWM*/
//////////////////////////////////////////////////////////////////////////////////
//need to be modified to make it stop between 2 lines.
//////////////////////////////////////////////////////////////////////////////////
unsigned short r_Lines = 0;
	while(r_Lines < Lines)
	{
		Reset_PWM();
////////////////////////////////////////////////////////////////////////////
//======================Car Move backward=================================//
////////////////////////////////////////////////////////////////////////////
		if(Left_Sensor == 0 && Mid_Sensor == 0 && Right_Sensor == 0)
		{
			delay_ms(50);
			//Move backward Motor 1 with 50%
			Left_Motor_Nve = 1;
			PWM_C1(50);
			//Move backward Motor 2 with 50%
			Right_Motor_Nve = 1;
			PWM_C2(50);
			//Setup time.
			delay_ms(100);
			while(Left_Sensor == 0 && Mid_Sensor == 0 && Right_Sensor == 0)
			{
			}
		}
////////////////////////////////////////////////////////////////////////////
//======================Car Move forward==================================//
////////////////////////////////////////////////////////////////////////////
		else if(Mid_Sensor == 1)
		{
			delay_ms(50);
			//Move forward Motor 1 with 100%
			Left_Motor_Nve = 0;
			PWM_C1(100);
			//Move forward Motor 2 with 100%
			Right_Motor_Nve = 0;
			PWM_C2(100);
			//Setup time.
			delay_ms(100);
			while(Mid_Sensor == 1)
			{
			}
		}
////////////////////////////////////////////////////////////////////////////
//======================Car divergented right=============================//
////////////////////////////////////////////////////////////////////////////
		else if(Left_Sensor == 1 && Mid_Sensor == 0 && Right_Sensor == 0)
		{
			delay_ms(50);
			//Move forward Motor 1 with 50%
			Left_Motor_Nve = 0;
			PWM_C1(50);
			//Move forward Motor 2 with 100%
			Right_Motor_Nve = 0;
			PWM_C2(100);
			//Setup time.
			delay_ms(100);
			while(Left_Sensor == 1 && Mid_Sensor == 0 && Right_Sensor == 0)
			{
			}
		}
////////////////////////////////////////////////////////////////////////////
//======================Car divergented Left=============================//
////////////////////////////////////////////////////////////////////////////
		else if(Left_Sensor == 0 && Mid_Sensor == 0 && Right_Sensor == 1)
		{
			delay_ms(50);
			//Move forward Motor 1 with 100%
			Left_Motor_Nve = 0;
			PWM_C1(100);
			//Move forward Motor 2 with 50%
			Right_Motor_Nve = 0;
			PWM_C2(50);
			//Setup time.
			delay_ms(100);
  			while(Left_Sensor == 0 && Mid_Sensor == 0 && Right_Sensor == 1)
			{
			}
		}
////////////////////////////////////////////////////////////////////////////
//=======================Vertical Line detected===========================//
////////////////////////////////////////////////////////////////////////////
		else if(Left_Sensor == 1 && Mid_Sensor == 1 && Right_Sensor == 1)
		{
			delay_ms(200);
			//recheck the line.
			if(Left_Sensor == 1 && Mid_Sensor == 1 && Right_Sensor == 1)
			{
				//there is a line.
				r_Lines++;
				if(r_Lines == Lines)
				{
					Reset_PWM();
					delay_ms(50);
					Left_Motor_Pve = 1;
					Left_Motor_Nve = 1;
					Right_Motor_Pve = 1;
					Right_Motor_Nve = 1;
					delay_ms(5000);
					//wait for 5 sec.
					return;
				}
				else
				{
					//get out of the line.
					delay_ms(500);
				}
			}
		}
	}
}

void Rotate_Right()
{
//////////////////////////////////////////////////////////////////////////////////
/*this program is used to rotate right till the first line detected (90 Degree)*/
//////////////////////////////////////////////////////////////////////////////////
	//reset the counter.
	Init_PWM();
	PWM_C1(75);
	Left_Motor_Nve = 0;
	PWM_C2(25);
	Right_Motor_Nve = 1;
	//rotate.
	
	delay_ms(1000);
	//wait until the robot is out of the line.
	
	//hult until the robot sense a line.
	while(Mid_Sensor == 0)
	{
	}
	
	//stop the robot.
	Reset_PWM();
	delay_ms(50);
	Left_Motor_Pve = 1;
	Left_Motor_Nve = 1;
	Right_Motor_Pve = 1;
	Right_Motor_Nve = 1;
	delay_ms(5000);
}

void Rotate_Left()
{
//////////////////////////////////////////////////////////////////////////////////
/*this program is used to rotate left till the first line detected (90 Degree)*/
//////////////////////////////////////////////////////////////////////////////////
	//reset the counter.
	Init_PWM();
	PWM_C2(75);
	Right_Motor_Nve = 0;
	PWM_C1(25);
	Left_Motor_Nve = 1;
	//rotate.
	
	delay_ms(1000);
	//wait until the robot is out of the line.
	
	//hult until the robot sense a line.
	while(Mid_Sensor == 0)
	{
	}
	
	//stop the robot.
	Reset_PWM();
	delay_ms(50);
	Left_Motor_Pve = 1;
	Left_Motor_Nve = 1;
	Right_Motor_Pve = 1;
	Right_Motor_Nve = 1;
	delay_ms(5000);
}
//========================== Movement ==============================//

//========================== Lifters ===============================//
void Lifter_upward()
{
//////////////////////////////////////////////////////////////////////////////////
//this program is used to move the motor upward until the limit sensor is enabled
//////////////////////////////////////////////////////////////////////////////////
	while(1)
	{
		//if the lifter is not at top point.
		if(upper_sensor == 0)
		{
			delay_ms(50);
			//rotate the lifter motor upward
			Lifter_Nve = 0;
			Lifter_Pve = 1;
			delay_ms(100);
			
			while(upper_sensor == 0)
			{
			}
			
			//stop the motor.
			delay_ms(50);
			Lifter_Nve = 1;
			Lifter_Pve = 1;
			delay_ms(100);
		}
		//if the lifter is at top.
		else
		{
			delay_ms(50);
			//stop the motor.
			Lifter_Nve = 1;
			Lifter_Pve = 1;
			delay_ms(100);
		}
	}
}

void Lifter_downward()
{
//////////////////////////////////////////////////////////////////////////////////
//this program is used to move the motor downward until the limit sensor is enabled
//////////////////////////////////////////////////////////////////////////////////
	while(1)
	{
		//if the lifter is not at bottom point.
		if(lower_sensor == 0)
		{
			delay_ms(50);
			//rotate the lifter motor upward
			Lifter_Nve = 1;
			Lifter_Pve = 0;
			delay_ms(100);
			
			while(lower_sensor == 0)
			{
			}
			
			//stop the motor.
			delay_ms(50);
			Lifter_Nve = 1;
			Lifter_Pve = 1;
			delay_ms(100);
		}
		//if the lifter is at bottom.
		else
		{
			delay_ms(50);
			//stop the motor.
			Lifter_Nve = 1;
			Lifter_Pve = 1;
			delay_ms(100);
		}
	}
}
//========================== Lifters ===============================//

//====================== Horizontal Arm ============================//
void horizontal_forward()
{
//////////////////////////////////////////////////////////////////////////////////
//this program is used to move the motor forward until the limit sensor is enabled
//////////////////////////////////////////////////////////////////////////////////
	while(1)
	{
		//if the Arm is not extended.
		if(front_sensor == 0)
		{
			delay_ms(50);
			//rotate the horizontal motor forward.
			horizontal_Nve = 0;
			horizontal_Pve = 1;
			delay_ms(100);
			
			while(front_sensor == 0)
			{
			}
			
			//stop the motor.
			delay_ms(50);
			horizontal_Nve = 1;
			horizontal_Pve = 1;
			delay_ms(100);
		}
		//if the Arm is extended.
		else
		{
			delay_ms(50);
			//stop the motor.
			horizontal_Nve = 1;
			horizontal_Pve = 1;
			delay_ms(100);
		}
	}
}

void horizontal_backward()
{
//////////////////////////////////////////////////////////////////////////////////
//this program is used to move the motor backward until the limit sensor is enabled
//////////////////////////////////////////////////////////////////////////////////
	while(1)
	{
		//if the Arm is extended.
		if(back_sensor == 0)
		{
			delay_ms(50);
			//rotate the horizontal motor upward
			horizontal_Nve = 1;
			horizontal_Pve = 0;
			delay_ms(100);
			
			while(back_sensor == 0)
			{
			}
			
			//stop the motor.
			delay_ms(50);
			horizontal_Nve = 1;
			horizontal_Pve = 1;
			delay_ms(100);
		}
		//if the Arm is not extended.
		else
		{
			delay_ms(50);
			//stop the motor.
			horizontal_Nve = 1;
			horizontal_Pve = 1;
			delay_ms(100);
		}
	}
}
//====================== Horizontal Arm ============================//

//======================== Main Program ============================//
void Init_Main()
{
//////////////////////////////////////////////////
//this function Initialize the PIC before starting
//////////////////////////////////////////////////
	delay_ms(200);
	TRISB=0xff;		//PortB is used as input port from the sensors
					//that detect the direction of the robot.
					
	TRISC=0x00;		//PortC is used as the output signal for the Motors
					//that control the movement & speed of the Motors.
					
	//initializing base Motors by zero
	Left_Motor_Nve = 0;
	Right_Motor_Nve = 0;
	Left_Motor_Pve = 0;
	Right_Motor_Pve = 0;
	//initializing the PWM for C1 & C2
	Init_PWM();
	delay_ms(200);
}

void main()
{
	Init_Main();
	
	while(1)
	{
		Track_Line_forward(4);
		Lifter_upward();
		Rotate_Right();
		Track_Line_forward(3);
		Lifter_downward();
	}
}