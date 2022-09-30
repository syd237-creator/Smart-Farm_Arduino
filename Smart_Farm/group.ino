void Fan(int a)
{
  if ( a == 1)
  {
    digitalWrite(Relay_F,HIGH);
  }
  else
  {
    digitalWrite(Relay_F,LOW);
  }
}

void Lx(int a)
{
  if ( a == 1)
  {
    digitalWrite(Relay_L,HIGH);
  }
  else
  {
    digitalWrite(Relay_L,LOW);
  }
}

void Humi(int a)
{
  if ( a == 1)
  {
    digitalWrite(Humi_F,HIGH);
  }
  else
  {
    digitalWrite(Humi_F,LOW);
  }
}

void Pump(int a, int b, int c, int d)
{
  if ( a == 1)
  {
    digitalWrite(Relay_P1,HIGH);
  }
  else
  {
    digitalWrite(Relay_P1,LOW);
  }
  if ( b == 1)
  {
    digitalWrite(Relay_P2,HIGH);
  }
  else
  {
    digitalWrite(Relay_P2,LOW);
  }
  if ( c == 1)
  {
    digitalWrite(Relay_P3,HIGH);
  }
  else
  {
    digitalWrite(Relay_P3,LOW);
  }
  if ( d == 1)
  {
    digitalWrite(Relay_P4,HIGH);
  }
  else
  {
    digitalWrite(Relay_P4,LOW);
  }
}

void Soil1_F()
{
  Soil1_V = analogRead(SOIL1);

  EMA_S1_pre = (EMA_a*Soil1_V) + ((1-EMA_a)*EMA_S1_pre);
  Sum1_S-=Buffer1_S[0];
  for(int i = 0; i < SIZE-1; i++)
  {
    Buffer1_S[i] = Buffer1_S[i+1];
  }
  Buffer1_S[SIZE - 1] = EMA_S1_pre;
  Sum1_S+=Buffer1_S[SIZE-1];
  EMA_S1=Sum1_S/SIZE+2;

  soil1 = map(EMA_S1,560,960,100,0);
}

void Soil2_F()
{
  Soil2_V = analogRead(SOIL2);

  EMA_S2_pre = (EMA_a*Soil2_V) + ((1-EMA_a)*EMA_S2_pre);
  Sum2_S-=Buffer2_S[0];
  for(int i = 0; i < SIZE-1; i++)
  {
    Buffer2_S[i] = Buffer2_S[i+1];
  }
  Buffer2_S[SIZE - 1] = EMA_S2_pre;
  Sum2_S+=Buffer2_S[SIZE-1];
  EMA_S2=Sum2_S/SIZE+2;

  soil2 = map(EMA_S2,560,960,100,0);
}

void Soil3_F()
{
  Soil3_V = analogRead(SOIL3);

  EMA_S3_pre = (EMA_a*Soil3_V) + ((1-EMA_a)*EMA_S3_pre);
  Sum3_S-=Buffer3_S[0];
  for(int i = 0; i < SIZE-1; i++)
  {
    Buffer3_S[i] = Buffer3_S[i+1];
  }
  Buffer3_S[SIZE - 1] = EMA_S3_pre;
  Sum3_S+=Buffer3_S[SIZE-1];
  EMA_S3=Sum3_S/SIZE+2;

  soil3 = map(EMA_S3,560,960,100,0);
}

void Soil4_F()
{
  Soil4_V = analogRead(SOIL4);

  EMA_S4_pre = (EMA_a*Soil4_V) + ((1-EMA_a)*EMA_S4_pre);
  Sum4_S-=Buffer4_S[0];
  for(int i = 0; i < SIZE-1; i++)
  {
    Buffer4_S[i] = Buffer4_S[i+1];
  }
  Buffer4_S[SIZE - 1] = EMA_S4_pre;
  Sum4_S+=Buffer4_S[SIZE-1];
  EMA_S4=Sum4_S/SIZE+2;

  soil4 = map(EMA_S4,560,960,100,0);
}

