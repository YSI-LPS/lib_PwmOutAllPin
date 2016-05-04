/** Lib PwmOutAllPin using TimeOut
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
/** PwmOutAllPin class
 */
class PwmOutAllPin : public Timeout
{
	public:
	/** Crée un PwmOutAllPin connecté à la pin spécifiée
	 *	@note init period 20ms and duty cycle 0%
	 *  @param pin Pin à connecter
	 */
    PwmOutAllPin(PinName pin);
	/** Fixe le rapport cyclique au pourcentage (float) spécifié
	 *
	 *  @param value Une valeure floating-point représentant le rapport cyclique,
	 *    spécifié sous la forme d'un pourcentage. La valeur doit être comprise entre
	 *    0.0f (correspondant à 0%) et 1.0f (correspondant à 100%).
	 *    Les valeurs exterieures à cette plage sont saturées à 0.0f ou 1.0f.
	 */
	void write(float value);
	/** Retourne la valeur courante du rapport cyclique de la sortie, mesurée sous la forme d'un pourcentage (float)
	 *
	 *  @returns
	 *    Une valeur floating-point représentant la valeur courante du rapport cyclique qui est sur la pin de sortie,
	 *    mesurée sous la forme d'un pourcentage. La valeur doit être comprise entre
	 *    0.0f (correspondant à 0%) et 1.0f (correspondant à 100%).
	 */
	float read(void);
	/** Fixe la période du PWM, spécifié en secondes (float), garde le même rapport cyclique.
	 *
	 *  @note
	 *   La résolution est en microsecondes mais les périodes inférieure à 100µs sont imprécises.
	 */
	void period(float seconds);
	/** Fixe la période du PWM, spécifié en millisecondes (int), garde le même rapport cyclique.
	 */
	void period_ms(int ms);
	/** Fixe la période du PWM, spécifié en microsecondes (int), garde le même rapport cyclique.
	 */
	void period_us(int us);
	/** Fixe la largeur d'impulsion du PWM, spécifié en secondes (float), garde la même période.
	 */
	void pulsewidth(float seconds);
	/** Fixe la largeur d'impulsion du PWM, spécifié en millisecondes (int), garde la même période.
	 */
	void pulsewidth_ms(int ms);
	/** Fixe la largeur d'impulsion du PWM, spécifié en microsecondes (int), garde la même période.
	 */
	void pulsewidth_us(int us);
	/** raccourci pour write()
	*/
	PwmOutAllPin& operator= (float value);
	/** raccourci pour effectuer des opperations mathématique avec write()
	*/ 
	PwmOutAllPin& operator= (PwmOutAllPin& rhs);
	/** raccourci pour read()
	 */
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