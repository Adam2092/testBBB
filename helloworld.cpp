#include <roboticscape.h>
#include <rc_usefulincludes.h>

#include <iostream>

/* typedef enum test_mode_t{
	DISABLED,
	SERVO,
	ESC,
	MICROSECONDS,
	SWEEP,
	RADIO
}test_mode_t; */

int main(int argc, char *argv[]){
	double servo_pos = -1.2; // servo position
	// double sweep_limit = 0;
	// double esc_throttle = 0;
	// int width_us = 0;
	int ch = 1; // channel number
	// double direction = 1; // switches between 1 & -1 in sweep mode
	// int c;
	// int all = 1;	// set to 0 if a channel -c  argument is given 
	// test_mode_t mode = DISABLED; //start mode disabled
	int power_en = 0; // change to 1 if user wishes to enable power rail (??? not sure)
	// int frequency_hz = 50; // default 50hz frequency to send pulses
	// int toggle = 0;
	// int i;
	
	std::cout << "This is a test of servo and engine by AdamK." << std::endl;
	if(rc_initialize())
	{
		std::cout << "ERROR: failed to init. Are you root?" << std::endl;
		return -1;
	}
	if(power_en)
	{
		std::cout << "Turning on 6V Servo Power Rail." << std::endl;
		rc_enable_servo_power_rail();
	}
	
	//main loop starts here
	int timer = 0;
	while((rc_get_state()!=EXITING)&&(timer < 5))
	{
		std::cout << "Turning trial: " << (timer+1) << " ... ";
		if(rc_send_servo_pulse_normalized(ch, servo_pos))
		{
			std::cout << "succeed." << std::endl;
		}
		else
		{
			std::cout << "failed!" << std::endl;
		}
		rc_usleep(1000);
		servo_pos *= -1;
		timer++;
	}
	std::cout << "Turing function test executed. Cleaning up... " << std::endl;
	rc_cleanup();
	
	return 1;
}