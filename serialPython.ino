// variables
String serialData = "";
char pinSector = '0';
char writingType = '0'; 
int writingData = 0;
String readingData = "0";
int pinNumber = 0;

// pins
int digitPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53};
int analogPins[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15};


void setup() {
  Serial.begin(9600);
  for (int i=0; i<53; i++){
    pinMode(digitPins[i], OUTPUT);
  }
}

/*
serialData format:

first char:
D = digital pin sector
A = analog pin sector

2nd and 3th char:
** = pin number in that secor


When digital pin sector:
4th char:
writing type 
d = digital
a = analog

5th, 6th, 7th char:
data to write on pin
===============================================================
When analog sector:
sending data back, so no further information needed

Analog Data format:
first char:
A = analog pin sector

2nd and 3th char:
** = pin number in that secor

4th, 5th, 6th, 7th char:
data from the analog pin

*/ 
void loop() {
  if (Serial.available() > 0) {
    serialData = Serial.readStringUntil('\n');
    
    // get pin sector
    pinSector = serialData.charAt(0);
    // get pin number
    pinNumber = (serialData.substring(1,3)).toInt();

    // Digital Pins
    if(pinSector == 'D'){
      // get writing type
      writingType = serialData.charAt(3);
      
      // writing digital
      if (writingType == 'd'){
        writingData = (serialData.substring(4, 5)).toInt();
        digitalWrite(pinNumber, writingData);
        
        
      }
      // writing analog
      else if(writingType == 'a'){
        writingData = (serialData.substring(4, 7)).toInt();
        analogWrite(pinNumber, writingData);

      }
    }

    
    //Analog
    else if (pinSector == 'A'){
      // reading data from analog pin
      readingData = String (analogRead(pinNumber));
      
      // adding numers for the formating
      for (int i = readingData.length(); i<4; i++){
        readingData = "0" + readingData;
      }
      // send back PinSector
      Serial.print(pinSector);

      // adding numers for the formating
      if(pinNumber < 10){
        Serial.print("0");
        
      } 
      // send back pin number
      Serial.print(pinNumber);
      
      // send back reading data
      Serial.println(readingData);
      
    }
  }
}
