#include <SPI.h>
 
char buf [10];
volatile byte pos;
volatile boolean process_it;
float vel[3];
int i=0;
 
void setup (void)
{
  Serial.begin (115200);
 
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
 
  // 设置为接收状态
  SPCR |= _BV(SPE);
 
  // 准备接受中断
  pos = 0;   // 清空缓冲区
  process_it = false;
 
  // 开启中断
  SPI.attachInterrupt();
}
 
 
// SPI 中断程序
ISR (SPI_STC_vect)
{  
  byte c = SPDR;  // 从 SPI 数据寄存器获取数据
    buf [pos++] = c;
    if (c == '\n')
    {
      buf[pos-1] = 0;
      pos = 0;
      vel[i] = atof(buf);
      i++;
    }
    
    if(c == '\r')
    {
      process_it = true;
      pos = 0;
      i = 0;
    }
    
}
 
void loop (void)
{
  if (process_it)
  {
  //  float t = atof(buf);
  for(int t=0;t<3;t++)
  {
   Serial.println(vel[t]); 
  }
    Serial.println();
//    pos = 0;
    process_it = false;
  } 
}
