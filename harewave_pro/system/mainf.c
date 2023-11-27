#include "stm32f10x.h"                  // Device header#include "stm32f10x.h"                  // Device header
#include "delay.h"											//相比上一个版本多了个闪灯并归零
#include "LED.H"												//表示正常
#include "Serial.h"											//串口通信
#include "PWM.h"												//呼吸灯
#include "OLED.h"												//反映状态
#include "PWM2.h"
#include "Timer.h"
//研究一下发送数据包    控制倒计时数字 小于60  当用户输入大于60，报错弹窗     ，       休眠状态
extern uint16_t i; 
extern uint16_t bnmax; 
extern uint8_t RxData;
extern uint16_t csum;//计算改变次数    A呼吸，B是常  C控制亮度
extern uint16_t Cconst;//常亮颜色控制器		01234567  off rgbwcpy
extern uint16_t CPWM;//呼吸颜色控制器				01234567  off rgbwcpy
extern uint16_t cbn;//亮度控制器								//A0 :PWMRED  A1:PWM_GREEN  A2:PWM_BLUE
extern uint16_t cnum;//定时器的计数
extern uint16_t ccnum;//控制定时器的计数
void osserial(void);//中断控制
void main_init(void);//初始化
void lconst(uint16_t cbn,uint16_t Cconst);//常亮
void lpwm(uint16_t i,uint16_t CPWM);// 呼吸   
void Clconst(uint16_t RxData);//常亮  改变常亮颜色控制器
void Clpwm(uint16_t RxData);// 呼吸   改变呼吸颜色控制器
void ccbn(uint16_t RxData);//		    	改变亮度
void coled(void );
void EnterStandbyMode(void);	
	
void osserial(void)//串口触发
{
	
		if (Serial_GetRxFlag() == 1)
		{
			
			
			RxData = Serial_GetRxData();
			if(RxData /16==0x0A)
			{
				if(RxData ==0xAF)
				{
						ccnum=1;cnum=10;
				}
			
			
			  else Clpwm (RxData);
			}
			else if(RxData /16==0x0B)Clconst(RxData );

//			else if(RxData ==0xC1){ccnum =1;cnum=10;}
			//else Clconst(RxData);
			else if(RxData/16 ==0x0C){
			 if(RxData %16==0x00)ccnum =0;			
			 else {ccnum=1;cnum =RxData %16-2;} 
			
			
			}
			else if(RxData/16 ==0x0D){
			 if(RxData %16==0x00)ccnum =0;			
			 else {ccnum=1;cnum =RxData %16+12;} 
			
			
			}
			else if(RxData/16 ==0x0E){
			 if(RxData %16==0x00)ccnum =0;			
			 else {ccnum=1;cnum =RxData %16+28;} 
			
			
			}
			else if(RxData/16 ==0x0F){
			 if(RxData %16==0x00)ccnum =0;
			 
			 else {ccnum=1;cnum =RxData %16+44;} 
			
			
			}
			
			else {int a =(RxData/16)*10 +RxData%16;
					if(a<100)cbn=a;
				else {cnum =a;
					ccnum =1;}
				
			
			
			}

			coled();
			Serial_SendByte(RxData);//发送到上位机
			
			
			
		}
}//串口触发

void main_init(void)
{
		LED_init();LED_W_ON ();//全开表示正常运行
	PWM_Init();PWM2_Init();

	
	OLED_Init ();
	Serial_Init ();
	OLED_ShowString (1,1,"hello world");//12
	OLED_ShowString (2,1,"hello world");//12
	OLED_ShowString (3,1,"hello world");//12
	OLED_ShowString (4,1,"hello world");//12
	Delay_ms (700);
	OLED_Clear ();
	
	OLED_ShowString (1,1,"timer:");//6
	OLED_ShowString (2,1,"Breath:");//7
	OLED_ShowString (3,1,"led:");//4
	OLED_ShowString (4,1,"lum:");//4
	Timer_Init ();

}
void main_reset(void ){


	// csum=0;//计算改变次数    A呼吸，B是常  C控制亮度
	 Cconst=0;//常亮颜色控制器		01234567  off rgbwcpy
	 CPWM=0;//呼吸颜色控制器				01234567  off rgbwcpy
	 cbn=0;//亮度控制器								//A0 :PWMRED  A1:PWM_GREEN  A2:PWM_BLUE   
	 cnum=0;//定时器的计数      
	ccnum=0;//控制定时器的计数
	}
