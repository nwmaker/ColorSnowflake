#include<Wire.h>

#define Addr_GND_GND 0xC0

void setup() {
  // put your setup code here, to run once:  
  pinMode(13, OUTPUT);//ARDUINO BOARD LED control
  Wire.begin();
  Wire.setClock(400000);//I2C 400kHz
}


byte PWM_Gamma64[64]=
{
  0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
  0x08,0x09,0x0b,0x0d,0x0f,0x11,0x13,0x16,
  0x1a,0x1c,0x1d,0x1f,0x22,0x25,0x28,0x2e,
  0x34,0x38,0x3c,0x40,0x44,0x48,0x4b,0x4f,
  0x55,0x5a,0x5f,0x64,0x69,0x6d,0x72,0x77,
  0x7d,0x80,0x88,0x8d,0x94,0x9a,0xa0,0xa7,
  0xac,0xb0,0xb9,0xbf,0xc6,0xcb,0xcf,0xd6,
  0xe1,0xe9,0xed,0xf1,0xf6,0xfa,0xfe,0xff
};


void IS_IIC_WriteByte(uint8_t Dev_Add,uint8_t Reg_Add,uint8_t Reg_Dat)//writing an LED register
{
  Wire.beginTransmission(Dev_Add/2);
  Wire.write(Reg_Add); // sends regaddress
  Wire.write(Reg_Dat); // sends regaddress
  Wire.endTransmission(); // stop transmitting
}

void loop() {
  // put your main code here, to run repeatedly:
  mainloop();
}
void Init3746A(void)
{
  int i,j;
  IS_IIC_WriteByte(Addr_GND_GND,0xfe,0xc5);
  IS_IIC_WriteByte(Addr_GND_GND,0xfd,0x00);//page 0
  for(i=1;i<0x49;i++)
  {
    IS_IIC_WriteByte(Addr_GND_GND,i,0);//PWM
  }
  IS_IIC_WriteByte(Addr_GND_GND,0xfe,0xc5);
  IS_IIC_WriteByte(Addr_GND_GND,0xfd,0x01);//page 1  
  for(i=1;i<0x49;i++)
  {
    IS_IIC_WriteByte(Addr_GND_GND,i,0xff);//scaling
  }  
  
  IS_IIC_WriteByte(Addr_GND_GND,0x52,0x70);
  IS_IIC_WriteByte(Addr_GND_GND,0x51,0xFF);//GCC
  IS_IIC_WriteByte(Addr_GND_GND,0x50,0x01);//
}

void mainloop(void)//
{
  int i,j; 
  Init3746A();
  digitalWrite(13, LOW);   // turn the ARDUINO BOARD LED on (HIGH is the voltage level)     
  while(1)
  {
    //RED    
    digitalWrite(13, HIGH);   // turn the ARDUINO BOARD LED on (HIGH is the voltage level)   
    IS_IIC_WriteByte(Addr_GND_GND,0xfe,0xc5);
    IS_IIC_WriteByte(Addr_GND_GND,0xfd,0x00);//page 0
    for(j=0;j<64;j++)
    {
      for(i=1;i<0x49;i=i+3)
      {
        IS_IIC_WriteByte(Addr_GND_GND,i,PWM_Gamma64[j]);//PWM}
      }
    }
    delay(500);
     
    digitalWrite(13, LOW);   // turn the ARDUINO BOARD LED OFF (HIGH is the voltage level)    
    IS_IIC_WriteByte(Addr_GND_GND,0xfe,0xc5);
    IS_IIC_WriteByte(Addr_GND_GND,0xfd,0x00);//page 0
    for(j=63;j>=0;j--)
    {
      for(i=1;i<0x49;i=i+3)
      {
        IS_IIC_WriteByte(Addr_GND_GND,i,PWM_Gamma64[j]);//PWM}
      }
    }
    delay(500);
     
    //GREEN    
    digitalWrite(13, HIGH);   // turn the ARDUINO BOARD LED on (HIGH is the voltage level)   
    IS_IIC_WriteByte(Addr_GND_GND,0xfe,0xc5);
    IS_IIC_WriteByte(Addr_GND_GND,0xfd,0x00);//page 0
    for(j=0;j<64;j++)
    {
      for(i=2;i<0x49;i=i+3)
      {
        IS_IIC_WriteByte(Addr_GND_GND,i,PWM_Gamma64[j]);//PWM}
      }
    }
    delay(500);
     
    digitalWrite(13, LOW);   // turn the ARDUINO BOARD LED OFF (HIGH is the voltage level)    
    IS_IIC_WriteByte(Addr_GND_GND,0xfe,0xc5);
    IS_IIC_WriteByte(Addr_GND_GND,0xfd,0x00);//page 0
    for(j=63;j>=0;j--)
    {
      for(i=2;i<0x49;i=i+3)
      {
        IS_IIC_WriteByte(Addr_GND_GND,i,PWM_Gamma64[j]);//PWM}
      }
    }
    delay(500);

    //BLUE    
    digitalWrite(13, HIGH);   // turn the ARDUINO BOARD LED on (HIGH is the voltage level)   
    IS_IIC_WriteByte(Addr_GND_GND,0xfe,0xc5);
    IS_IIC_WriteByte(Addr_GND_GND,0xfd,0x00);//page 0
    for(j=0;j<64;j++)
    {
      for(i=3;i<0x49;i=i+3)
      {
        IS_IIC_WriteByte(Addr_GND_GND,i,PWM_Gamma64[j]);//PWM}
      }
    }
    delay(500);
     
    digitalWrite(13, LOW);   // turn the ARDUINO BOARD LED OFF (HIGH is the voltage level)    
    IS_IIC_WriteByte(Addr_GND_GND,0xfe,0xc5);
    IS_IIC_WriteByte(Addr_GND_GND,0xfd,0x00);//page 0
    for(j=63;j>=0;j--)
    {
      for(i=3;i<0x49;i=i+3)
      {
        IS_IIC_WriteByte(Addr_GND_GND,i,PWM_Gamma64[j]);//PWM}
      }
    }
    delay(500);

     
  }
}
