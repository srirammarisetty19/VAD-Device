//////////////////////////////////////////////////////////////////////////////////////////
//
//   Arduino Library for ADS1292R Shield/Breakout
//
//   Copyright (c) 2017 ProtoCentral
//   
//   This software is licensed under the MIT License(http://opensource.org/licenses/MIT). 
//   
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
//   NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
//   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
//   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
//   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//   Requires g4p_control graphing library for processing.  Built on V4.1
//   Downloaded from Processing IDE Sketch->Import Library->Add Library->G4P Install
//
/////////////////////////////////////////////////////////////////////////////////////////

#include <ads1292r.h>
#include <SPI.h>

ads1292r ADS1292;   // define class

//Packet format
#define  CES_CMDIF_PKT_START_1    0x0A
#define  CES_CMDIF_PKT_START_2     0xFA
#define  CES_CMDIF_TYPE_DATA       0x02
#define  CES_CMDIF_PKT_STOP        0x0B

volatile uint8_t  SPI_Dummy_Buff[30];
uint8_t DataPacketHeader[16];
volatile signed long s32DaqVals[8];
volatile signed long previousVal;
uint8_t data_len = 8;
volatile byte SPI_RX_Buff[15] ;
volatile static int SPI_RX_Buff_Count = 0;
volatile char *SPI_RX_Buff_Ptr;
volatile bool ads1292dataReceived =false;
unsigned long uecgtemp = 0;
signed long secgtemp=0;
int i,j;

void setup() 
{
  // initalize the  data ready and chip select pins:
  pinMode(ADS1292_DRDY_PIN, INPUT);  //6
  pinMode(ADS1292_CS_PIN, OUTPUT);    //7
  pinMode(ADS1292_START_PIN, OUTPUT);  //5
  pinMode(ADS1292_PWDN_PIN, OUTPUT);  //4
  
  Serial.begin(115200);  // Baudrate for serial communica
  
  ADS1292.ads1292_Init();  //initalize ADS1292 slave
}

void loop() 
{
  if((digitalRead(ADS1292_DRDY_PIN)) == LOW)       // Sampling rate is set to 125SPS ,DRDY ticks for every 8ms
  {                                                  
    SPI_RX_Buff_Ptr = ADS1292.ads1292_Read_Data(); // Read the data,point the data to a pointer

    for(i = 0; i < 9; i++)
    {
      SPI_RX_Buff[SPI_RX_Buff_Count++] = *(SPI_RX_Buff_Ptr + i);  // store the result data in array
    }
    ads1292dataReceived = true;
  }

  
  if(ads1292dataReceived == true)       // process the data 
  {     
    j=0;
    for(i=0;i<6;i+=3)                  // data outputs is (24 status bits + 24 bits Respiration data +  24 bits ECG data) 
    {
        uecgtemp = (unsigned long) (  ((unsigned long)SPI_RX_Buff[i+3] << 16) | ( (unsigned long) SPI_RX_Buff[i+4] << 8) |  (unsigned long) SPI_RX_Buff[i+5]);
        uecgtemp = (unsigned long) (uecgtemp << 8);
        secgtemp = (signed long) (uecgtemp);
        secgtemp = (signed long) (secgtemp >> 8);

        s32DaqVals[j++]=secgtemp;
    }
//    if ((previousVal - s32DaqVals[1]) > 100000) {
//      s32DaqVals[1] = previousVal;
//    }
//    if ((s32DaqVals[1] - previousVal) > 100000) {
//      s32DaqVals[1] = previousVal;
//    }
    Serial.println(s32DaqVals[1]); 
//    previousVal = s32DaqVals[1];
   }
    ads1292dataReceived = false;
    SPI_RX_Buff_Count = 0;
}           
