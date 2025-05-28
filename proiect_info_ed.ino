#include <Servo.h>

#define ENA 2   // Enable Motor A
#define IN1 3   // Motor A pin 1
#define IN2 4   // Motor A pin 2

#define ENB 8   // Enable Motor B
#define IN3 9   // Motor B pin 1
#define IN4 10  // Motor B pin 2

#define SERVO_PIN 6
#define MOISTURE_PIN A0

#define RED_LED 11
#define GREEN_LED 12

int moisture;

Servo myServo;

void moveForward();
void stopMotors();

void setup() {
  Serial.begin(9600);

  // Motor control pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // LED pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Servo init
  myServo.attach(SERVO_PIN);
  myServo.write(90); // Brațul ridicat

}

void loop() {;

  // 1. Mergi 5 secunde

  myServo.write(90);

  moveForward();
  delay(5000);

  // 2. Oprește
  stopMotors();

  // 3. Coboară servo
  myServo.write(149);
  delay(2000);

    // 4. Citește umiditatea
  moisture = analogRead(MOISTURE_PIN);
  Serial.print("Umiditate: ");
  Serial.println(moisture)

  // 5. Dacă e uscat, semnalează cu LED roșu
  if (moisture > 600) {
    Serial.println("Pamant uscat!");
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  } else {
    Serial.println("Pamant OK.");
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }

  delay(10000);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
