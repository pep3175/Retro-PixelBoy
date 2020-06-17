const int powerCtrl = 0;
const int pushButton = 1;
const int gpioShutdown = 2;
const int gpioPoweroff = 3;
const int powerRasp = 4;

int buttonState = 0;
int raspOff = 0;
int count1 = 0;
int count2 = 0;

void setup() {
  pinMode(powerCtrl, OUTPUT);
  pinMode(powerRasp, OUTPUT);
  pinMode(gpioShutdown, OUTPUT); 
  pinMode(gpioPoweroff, INPUT); 
  pinMode(pushButton, INPUT);

  digitalWrite(powerCtrl, LOW);

  delay(2000);

  digitalWrite(powerCtrl, HIGH);
  digitalWrite(powerRasp, HIGH);
}

void loop() {
  buttonState = digitalRead(pushButton);
  raspOff = digitalRead(gpioPoweroff);
  
  if (buttonState == HIGH) {
    count1++;
    if (count1 == 30) digitalWrite(gpioShutdown, HIGH);
  } else {
    digitalWrite(gpioShutdown, LOW);
    count1 = 0;
  }

  if (raspOff == HIGH) {
    count2++;
    if (count2 == 30) {
      delay(2000);
      digitalWrite(powerRasp, LOW);
      delay(1000);
      digitalWrite(powerCtrl, LOW);
    }
  } else {
    count2 = 0;
  }
  
  delay(50);
}
