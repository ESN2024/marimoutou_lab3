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

uint8_t X0,X1,Y0,Y1,Z0,Z1;
	
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
	write_adxl345(reg_OFSZ,0);

}

static void timer_irq(void *Context)
{	
	X0=read_adxl345(DATAX0);
	X1=read_adxl345(DATAX1);
	Y0=read_adxl345(DATAY0);
	Y1=read_adxl345(DATAY1);
	Z0=read_adxl345(DATAZ0);
	Z1=read_adxl345(DATAZ1);
	
	alt_printf("X: %x%x Y: %x%x Z: %x%x\n",X0,X1,Y0,Y1,Z0,Z1);
	
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0b1);
}



int main()
{
	

	I2C_init(OPENCORES_I2C_0_BASE,ALT_CPU_CPU_FREQ,I2C_SPEED);
	
	calibrate_adxl345();
	
	// Register IRQ
	alt_irq_register(TIMER_0_IRQ,NULL,timer_irq);
	
	while(1){}
	
	return 0;
	
	
	
}