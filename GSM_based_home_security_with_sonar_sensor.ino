#include <SoftwareSerial.h>
#include <String.h>
//Code written by KOBIR
//kobirphero
SoftwareSerial SIM800L(2, 3);                  // tx,rx of GSM
String text_SMS;
int data = 0; 
String Phone_01 = "1234567890";             //Replace the number 1234567890 with your mobile number here.
String Phone_02 = "1234567890";            //Replace the number 1234567890 with your mobile number here.
String Phone_03 = "1234567890";           //Replace the number 1234567890 with your mobile number here.
boolean sms;
int trigPin = 10;
int echoPin = 9;
int led = 13;
int buzzer = 11;

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600); 
  SIM800L.begin(9600); 
  Serial.println(" Device is ready");
  delay(2000);
   pinMode(led, OUTPUT);
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(buzzer, OUTPUT);

   long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;
  Serial.print(distance);
  Serial.println("CM");
  delay(20);
   if(distance>13){
     text_SMS = "\n Someone has entered your room.";
     delay(400);
     SendSMS (text_SMS, Phone_01);
     delay(600);
     Serial.println(text_SMS);
     Serial.println("message sent to phone 01.");
     delay(500);    
  }
}
void loop() {
  long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;
  Serial.print(distance);
  Serial.println("CM");
  delay(20);
 
 if((distance<=13)) 
  {
    digitalWrite(led, LOW);
    sms=true;
    delay(50);
  }
   else if(distance>13)
 {
     if(sms==true){
     
     text_SMS = "\n Someone has entered your room.";
     delay(200);
     SendSMS (text_SMS, Phone_01);
     delay(600);
     Serial.println(text_SMS);
     Serial.println("message sent to phone 01.");
     delay(500);
     
     text_SMS = "\n Someone has entered your room.";
     SendSMS (text_SMS, Phone_02); 
     Serial.println(text_SMS);
     Serial.println("message sent to phone 02.");
     delay(2000);
     
     call(Phone_01);
     sms=false;
     delay(400);
     }
     digitalWrite(led, HIGH);
     digitalWrite(buzzer, LOW);
     delay (300);
     digitalWrite(led, LOW);
     digitalWrite(buzzer, LOW);
     delay (300);
   }
}
void SendSMS(String message, String number){
  
  String mnumber = "AT + CMGS = \"number\"\r"; 
   SIM800L.print("AT+CMGF=1\r");                   
   delay(900);
   SIM800L.println(mnumber);
 
  delay(800);
  SIM800L.println(message);                         // je message ta pathabe seta
  delay(900);
  SIM800L.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(700); 
  SIM800L.println();
  delay(100);                                     // give module time to send SMS
 // SIM900power();  
}
void call(String phone)
{
      Serial.println("calling...");
      SIM800L.println("ATD"+phone+";");
      delay(25000); 
      SIM800L.println("ATH");
      Serial.println("Call End.");
      delay(900);
}
