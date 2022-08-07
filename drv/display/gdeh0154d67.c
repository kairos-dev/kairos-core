#include "gdeh0154d67.h"

void driver_delay_us(unsigned int xus){
  for(;xus>1;xus--);
}

void driver_delay_xms(unsigned long xms) {
    unsigned long i = 0 , j=0;

    for(j=0;j<xms;j++)
  {
        for(i=0; i<256; i++);
    }
}

void DELAY_S(unsigned int delaytime){
  int i,j,k;
  for(i=0;i<delaytime;i++)
  {
    for(j=0;j<4000;j++)
    {
      for(k=0;k<222;k++);

    }
  }
}
//////////////////////SPI///////////////////////////////////
void SPI_Delay(unsigned char xrate){
  unsigned char i;
  while(xrate)
  {
    for(i=0;i<2;i++);
    xrate--;
  }
}


void SPI_Write(unsigned char value){
    unsigned char i;
   SPI_Delay(1);
    for(i=0; i<8; i++)
    {
        EPD_W21_CLK_0;
        SPI_Delay(1);
        if(value & 0x80){
          EPD_W21_MOSI_1;
        }
        else{
            EPD_W21_MOSI_0;
        }
        value = (value << 1);
        SPI_Delay(1);
        driver_delay_us(1);
        EPD_W21_CLK_1;
        SPI_Delay(1);
    }
}

void Epaper_Write_Command(unsigned char command){
  SPI_Delay(1);
  EPD_W21_CS_0;
  EPD_W21_DC_0;   // command write
  SPI_Write(command);
  EPD_W21_CS_1;
}
void Epaper_Write_Data(unsigned char datas){
  SPI_Delay(1);
  EPD_W21_CS_0;
  EPD_W21_DC_1;   // command write
  SPI_Write(datas);
  EPD_W21_CS_1;
}

/////////////////EPD settings Functions/////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void EPD_HW_Init(void){
  EPD_W21_RST_0;  // Module reset
  delay_ms(1); //At least 10ms delay
  EPD_W21_RST_1;
  delay_ms(1); //At least 10ms delay

  Epaper_READBUSY();
  Epaper_Write_Command(0x12);  //SWRESET
  Epaper_READBUSY();

  Epaper_Write_Command(0x01); //Driver output control
  Epaper_Write_Data(0xC7);
  Epaper_Write_Data(0x00);
  Epaper_Write_Data(0x00);

  Epaper_Write_Command(0x11); //data entry mode
  Epaper_Write_Data(0x01);

  Epaper_Write_Command(0x44); //set Ram-X address start/end position
  Epaper_Write_Data(0x00);
  Epaper_Write_Data(0x18);    //0x0C-->(18+1)*8=200

  Epaper_Write_Command(0x45); //set Ram-Y address start/end position
  Epaper_Write_Data(0xC7);   //0xC7-->(199+1)=200
  Epaper_Write_Data(0x00);
  Epaper_Write_Data(0x00);
  Epaper_Write_Data(0x00);

  Epaper_Write_Command(0x3C); //BorderWavefrom
  Epaper_Write_Data(0x05);

  Epaper_Write_Command(0x18); //Reading temperature sensor
  Epaper_Write_Data(0x80);

  Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
  Epaper_Write_Data(0x00);
  Epaper_Write_Command(0x4F);   // set RAM y address count to 0X199;
  Epaper_Write_Data(0xC7);
  Epaper_Write_Data(0x00);
  Epaper_READBUSY();

}
//////////////////////////////All screen update////////////////////////////////////////////
void EPD_WhiteScreen_ALL(const unsigned char * datas){
   unsigned int i;
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {
     Epaper_Write_Data(pgm_read_byte(&datas[i]));
   }
   EPD_Update();
}

