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
	
	int Pwm_period_us;
	float Pwm_Duty_Cycle;
	int TimeDown;

	void DigitalUp(void);
	void DigitalDown(void);
	void UsePwm(void);
};
	
#endif