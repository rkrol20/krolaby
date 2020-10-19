#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

float t=10.0;
int count=1,score=0,i=16, sterowanie=13, last_bright=175;

byte run1[] = {
  B00000,
  B00110,
  B00110,
  B01100,
  B10111,
  B00100,
  B11010,
  B00010
};
byte run2[] = {
  B00000,
  B00110,
  B00110,
  B11101,
  B10110,
  B00100,
  B00110,
  B01100
};
byte jumpOver[] = {
  B00110,
  B00110,
  B01111,
  B10100,
  B00110,
  B01001,
  B11000,
  B11000
};
byte jump1[] = {
  B00110,
  B00110,
  B01111,
  B10100,
  B00110,
  B01001,
  B00000,
  B00000
};
byte jump2[] = {
  B00000,
  B00110,
  B00110,
  B01111,
  B10100,
  B00110,
  B01001,
  B00000
};


byte block2[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11000,
  B11000
};

byte crash1[] = {
  B00000,
  B00110,
  B00110,
  B01100,
  B10110,
  B00100,
  B01011,
  B10111
};

byte crash2[] = {
  B11111,
  B11001,
  B11001,
  B10011,
  B01001,
  B11011,
  B10100,
  B01000
};

int menu()
{
  int start=0;
  while(start==0)
  {
    
    brightness();
    lcd.setCursor(0,0);
    lcd.print("MENU");
    lcd.setCursor(0,1);
    lcd.print("Start Ustawienia");
    if(digitalRead(12)==LOW)
    {
      lcd.setCursor(0,1);
    lcd.print("                ");
      delay(200);
    lcd.setCursor(0,1);
    lcd.print("Start           ");
      delay(200);
      lcd.clear();
      start=1;
    }
    if(digitalRead(13)==LOW)
    {
      lcd.setCursor(0,1);
    lcd.print("                ");
      delay(200);
    lcd.setCursor(0,1);
    lcd.print("      Ustawienia");
      delay(200);
      lcd.clear();
      ustawienia();
    }
  }
  lcd.clear();
}

int ustawienia()
{
  int back=0;
  while(back==0)
  {
    //brightness();
    lcd.setCursor(0,0);
    lcd.print("USTAWIENIA");
    lcd.setCursor(0,1);
    lcd.print("Przyciski  Gesty");
    if(digitalRead(12)==LOW)
    {
      lcd.setCursor(0,1);
    lcd.print("                ");
      delay(200);
    lcd.setCursor(0,1);
    lcd.print("Przyciski       ");
      delay(200);
      lcd.clear();
      sterowanie=13;
     back=1;
    }
    if(digitalRead(13)==LOW)
    {
      lcd.setCursor(0,1);
      lcd.print("                ");
      delay(200);
    lcd.setCursor(0,1);
    lcd.print("           Gesty");
      delay(200);
      lcd.clear();
      sterowanie=1; 
      back=1;
    }
  }
}

int gesty()
{
  long czas, dystans;
   digitalWrite(8, LOW);
  delayMicroseconds(2);
  digitalWrite(8, HIGH);
  delayMicroseconds(10);
  digitalWrite(8, LOW);
  czas = pulseIn(9, HIGH);
  dystans = czas/58;
  if(dystans<10)
  {
    digitalWrite(0,HIGH);
    return 1;
  }
  else
  {
    digitalWrite(1,HIGH);
    return 0;
  }
}

int akcja()
{
  if(sterowanie==1)
  {
    return gesty();
  }
  else
  {
    if(digitalRead(13)==LOW)
    {
      return 1;
    }
    else
    {
      return 0;
    }
   }
}

int action_jump(int i)
  {
    
    if(akcja()==1)
     {
      if(i==16)
      {
       lcd.setCursor(0,1);
       lcd.write(4);
       if(i==1)
       delay(40*t);
       else
       {
      delay(10*t);}
      lcd.setCursor(0,1);
      lcd.write(6);//animacja nad klockiem
      lcd.write(" ");
      count++;
      score++;
      delay(40*t);
       
      
      }
      else
      {
     lcd.setCursor(0,1);
       lcd.write(4);
      delay(10*t);
      lcd.setCursor(0,1);
      lcd.write(3);
      delay(30*t);
      lcd.setCursor(i,1);
      lcd.write(5);
      lcd.write(" ");


      i--;
      delay(10*t);
      if(i<1)
      {
        lcd.setCursor(1,1);
        lcd.print(" ");
        i=16;
       }
      delay(40*t);
      lcd.setCursor(0,1);
      lcd.write(4);
      delay(10*t);
     }
     }
    else
    {
     delay(10*t);
     if(akcja()==0)
      {
        delay(10*t);
      }
      if(akcja()==0)
      {
        delay(10*t);
      }
      if(akcja()==0)
      {
        delay(10*t);
        if(i==16)
        {
          i=-1;
        }
      }
      
     
    }
    digitalWrite(1,LOW);
    digitalWrite(0,LOW);
    return i;
  }

  void gameOver()
{
  int j;
  for(j=0;j<4;j++)
  {
    brightness();
    lcd.setCursor(0,1);
    lcd.write(7);
    lcd.print(" ");
    delay(500);
    lcd.setCursor(0,1);
    lcd.write(8);
    lcd.print(" ");
    delay(500);
  }
  while(digitalRead(13)==HIGH)
  {
  lcd.setCursor(0,0);
  lcd.print("PRZEGRANA");
  brightness();
  }
  delay(250);
      
  
  lcd.setCursor(0,1);
  lcd.clear();
  i=16;
  score=0;
  count=1;
  t=10.0;
  menu();
}

void brightness()
{
  int b;
  b=analogRead(A0)/4;
  b=(b+last_bright)/2;
  if(b<1)
  {
    b=1; //trzyma minimalną jasn
  }
  last_bright=b;
  analogWrite(11,b*1.1);
}

void setup() 
{
  lcd.begin(16,2);
  lcd.createChar(1, run1);
  lcd.createChar(2, run2);
  lcd.createChar(3, jump1);
  lcd.createChar(4, jump2);
  lcd.createChar(5, block2);
  lcd.createChar(6, jumpOver);
  lcd.createChar(7, crash1);
  lcd.createChar(8,crash2);
  lcd.home();
  lcd.setCursor(0,1);
  
  pinMode(13,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  pinMode(A0,INPUT);
  pinMode(11,OUTPUT);
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,INPUT);
  brightness();
 menu();
}

int x=0;
void loop() 
{
   
  brightness();
  
   lcd.setCursor(14,0);
   lcd.print(score);
   lcd.setCursor(0,1);
   lcd.write(1);
   lcd.setCursor(1,1);
   lcd.print(" ");
   lcd.setCursor(i,1);
   lcd.write(5);
   lcd.write(" ");

   
   i--;
   if(i<1)
   {
    i=16;
   }
   
   i=action_jump(i);
   brightness();
   if(i==-1)
   {
    gameOver();
   }
   lcd.setCursor(0,1);
   lcd.write(2);
   i=action_jump(i);
   if(i==-1)
   {
    gameOver();
   }

   
   if(count>1)
   {
    t=0.8*t;
    count=1;
   }

  
 // czas=pulseIn(echo,HIGH);
//  dystans=czas/5800.00;

 
}
