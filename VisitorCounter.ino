#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define in 2
#define out 3
#define led 4
#define buzzer 5
int i1 = 1;
int i2 = 3;
int count = 0;
int limit = 5;
boolean state1 = true;
boolean state2 = true; 

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
  lcd.print("Visitor Counter");
  delay(2000);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.clear();
}

void loop()
{  
  int in_value = digitalRead(in);
  int out_value = digitalRead(out);

  if(in_value == LOW && i1 == 1 && state1 && i2 != 4)
  {
    delay (400);
    i1 = 2;
    state1 = false;
  }
  else if(out_value == LOW && i1 == 2 && state2)
  {   
    delay(400);
    i1 = 1; 
    count++;
    lcd.clear();
    lcd.print("People In Room:");
    lcd.setCursor(0,1);
    lcd.print(count);
    if(count > limit)
    {
      count = limit;
      lcd.clear();
    }
    state2 = false;
  }
  
  else if(out_value == LOW && i2 == 3 && state2 && i1 != 2)
  {
    delay(400);
    i2 = 4;
    state2 = false;
  }
  else if(in_value == LOW && i2 == 4 && state1)
  {
    delay(400);
    i2 = 3;
    count--;
    lcd.clear();
    lcd.print("People In Room:");
    lcd.setCursor(0,1);
    lcd.print(count);
    if(count<0)
    {
      count = 0;
      lcd.clear();
    }
    state1 = false;
  }
  if(count >= limit)
  {
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Room is Fulling");
    lcd.setCursor(0,1);
    lcd.print("Please Wait!");
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
  }
  if(count<=0)
  {
    digitalWrite(led, LOW);
    lcd.setCursor(0,0);
    lcd.print("Nobody In Room");
    lcd.setCursor(0,1);
    lcd.print("Light is Off");
    delay(200);
  }
  else
    digitalWrite(led, HIGH);

  if (in_value)
  {
    state1 = true;
  }
  if (out_value)
  {
    state2 = true;
  } 
}