void Lx_F()
{
  Lx_V = analogRead(LX);

  EMA_L_pre = (EMA_a*Lx_V) + ((1-EMA_a)*EMA_L_pre);
  Sum_L-=Buffer_L[0];
  for(int i = 0; i < SIZE-1; i++)
  {
    Buffer_L[i] = Buffer_L[i+1];
  }
  Buffer_L[SIZE - 1] = EMA_L_pre;
  Sum_L+=Buffer_L[SIZE-1];
  EMA_L=Sum_L/SIZE+2;

  lx = map(EMA_L,0,1023,0,950);
}

void Fan_Count(int a)
{
  int Fan_N = millis();
  if( F == 1)
  {
    if( Fan_N - Fan_P >= 1000 )
    {
      Fan_P = Fan_N;
      Fan_C += 1;
      Serial.println(Fan_C);
      if(Fan_C == a)
      {
        Fan_C = 0;
        F=0;
        Serial3.print("333");
        Serial3.print(",");
        Serial3.print("a");
        Serial3.print(",");
        Serial3.print("444");
        delay(100);
      }
    }
  }
}

void Humi_Count(int a)
{
  int Humi_N = millis();
  if( H == 1)
  {
    if( Humi_N - Humi_P >= 1000 )
    {
      Humi_P = Humi_N;
      Humi_C += 1;
      Serial.println(Humi_C);
      if(Humi_C == a)
      {
        Humi_C = 0;
        H=0;
        Serial3.print("333");
        Serial3.print(",");
        Serial3.print("b");
        Serial3.print(",");
        Serial3.print("444");
        delay(100);
      }
    }
  }
}

void Lx_Count(int a)
{
  int Lx_N = millis();
  if( L == 1)
  {
    if( Lx_N - Lx_P >= 1000 )
    {
      Lx_P = Lx_N;
      Lx_C += 1;
      Serial.println(Lx_C);
      if(Lx_C == a)
      {
        Lx_C = 0;
        L=0;
        Serial3.print("333");
        Serial3.print(",");
        Serial3.print("c");
        Serial3.print(",");
        Serial3.print("444");
        delay(100);
      }
    }
  }
}

void Pump1_Count(int a)
{
  Pump1_N = millis();
  
  if( P1 == 1)
  {
    if( Pump1_N - Pump1_P >= 1000 )
    {
      Pump1_P = Pump1_N;
      Pump1_C += 1;
      Serial.println(Pump1_C);
      if(Pump1_C == a)
      {
        Pump1_C = 0;
        P1=0;
        Serial3.print("333");
        Serial3.print(",");
        Serial3.print("d");
        Serial3.print(",");
        Serial3.print("444");
        delay(100);
      }
    }
  }
}

void Pump2_Count(int a)
{
  if( P2 == 1)
  {
    if( Pump1_N - Pump2_P >= 1000 )
    {
      Pump2_P = Pump1_N;
      Pump2_C += 1;
      Serial.println(Pump2_C);
      if(Pump2_C == a)
      {
        Pump2_C = 0;
        P2=0;
        Serial3.print("333");
        Serial3.print(",");
        Serial3.print("e");
        Serial3.print(",");
        Serial3.print("444");
        delay(100);
      }
    }
  }
}

void Pump3_Count(int a)
{
  if( P3 == 1)
  {
    if( Pump1_N - Pump3_P >= 1000 )
    {
      Pump3_P = Pump1_N;
      Pump3_C += 1;
      Serial.println(Pump3_C);
      if(Pump3_C == a)
      {
        Pump3_C = 0;
        P3=0;
        Serial3.print("333");
        Serial3.print(",");
        Serial3.print("f");
        Serial3.print(",");
        Serial3.print("444");
        delay(100);
      }
    }
  }
}

void Pump4_Count(int a)
{
  if( P4 == 1)
  {
    if( Pump1_N - Pump4_P >= 1000 )
    {
      Pump4_P = Pump1_N;
      Pump4_C += 1;
      Serial.println(Pump4_C);
      if(Pump4_C == a)
      {
        Pump4_C = 0;
        P4=0;
        Serial3.print("333");
        Serial3.print(",");
        Serial3.print("g");
        Serial3.print(",");
        Serial3.print("444");
        delay(100);
      }
    }
  }
}
