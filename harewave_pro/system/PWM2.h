#ifndef __PWM2_H
#define __PWM2_H

void PWM2_Init(void);
void PWM2_SetCompare1(uint16_t Compare);
void PWM2_SetCompare2(uint16_t Compare);
void PWM2_SetCompare3(uint16_t Compare);
void rpwm2(uint16_t cbn);
void gpwm2(uint16_t cbn);
void bpwm2(uint16_t cbn);
void wpwm2(uint16_t cbn);
void cpwm2(uint16_t cbn);
void ypwm2(uint16_t cbn);
void ppwm2(uint16_t cbn);
void PWM2_SetCompare_no(void);
	
#endif
