/*****************************************************
 *Author : Moatasem
 *Date:    12/10/2018
 *Version: v02
 *Brief:   SPI peripheral
 *******************************************************/
#include "SPI.h"
static void SPI_SLAVE_Init();

void SPI_Init(){

	if(DIV_FACTOR<=7)
	{
		/* Enable SPI, Enable in master mode,Data Order , FOSC_DIV */
		WRITE_PORT(SPCR,(1<<SPE)|(DATA_ORDER<<DORD)|(1<<MSTR)|
				(SPI_MODE<<2)|
				(GET_BIT(DIV_FACTOR,1)<<SPR1)|
				(GET_BIT(DIV_FACTOR,0)<<SPR0)
		);
		WRITE_BIT (SPSR,SPI2X,GET_BIT(DIV_FACTOR,2));
	}
	else
	{
		SPI_SLAVE_Init();
	}
}

static void SPI_SLAVE_Init(){
	WRITE_PORT(SPCR,(1<<SPE)|DATA_ORDER<<DORD);/* Enable SPI, Enable in master mode, with Fosc/16 SCK frequency */
}

void SPI_Write(uint8 data){
	uint8 flush_buffer;
	SPDR = data;							/* Write data to SPI data register */
	while(! GET_BIT(SPSR ,SPIF));				/* Wait till transmission complete */
	flush_buffer = SPDR;					/* Flush received data */
/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */

}						/* SPI write data function */
uint8 SPI_Read(){
	SPDR = 0xFF;
	while(!GET_BIT(SPSR ,SPIF));				/* Wait till reception complete */
	return(SPDR);							/* return received data */

}

