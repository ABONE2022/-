#include "stm32f10x.h"  // Device header
//A3:RED; A4:GREEN; A5:BLUE  
#include "oled.h"
void LED_init(void)
{


RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}
///////////
void LED_R_oFF(void){
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
}
void LED_R_ON(void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_All);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}
////////////
void LED_G_oFF(void){
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}
void LED_G_ON(void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_All);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}
///////

void LED_B_oFF(void){	
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}
void LED_B_ON(void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_All);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
}
////////////


void LED_W_oFF(void){	
	GPIO_ResetBits(GPIOA, GPIO_Pin_All);	
	
}
void LED_W_ON(void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_All);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);GPIO_SetBits(GPIOA,GPIO_Pin_3);GPIO_SetBits(GPIOA,GPIO_Pin_4);
}
////////////
//////蓝红
void LED_P_oFF(void){	
		
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}
void LED_P_ON(void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_All);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);GPIO_SetBits(GPIOA,GPIO_Pin_5);
}
////////////
//////青色 蓝绿
void LED_C_oFF(void){	
		
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}
void LED_C_ON(void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_All);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);GPIO_SetBits(GPIOA,GPIO_Pin_5);
}
////////////黄色 绿红
void LED_Y_oFF(void){	
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}
void LED_Y_ON(void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_All);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);GPIO_SetBits(GPIOA,GPIO_Pin_4);
}



































