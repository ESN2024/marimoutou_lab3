#include<stdio.h>
#include<stdint.h>
#include <unistd.h>
#include "system.h"
#include <sys/alt_irq.h>
#include <io.h>
#include <alt_types.h>
#include <sys/alt_stdio.h>
#include "sys/alt_sys_init.h"
#include"opencores_i2c.h"
#include"opencores_i2c_regs.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_timer.h"
#include "altera_avalon_pio_regs.h"

uint8_t X0,X1,Y0,Y1,Z0,Z1;
int16_t X,Y,Z;
uint8_t flag=0;
#define ADXL345_addr 0x1D
#define I2C_SPEED 100000
#define DATAX0 0x32
#define DATAX1 0x33
#define DATAY0 0x34
#define DATAY1 0x35
#define DATAZ0 0x36
#define DATAZ1 0x37


#define reg_OFSX 0x1E
#define reg_OFSY 0x1F
#define reg_OFSZ 0x20

unsigned int read_adxl345(int addr)
{
	uint8_t capture=0;	
	
	I2C_start(OPENCORES_I2C_0_BASE,ADXL345_addr, 0);	
	I2C_write(OPENCORES_I2C_0_BASE,addr, 0);
	I2C_start(OPENCORES_I2C_0_BASE,ADXL345_addr, 1);
	
	capture = I2C_read(OPENCORES_I2C_0_BASE, 1);
	return capture;
}

void write_adxl345(int addr, int value)
{
	I2C_start(OPENCORES_I2C_0_BASE,ADXL345_addr, 0);	
	I2C_write(OPENCORES_I2C_0_BASE,addr, 0);
	I2C_write(OPENCORES_I2C_0_BASE,value, 1);
}


void calibrate_adxl345()
{
	write_adxl345(reg_OFSX,0);
	write_adxl345(reg_OFSY,0);
	write_adxl345(reg_OFSZ,-29);

}

int16_t complement(int16_t value)
{
	if(value & 0x8000)
	{
		value=-(0xFFFF - value +1);
	}
	
	return value*3.9;
}

void print_to_7seg(int16_t value)
{
	int8_t data[5] = {0,0,0,0,0};
	if (value < 0)
	{
		data[0] = value % 10 ;
		data[1] = (value/10) % 10 ;
		data[2] = (value/100) % 10 ;
		data[3] = value / 1000 ;
		data[4] = 10;			
	}
	else
	{
		data[0] = value % 10 ;
		data[1] = (value/10) % 10 ;
		data[2] = (value/100) % 10 ;
		data[3] = value / 1000 ;
		data[4] = 11;		
	}

	
	
	// Write on BCD 7 SEGMENTS
	IOWR_ALTERA_AVALON_PIO_DATA(SEG1_BASE,data[0]);
	IOWR_ALTERA_AVALON_PIO_DATA(SEG2_BASE,data[1]);
	IOWR_ALTERA_AVALON_PIO_DATA(SEG3_BASE,data[2]);
	IOWR_ALTERA_AVALON_PIO_DATA(SEG4_BASE,data[3]);
	IOWR_ALTERA_AVALON_PIO_DATA(SEG5_BASE,data[4]);
	
	
}

static void timer_irq(void *Context)
{

	
	X0=read_adxl345(DATAX0);
	X1=read_adxl345(DATAX1);
	Y0=read_adxl345(DATAY0);
	Y1=read_adxl345(DATAY1);
	Z0=read_adxl345(DATAZ0);
	Z1=read_adxl345(DATAZ1);
	
	
	//complement a deux
	X= (X1 << 8) | X0;
	Y= (Y1 << 8) | Y0;
	Z= (Z1 << 8) | Z0;
	
	complement(X);
	complement(Y);
	complement(Z);
	
	alt_printf("X: %x Y: %x Z: %x\n",X,Y,Z);
	
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0b1);
}


static void key_irq(void *Context)
{
	alt_printf("KEY Interrupt\n");
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_BASE,0b1);
	
	flag++;
	if (flag>3){flag=0;}
	

}

int main()
{
	// Enable IRQ end button capture
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BTN_BASE,0b1);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BTN_BASE,0b1);

	I2C_init(OPENCORES_I2C_0_BASE,ALT_CPU_CPU_FREQ,I2C_SPEED);
	
	calibrate_adxl345();
	//write_adxl345(0x31, 0x7);
	
	// Register IRQ
	alt_irq_register(TIMER_0_IRQ,NULL,timer_irq);
	alt_irq_register(BTN_IRQ,NULL,key_irq);
	
	while(1)
	{
		switch(flag)
		{
			case 0 : print_to_7seg(X);
			break;
			
			case 1 : print_to_7seg(Y);
			break;
			
			case 2 : print_to_7seg(Z);
			break;
			
			default	: print_to_7seg(X);	
		}
		
	}
	
	return 0;
	
	
	
}