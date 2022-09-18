#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Keypad.h>
#include <SPI.h> //RFID
#include <MFRC522.h> //RFID


LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial hc05(10,11);
//RFID Start
#define SS_PIN 53
#define RST_PIN 13
int card_pin = 6;
int ring_pin = 12;

#define card "40 EF 81 7C"
#define tag "D3 46 14 0A"
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
//RFID End

int count=0;
int cost = 0;
int balance=500;
int password=787;
int password1=8787;
bool flag =false;
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );


void setup() {
  Serial.begin(9600);
  //lcd.begin(16,2);
  //Sensor Start
   pinMode(35,INPUT);
  pinMode(42,OUTPUT);
  pinMode(26,OUTPUT);
  //Sensor End
  //RFID Start
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(card_pin,OUTPUT);
  pinMode(ring_pin,OUTPUT); 
  //RFID End
  lcd.init();
  lcd.backlight();
  hc05.begin(9600);
  //hc05.print("TABLE NO 1\n"); 



}

void loop()
{
  //Sensor Start
  if(digitalRead(35)==0){
    digitalWrite(26,LOW);
     digitalWrite(42,HIGH);
  }
  if(digitalRead(35)==1){
     digitalWrite(26,HIGH);
    digitalWrite(42,LOW);
  }
  //Sensor End
  //RFID Start
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
   //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  /*
  if (content.substring(1) == card) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access to this card");
    Serial.println();
    digitalWrite(6,HIGH);
    delay(3000);
    digitalWrite(6,LOW);
  }
  
  if(content.substring(1) == tag)
  {
    Serial.println("Authorized access to this tag");
    Serial.println();
    digitalWrite(12,HIGH);
    delay(5000);
    digitalWrite(12,LOW);
  }
  
 else   
 {
    Serial.println(" Access denied");
    delay(3000);
  }
 
*/
//RFID End

if(content.substring(1) == tag && balance>0 ){
  
    Serial.println("Authorized access to this tag");
    Serial.println();
    digitalWrite(12,HIGH);
    
    
  char keypressed = keypad.getKey();

  if (keypressed != NO_KEY)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    
    Serial.print(keypressed);
    if(keypressed=='1')
    {
      hc05.print("\nPIZZA  "); //Send message to smartphone
       delay(100);

       lcd.setCursor(2, 0);
       lcd.print("1. PIZZA ");
        lcd.setCursor(2, 1);
       lcd.print("250 taka");
       count = count+10;
       cost = cost + 250;
       balance-=250;
      
       
    }
    if(keypressed=='2')
    {
      hc05.print("\nSORMA  "); //Send message to smartphone
       delay(100);

       lcd.setCursor(2, 0);
       lcd.print("2. SORMA ");
           lcd.setCursor(2, 1);
        lcd.print("100 taka");
       count = count+5;
       cost = cost + 100;
       balance-=100;
      
    }
    if(keypressed=='3')
    {
      hc05.print("\nBURGER  "); //Send message to smartphone
       delay(100);

       lcd.setCursor(2, 0);
       lcd.print("3. BURGER ");
           lcd.setCursor(2, 1);
        lcd.print("150 taka");
        delay(2000);
        lcd.clear();
       count = count+10;
       cost = cost + 150;
       balance-=150;
      
    }
    if(keypressed=='5')
    {
       lcd.setCursor(2, 0);
       lcd.print("Your Balance:");
        lcd.setCursor(2, 1);
       lcd.print(balance);
       lcd.print(" Taka");

    
    }
     
       if(keypressed=='7'){
       balance+=500;
       lcd.setCursor(0, 0);
       lcd.print("Balance Reacharged");
       delay(1000);
       lcd.clear(); 
       lcd.setCursor(0, 0);
       lcd.print("Current Balance: ");
       lcd.setCursor(0, 1);
       lcd.print(balance);
       lcd.print(" Taka");
        delay(2000);
        lcd.clear();
       

       }
       if(keypressed=='8'){
       balance+=1000;
       lcd.setCursor(0, 0);
       lcd.print("Balance Reacharged");
       lcd.clear();
       delay(1000);
       lcd.setCursor(0, 0);
       lcd.print("Current Balance: ");
       lcd.setCursor(0, 1);
       lcd.print(balance);
       lcd.print(" Taka");
       }
       
    }


    if(keypressed=='*')
    {
      Serial.println(" Access denied");
      hc05.print("\nOrder Confirmed "); 
      digitalWrite(12,LOW);
      
      lcd.setCursor(0, 0);
        lcd.print("Order Received");
        delay(2000);
        lcd.clear();
      
      lcd.print("Processing Time : ");
      lcd.setCursor(2, 1);
      lcd.print(count);
     lcd.print(" min");
     delay(1000);
     lcd.clear();
       delay(2000);
       lcd.setCursor(0,0);
     lcd.print("Total Cost:");
      //lcd.setCursor(2, 1);
      lcd.print(cost);
      cost=0;
      count=0;
        delay(10000);
         lcd.clear();

    }
    if(keypressed=='9')
    {
      Serial.println(" Access denied"); 
      digitalWrite(12,LOW);
    }
    if(keypressed=='#')
    {
      hc05.print("\nCenceled Whole Order "); 
       lcd.setCursor(0, 0);
        lcd.print("Order Cenceled");
        
        count=0;
        cost=0;
        //balance=500;
         delay(5000);
         lcd.clear();
      
    }
    
  }
  
 else {
    hc05.print("\nCenceled Whole Order "); 
        lcd.setCursor(0, 0);
        lcd.print("Balance");
        lcd.setCursor(0, 1);
        lcd.print("Insufficient");
        delay(2000);
        lcd.clear();
        cost=0;
        count=0;
        balance=500;
        lcd.setCursor(0, 0);
        lcd.print("Please Reacharge");
        delay(2000);
        lcd.clear();
        lcd.setCursor(2, 0);
       lcd.print("7--> 500");
       lcd.setCursor(2, 1);
       lcd.print("8--> 1000");
       delay(3000);
       lcd.clear();
}
}
