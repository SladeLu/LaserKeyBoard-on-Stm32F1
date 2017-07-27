#ifndef	__FLASH_SPI_H_
#define __FLASH_SPI_H_

#include "stm32f4xx.h"

#define EN_ASCII_WRITE_FLASH

/*									
																�洢һЩ������ռ�õĵ�ַ  ÿһ��ռ��һ��sector(4KB)
																
					������У����־λ��У������							1FF000H  ~  1FFFFFH					(���һ��sector)    
					ASCII16x24�ֿ�													1F0000H  ~  1F0FFFH
					ASCII8x16�ֿ�														1F1000H	 ~  1F1FFFH
					ASCII6x12�ֿ�														1F2000H  ~	1F2FFFH



*/


#define TOUCH_PARA_FLASHADDRESS		0x1FF000
#define ASCII16x24_FLASHADDRESS		0x1F0000
#define ASCII8x16_FLASHADDRESS		0x1F1000
#define ASCII6x12_FLASHADDRESS		0x1F2000








#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_4)

/******************		�ײ㺯��  **************************/
u8 SPI_FLASH_ReadByte(void);
u8 SPI_FLASH_SendByte(u8 byte);
u16 SPI_FLASH_SendHalfWord(u16 HalfWord);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);

/******************		��������	**************************/
void SPI_FLASH_Init(void);
void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
u32 SPI_FLASH_ReadID(void);
u32 SPI_FLASH_ReadDeviceID(void);
void SPI_FLASH_StartReadSequence(u32 ReadAddr);
void SPI_Flash_PowerDown(void);
void SPI_Flash_WAKEUP(void);

/*******************			Ӧ�ú���			*************************/
////////////////ע��:д������ǰһ��Ҫ�����飬����д����Ч/////////////////
void SPI_FLASH_SectorErase(u32 SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
void SPI_FLASH_WriteSector(u8 *pBuffer,u32 WriteAddress,u32 NumOfBytes);
void SPI_FLASH_WriteASCII(void);

#endif