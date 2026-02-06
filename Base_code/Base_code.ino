// Pin Definitions
#define in1 3
#define in2 5
#define in3 6
#define in4 11
#define LEDF 9
#define LEDB 8
#define HORN 7
#define LEDP 4

// Variables
int command;            // Store Bluetooth command
int Speed = 225;        // Speed range: 0 - 255
int Speedsec;           // Used for turning (secondary motor speed)
int Turnradius = 110;   // Radius for turns, must be less than Speed
int brakeTime = 45;     // Time to apply electronic brake
int brkonoff = 1;       // 1 = braking on, 0 = normal stop
int buttonState = 0;
int lastButtonState = 0;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LEDF, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(HORN, OUTPUT);
  pinMode(LEDP, OUTPUT);
  Serial.begin(9600);   // Bluetooth module communication
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    Stop();  // Stop motors before each new command

    switch (command) {
      case 'L': forward(); break;
      case 'R': back(); break;
      case 'B': left(); break;
      case 'F': right(); break;
      case 'G': forwardleft(); break;
      case 'I': forwardright(); break;
      case 'H': backleft(); break;
      case 'J': backright(); break;
      case 'W': frontledon(); break;
      case 'w': frontledoff(); break;
      case 'U': backledon(); break;
      case 'u': backledoff(); break;
      case 'V': hornon(); break;
      case 'v': hornoff(); break;
      case 'X': parkledon(); break;
      case 'x': parkledoff(); break;
      case '0': Speed = 100; break;
      case '1': Speed = 140; break;
      case '2': Speed = 153; break;
      case '3': Speed = 165; break;
      case '4': Speed = 178; break;
      case '5': Speed = 191; break;
      case '6': Speed = 204; break;
      case '7': Speed = 216; break;
      case '8': Speed = 229; break;
      case '9': Speed = 242; break;
      case 'q': Speed = 255; break;
      case 'S':
        if (brkonoff == 1) {
          brakeOn();
        } else {
          brakeOff();
        }
        break;
    }

    Speedsec = Turnradius;

    // Optional brake mode check for every command
    if (brkonoff == 1 && command != 'S') {
      brakeOn(); // Applies e-brake when command changes (optional)
    }
  }
}

// Movement Functions
void forward() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
}

void back() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
}

void left() {
  analogWrite(in3, Speed);
  analogWrite(in2, Speed);
}

void right() {
  analogWrite(in4, Speed);
  analogWrite(in1, Speed);
}

void forwardleft() {
  analogWrite(in1, Speedsec);
  analogWrite(in3, Speed);
}

void forwardright() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speedsec);
}

void backleft() {
  analogWrite(in2, Speedsec);
  analogWrite(in4, Speed);
}

void backright() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speedsec);
}

void Stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}

// LED & Horn Control
void frontledon()  { digitalWrite(LEDF, HIGH); }
void frontledoff() { digitalWrite(LEDF, LOW); }
void backledon()   { digitalWrite(LEDB, HIGH); }
void backledoff()  { digitalWrite(LEDB, LOW); }
void hornon()      { digitalWrite(HORN, HIGH); }
void hornoff()     { digitalWrite(HORN, LOW); }
void parkledon()   { digitalWrite(LEDP, HIGH); }
void parkledoff()  { digitalWrite(LEDP, LOW); }

// Electronic Brake
void brakeOn() {
  buttonState = command;
  if (buttonState != lastButtonState) {
    if (buttonState == 'S') {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, HIGH);
      delay(brakeTime);
      Stop();
    }
    lastButtonState = buttonState;
  }
}

void brakeOff() {
  Stop(); // Normal stop
}
