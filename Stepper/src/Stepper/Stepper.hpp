/**
	Stepper.hpp
	Purpose: Library to be used with the TB6600 Stepper Driver and a Raspberry Pi

	@author Kaushik Prakash
	@version 1.0 03/01/19
*/

#include <vector>

class Stepper {

	public:
		Stepper(const int DIRECTION_PIN, const int PULSE_PIN, const int MICRO_STEP_SIZE);
		void pulse(bool direction, float pulseDelay);             // Take 1 step
		void relStep(const int STEPS);                          // Step a certain number of times
		void absStep(const int DESIRED_POSITION);               // Step to a certain position
		void setMaxAcceleration(const float MAX_ACCELERATION);  // Set max acceleration rev/s^2
		void setMaxVelocity(const float MAX_VELOCITY);          // Set max velocity in rev/s
		int getCurrentPosition();

	private:
		std::vector<float> _allDelays;  							// Contains time intervals for every step in the routine
		float _multiplier;	// Multiplier [19] to calculate time interval for next step [20]
		const float _propAccel = 0.2;   		        			// Proportion of stepper routine to be accelerating/decelerating
		const int _frqcy = 100;               						// Frequency of timer in ticks per second (100 for RPI 3 
		
		int _maxSteps; 					// Number of steps in a revolution after microstepping
		float _initVel;    				// Starting velocity in steps/s
		float _maxVel;        	// Max velocity in steps/s
		float _maxAccel;	// Max acceleration in steps/s^2
		float _currDelay;   				// Delay of the next step to be taken
		int _stopAccel;     				// Step number at which to stop acceleration
		int _startDecel;      				// Step number at which to start deceleration
		int _currPosition;				// Current Position of Stepper Shaft
		int _microStepSize; 			// Microstepping size in microsteps/step: 1/2, 1/4 would be 2, 4 etc.
		int _directionPin;  				// Direction pin on the RPI using Broadcom pin numbers
		int _pulsePin;         				// Signal pin on the RPI using Broadcom pin numbers
		

		void calculateParameters(const int STEPS);  // Calculate time intervals for each step
};
