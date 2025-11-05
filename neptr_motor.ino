#include <Servo.h>
#include <LiquidCrystal_I2C.h> // Liquid crystal library

LiquidCrystal_I2C lcd(0x27, 16, 2); // Specifies how to reference the LCD and its characteristics

int servoPin = 6; // Pin for the servo motor
Servo armServo; // Create Servo object for the arm

const int buttonPin = A3;      // Button connected to analog pin A3
int mode = 0;                  // Tracks the current mode (0 or 1)
bool buttonState = false;      // Tracks the current button state
bool lastButtonState = false;  // Tracks the previous button state

int echoPin = 7; // attach pin D8 to pin Echo of HC-SR04
int trigPin = 8; // attach pin D7 to pin Trig of HC-SR04

int echoPinl = 2; // attach pin D8 to pin Echo of HC-SR04
int trigPinl = 3; // attach pin D7 to pin Trig of HC-SR04

int echoPinr = 12; // attach pin D8 to pin Echo of HC-SR04
int trigPinr = 13; // attach pin D7 to pin Trig of HC-SR04

long duration; // duration of sound wave travel
long durationl;
long durationr;
int distance; // distance measurement
int distancel;
int distancer;

#define IN1 4 // connect IN1 on the H-Bridge to Arduino pin 4
#define IN2 5 // connect IN2 on the H-Bridge to Arduino pin 5
#define IN3 9 // connect IN3 on the H-Bridge to Arduino pin 9
#define IN4 10 // connect IN4 on the H-Bridge to Arduino pin 10

int StopDistance = 40;

void setup() {

  // put your setup code here, to run once:

  armServo.attach(servoPin);

  // Set initial servo position
  armServo.write(90); // Neutral position (straight arm)

  lcd.init();       // Initializes LCD
  lcd.backlight();  // Turns on the backlight

  pinMode(buttonPin, INPUT);   // Set the button pin as input
  lcd.setCursor(0, 0);
  lcd.print("Time Elapsed:");  // Default mode

     
    pinMode (trigPin, OUTPUT) ; // sonar digital pin mode for trig
    pinMode (echoPin, INPUT); // sonar digital pin mode for echo
    pinMode (trigPinl, OUTPUT) ; // sonar digital pin mode for trig
    pinMode (echoPinl, INPUT); // sonar digital pin mode for echo
    pinMode (trigPinr, OUTPUT) ; // sonar digital pin mode for trig
    pinMode (echoPinr, INPUT); // sonar digital pin mode for echo

    Serial.begin(9600);  
}

void waveArm() {
  // Simple waving motion back and forth
  armServo.write(45); // Move arm to 45 degrees
  delay(200); // Wait
  armServo.write(135); // Move arm to 135 degrees
  delay(200); // Wait
  armServo.write(90); // Return arm to neutral position
  delay(200); // Wait
}

void Forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void TurnRightF() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void TurnLeftF() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void TurnRight() {
  digitalWrite(IN1, HIGH); // Right wheels move backward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  // Left wheels move forward
  digitalWrite(IN4, LOW);
}

void TurnLeft() {
  digitalWrite(IN1, LOW);  // 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // Left wheels move backward
  digitalWrite(IN4, HIGH);
}
void Backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


void measureDistance() {
  for (int i=0;i<2;i++) {
    digitalWrite (trigPin, LOW); //makes trig pin high
    delayMicroseconds (2); //waits for hardware to respond
    digitalWrite (trigPin, HIGH); //makes trig pin high
    delayMicroseconds (10) ; //continues high trig pin state for 10 microseconds
    digitalWrite (trigPin, LOW); //after 10 microseconds trig pin is brought low
    duration = pulseIn (echoPin, HIGH); //reads echo as it receives the pulse and stores duration
    distance = duration * 0.034 / 2; // Converts the time of flight to distance to object
    return distance;
    delayMicroseconds(2);
    }
}

 void measureDistanceL() {
    for (int i=0;i<2;i++) {
    digitalWrite (trigPinl, LOW); //makes trig pin high
    delayMicroseconds (2); //waits for hardware to respond
    digitalWrite (trigPinl, HIGH); //makes trig pin high
    delayMicroseconds (10) ; //continues high trig pin state for 10 microseconds
    digitalWrite (trigPinl, LOW); //after 10 microseconds trig pin is brought low
    durationl = pulseIn (echoPinl, HIGH); //reads echo as it receives the pulse and stores duration
    distancel = durationl * 0.034 / 2; // Converts the time of flight to distance to object
    return distancel;

    delayMicroseconds(2);
    }
  }

 void measureDistanceR() {
    for (int i=0;i<2;i++) {
    digitalWrite (trigPinr, LOW); //makes trig pin high
    delayMicroseconds (2); //waits for hardware to respond
    digitalWrite (trigPinr, HIGH); //makes trig pin high
    delayMicroseconds (10) ; //continues high trig pin state for 10 microseconds
    digitalWrite (trigPinr, LOW); //after 10 microseconds trig pin is brought low
    durationr = pulseIn (echoPinr, HIGH); //reads echo as it receives the pulse and stores duration
    distancer = durationr * 0.034 / 2; // Converts the time of flight to distance to object
    return distancer;

    delayMicroseconds(2);
    }
  }