void coled(void )//控
{
	
	if(ccnum ==0)OLED_ShowString (1,12,"OFF");
	else if(ccnum ==1)OLED_ShowString (1,12,"ON ");
	OLED_ShowNum (1,8,cnum,2);///显示
		//OLED_ShowNum (2,8,CPWM ,2);
	if(CPWM==1)
	OLED_ShowString(2, 8, "RED   ");
	else if(CPWM==2)
	OLED_ShowString(2, 8, "GREEN ");
	else if(CPWM==3)
	OLED_ShowString(2, 8, "BLUE  ");
	else if(CPWM==4)
	OLED_ShowString(2, 8, "WHITE ");
	else if(CPWM==5)
	OLED_ShowString(2, 8, "CHING ");
	else if(CPWM==6)
	OLED_ShowString(2, 8, "PURPLE");
	else if(CPWM==7)
	OLED_ShowString(2, 8, "YELLOW");
	else if(CPWM==0)
	OLED_ShowString(2, 8, "NONE  ");
	
	
	//OLED_ShowNum (3,8,Cconst ,2);
	if(Cconst==1)
	OLED_ShowString(3, 8, "RED   ");
	else if(Cconst==2)
	OLED_ShowString(3, 8, "GREEN ");
	else if(Cconst==3)
	OLED_ShowString(3, 8, "BLUE  ");
	else if(Cconst==4)
	OLED_ShowString(3, 8, "WHITE ");
	else if(Cconst==5)
	OLED_ShowString(3, 8, "CHING ");
	else if(Cconst==6)
	OLED_ShowString(3, 8, "PURPLE");
	else if(Cconst==7)
	OLED_ShowString(3, 8, "YELLOW");
	else if(Cconst==0)
	OLED_ShowString(3, 8, "NONE  ");
	OLED_ShowString(3, 5, "   ");
	OLED_ShowString(4, 5, "   ");
	OLED_ShowString(4, 11, "     ");
	OLED_ShowNum (4,8,cbn ,2);

}
void Clpwm(uint16_t RxData )
{
	if(RxData ==0xA0)CPWM=0; 
	else if(RxData ==0XA1)CPWM=1; 
	else if(RxData ==0XA2)CPWM=2; 
	else if(RxData ==0XA3)CPWM=3; 
	else if(RxData ==0XA4)CPWM=4; 
	else if(RxData ==0XA5)CPWM=5; 
	else if(RxData ==0XA6)CPWM=6; 
	else if(RxData ==0XA7)CPWM=7; 
}
	
void Clconst(uint16_t RxData)
{
	if(RxData ==0XB0)Cconst=0;
	else if(RxData ==0XB1)Cconst=1;
	else if(RxData ==0XB2)Cconst=2;
	else if(RxData ==0XB3)Cconst=3;
	else if(RxData ==0XB4)Cconst=4;
	else if(RxData ==0XB5)Cconst=5;
	else if(RxData ==0XB6)Cconst=6;
	else if(RxData ==0XB7)Cconst=7;
}
/*
void ccbn(uint16_t RxData)	{
	if(RxData ==0XC0)cbn =0;
	else if(RxData ==0XC1)cbn =5;
	else if(RxData ==0XC2)cbn =10;
	else if(RxData ==0XC3)cbn =20;
	else if(RxData ==0XC4)cbn =40;
	else if(RxData ==0XC5)cbn =50;
	else if(RxData ==0XC6)cbn =60;
	else if(RxData ==0XC7)cbn =70;
	else if(RxData ==0XC8)cbn =80;
	else if(RxData ==0XC9)cbn =99;
	
	 //if(RxData%16=='C')cbn =RxData%16;
	
}*/

void lconst(uint16_t cbn,uint16_t Cconst)//常亮   刚试了一下 ，这个函数有问题，可能是switch，现在尝试使用if
{
	
		
		if (Cconst ==0)PWM2_SetCompare_no();
		else if (Cconst ==1)rpwm2( cbn);
		else if (Cconst ==2)gpwm2( cbn);
		else if (Cconst ==3)bpwm2( cbn);
		else if(Cconst ==4)wpwm2( cbn);
		else if(Cconst ==5)cpwm2( cbn);
		else if(Cconst ==6)ppwm2( cbn);
		else if(Cconst ==7)ypwm2( cbn);
	
}	

void lpwm(uint16_t i,uint16_t CPWM)// 呼吸
{
		if (CPWM ==0)PWM_SetCompare_no();
		else if (CPWM ==1)rpwm( i);
		else if (CPWM ==2)gpwm( i);
		else if(CPWM ==3)bpwm( i);
		else if (CPWM ==4)wpwm( i);
		else if(CPWM ==5)cpwm( i);
		else if(CPWM ==6)ppwm( i);
		else if(CPWM ==7)ypwm( i);

}
void ledblink(void)
{
	wpwm (25);wpwm2(25);Delay_ms (400);
	wpwm (0);wpwm2(0);Delay_ms (400);
	wpwm (25);wpwm2(25);Delay_ms (400);
	wpwm (0);wpwm2(0);Delay_ms (400);
	wpwm (25);wpwm2(25);Delay_ms (400);
	wpwm (0);wpwm2(0);Delay_ms (400);

	
	

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
		if(cnum==0){ccnum=0;ledblink ();}
		}
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}	


//// 定义退出待机模式函数
//void ExitStandbyMode(void)
//{
//  // 重新开启所有外设
//  RCC_DeInit();
//  SystemInit();
//  
//  // 重新初始化所有外设
//  RCC_Configuration();
//  GPIO_Configuration();
//  USART_Configuration();
//  // ...
//}
