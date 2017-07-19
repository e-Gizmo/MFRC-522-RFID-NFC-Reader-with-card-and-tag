/*
 E-GIZMO NFC RFID-RC522 RF IC Card 13.56Mhz
 
 SAMPLE CODE TO READ A CARD 
 USING A MFRC522 READER ON YOUR SPI INTERFACE.
 
 NOTE: DOWNLOAD THE RFID LIBRARY.
 
 WIRE CONNECTIONS:
 GIZDUINO PLUS   RFID-RC522
 =============   ============
 SS   ------> PIN 10
 MOSI ------> PIN 11 /ICSP-4
 MISO ------> PIN 12 /ICSP-1
 SCK  ------> PIN 13 /ICSP-3
 RST  ------> PIN  9
 
 CODES BY E-GIZMO MECHATRONIX CENTRAL
 http://www.e-gizmo.com
 MARCH 10,2017
 
 */
//LIBRARY
#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);

//SERIAL NUMBER CARD
int serNum[5];
int cards[][5] = {
  {5,117,21,219,190} // 5 117 21 219 190

};

bool access = false;

void setup(){
  //INITIALIZE SERIAL COMMUNICATION
  Serial.begin(9600);
  SPI.begin();
  rfid.init();


}

void loop(){

  if(rfid.isCard()){
    //READ THE RFID CARD INFO
    if(rfid.readCardSerial()){
      //PRINTS THE SERIAL NUMBER
      Serial.print(rfid.serNum[0]);
      Serial.print(" ");
      Serial.print(rfid.serNum[1]);
      Serial.print(" ");
      Serial.print(rfid.serNum[2]);
      Serial.print(" ");
      Serial.print(rfid.serNum[3]);
      Serial.print(" ");
      Serial.print(rfid.serNum[4]);
      Serial.println("");

      for(int x = 0; x < sizeof(cards); x++){
        for(int i = 0; i < sizeof(rfid.serNum); i++ ){
          if(rfid.serNum[i] != cards[x][i]) {
            access = false;
            break;
          } 
          else {
            access = true;
          }
        }
        if(access) break;
        delay(100); // DELAY TO READ A CARD (NOTE: YOU CAN COMMENT/DELETE IT)
      }

      if(access){
              //ADD YOUR CODES HERE
      }
    }
    rfid.halt();

  }
}







