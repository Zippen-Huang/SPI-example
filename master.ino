#include <SPI.h>

char cstr[]="";
float tf_data[3]={-1.2,1.3,0.67};
  
void setup (void)
{
  // 开始串口通讯
  //注意：此串口与SPI通信没有任何关系，只是为了程序演示输出SPI接收到的字节。
  Serial.begin(115200);      
  digitalWrite(SS, HIGH);    //SPI内部逻辑复位
  SPI.begin ();              // SPI通讯初始化配置
}
void loop (void)
{
//for(int i=0;i<3;i++)
//{
//  transformer(tf_data[i]);
//  delay(10);
//}
  
//     transformer(-1.23); 
   arr_tf(tf_data,3);
   

  
  delay (1000);
}


void arr_tf(float arr[], int n)
{
  digitalWrite(SS, LOW);
//  for(int i=0;i<sizeof(arr)/sizeof(float);i++)
  for(int i=0;i<n;i++)
  {
//    Serial.println("***");
    char intel_char[]="";
    dtostrf(arr[i],3,3,intel_char);
//    Serial.println(intel_char);
//    Serial.println(strlen(intel_char));
    for (int j =0; j<strlen(intel_char);j++)
    {
      char c=intel_char[j];
      SPI.transfer(c);//主机SPI发送
//      Serial.print(c);//串口显示发送的字节
//      Serial.print("  ");//串口显示发送的字节
//      Serial.print(j);//串口显示发送的字节
//      Serial.println();
      delay(2);
    }
//    Serial.println("--------------------");
      SPI.transfer ('\n');
      delay(10);
    
  }
  SPI.transfer ('\r');
  digitalWrite(SS, HIGH);
//  Serial.println(" ");
}

//----------------------------------------
void transformer(float val)
{
  char c;
  dtostrf(val,2,2,cstr);
  
    // 使能从机
  digitalWrite(SS, LOW);    // SS - pin 10
  // 循环发送字节，实现字符串的发送
//  for (const char * p = "-12.3456\n" ; c = *p; p++) 
for (int i =0; i<strlen(cstr);i++)
{
    c=cstr[i];
    SPI.transfer(c);//主机SPI发送
    Serial.print(c);//串口显示发送的字节
  }
  SPI.transfer ('\n');
  // 复位从机
  digitalWrite(SS, HIGH);
}
