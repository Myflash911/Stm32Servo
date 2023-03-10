#include "control.h"	
#include "motor.h"
#include "led.h"
extern int KDshu;//点电机要转的圈数/11
extern u16 motor_pwm1;
int pi_motor_next_enc1 = 0;   //pi调速用来计算的上一次编码器值
int pi_motor_next_enc2 = 0;
int pi_motor_next_enc3 = 0;
int pi_motor_next_enc4 = 0;

int pi_motor_new_enc1 = 0;   //pi调速用来计算的上一次编码器值
int pi_motor_new_enc2 = 0;
int pi_motor_new_enc3 = 0;
int pi_motor_new_enc4 = 0;

int Target_velocity1	= 50;  //设定速度控制的目标速度为50个脉冲每10ms
int Target_velocity2	= 50;  //设定速度控制的目标速度为50个脉冲每10ms
int Target_velocity3	= 50;  //设定速度控制的目标速度为50个脉冲每10ms
int Target_velocity4	= 20;  //设定速度控制的目标速度为50个脉冲每10ms

int Pwm1 = 0;   //pi调速用来计算的上一次编码器值
int Pwm2 = 0;
int Pwm3 = 0;
int Pwm4 = 150;
int rnm  =0 ;
u16 t;
	float cs =0;
/************获得四路编码器的码字差值*************/
void Read_Encoder_cha()
{
	int jj1,jj2,jj3,jj4;
			jj1   = TIM_GetCounter(TIM2); 
			jj2		= TIM_GetCounter(TIM3); 
			jj3 	= TIM_GetCounter(TIM4); 
			jj4 	= TIM_GetCounter(TIM5); 
			
			
	
			pi_motor_new_enc1  = jj1 - pi_motor_next_enc1;
			pi_motor_new_enc2  = jj2 - pi_motor_next_enc2;
			pi_motor_new_enc3  = jj3 - pi_motor_next_enc3;
//	if(jj4 - pi_motor_next_enc4<0)
//	{
//		pi_motor_new_enc4  = jj4 - pi_motor_next_enc4+65535;
//	}
//	else
			pi_motor_new_enc4  = jj4 - pi_motor_next_enc4;
	
			pi_motor_next_enc1 = jj1;
			pi_motor_next_enc2 = jj2;
			pi_motor_next_enc3 = jj3;
			pi_motor_next_enc4 = jj4;

}

void TIM6_IRQHandler(void)   //TIM3中断
{	
	
	
	u16  j=0;

	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIMx更新中断标志 
			
			
			if(KDshu!=0)
				{
			
				if(TIM_GetCounter(TIM5)!=0)  j=TIM_GetCounter(TIM5);
					
					
				if(motor_pwm1<255)//说明逆时针转
				{  if((j-0)>=KDshu)
					{
							MOTOR_STOP(1); 
							MOTOR_STOP(2);
						TIM_SetCounter(TIM2, 0);
						TIM_SetCounter(TIM3, 0);
						TIM_SetCounter(TIM4, 0);
						TIM_SetCounter(TIM5, 0);
							KDshu=0;
						
						
						if(USART_GetFlagStatus(USART2,USART_FLAG_TC)==SET)  USART_ClearFlag(USART2,USART_FLAG_TC);//
						USART_SendData(USART2,'f');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
						USART_SendData(USART2,'i');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
						USART_SendData(USART2,'n');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
						USART_SendData(USART2,'i');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
						USART_SendData(USART2,'s');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
						USART_SendData(USART2,'h');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结?
						USART_SendData(USART2,'\r');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
//						USART_SendData(USART2,'\n');
						
					}
					
					
					
					
					
					
					
					
				
				}
				 if(motor_pwm1>255)
				{  if(((11000-j)>=KDshu)&&(j!=0))
					{
							MOTOR_STOP(1); 
							MOTOR_STOP(2); 
						TIM_SetCounter(TIM2, 0);
						TIM_SetCounter(TIM3, 0);
						TIM_SetCounter(TIM4, 0);
						TIM_SetCounter(TIM5, 0);
							KDshu=0;
						
						
						if(USART_GetFlagStatus(USART2,USART_FLAG_TC)==SET)  USART_ClearFlag(USART2,USART_FLAG_TC);//
						USART_SendData(USART2,'f');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
						USART_SendData(USART2,'i');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
						USART_SendData(USART2,'n');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
						USART_SendData(USART2,'i');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
						USART_SendData(USART2,'s');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
						USART_SendData(USART2,'h');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结?
						USART_SendData(USART2,'\r');
						while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
//						USART_SendData(USART2,'\n');

					}
					
					
					
					
				
				}
					
				
				

				
				
			
			}

			
			
			
			
			
			
			
			
			
			
			
			

		}
}



