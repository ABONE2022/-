#include "stm32f10x.h"                  // Device header
//PB0:RED CH3;  PA7:BLUE CH2 PA6:GREEN CH1

void PWM2_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7 |GPIO_Pin_0  ;		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR 比较寄存器?
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_Cmd(TIM3, ENABLE);
}
//PB0:RED CH3;  PA7:BLUE CH2 PA6:GREEN CH1
void PWM2_SetCompare1(uint16_t Compare)//green
{
	
	TIM_SetCompare1(TIM3, Compare);
	
}
void PWM2_SetCompare2(uint16_t Compare)//blue
{
	TIM_SetCompare2(TIM3, Compare);
	
}
void PWM2_SetCompare3(uint16_t Compare)//red
{
	TIM_SetCompare3(TIM3, Compare);
	
}
void PWM2_SetCompare_no(void)//全灭
{
	PWM2_SetCompare1 (0);PWM2_SetCompare2 (0);PWM2_SetCompare3 (0);//先全灭
	
}
void rpwm2(uint16_t cbn)
{
	
		PWM2_SetCompare1 (0);PWM2_SetCompare2 (0);PWM2_SetCompare3 (0);//先全灭
		PWM2_SetCompare3 (cbn);}

void gpwm2(uint16_t cbn)
{
	
		PWM2_SetCompare1 (0);PWM2_SetCompare2 (0);PWM2_SetCompare3 (0);//先全灭
		PWM2_SetCompare1 (cbn);
}
	

void bpwm2(uint16_t cbn)
{
	
		PWM2_SetCompare1 (0);PWM2_SetCompare2 (0);PWM2_SetCompare3 (0);//先全灭
		PWM2_SetCompare2 (cbn);
}
void cpwm2(uint16_t cbn)
{
	
		PWM2_SetCompare1 (0);PWM2_SetCompare2 (0);PWM2_SetCompare3 (0);//先全灭
		PWM2_SetCompare1 (cbn);PWM2_SetCompare2 (cbn);
}
void ypwm2(uint16_t cbn)
{
	
		PWM2_SetCompare1 (0);PWM2_SetCompare2 (0);PWM2_SetCompare3 (0);//先全灭
		PWM2_SetCompare3 (cbn);PWM2_SetCompare1 (cbn);
}
void ppwm2(uint16_t cbn)
{
	
		PWM2_SetCompare1 (0);PWM2_SetCompare2 (0);PWM2_SetCompare3 (0);//先全灭
		PWM2_SetCompare3 (cbn);PWM2_SetCompare2 (cbn);
}
void wpwm2(uint16_t cbn)
{	
		PWM2_SetCompare1 (0);PWM2_SetCompare2 (0);PWM2_SetCompare3 (0);//先全灭
		PWM2_SetCompare3 (cbn);PWM2_SetCompare1 (cbn);PWM2_SetCompare2 (cbn);
}

