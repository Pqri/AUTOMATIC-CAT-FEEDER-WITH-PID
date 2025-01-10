#include <HX711_ADC.h>
#include <Servo.h>

#define TRIG_PIN 10  // Pin trig ultrasonic sensor
#define ECHO_PIN 11  // Pin echo ultrasonic sensor

const int jarakMax = 20;

const int HX711_dout = 6;
const int HX711_sck = 5;
#define SERVO_PIN 9

Servo myServo;

HX711_ADC LoadCell(HX711_dout, HX711_sck);

// PID constants
float Kp = 2.0; // Proportional gain
float Ki = 0.5; // Integral gain
float Kd = 1.0; // Derivative gain

// PID variables
float setPoint = 50.0; // Target weight in grams
float currentWeight = 0.0;
float error = 0.0;
float lastError = 0.0;
float integral = 0.0;
float derivative = 0.0;
float output = 0.0;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize Load Cell
  LoadCell.begin();
  LoadCell.start(2000);  // Delay for HX711 startup
  LoadCell.setCalFactor(427);  // Calibration factor for the load cell

  // Initialize Servo
  myServo.attach(SERVO_PIN);
  myServo.write(0); // Start with servo at 180 degrees (opened)

  // Print labels for Serial Plotter
  Serial.println("SetPoint\tOutputLoadCell");
}

void loop() {
  // Update and get the weight from LoadCell
  LoadCell.update();
  currentWeight = LoadCell.getData();  // Read current weight from load cell

  // Prevent negative weight values
  if (currentWeight < 0) { 
    currentWeight = 0; 
  }

  if (cekJarak() > jarakMax) {
    myServo.write(180);
  } else if (cekJarak() < jarakMax) {
    // Check weight conditions
    if (currentWeight > setPoint) {
      // If weight exceeds setPoint, servo stays at 180 degrees (closed)
      myServo.write(180);
    } else if (currentWeight <= setPoint) {
      // If weight is below setPoint, calculate servo angle
      error = setPoint - currentWeight;
      integral += error;
      integral = constrain(integral, -50, 50); // Prevent integral wind-up
      derivative = error - lastError;
      output = (Kp * error) + (Ki * integral) + (Kd * derivative);

      // Constrain PID output to be in the range -100 to 100
      output = constrain(output, -100, 100);

      // Map error to servo angle (180 to 0 degrees)
      int servoAngle = map(abs(error), 0, setPoint, 180, 0);
      servoAngle = constrain(servoAngle, 0, 180);  // Ensure angle is within 0 to 180 degrees

      myServo.write(servoAngle);
    }
  }

  // Send data to Serial Plotter
  Serial.print(setPoint);
  Serial.print("\t");
  Serial.println(currentWeight);

  // Save last error for next iteration
  lastError = error;

  // Delay to control loop frequency
  delay(500); // Adjust loop delay as needed
}

int cekJarak() {
  long duration;
  int distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.0343 / 2; // Konversi ke cm

  return distance;
}
