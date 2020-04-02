#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>


const char* ssid = "MYSSID";
const char* password = "SSID_PASSWORD";


//This is for a Wemos D1 Mini
#define RSTPIN D1
#define SSPIN D2
// Pin usage for MFRC5522
MFRC522 rc(SSPIN, RSTPIN);

int readsuccess;

/* the following are the UIDs of the card which are authorised
    to know the UID of your card/tag use the example code 'DumpInfo', 
    from the library mfrc522 it give the UID of the card as well as
    other information in the card on the serial monitor of the arduino
    alternatively, this sketch will output the code in the serial monitor
*/

//byte defcard[4]={0x32,0xD7,0x0F,0x2B}; // if you only want one card
byte defcard[][4] = {{0x4, 0xDE, 0xC6, 0xFA}, {0x4, 0xDA, 0xC6, 0xFA}, {0x4, 0xE1, 0xC7, 0xFA},{0x4, 0x85, 0x77, 0xFA}, {0x4, 0xE1, 0xC7, 0xFA},{0x4, 0xE6, 0xC7, 0xFA}}; //for multiple cards

int N = 6; //change this to the number of cards/tags you will use
byte readcard[4]; //stores the UID of current tag which is read
int cardNumber;

void setup() {
  Serial.begin(9600);
  // Connecting to Wifi
  WiFi.begin(ssid, password);
  Serial.print("Connecting..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("..");
    delay(1000);
  }
  // Initialize the MFRC522
  SPI.begin();
  rc.PCD_Init(); //initialize the receiver
  rc.PCD_DumpVersionToSerial(); //show details of card reader module

  // Display list of authorized card
  Serial.println(F("the authorised cards are")); 
  for (int i = 0; i < N; i++) {
    Serial.print(i + 1);
    Serial.print("  ");
    for (int j = 0; j < 4; j++) {
      Serial.print(defcard[i][j], HEX);
    }
    Serial.println("");
  }
  Serial.println("");

  Serial.println(F("Scan RFID Tags to launch volumio"));
}


void loop() {

  readsuccess = getid();

  if (readsuccess) {
    int match = 0; // This change to 1 if the tag is in our defcard Array
    int cardIncr = 0; // Variable to know the location of the uid in the array

    //this is the part where compare the current tag with pre defined tags
    for (int i = 0; i < N; i++) {
      //Serial.print("Testing Against Authorised card no: ");
      //Serial.println(i+1);
      cardIncr++;
      if (memcmp(readcard, defcard[i], 4) == 0) {
        match = 1;
        cardNumber = cardIncr;
        Serial.print("la valeur de cardNumber est");
        Serial.println(cardNumber);
      } else {

        // Serial.println("no match");
      }

    }


    if (match)
    {
      if (cardNumber == 2)
      {
        Serial.println("numero de carte 2");
        if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
          Serial.println("le wifi est connecte");
          HTTPClient http;  //Declare an object of class HTTPClient

          http.begin("http://192.168.1.47/api/v1/commands/?cmd=toggle");  //Specify request destination
          int httpCode = http.GET();                                                                  //Send the request
          Serial.print("le code http recu est le : ");
          Serial.println(httpCode);
          if (httpCode > 0) { //Check the returning code
            String payload = http.getString();   //Get the request response payload
            Serial.println(payload);                     //Print the response payload
          }
          http.end();   //Close connection

        }
        //delay(30000);    //Send a request every 30 seconds
      }
      else if (cardNumber == 1) {
        Serial.println("numero de carte 1 - django reinhardt");
        if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
          Serial.println("le wifi est connecte");
          HTTPClient http;  //Declare an object of class HTTPClient

          http.begin("http://192.168.1.47/api/v1/commands/?cmd=playplaylist&name=django");  //Specify request destination
          int httpCode = http.GET();                                                                  //Send the request
          Serial.print("le code http recu est le : ");
          Serial.println(httpCode);
          if (httpCode > 0) { //Check the returning code
            String payload = http.getString();   //Get the request response payload
            Serial.println(payload);                     //Print the response payload
          }
          http.end();   //Close connection

        }
      }
      else if (cardNumber == 4) {
        Serial.println("numero de carte 4 - Polo et Pan");
        if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
          Serial.println("le wifi est connecte");
          HTTPClient http;  //Declare an object of class HTTPClient

          http.begin("http://192.168.1.47/api/v1/commands/?cmd=playplaylist&name=poloetpan");  //Specify request destination
          int httpCode = http.GET();                                                                  //Send the request
          Serial.print("le code http recu est le : ");
          Serial.println(httpCode);
          if (httpCode > 0) { //Check the returning code
            String payload = http.getString();   //Get the request response payload
            Serial.println(payload);                     //Print the response payload
          }
          http.end();   //Close connection

        }
      } else if (cardNumber == 5) {
        Serial.println("numero de carte 5 - corsica playlist");
        if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
          Serial.println("le wifi est connecte");
          HTTPClient http;  //Declare an object of class HTTPClient

          http.begin("http://192.168.1.47/api/v1/commands/?cmd=playplaylist&name=corse");  //Specify request destination
          int httpCode = http.GET();                                                                  //Send the request
          Serial.print("le code http recu est le : ");
          Serial.println(httpCode);
          if (httpCode > 0) { //Check the returning code
            String payload = http.getString();   //Get the request response payload
            Serial.println(payload);                     //Print the response payload
          }
          http.end();   //Close connection

        }
      }  else if (cardNumber == 6) {
        Serial.println("numero de carte 6 - beach playlist");
        if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
          Serial.println("le wifi est connecte");
          HTTPClient http;  //Declare an object of class HTTPClient

          http.begin("http://192.168.1.47/api/v1/commands/?cmd=playplaylist&name=plage");  //Specify request destination
          int httpCode = http.GET();                                                                  //Send the request
          Serial.print("le code http recu est le : ");
          Serial.println(httpCode);
          if (httpCode > 0) { //Check the returning code
            String payload = http.getString();   //Get the request response payload
            Serial.println(payload);                     //Print the response payload
          }
          http.end();   //Close connection

        }
      }
      else {
        Serial.println("pas enregistre");
      }
    }
  }

}
//function to get the UID of the card
int getid() {
  if (!rc.PICC_IsNewCardPresent()) {
    return 0;
  }
  if (!rc.PICC_ReadCardSerial()) {
    return 0;
  }
  Serial.println("THE UID OF THE SCANNED CARD IS:");

  for (int i = 0; i < 4; i++) {
    readcard[i] = rc.uid.uidByte[i]; //storing the UID of the tag in readcard
    Serial.print(readcard[i], HEX);

  }
  Serial.println("");
  Serial.println("Now Comparing with Authorised cards");
  rc.PICC_HaltA();

  return 1;
}



