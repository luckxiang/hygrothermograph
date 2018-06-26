#include "DHT11.h"

//�������
unsigned char HUMI_Buffer_Int = 0;
unsigned char TEM_Buffer_Int = 0;
 

//****************************************************
//MS��ʱ����(12M�����²���)
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
//��ʱ����
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
//��ʼ��DHT11
//****************************************************
bit DHT11_Init()
{
	bit Flag_DHT11 = 1;
	DHT11_DQ = 0;
	DHT11_delay_ms(25);			//��ʱ>18ms

	DHT11_DQ = 1;
	DHT11_Delay(3);				//��ʱ20~40us
				
	Flag_DHT11 = DHT11_DQ;		
	DHT11_Delay(3);				//DHT11��Ӧ��ʱ��80us

	DHT11_Delay(4);				//DHT11�����ź�80us

	return Flag_DHT11;		
}

//****************************************************
//��һ���ֽ�DHT11����
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
			dat &= 0xfe;		//��λ����
		else
			dat |= 0x01;		//��λ��һ
	}
	return dat;
}

//****************************************************
//��ȡ��ʪ��ֵ�������TEM_Buffer��HUMI_Buffer
//****************************************************
void DHT11_Read()
{
	if( DHT11_Init() == 0 )
	{
		HUMI_Buffer_Int = DHT11_Read_Byte();   		//��ȡʪ�ȵ�����ֵ
		DHT11_Read_Byte();							//��ȡʪ�ȵ�С��ֵ
		TEM_Buffer_Int = DHT11_Read_Byte();			//��ȡ�¶ȵ�����ֵ
		DHT11_Read_Byte();		//��ȡ�¶ȵ�С��ֵ
		DHT11_Read_Byte();							//��ȡУ���
		DHT11_Delay(5);					//DHT11��������50us

		DHT11_DQ = 1;					//�ͷ�����			
	}	
}



