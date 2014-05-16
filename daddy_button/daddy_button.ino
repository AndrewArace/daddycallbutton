int INTERNAL_LED = 13;

int BUTTON = 2;

int LED1 = 9;
int LED2 = 3;
int LEDS[] = {
  LED1, LED2};
boolean caught = false;

void setup() {
  pinMode(INTERNAL_LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}


void loop() {
  checkReceive();
  checkTransmit();
}


void checkReceive() {
  if (Serial.available() > 0) {
    if (Serial.read() == 'D'){
      if(!caught) {
        caught = true;
        pulseh2l(LEDS, 2);
      }  
    }
  }
  else {
    caught = false;
  }
}


void checkTransmit() {
  if (digitalRead(BUTTON) == HIGH) {
    Serial.print('D');
    delay(10); // prevents overwhelming the serial port
  }
}


void pulseh2l(int pin) {
  int pins[] = {
    pin  };
  pulseh2l(pins, 1, 5, 10);
}


void pulseh2l(int pins[], int numPins) {
  pulseh2l(pins, numPins, 5, 10);
}


void pulseh2l(int pins[], int numPins, int stepSpeed, int wait) {
  for(int i = 255; i >= 0; i-=stepSpeed) {
    for(int j = 0; j < numPins; j++) {
      analogWrite(pins[j], i);
    }
    delay(wait);
  }
  //ensure off at the end
  for(int j = 0; j < numPins; j++) {
    analogWrite(pins[j], 0);
  }
}

