#include<avr/io.h>

const int ATTN = 3;
const int SSEL = 4;
const int LED = 5;

boolean collisionOccurred = false;

//Delimiter bit 0x7E

void setup()
{
  //SPSR = SPSR | 0x01; // SPI2X set - not needed
  SPCR = 0xD3; // Fosc/128 (Mode 0, MSB first, Interrupts enabled)

  pinMode(ATTN, INPUT);
  pinMode(SSEL, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(SSEL, LOW);
  digitalWrite(LED, LOW);

  Serial.begin(9600);
}
void loop()
{
  String msg = "AGV-Xiaomi";
  int len = msg.length();

  // Field 1 - delimiter
  SPDR = 0x7E;
  delay(10);

  // Field 2,3 - length (limited to 65,535)
  SPDR = len >> 8; // MSB
  delay(10);
  SPDR = len & 0xFF; // LSB
  delay(10);

  // Field 4 - cmdID
  int cmdID = 0x01;
  SPDR = cmdID; // Zigbee Transmit Request
  delay(10);
  int chksum = cmdID;

  // Field 5 Frame ID
  int FID = 0x01;
  SPDR = FID;
  delay(10);
  chksum += FID;

  // Field 6,7 - 16-bit address - 0xFFFF for broadcast
  int address = 0xFFFF;
  SPDR = address >> 8;
  delay(10);
  SPDR = address & 0xFF;
  delay(10);
  chksum += address;

  // Field 8 - Spacer
  SPDR = 0x00;
  delay(10);  

  // Field 9 to n - data
  for (int i = 0; i < len; i++) {
    SPDR = msg[i];
    chksum += msg[i];
    delay(10);
  }

  // Field n+1 - checksum
  SPDR = 0xFF - (chksum & 0xFF);
  delay(10);

  Serial.println("SUMMARY");
  
  Serial.print("Collision Status: ");
  if(collisionOccurred){
    Serial.println("Occurred");
  }
  else{
    Serial.println("None.");
  }
    
  delay(1000);
}
