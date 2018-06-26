#include "DHT11.h"

//定义变量
unsigned char HUMI_Buffer_Int = 0;
unsigned char TEM_Buffer_Int = 0;
 

//****************************************************
//MS延时函数(12M晶振下测试)
//****************************************************
static void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

void DHT11_delay_ms(unsigned int n)
{
	unsigned int  i;
	for(i=0;i<n;i++)
	{
	   Delay1ms();   
	}
}
//****************************************************
//延时函数
//****************************************************
static void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 24;
	while (--i);
}
void DHT11_Delay( unsigned int n )
{
	unsigned int i;
	for(i = 0 ; i < n ; i++ )
	  Delay10us();
}

//****************************************************
//初始化DHT11
//****************************************************
bit DHT11_Init()
{
	bit Flag_DHT11 = 1;
	DHT11_DQ = 0;
	DHT11_delay_ms(25);			//延时>18ms

	DHT11_DQ = 1;
	DHT11_Delay(3);				//延时20~40us
				
	Flag_DHT11 = DHT11_DQ;		
	DHT11_Delay(3);				//DHT11响应总时间80us

	DHT11_Delay(4);				//DHT11拉高信号80us

	return Flag_DHT11;		
}

//****************************************************
//读一个字节DHT11数据
//****************************************************
unsigned char DHT11_Read_Byte()
{
	unsigned char i,dat,j;
	while( DHT11_DQ == 1 );
	for( i = 0 ; i < 8 ; i++ )
	{
		while( DHT11_DQ == 0 );	
		dat <<= 1;
		for( j = 0 ; DHT11_DQ == 1 ; j++);
		if( j < 30 )
			dat &= 0xfe;		//低位清零
		else
			dat |= 0x01;		//低位置一
	}
	return dat;
}

//****************************************************
//读取温湿度值，存放在TEM_Buffer和HUMI_Buffer
//****************************************************
void DHT11_Read()
{
	if( DHT11_Init() == 0 )
	{
		HUMI_Buffer_Int = DHT11_Read_Byte();   		//读取湿度的整数值
		DHT11_Read_Byte();							//读取湿度的小数值
		TEM_Buffer_Int = DHT11_Read_Byte();			//读取温度的整数值
		DHT11_Read_Byte();		//读取温度的小数值
		DHT11_Read_Byte();							//读取校验和
		DHT11_Delay(5);					//DHT11拉低总线50us

		DHT11_DQ = 1;					//释放总线			
	}	
}



