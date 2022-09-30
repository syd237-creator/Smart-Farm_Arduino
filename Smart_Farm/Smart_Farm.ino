#include <DHT.h>
#include <SoftwareSerial.h>
#define SIZE 15
#define DHTPIN A0
#define LX A1
#define SOIL1 A2
#define SOIL2 A3
#define SOIL3 A4
#define SOIL4 A5
#define Relay_F 2
#define Relay_L 3
#define Relay_P1 4
#define Relay_P2 5
#define Relay_P3 6
#define Relay_P4 7
#define Humi_F 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int Soil1_V;
int Soil2_V;
int Soil3_V;
int Soil4_V;
int Lx_V;

int Buffer1_S[SIZE];
int Buffer2_S[SIZE];
int Buffer3_S[SIZE];
int Buffer4_S[SIZE];
float Sum1_S;
float Sum2_S;
float Sum3_S;
float Sum4_S;
int soil1;
int soil2;
int soil3;
int soil4;

int Buffer_L[SIZE];
float Sum_L;
int lx;

float EMA_a = 0.4;
int EMA_S1_pre = 0;
int EMA_S1 = 0;
int EMA_S2_pre = 0;
int EMA_S2 = 0;
int EMA_S3_pre = 0;
int EMA_S3 = 0;
int EMA_S4_pre = 0;
int EMA_S4 = 0;

int EMA_L_pre = 0;
int EMA_L = 0;

int h,t;

int A = 0;
int Fan_C = 0;
int F = 0;
int Fan_P = 0;

int Humi_C = 0;
int H = 0;
int Humi_P = 0;

int Lx_C = 0;
int L = 0;
int Lx_P = 0;

int Pump1_C = 0;
int P1 = 0;
int Pump1_P = 0;

int Pump2_C = 0;
int P2 = 0;
int Pump2_P = 0;

int Pump3_C = 0;
int P3 = 0;
int Pump3_P = 0;

int Pump4_C = 0;
int P4 = 0;
int Pump4_P = 0;

int PA = 0;
int b;
unsigned long Pump1_N = 0;
extern volatile unsigned long timer0_millis;

void setup(){
  pinMode(Relay_F, OUTPUT);
  pinMode(Relay_L, OUTPUT);
  pinMode(Relay_P1, OUTPUT);
  pinMode(Relay_P2, OUTPUT);
  pinMode(Relay_P3, OUTPUT);
  pinMode(Relay_P4, OUTPUT);
  pinMode(Humi_F,OUTPUT);
  pinMode(SOIL1, INPUT);
  pinMode(SOIL2, INPUT);
  pinMode(SOIL3, INPUT);
  pinMode(SOIL4, INPUT);
  pinMode(LX, INPUT);
  Serial.begin(9600);
  Serial3.begin(9600);
  EMA_S1_pre = analogRead(SOIL1);
  EMA_S2_pre = analogRead(SOIL2);
  EMA_S3_pre = analogRead(SOIL3);
  EMA_S4_pre = analogRead(SOIL4);
  EMA_L_pre = analogRead(LX);
}

void loop()
{
  Pump1_N = millis();
  Serial.println(Pump1_N);
  h = dht.readHumidity();
  t = dht.readTemperature();
  Com_Read();
  Smart_F_A(A);
  Soil1_F();
  Soil2_F();
  Soil3_F();
  Soil4_F();
  Lx_F();
  Com_OUT();
}
void Com_OUT()
{
  Serial3.print("111");
  Serial3.print(",");
  Serial3.print(t);
  Serial3.print(",");
  Serial3.print(h);
  Serial3.print(",");
  Serial3.print(soil1);
  Serial3.print(",");
  Serial3.print(soil2);
  Serial3.print(",");
  Serial3.print(soil3);
  Serial3.print(",");
  Serial3.print(soil4);
  Serial3.print(",");
  Serial3.print(lx);
  Serial3.print(",");
  Serial3.print("222");
  delay(50);
}

void Com_Read()
{
  if(Serial3.available())
  {
   char data = Serial3.read();
   Serial.print(data);
   if( data == 'a' )
   {
    F=1;
   }
   else if ( data == 'j' )
   {
    F=0;
    Fan_C = 0;
   }
   else if( data == 'b' )
   {
    H=1;
   }
   else if( data == 'k' )
   {
    H=0;
    Humi_C = 0;
   }
   else if( data == 'c' )
   {
    L=1;
   }
   else if( data == 'l' )
   {
    L=0;
    Lx_C = 0;
   }
   else if( data == 'd' )
   {
    P1=1;
    timer0_millis=0;
   }
   else if( data == 'm' )
   {
    P1=0;
    Pump1_C = 0;
   }
   else if( data == 'e' )
   {
    P2=1;
    timer0_millis=0;
   }
   else if( data == 'o' )
   {
    P2=0;
    Pump2_C = 0;
   }
   else if( data == 'f' )
   {
    P3=1;
    timer0_millis=0;
   }
   else if( data == 'p' )
   {
    P3=0;
    Pump3_C = 0;
   }
   else if( data == 'g' )
   {
    P4=1;
    timer0_millis=0;
   }
   else if( data == 'q' )
   {
    P4=0;
    Pump4_C = 0;
   }
   else if( data == 'h' )
   {
    A=1;
    b=1;
   }
   else if( data == 'i' )
   {
    A=0;
   }
  }
}

void Smart_F_A(int a)
{
  int N = millis();
  if( a == 1 )
  {
    if( b == 1 )
    {
      if( t > 25 ) { F = 1; }
      if( h < 40 ) { H = 1; }
      if( soil1 < 40 ) { P1 = 1; }
      if( soil1 < 40 ) { P1 = 1; }
      if( soil2 < 40 ) { P2 = 1; }
      if( soil3 < 40 ) { P3 = 1; }
      if( soil4 < 40 ) { P4 = 1; }
      b = 0;
    }
    if ( N - PA >= 1800000 )
    {
      PA = N;
      if( t > 25 ) { F = 1; }
      if( h < 40 ) { H = 1; }
      if( soil1 < 40 ) { P1 = 1; }
      if( soil1 < 40 ) { P1 = 1; }
      if( soil2 < 40 ) { P2 = 1; }
      if( soil3 < 40 ) { P3 = 1; }
      if( soil4 < 40 ) { P4 = 1; }
    }
    if( lx < 250 ) { L = 1; }
    
    Fan(F);
    Lx(L);
    Humi(H);
    Pump(P1,P2,P3,P4);

    Fan_Count(10);
    Humi_Count(10);
    Lx_Count(10);
    Pump1_Count(10);
    Pump2_Count(10);
    Pump3_Count(10);
    Pump4_Count(10);
  }
  else if ( a == 0 )
  {
    Fan(F);
    Lx(L);
    Humi(H);
    Pump(P1,P2,P3,P4);
    
   //Fan_Count(10);
   //Humi_Count(10);
   //Lx_Count(10);
    Pump1_Count(10);
    Pump2_Count(10);
    Pump3_Count(10);
    Pump4_Count(10);
  }
}

