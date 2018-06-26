#include "main.h"
#include "TFT.h"
#include "stdio.h"
#include "DHT11.h"

/*************	�û�ϵͳ����	**************/

#define MAIN_Fosc		22118400L	//������ʱ��, ��ʱ���Զ���Ӧ��5~35MHZ
#define D_TIMER0		1000		//	ѡ��ʱ��ʱ��us��ע�ⲻҪ��������ʱ����ᱨ��

/******************************************/

#define Timer0_Reload_s			((MAIN_Fosc / 1000) * D_TIMER0 / 12000)
#if (Timer0_Reload_s < 65536)
	#define	Timer0_Reload		(65536 - Timer0_Reload_s)
#endif
static unsigned long ms_cnt = 0;

static void ui_init(void)
{
	dsp_single_colour(YELLOW);//��ɫ
	Fast_DrawFont_GBK16(5,10,BLUE,YELLOW,	"��ʪ��ʵʱ���");
	Display_ASCII8X16_Color(0,26,"----------------",RED,YELLOW);
	Fast_DrawFont_GBK16(5,42,BLUE,YELLOW,	"�¶ȣ�");
	Fast_DrawFont_GBK16(95,42,RED,YELLOW,	"��");

	Fast_DrawFont_GBK16(5,68,BLUE,YELLOW,	"ʪ�ȣ�");
	Display_ASCII8X16_Color(90,68,"%RH",RED,YELLOW);
	Display_ASCII8X16_Color(0,84,"----------------",RED,YELLOW);
}

static void temperature_and_humidity_display(int temperature, int humidity)
{
     char str_temperature[6];
	 char str_humidity[6];


	 sprintf(str_temperature, "%3d", temperature);
	 sprintf(str_humidity, "%3d", humidity);

	 Display_ASCII8X16_Color(53,42,str_temperature,BLACK,YELLOW);
	 Display_ASCII8X16_Color(53,68,str_humidity,BLACK,YELLOW);
}

static void timer_init(void)
{
	TMOD |= 0x01;			//Timer0 set as 16bit timer
	TH0  = Timer0_Reload / 256;
	TL0  = Timer0_Reload % 256;
	ET0 = 1;
	TR0 = 1;
	EA = 1;
}

static void sys_time_display(unsigned long s_cnt)
{
    char str_hour[10];
    char str_min[3];
    char str_sec[3];

    sprintf(str_hour, "%3d", (int)s_cnt/3600);
    sprintf(str_min, "%2d", (int)s_cnt/60);
	sprintf(str_sec, "%2d", (int)s_cnt%60);

    Display_ASCII8X16_Color(0,100,str_hour,BLACK,YELLOW);
	Fast_DrawFont_GBK16(30,100,BLUE,YELLOW,	"ʱ");
    Display_ASCII8X16_Color(50,100,str_min,BLACK,YELLOW);
	Fast_DrawFont_GBK16(70,100,BLUE,YELLOW,	"��");
	Display_ASCII8X16_Color(90,100,str_sec,BLACK,YELLOW);
	Fast_DrawFont_GBK16(110,100,BLUE,YELLOW, "��");
}

void main(void)
{
	lcd_initial();
    ui_init();
	timer_init();
	DHT11_Read();
	delay_ms(200);

	while(1)
	{
	    DHT11_Read();
	    temperature_and_humidity_display((int)TEM_Buffer_Int, (int)HUMI_Buffer_Int);
		sys_time_display(ms_cnt/1000);
		delay_ms(500);				
	}	
}

void timer0 (void) interrupt 1
{
	TR0 = 0;
	TH0  = Timer0_Reload / 256;
	TL0  = Timer0_Reload % 256;
	TR0 = 1;
	
	ms_cnt++;
}
