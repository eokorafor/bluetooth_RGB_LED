//Ejeh Okorafor   1/3/2107  
//RGB LED bluetooth controller, originally made using arduino uno
//can optionally add a passcode to use

#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);        //Softwareserial necessary for pins other than 13
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11 (Max sure to drop voltage)
// connect BT Vcc to 5V, GND to GND

char a; // stores incoming character from other device
char message[10];

void clearArray(char arr[], int);

void setup()  {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  BT.begin(9600);
}

void loop() {
  int i;
  int k = 0;
  while(BT.available()){
    a = BT.read();
    delay(100);
    message[k] = a;
    k++;
  }
  
  if(message[0] > 0){  //check if there was a message
    //BT.println(message);
     int val = -1;

    if((message[0] >= '0' && message[0] <= '9') && strlen(message) < 4){ // a number
     //Assume a three digit value
     val = (message[0] - 0x30) * 100;
     val = val + ((message[1] - 0x30) * 10);
     val = val + ((message[2] - 0x30) * 1);
    }
    else if(strcmp(message, "off") == 0){
      analogWrite(3, 255);
      analogWrite(5, 255);
      analogWrite(6, 255);
    }
    else if(strlen(message) >= 4 && (message[0] >= '0' && message[0] <= '9')){
     BT.println("Number too long. Input a three digit number");
    }
    else{
     BT.println("Not a number. Try again");
    }
    
     if(val < 256 && val >= 0){
      BT.println("For which light (RGB)?");
      char color = 0;
      while(color == 0){
        int sen = 0;
        if(BT.available()){
          color = BT.read();
          sen = 1;
        }
        if((color != 'R' && color != 'G' && color != 'B') && sen){
          BT.println("Invalid color. Try again.");
          color = 0;
        }
      }

      if(color == 'R'){
        analogWrite(3, val);
      }
       if(color == 'G'){
        analogWrite(5, val);
      }
       if(color == 'B'){
        analogWrite(6, val);
      }
     }
     else if(val > 255){
      BT.println("Number too high, use 000-255");     
     }
  }

  
  clearArray(message, 10);
  delay(50);
}

void clearArray(char arr[], int len){
  for(int i = 0; i < len; i++){
    arr[i] = 0;
  }
  return;
}

