#include<LiquidCrystal.h>
#include <IRremote.h>
const int RECV_PIN=14;
IRrecv irrecv(RECV_PIN);
decode_results results;
#include<LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define Light 7
#define Bulb 8
#define Fan 9

int i=0,j=0,k=0,n=0,p=0;
int pwmValue = 0;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(Light, OUTPUT);
  pinMode(Bulb, OUTPUT);
  pinMode(Fan, OUTPUT);
  lcd.print("Good Morning Sir");
  delay(2000);
  lcd.clear();
  lcd.print("My Project is");
  delay(2000);
  lcd.clear();
  lcd.print("Remote Controled");
  lcd.setCursor(0,1);
  lcd.print("Home Automation");
  delay(2000);
  lcd.clear();
  lcd.print("My System is now");
  lcd.setCursor(0,1);
  lcd.print("Ready to use...");
  delay(5000);
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  lcd.clear();
  lcd.print("Press the Power Key..");
}

void loop() 
{
  if (irrecv.decode(&results)) 
   {
     Serial.println(results.value,HEX);
     delay(100);
    // lcd.setCursor(0,0);
    // lcd.print("Light  Bulb  Fan"); 
    if(results.value==0x6D5D1DB3)
     {
       lcd.clear();
        p++;
        int x=p%2;
        if(x)
        {
         lcd.setCursor(0,0);
         lcd.print("Light  Bulb  Fan");
         lcd.setCursor(0,1);
         lcd.print("OFF    OFF   OFF");
        }
        else
        {
        lcd.print("Good Bye...");
        delay(2000);
        lcd.clear();
        }
     }
     if(results.value==0x885B30D5)
     {
        i++;
        int x=i%2;
        digitalWrite(Light, x);
        lcd.setCursor(0,1);
        if(x)
        lcd.print("ON  ");
        else
        lcd.print("OFF ");
       // delay(200);
     }
    
     if(results.value==0xE7E0CFB1)    //  key 1 

     {
        j++;
        int x=j%2;
        digitalWrite(Bulb, x);
        lcd.setCursor(7,1);
        if(x)
        lcd.print("ON   ");
        else
        lcd.print("OFF  ");
        delay(200);
     }
      if(results.value==0x4B12992B)    //  key 1 

     {
       if(pwmValue<=245)
       {
         pwmValue=pwmValue + 10;
         analogWrite(Fan,pwmValue);
         //analogWrite(Light,pwmValue);
         delay(200);
       }
       // delay(200);
     }
     if(results.value==0x1BE8C80D)    //  key 1 

     {
       if(pwmValue>=20)
       {
         pwmValue=pwmValue - 10;
         analogWrite(Fan,pwmValue);
         //analogWrite(Light,pwmValue);
         delay(200);
       }
        delay(200);
     }
   
     if(results.value==0xA34F5A01)
     {
        k++;
        int x=k%2;
        lcd.setCursor(13,1);
        if(x)
        {
         pwmValue = 255 ;
         analogWrite(Fan,pwmValue);
         lcd.print("ON ");
         delay(200);
        }
        else
        {
         pwmValue = 0 ;
         analogWrite(Fan,pwmValue);         
         lcd.print("OFF");
         delay(200);
        }
       }
       
        if(results.value==0x22614D75)
       {
        n++;
        int x=n%2;
        digitalWrite(Fan, x);
        digitalWrite(Bulb,x);
        digitalWrite(Light,x);
        lcd.setCursor(0,1);
        if(x)
        lcd.print("ON     ON    ON ");
        else
        lcd.print("OFF    OFF   OFF");
        delay(200);
       }
     irrecv.resume(); // Receive the next value
     //delay(100);
   }
}

