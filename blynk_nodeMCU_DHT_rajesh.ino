#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <dht11.h>
dht11 DHT11;

BlynkTimer timer;
WidgetLCD BLYNK_LCD(V0); 
int t,h;
char auth[] = "8507cac915f04a1bb4b00987e420afa0";//rajesh token
char ssid[] = "ESPServer_RAJ";
char pass[] = "RAJ@12345";
int LED=D1;//D1
BLYNK_WRITE(V1)
{
  int LED_VAL = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(LED_VAL==HIGH)
  {
    digitalWrite(LED,HIGH);
    BLYNK_LCD.print(0,1,"Sprinkler ON ");
    delay(10);
    }
   else
   {
    //lcd.clear();
    digitalWrite(LED,LOW);
    BLYNK_LCD.print(0,1,"Sprinkler OFF");
    delay(10); 
    }
    
}


void READ_SENSOR()
{
  int chk = DHT11.read();
  t=DHT11.temperature;
  h=DHT11.humidity;

  int L=analogRead(A0);
  //BLYNK_LCD.clear();
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, h);
   Blynk.virtualWrite(V4, L);
  
  BLYNK_LCD.print(0,0,"T:");
  BLYNK_LCD.print(2,0,t);
  BLYNK_LCD.print(5,0,"H:");
  BLYNK_LCD.print(7,0,h);
  BLYNK_LCD.print(10,0,"L:");
  BLYNK_LCD.print(12,0,L);
 
}

void setup()
{
  Serial.begin(9600);
 // lcd.begin(20, 4);
  DHT11.attach(D2);
  Blynk.begin(auth, ssid, pass);
  pinMode(LED,OUTPUT);//D6 pin of NodeMCU
  timer.setInterval(1000L,READ_SENSOR);//// change
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}

