#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "LED.H"												//表示正常
#include "Serial.h"											//串口通信
#include "PWM.h"												//呼吸灯 //PA2:RED CH3;  PA1:BLUE CH2 PA0:GREEN CH1
#include "OLED.h"												

#include "PWM2.h"												//常亮  可控亮度PB0:RED;  PA7:BLUE  PA6:GREEN
#include "mainf.h"
#include "Timer.h"  
//C0:off  C1:on  
uint16_t i; 
uint16_t bnmax=60; 
uint8_t RxData;
uint16_t csum=0;//计算改变次数    A呼吸，B是常  C控制亮度
uint16_t Cconst=0;//常亮颜色控制器		01234567  off rgbwcpy
uint16_t CPWM=0;//呼吸颜色控制器				01234567  off rgbwcpy
uint16_t cbn=0;//亮度控制器								//A0 :PWMRED  A1:PWM_GREEN  A2:PWM_BLUE   
uint16_t cnum=0;//定时器的计数      
uint16_t ccnum=0;//控制定时器的计数



int main(void)	
{



	//main_init ();
	//	while (1)
	{
////////////////////////////////////////////////////start
		
		for ( i= 0; i <= bnmax; i++)//UP
		{
			osserial ();
			coled ();
			lconst (cbn ,Cconst );	
			lpwm (i,CPWM );
//				OLED_ShowNum (3,12,i,2);	
			Delay_ms(10);	
		}
			for (i = 0; i <= bnmax; i++)//DOWN
		{
			osserial ();
			coled ();
			lconst (cbn  ,Cconst );	
			lpwm (bnmax -i,CPWM );
//			 OLED_ShowNum (3,12,i,2);			
			Delay_ms(10);
		}		
	}
///////////////////////////////////end
}   
	  
void TIM4_IRQHandler(void)
{
	
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
		osserial ();
		if(ccnum ==0)cnum =0;
		else if(ccnum==1)
		{
			cnum--;
		if(cnum==0){ccnum=0;ledblink ();main_init ();}
		}
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}	
	

