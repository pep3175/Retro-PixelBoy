const int powerCtrl = 0;      //Controle l'alim de l'ATTiny
const int powerRasp = 4;      //Contrôle l'alim du RPI
const int gpioShutdown = 2;   //Commande l'extinction du RPI
const int gpioPoweroff = 3;   //Signale que le RPI est éteint
const int pushButton = 1;     //Bouton PWR

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
  digitalWrite(powerRasp, LOW);
  digitalWrite(gpioShutdown, LOW);

  delay(2000);    //Tempo pression boutton avant démarrage

  digitalWrite(powerCtrl, HIGH);
  digitalWrite(powerRasp, HIGH);
  
  //delay(2000);
  
  delay(20000);    //Attendre que le RPI ai bien démarré avant de permettre l'extinction
  /*raspOff = digitalRead(gpioPoweroff);
  while (raspOff == HIGH) {
    delay(500);
    raspOff = digitalRead(gpioPoweroff);
  }*/
}

void loop() {
  buttonState = digitalRead(pushButton);
  raspOff = digitalRead(gpioPoweroff);

  //Appui environ 1.5s sur le bouton pour commander l'extinction du RPI  
  if (buttonState == LOW) {
    count1++;
    if (count1 == 30) {
      digitalWrite(gpioShutdown, HIGH);
      delay(200);
      digitalWrite(gpioShutdown, LOW);
    }
  } else {
    count1 = 0;
  }

  //Lorsque le RPI est éteint raspOff passe à HIGH
  if (raspOff == HIGH) {
    count2++;
    if (count2 == 20) {
      delay(1000);
      digitalWrite(powerRasp, LOW); //On coupe l'alim du RPI
      delay(1000);
      digitalWrite(powerCtrl, LOW); //On coupe l'alim du ATTiny
    }
  } else {
    count2 = 0;
  }
  
  delay(50);
}
