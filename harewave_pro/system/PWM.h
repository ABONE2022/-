#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);
void PWM_SetCompare1(uint16_t Compare);
void PWM_SetCompare2(uint16_t Compare);
void PWM_SetCompare3(uint16_t Compare);
void rpwm(uint16_t cbn);
void gpwm(uint16_t cbn);
void bpwm(uint16_t cbn);
void wpwm(uint16_t cbn);
void cpwm(uint16_t cbn);
void ypwm(uint16_t cbn);
void ppwm(uint16_t cbn);
void PWM_SetCompare_no(void);
#endif
