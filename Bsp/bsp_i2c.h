#ifndef __BSP_I2C_H
#define __BSP_I2C_H


void bsp_i2cInit(void);
unsigned char I2C_ReadOneByte(uint8_t DevAddr, uint8_t RegAddr);
uint8_t IICwriteByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t WriteData);
uint8_t IICreadBytes(uint8_t DevAddr, uint8_t RegAddr, uint8_t ReadNum, uint8_t * ReadTemp);
#endif //__BSP_I2C_H