/////////////////////////////////////////////////////////////////////////////////////////
void EPD_Update(void){
  Epaper_Write_Command(0x22); //Display Update Control
  Epaper_Write_Data(0xF7);
  Epaper_Write_Command(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();

}

void EPD_Part_Update(void){
  Epaper_Write_Command(0x22);//Display Update Control
  Epaper_Write_Data(0xFF);
  Epaper_Write_Command(0x20); //Activate Display Update Sequence
  Epaper_READBUSY();
}

void EPD_DeepSleep(void){
  Epaper_Write_Command(0x10); //enter deep sleep
  Epaper_Write_Data(0x01);
  delay_ms(100);
}

void Epaper_READBUSY(void){
  while(1)
  {   //=1 BUSY
     if(isEPD_W21_BUSY==0) break;
  }
}

///////////////////////////Part update//////////////////////////////////////////////
void EPD_SetRAMValue_BaseMap( const unsigned char * datas){
  unsigned int i;
  const unsigned char  *datas_flag;
  datas_flag=datas;
  Epaper_Write_Command(0x24);   //Write Black and White image to RAM
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {
     Epaper_Write_Data(pgm_read_byte(&datas[i]));
   }
   datas=datas_flag;
  Epaper_Write_Command(0x26);   //Write Black and White image to RAM
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {
     Epaper_Write_Data(pgm_read_byte(&datas[i]));
   }
   EPD_Update();
}


void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE){
  unsigned int i;
  unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
  x_start=x_start/8;//
  x_end=x_start+PART_LINE/8-1;

  y_start1=0;
  y_start2=y_start;
  if(y_start>=256)
  {
    y_start1=y_start2/256;
    y_start2=y_start2%256;
  }
  y_end1=0;
  y_end2=y_start+PART_COLUMN-1;
  if(y_end2>=256)
  {
    y_end1=y_end2/256;
    y_end2=y_end2%256;
  }

  Epaper_Write_Command(0x44);       // set RAM x address start/end, in page 35
  Epaper_Write_Data(x_start);    // RAM x address start at 00h;
  Epaper_Write_Data(x_end);    // RAM x address end at 0fh(15+1)*8->128
  Epaper_Write_Command(0x45);       // set RAM y address start/end, in page 35
  Epaper_Write_Data(y_start2);    // RAM y address start at 0127h;
  Epaper_Write_Data(y_start1);    // RAM y address start at 0127h;
  Epaper_Write_Data(y_end2);    // RAM y address end at 00h;
  Epaper_Write_Data(y_end1);    // ????=0


  Epaper_Write_Command(0x4E);   // set RAM x address count to 0;
  Epaper_Write_Data(x_start);
  Epaper_Write_Command(0x4F);   // set RAM y address count to 0X127;
  Epaper_Write_Data(y_start2);
  Epaper_Write_Data(y_start1);


   Epaper_Write_Command(0x24);   //Write Black and White image to RAM
   for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
   {
     Epaper_Write_Data(pgm_read_byte(&datas[i]));
   }
   EPD_Part_Update();

}




/////////////////////////////////Single display////////////////////////////////////////////////

void EPD_WhiteScreen_Black(void){
   unsigned int i,k;
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
  for(k=0;k<250;k++)
  {
    for(i=0;i<25;i++)
    {
      Epaper_Write_Data(0x00);
      }
  }
    EPD_Update();
}

void EPD_WhiteScreen_White(void){
   unsigned int i,k;
    Epaper_Write_Command(0x24);   //write RAM for black(0)/white (1)
  for(k=0;k<250;k++)
  {
    for(i=0;i<25;i++)
    {
      Epaper_Write_Data(0xff);
      }
  }
  EPD_Update();
}

kairos_err_t init_gdeh0154d67(void){
    gpio_pad_select_gpio(PIN_BUSY);
    gpio_set_direction(PIN_BUSY, GPIO_MODE_INPUT);

    gpio_pad_select_gpio(PIN_RES);
    gpio_set_direction(PIN_RES, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(PIN_DC);
    gpio_set_direction(PIN_DC, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(PIN_CS);
    gpio_set_direction(PIN_CS, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(PIN_SCLK);
    gpio_set_direction(PIN_SCLK, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(PIN_MOSI);
    gpio_set_direction(PIN_MOSI, GPIO_MODE_OUTPUT);

    return KAIROS_ERR_OK;
}
