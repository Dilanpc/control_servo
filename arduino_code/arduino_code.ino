#include <Servo.h>

int angle=0;
Servo servo;
const int pinServo = 8;

void setup(){
  Serial.begin(9600);
  servo.attach(pinServo);

}

void loop(){
  // read entrance
  if (Serial.available() >= 4){
    if (Serial.peek() != '\n' && Serial.peek() != '\r'){
      // se reciben número en ASCII, por ello se resta el caracter '0' en cada dígito
      angle = (Serial.read() - '0')*100 + (Serial.read() - '0')*10 + Serial.read() - '0';
      Serial.println(angle);
    }
    clear();
  }

  servo.write(angle);

  delay(100);

}


void clear(){
  while(Serial.available() > 0) Serial.read(); //Descartar excedentes
}
void printAll(){
  while (Serial.available() > 0){
    Serial.print(Serial.read());
  }
}