/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM
返回  值：无
**************************************************************************/
void Set_Pwm()
{							
			if(Pwm1<0)		
			{
							TIM_SetCompare1(TIM8,0);
							TIM_SetCompare2(TIM8,(unsigned char)Pwm1);
			}
			else 
			{
							TIM_SetCompare1(TIM8,(unsigned char)Pwm1);
							TIM_SetCompare2(TIM8,0);
			}
			if(Pwm2<0)		
			{
							TIM_SetCompare3(TIM8,0);
							TIM_SetCompare4(TIM8,(unsigned char)Pwm2);
			}
			else 
			{
							TIM_SetCompare3(TIM8,(unsigned char)Pwm2);
							TIM_SetCompare4(TIM8,0);
			}
			if(Pwm1<0)		
			{
							TIM_SetCompare1(TIM1,0);
							TIM_SetCompare2(TIM1,(unsigned char)Pwm3);
			}
			else 
			{
							TIM_SetCompare1(TIM1,(unsigned char)Pwm3);
							TIM_SetCompare2(TIM1,0);
			}
			if(Pwm1<0)		
			{
							TIM_SetCompare3(TIM1,0);
							TIM_SetCompare4(TIM1,(unsigned char)Pwm4);
			}
			else 
			{
							TIM_SetCompare3(TIM1,(unsigned char)Pwm4);
							TIM_SetCompare4(TIM1,0);
			}

}

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=200;    //===PWM满幅是7200 限制在7100
    if(Pwm1<-Amplitude) Pwm1=-Amplitude;	
		if(Pwm1>Amplitude)  Pwm1=Amplitude;	
	  if(Pwm2<-Amplitude) Pwm2=-Amplitude;	
		if(Pwm2>Amplitude)  Pwm2=Amplitude;	
	  if(Pwm3<-Amplitude) Pwm3=-Amplitude;	
		if(Pwm3>Amplitude)  Pwm3=Amplitude;	
	  if(Pwm4<-Amplitude) Pwm4=-Amplitude;	
		if(Pwm4>Amplitude)  Pwm4=Amplitude;	
}

/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
void Incremental_PI ()
{ 	
   float Kp1=100,Ki1=100;	
	 float Kp2=100,Ki2=100;	
	 float Kp3=100,Ki3=100;	
	 float Kp4=0.5,Ki4=0.01;	

	 static int Bias1,Pwm1,Last_bias1;
	 static int Bias2,Pwm2,Last_bias2;
	 static int Bias3,Pwm3,Last_bias3;
	 static int Bias4,Last_bias4;
	u8  U2TxBuff[50] ={0};
	 Bias1=pi_motor_new_enc1-Target_velocity1;                //计算偏差
	 Pwm1+=Kp1*(Bias1-Last_bias1)+Ki1*Bias1;   //增量式PI控制器
	 Last_bias1=Bias1;	                   //保存上一次偏差 
	
	 Bias2=pi_motor_new_enc2-Target_velocity2;                //计算偏差
	 Pwm2+=Kp2*(Bias2-Last_bias2)+Ki2*Bias2;   //增量式PI控制器
	 Last_bias2=Bias2;	                   //保存上一次偏差    
	
	 Bias3=pi_motor_new_enc3-Target_velocity3;                //计算偏差
	 Pwm3+=Kp3*(Bias3-Last_bias3)+Ki3*Bias3;   //增量式PI控制器
	 Last_bias3=Bias3;	                   //保存上一次偏差 
	
	 Bias4=pi_motor_new_enc4-Target_velocity4;                //计算偏差
		cs=		(float)Kp4*(Bias4-Last_bias4)+(float)Ki4*Bias4;
	rnm = (int)((float)Kp4*(Bias4-Last_bias4)+(float)Ki4*Bias4);
// Pwm4= (int)Pwm4+(int)((float)Kp4*(Bias4-Last_bias4)+(float)Ki4*Bias4);   //增量式PI控制器
Pwm4+=	rnm;
	Last_bias4=Bias4;	                   //保存上一次偏差 
	 
//	  U2TxBuff[0]=Pwm4/10000+'0';	Pwm4=Pwm4%10000; U2TxBuff[1]=Pwm4/1000+'0'; Pwm4=Pwm4%1000; U2TxBuff[2]=Pwm4/100+'0';	Pwm4=Pwm4%100;
//	  U2TxBuff[3]=Pwm4/10+'0';	U2TxBuff[4]=')';	U2TxBuff[5]='\r';U2TxBuff[6]='\n';		
//		for(t=0;t<7;t++)
//			{
//				USART_SendData(USART2, U2TxBuff[t]);//向串口1发送数据
//				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
//			}
	       
}
