#include "lib_PwmOutAllPin.h"

/** Crée un PwmOutAllPin connecté à la pin spécifié
 *
 *  @param pin Pin à connecter
 */
PwmOutAllPin::PwmOutAllPin(PinName pin) : PwmOutPin(pin)
{
    Pwm_period_us = 20000;
	Pwm_Duty_Cycle = 0.0;
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
	if(value != Pwm_Duty_Cycle)
	{
		Pwm_Duty_Cycle = value;
		UsePwm();
	}
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
	Pwm_period_us = seconds*1000000;
	UsePwm();
}

/** Fixe la période du PWM, spécifié en millisecondes (int), garde le même rapport cyclique.
 */
void PwmOutAllPin::period_ms(int ms)
{
	Pwm_period_us = ms*1000;
	UsePwm();
}

/** Fixe la période du PWM, spécifié en microsecondes (int), garde le même rapport cyclique.
 */
void PwmOutAllPin::period_us(int us)
{
	Pwm_period_us = us-8;
	UsePwm();
}

/** Fixe la largeur d'impulsion du PWM, spécifié en secondes (float), garde la même période.
 */
void PwmOutAllPin::pulsewidth(float seconds)
{
	Pwm_Duty_Cycle = seconds*1000000/Pwm_period_us;
	UsePwm();
}

/** Fixe la largeur d'impulsion du PWM, spécifié en millisecondes (int), garde la même période.
 */
void PwmOutAllPin::pulsewidth_ms(int ms)
{
	Pwm_Duty_Cycle = ms*1000/Pwm_period_us;
	UsePwm();
}

/** Fixe la largeur d'impulsion du PWM, spécifié en microsecondes (int), garde la même période.
 */
void PwmOutAllPin::pulsewidth_us(int us)
{
	Pwm_Duty_Cycle = us/Pwm_period_us;
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
	SwitchPin.attach_us(this, &PwmOutAllPin::DigitalDown, (Pwm_period_us*Pwm_Duty_Cycle));
	PwmOutPin = 1;
}

void PwmOutAllPin::DigitalDown(void)
{
	SwitchPin.attach_us(this, &PwmOutAllPin::DigitalUp, (Pwm_period_us*(1.0-Pwm_Duty_Cycle)));
	PwmOutPin = 0;
}

void PwmOutAllPin::UsePwm(void)
{
	if((Pwm_Duty_Cycle > 0.0) && (Pwm_Duty_Cycle < 1.0))
	{
		DigitalUp();
	}
	else if(Pwm_Duty_Cycle >= 1.0)
	{
		Pwm_Duty_Cycle = 1.0;
		SwitchPin.detach();
		PwmOutPin = 1;
	}
	else
	{
		Pwm_Duty_Cycle = 0.0;
		SwitchPin.detach();
		PwmOutPin = 0;
	}
}