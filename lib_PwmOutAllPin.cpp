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

#include "lib_PwmOutAllPin.h"

/** Crée un PwmOutAllPin connecté à la pin spécifiée
 *
 *  @param pin Pin à connecter
 */
PwmOutAllPin::PwmOutAllPin(PinName pin) : PwmOutPin(pin)
{
    Pwm_period_us = 20000;
	Pwm_Duty_Cycle = 0.0;
	TickerPeriod.attach_us(this, &PwmOutAllPin::DigitalDown, Pwm_period_us);
}

/** Fixe le rapport cyclique au pourcentage (float) spécifié
 *
 *  @param value Une valeure floating-point représentant le rapport cyclique,
 *    spécifié sous la forme d'un pourcentage. La valeur doit être comprise entre
 *    0.0f (correspondant à 0%) et 1.0f (correspondant à 100%).
 *    Les valeurs exterieures à cette plage sont saturées à 0.0f ou 1.0f.
 */
void PwmOutAllPin::write(float value)
{
	Pwm_Duty_Cycle = value;
	UsePwm();
}

/** Retourne la valeur courante du rapport cyclique de la sortie, mesurée sous la forme d'un pourcentage (float)
 *
 *  @returns
 *    Une valeur floating-point représentant la valeur courante du rapport cyclique qui est sur la pin de sortie,
 *    mesurée sous la forme d'un pourcentage. La valeur doit être comprise entre
 *    0.0f (correspondant à 0%) et 1.0f (correspondant à 100%).
 */
float PwmOutAllPin::read(void)
{
	return Pwm_Duty_Cycle;
}

/** Fixe la période du PWM, spécifié en secondes (float), garde le même rapport cyclique.
 *
 *  @note
 *   La résolution est en microsecondes mais les périodes inférieure à 100µs sont imprécises.
 */
void PwmOutAllPin::period(float seconds)
{
	period_us(seconds*1000000);
}

/** Fixe la période du PWM, spécifié en millisecondes (int), garde le même rapport cyclique.
 */
void PwmOutAllPin::period_ms(int ms)
{
	period_us(ms*1000);
}

/** Fixe la période du PWM, spécifié en microsecondes (int), garde le même rapport cyclique.
 */
void PwmOutAllPin::period_us(int us)
{
	if(us != Pwm_period_us)
	{
		Pwm_period_us = us;
		UsePwm();
		TickerPeriod.attach_us(this, &PwmOutAllPin::DigitalDown, Pwm_period_us);
	}
}

/** Fixe la largeur d'impulsion du PWM, spécifié en secondes (float), garde la même période.
 */
void PwmOutAllPin::pulsewidth(float seconds)
{
	pulsewidth_us(seconds*1000000);
}

/** Fixe la largeur d'impulsion du PWM, spécifié en millisecondes (int), garde la même période.
 */
void PwmOutAllPin::pulsewidth_ms(int ms)
{
	pulsewidth_us(ms*1000);
}

/** Fixe la largeur d'impulsion du PWM, spécifié en microsecondes (int), garde la même période.
 */
void PwmOutAllPin::pulsewidth_us(int us)
{
	Pwm_Duty_Cycle = (float)us/Pwm_period_us;
	UsePwm();
}

/** raccourci pour write()
*/
PwmOutAllPin& PwmOutAllPin::operator= (float value)
{
	write(value);
    return *this;
}

/** raccourci pour effectuer des opperations mathématique avec write()
*/ 
PwmOutAllPin& PwmOutAllPin::operator= (PwmOutAllPin& rhs)
{
	write(rhs.read());
	return *this;
}
 
/** raccourci pour read()
 */
PwmOutAllPin::operator float()
{
	return read();
}

void PwmOutAllPin::DigitalUp(void)
{
	PwmOutPin = 1;
}

void PwmOutAllPin::DigitalDown(void)
{
	if((Pwm_Duty_Cycle > 0.0) && (Pwm_Duty_Cycle < 1.0))
	{
		PwmOutPin = 0;
		SwitchPin.attach_us(this, &PwmOutAllPin::DigitalUp, TimeDown);
	}
}

void PwmOutAllPin::UsePwm(void)
{
	if((Pwm_Duty_Cycle > 0.0) && (Pwm_Duty_Cycle < 1.0))
	{
		TimeDown = Pwm_period_us*(1.0-Pwm_Duty_Cycle);
	}
	else if(Pwm_Duty_Cycle >= 1.0)
	{
		SwitchPin.detach();
		Pwm_Duty_Cycle = 1.0;
		PwmOutPin = 1;
	}
	else
	{
		SwitchPin.detach();
		Pwm_Duty_Cycle = 0.0;
		PwmOutPin = 0;
	}
}