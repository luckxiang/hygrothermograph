#ifndef __DHT11_H__
#define __DHT11_H__


#include <reg52.h>
#include <intrins.h>
//DHT11 IO设置
sbit DHT11_DQ = P3^4;

//函数或者变量声明
extern void DHT11_delay_ms(unsigned int n);
extern bit DHT11_Init();
extern void DHT11_Delay( unsigned int n );
extern unsigned char DHT11_Read_Byte();
extern void DHT11_Read();

extern unsigned char HUMI_Buffer_Int;
extern unsigned char TEM_Buffer_Int;

#endif