#include<stdio.h>
#include<stdint.h>
#include "system.h"
#include <sys/alt_irq.h>
#include <io.h>
#include <alt_types.h>
#include <sys/alt_stdio.h>
#include "sys/alt_sys_init.h"
#include"opencores_i2c.h"
#include"opencores_i2c_regs.h"



#define ADXL345_addr 0x1D
#define I2C_SPEED 100000
#define DATAX0 0x32
#define DATAX1 0x33
#define DATAY0 0x34
#define DATAY1 0x35
#define DATAZ0 0x36
#define DATAZ1 0x37

unsigned int read_adx345(int addr)
{
	uint32_t capture=0;	
	
	I2C_start(OPENCORES_I2C_0_BASE,ADXL345_addr, 0);	
	I2C_write(OPENCORES_I2C_0_BASE,addr, 0);
	I2C_start(OPENCORES_I2C_0_BASE,ADXL345_addr, 1);
	
	capture = I2C_read(OPENCORES_I2C_0_BASE, 0);
	return capture;
}







int main()
{
	
	uint8_t X0,X1,Y0,Y1,Z0,Z1;
	I2C_init(OPENCORES_I2C_0_BASE,ALT_CPU_CPU_FREQ,I2C_SPEED);
	
	while(1)
	{
		X0=read_adx345(DATAX0);
		X1=read_adx345(DATAX1);
		
		alt_printf("X : %x%x \n",X0,X1);
	}
	
	
	
}