#ifndef	__FLASH_SPI_H_
#define __FLASH_SPI_H_

#include "stm32f4xx.h"

#define EN_ASCII_WRITE_FLASH

/*									
																存储一些数据所占用的地址  每一类占用一个sector(4KB)
																
					触摸屏校正标志位和校正参数							1FF000H  ~  1FFFFFH					(最后一个sector)    
					ASCII16x24字库													1F0000H  ~  1F0FFFH
					ASCII8x16字库														1F1000H	 ~  1F1FFFH
					ASCII6x12字库														1F2000H  ~	1F2FFFH



*/


#define TOUCH_PARA_FLASHADDRESS		0x1FF000
#define ASCII16x24_FLASHADDRESS		0x1F0000
#define ASCII8x16_FLASHADDRESS		0x1F1000
#define ASCII6x12_FLASHADDRESS		0x1F2000








#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_4)

/******************		底层函数  **************************/
u8 SPI_FLASH_ReadByte(void);
u8 SPI_FLASH_SendByte(u8 byte);
u16 SPI_FLASH_SendHalfWord(u16 HalfWord);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);

/******************		基本函数	**************************/
void SPI_FLASH_Init(void);
void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
u32 SPI_FLASH_ReadID(void);
u32 SPI_FLASH_ReadDeviceID(void);
void SPI_FLASH_StartReadSequence(u32 ReadAddr);
void SPI_Flash_PowerDown(void);
void SPI_Flash_WAKEUP(void);

/*******************			应用函数			*************************/
////////////////注意:写入数据前一定要擦除块，否则写入无效/////////////////
void SPI_FLASH_SectorErase(u32 SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
void SPI_FLASH_WriteSector(u8 *pBuffer,u32 WriteAddress,u32 NumOfBytes);
void SPI_FLASH_WriteASCII(void);

#endif