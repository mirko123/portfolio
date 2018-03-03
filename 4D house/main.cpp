#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT22.h>
#include <stdio.h>
#define DHT22_PIN 8
DHT22 myDHT22(DHT22_PIN);
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);           
Servo myservo; 

byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x1E, 0xF9};
byte ip[] = {87,121,241,8};
IPAddress gateway(152, 97, 100, 1);
IPAddress subnet(255, 255, 254, 0);
EthernetServer server(80);

double tempC=0;
double Hum=0;
int temp;
int pos = 0;
int irsensorPin = 2;
int sensorValue;
int sustoqnie=0;
int lightSensor=3;
int prisustviePin=10;
long milis10=0;
long lightMillis=0;
long LCDmillis=0;
long LCDmillis2=0;

int STBY = 3;
int PWMA = 11; //Speed control 
int AIN1 = 6; //Direction
int AIN2 = 5; //Direction

int potPin = 1;
int val = 0;  //Стойност на потенциометъра.
int value=0; //Стойност, която определя дали да се движи мотора.

long lastchange=0; //Променливата, в която се съхранява текущото време.
int interval=350; //Времето между промяна на посоките.

void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(7); // digitalniq pin na servoto 
  pinMode(12, OUTPUT); 
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(prisustviePin, OUTPUT); 
  pinMode(9, OUTPUT); 
  pinMode(13, OUTPUT); 
  pinMode(10, INPUT); 
  if (Ethernet.begin(mac) == 0) {
     Serial.println("Failed to configure Ethernet using DHCP");
        // start the Ethernet connection and the server:
        Ethernet.begin(mac, ip, gateway, subnet);
  }
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
} 

void loop() 
{ 
  /* Автоматизацията на гаражната врата съм направил в няколко състояния.
  Състояние 0 е когато няма кола пред гаража и системата е в покой.
  Променливата sensorValue приема стойността на сензора за разстояние.
  Когато тя надвишава 300, се подава ток към сервото, което отваря
  вратата и се влиза в състояние 1. След 3 секунди (това
  е времето за което се смята, че колата ще е влязла в гаража на макета),
  се влиза в стъпка 2 - затварянето на вратата. Когато тя се затвори,
  се минава от ново към състояние 0.
  */
  sensorValue = analogRead (irsensorPin);
  if(sensorValue > 300&&sustoqnie==0) sustoqnie=1;
  if(pos==179&&sustoqnie==1&&millis()-milis10>3000) sustoqnie=2;
  if(sustoqnie==1&&millis()-milis10>15&&pos<180-1)
  {
    pos++;
    milis10=millis();
    myservo.write(pos);
  }
  else if(sustoqnie==2&&millis()-milis10>15&&pos>1)
  {
    pos--;
    milis10=millis();
    myservo.write(pos);
  }
  if(sustoqnie==2&&pos==1) sustoqnie=0;
  /*Тук съм използвал доста прост начин за „викане” на асансьора с потенциометър,
  който контролира посоката на въртене на мотора и движи асансьора.
  Това мисля да се осъществя през интернет и смятам, че ще успея.
  val променливата приема стойността на потенциометъра, която е от 0 до 1024.
  Ако тя е по-малка от 512, се задава на мотора да се движи по посока
  на часовниковата стрелка. Ако тя е по-голяма или равна на 512,
  моторът се движи по посока, обратна на часовниковата стрелка.
  Сложил съм малък интервал от 350 милисекунди,
  защото в противен случай рискувам да изгори електромотора.
  Тук са използвани 2 състояния.
  */
  val = analogRead(potPin);
  if(value==0&&val<512)
  {
    move(1, 255, 1);
    if(analogRead(potPin)>=512) value=1;
  }
  else if(value==0)
  {
    move(1, 255, 0); 
    if(analogRead(potPin)<512) value=1;
  }
  if(millis()-interval>=lastchange)
  {
    value=0;
    lastchange=millis();
  }
//  temp= analogRead(0)*0.2222-61.111;
 /* Serial.print("tempC:");
  Serial.print(temp);
  Serial.println();*/
  /*Тук се проверяват данните от димния сензор. Ако стойността
  е по-голяма от 600 означава, че има пожар и се подава сигнал (ток) към алармата.
  */
  if(analogRead(0)>600) digitalWrite(12,HIGH);
  else digitalWrite(12,LOW);
  /*С условието по-долу проверявам дали има присъствие в къщата и колко
  е осветено навън. Дали е време да се включи осветлението.
  */
  if(digitalRead(prisustviePin)==1&&analogRead(lightSensor)<51)
  {
    digitalWrite(9,HIGH);
    lightMillis=millis();
  }
  else if(analogRead(lightSensor)>50)
  {
    digitalWrite(9,LOW);
  }
  else if(digitalRead(prisustviePin)==0&&millis()-lightMillis>7000) 
  /*Тук се проверява дали са минали 7 секунди от както за последно е имало движение и ако са да, се изгася осветлението*/
  {
    digitalWrite(9,LOW);
    lightMillis=millis();
  }
//  Serial.println(digitalRead(prisustviePin));
  if(millis()-LCDmillis>1000)
  {
    DHT2();
    Eth();
  }
}