// IN2 BACKL IN3 IS BACKR IN1 IS RIGHT FORWARD IN4 is LEFT FORWARD

void loop() {
  // put your main code here, to run repeatedly:

    // Read button state
  buttonState = analogRead(buttonPin) > 512; // Detect press based on analog value threshold

  // Detect button press (transition from not pressed to pressed)
  if (buttonState && !lastButtonState) {
    mode = 1 - mode;  // Toggle between mode 0 and mode 1
    lcd.clear();      // Clear LCD screen for new mode
    if (mode == 0) {
      lcd.setCursor(0, 0);
      lcd.print("Time Elapsed:");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Mode 2 Active:"); // Placeholder for second mode
    }
  }
  lastButtonState = buttonState; // Update the last button state

  // Mode-specific actions
  if (mode == 0) {
    Stop();
    // Display elapsed time in hours, minutes, and seconds
    unsigned long elapsedMillis = millis();
    unsigned long totalSeconds = elapsedMillis / 1000;

    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;

    lcd.setCursor(0, 1);
    lcd.print(hours);
    lcd.print("h ");
    lcd.print(minutes);
    lcd.print("m ");
    lcd.print(seconds);
    lcd.print("s    ");
  } else if (mode == 1) {
    // Placeholder for second mode (do something else here)
    lcd.setCursor(0, 1);
    lcd.print("Neptr's Looking!"); // Example display for mode 2
    
    measureDistance();
    measureDistanceL();
    measureDistanceR();

    Serial.print ("Distance: ");
    Serial.print (distance);
    Serial.println(" cm");

    Serial.print ("DistanceL Left: ");
    Serial.print (distancel);
    Serial.println(" cm");

    Serial.print ("Distance Right: ");
    Serial.print (distancer);
    Serial.println(" cm");

  //   if (distance < distancel && distance < distancer) {
  //     if (distance < 15) {
  //       waveArm();
  //       while (distance < 15) 
  //       Backward();
  //       measureDistance();
  //       Serial.print ("Distance: ");
  //       Serial.print (distance);
  //       Serial.println(" cm");
  //     } else if (distance > 20) {
  //       armServo.write(180); // Neutral position (straight arm)
  //       while (distance > 20) {
  //         Forward();
  //         measureDistance();
  //       }
  //     } else if (distance > 15 && distance < 20) {
  //       Stop();
  //       armServo.write(90);
  //     }
  //   } else if (distancel < distance && distancel < distancer) {
  //     if (distancel < 15) {
  //       armServo.write(180); // Neutral position (straight arm)
  //       while (distancel < 15) {
  //         TurnLeft();
  //         measureDistanceL();
  //         Serial.print ("Distance Left: ");
  //         Serial.print (distancel);
  //         Serial.println(" cm");
  //       }
  //       armServo.write(90);
  //     } else if (distancel > 20){
  //       TurnLeftF();
  //     }
  //   } else if (distancer < distance && distancer < distancel) {
  //     if ( distancer < 15) {
  //       armServo.write(180); // Neutral position (straight arm)
  //       while (distancer < 15) {
  //         TurnRight();
  //         measureDistanceR();
  //         Serial.print ("Distance Right: ");
  //         Serial.print (distancer);
  //         Serial.println(" cm");
  //       }
  //       armServo.write(90);
  //     } else if (distancer > 40) {
  //       TurnRightF();
  //     }
  //   }
  // }

// Checking if the front distance is the smallest
if (distance < distancel && distance < distancer) {
    if (distance > 15) {
        waveArm();
        while (distance > 15) {
            Forward();
            measureDistanceL();
            measureDistance();
            measureDistanceR();
            Serial.print("Distance: ");
            Serial.print(distance);
            Serial.println(" cm");
            if (distancel < distance || distancer < distance) {
              break;
            }
        }
        Stop(); // Stop once the condition fails
    } else {
        armServo.write(90); // Neutral position (straight arm)
        Stop();
    }
} 
// Checking if the left distance is the smallest
else if (distancel < distance && distancel < distancer) {
    if (distancel > 15) {
        armServo.write(180); // Arm position for left turn
        while (distancel > 15) {
            TurnLeftF();
            measureDistanceL();
            measureDistance();
            measureDistanceR();
            Serial.print("Distance Left: ");
            Serial.print(distancel);
            Serial.println(" cm");
            if (distance < distancel || distancer < distance) {
              break;
            }
        }
        Stop();
    } else {
        armServo.write(90); // Neutral position (straight arm)
        Stop();
    }
} 
// Checking if the right distance is the smallest
else if (distancer < distance && distancer < distancel) {
    if (distancer > 15) {
        armServo.write(180); // Arm position for left turn
        while (distancer > 15) {
            TurnRightF();
            measureDistanceL();
            measureDistance();
            measureDistanceR();
            Serial.print("Distance Left: ");
            Serial.print(distancer);
            Serial.println(" cm");
            if (distance < distancer || distancel < distancer) {
              break;
            }
        }
        Stop();
    } else {
        armServo.write(90); // Neutral position (straight arm)
        Stop();
    }
  }
  }


  delay(200); // Small delay to debounce button
}

