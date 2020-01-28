#include <SoftwareSerial.h>
#include <Servo.h>

int angle;
int rpm;
bool button;
bool flag = true;

SoftwareSerial bt(12,13);
Servo steering;
Servo ESC;

void setup()
{
  Serial.begin(9600);
  bt.begin(9600);
  bt.print("CONNECTED");
  bt.print("#");
  Serial.print("Begin");
  steering.attach(10);
  ESC.attach(11);
  steering.write(90);
  ESC.write(90);
}

void loop()
{
  Joystick();

  Serial.print(angle);
  Serial.print("   ");
  Serial.print(rpm);
  Serial.print("   ");
  Serial.println(button);
  steering.write(angle);
  ESC.write(rpm);
}

void Joystick() {
  if (bt.available())
  {
    int data = bt.read();
    if (data <= 100) {
      if (flag) {
        angle = map(data, 0, 100, 60, 120);
        flag = false;
      }
      else {
        rpm = map(data, 0, 100, 60, 120);
        flag = true;
      }
    }
    else{
      if(data == 105){
        button = 1;
      }
      if(data == 106){
        button = 0;
      }
    }
  }
}