/*Контролът на електромотора, задвижващ асансьора, се осъществява от драйвер TB6612FNG, който се управлява с функцията move. Тя взима 3 входни параметъра. Първи – motor е номерът на мотора, който ще се управлява, защото драйверът има възможност за контрол на 2 електромотора. 
Втори параметър - speed, с който се  контролира скоростта на електромотора, от 0 до 255. 
Трети параметър - direction, който оказва посоката на въртене на мотора, като стойност 0 означава въртене по посока на часовниковата стрелка, а стойност 1 посока, обратна на часовниковата стрелка.
*/
void move(int motor, int speed, int direction){
  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }
  digitalWrite(AIN1, inPin1);
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA, speed);
}

/*Функцията DHT2 взима информация от "метерологичната станция",
обработва я и я извежда на LCD дисплея.
*/
void DHT2()
{  
  LCDmillis2=millis();
  lcd.init();      
  lcd.setBacklight(0);
  lcd.setCursor(0,0); 
  DHT22_ERROR_t errorCode;
  errorCode = myDHT22.readData();
  switch(errorCode)
  {
    case DHT_ERROR_NONE: 
      lcd.print("Temp:");
      lcd.print(myDHT22.getTemperatureC());
      lcd.print("C");
      lcd.setCursor(0,1); 
      lcd.print("Humidity:");
      lcd.print(myDHT22.getHumidity());
      lcd.print("%");
      char buf[128];
      break;
    case DHT_ERROR_CHECKSUM:
   //   lcd.print("check sum error ");
      lcd.print("Temp:");
      lcd.print(myDHT22.getTemperatureC());
      lcd.print("C");
      lcd.setCursor(0,1); 
      lcd.print("Humidity:");
      lcd.print(myDHT22.getHumidity());
      lcd.print("%");
      break;
    case DHT_BUS_HUNG:
      
      break;
    case DHT_ERROR_NOT_PRESENT:
      lcd.print("Not Present ");
      break;
    case DHT_ERROR_ACK_TOO_LONG:
      lcd.print("ACK time out ");
      break;
    case DHT_ERROR_SYNC_TIMEOUT:
      lcd.print("Sync Timeout ");
      break;
    case DHT_ERROR_DATA_TIMEOUT:
      lcd.print("Data Timeout ");
      break;
  }
  tempC=myDHT22.getTemperatureC(); //Temperature in C.
  Hum=myDHT22.getHumidity(); //Humidity.
}

/*С функцията Eth се осъществява комуникацията в интернет.
Тя изпраща HTTP заявка с данните от "метерологичната станция" в HTML.
*/
void Eth() {
    // listen for incoming clients
    EthernetClient client = server.available();
    if (client) {
        Serial.println("new client");
        // an http request ends with a blank line
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connnection: close");
                    client.println();

                    client.println("<!DOCTYPE HTML>");
                    client.println("<html>");
                    // add a meta refresh tag, so the browser pulls again every 5 seconds:
                    client.println("<meta http-equiv=\"refresh\" content=\"5\">");
                    // output the value of each analog input pin
                    
                        client.print("Temperature:");
                        client.print(tempC);
                        client.print("C");
                        client.println("<br />");
                        client.print("Humidity:");
                        client.print(Hum);
                        client.print("%");
                        client.println("<br />");
                    client.println("</html>");
                    break;

                }
                if (c == '\n') {
                    // you're starting a new line
                    currentLineIsBlank = true;
                } else if (c != '\r') {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
        // give the web browser time to receive the data
        // close the connection:
        client.stop();
        Serial.println("client disonnected");
    }
}