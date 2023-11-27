#ifndef __MAINF_H
#define __MAINF_H

void osserial(void);//中断控制
void main_init(void);//初始化
void lconst(uint16_t cbn,uint16_t Cconst);//常亮
void lpwm(uint16_t i,uint16_t CPWM);// 呼吸   
void Clconst(uint16_t RxData);//常亮  改变常亮颜色控制器
void Clpwm(uint16_t RxData);// 呼吸   改变呼吸颜色控制器
void ccbn(uint16_t RxData);//		    	改变亮度
void coled(void );
void ledblink(void);
void TIM4_IRQHandler(void);
#endif
