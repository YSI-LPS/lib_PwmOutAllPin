/** Lib PwmOutAllPin
*
* Copyright (c) 2014, cstyles (http://mbed.org)
*
* Exemple:
* @code
* #include "mbed.h"
* #include "lib_PwmOutAllPin.h"
* 
* PwmOutAllPin pin1(p20);
* PwmOutAllPin pin2(p12);
* 
* int main()
* {
*     pin2.period(0.0002);
*     pin2 = 0.25;
*     pin1 = 0.5;
*     pin1.period_us(20);
* 
*     while(1)
*     {
*     	wait(0.25);
*     }
* }
* @endcode
* @file          lib_PwmOutAllPin.h 
* @purpose       library for PwmOut on all pins
* @date          2015
* @author        Yannic Simon
*/

#ifndef DEF_lib_PwmOutAllPin_H
#define DEF_lib_PwmOutAllPin_H

#include "mbed.h"

class PwmOutAllPin : public Timeout
{
	public:
    PwmOutAllPin(PinName pin);
	
	void write(float value);
	float read(void);
	void period(float seconds);
	void period_ms(int ms);
	void period_us(int us);
	void pulsewidth(float seconds);
	void pulsewidth_ms(int ms);
	void pulsewidth_us(int us);
	PwmOutAllPin& operator= (float value);
	PwmOutAllPin& operator= (PwmOutAllPin& rhs);
	operator float();

	protected:
	DigitalOut PwmOutPin;
	Timeout SwitchPin;
	Ticker TickerPeriod;
	
	float Pwm_Duty_Cycle;
	int Pwm_period_us;
	int TimeDown;

	void DigitalUp(void);
	void DigitalDown(void);
	void UsePwm(void);
};
	
#endif