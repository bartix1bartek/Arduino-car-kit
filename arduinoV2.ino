#include <DIYables_IRcontroller.h>  // DIYables_IRcontroller library
#define IR_RECEIVER_PIN 11          // The Arduino pin connected to IR controller
#include <Servo.h>

DIYables_IRcontroller_21 irController(IR_RECEIVER_PIN, 200);  // debounce time is 200ms
Servo servo;
const int LIGHT_SENSOR_PIN = A0;  // Arduino pin connected to light sensor's  pin
const int LED_PIN = 10;            // Arduino pin connected to LED's pin
const int ANALOG_THRESHOLD = 20;
int analogValue;
int angle = 10;
int time = 0;
int bp = 0;
int fn = -1;
int fnb= -1;
#define ENA_PIN 7  // The Arduino pin connected to the ENA pin L298N
#define IN1_PIN 6  // The Arduino pin connected to the IN1 pin L298N
#define IN2_PIN 5  // The Arduino pin connected to the IN2 pin L298N
#define IN3_PIN 4  // The Arduino pin connected to the IN3 pin L298N
#define IN4_PIN 3  // The Arduino pin connected to the IN4 pin L298N
#define ENB_PIN 2  // The Arduino pin connected to the ENB pin L298N

void setup() {
  Serial.begin(9600);
  irController.begin();
  servo.attach(8);  //8
  servo.write(angle);
  servo.write(90);
  pinMode(LED_PIN, OUTPUT);  // set arduino pin to output mode
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  digitalWrite(ENA_PIN, HIGH);  // set full speed
  digitalWrite(ENB_PIN, HIGH);  // set full speed
}
void loop() {
  if (fn == 1) {
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
  } else {
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, LOW);
  }


  
  analogValue = analogRead(LIGHT_SENSOR_PIN);  // read the input on analog pin

  if (analogValue < ANALOG_THRESHOLD)
    digitalWrite(LED_PIN, HIGH);  // turn on LED
  else
    digitalWrite(LED_PIN, LOW);  // turn off LED
  delay(20);
  time = time + 1;
  Serial.println(bp);
  if (bp == 0) {
    time = 0;
    servo.write(90);
  }

  Key21 key = irController.getKey();
  if (key != Key21::NONE) {
    switch (key) {

      case Key21::KEY_0:
        Serial.println("0");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_1:
        Serial.println("1");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_2:
        Serial.println("2");
        fn = (fn * -1);

        break;

      case Key21::KEY_3:
        Serial.println("3");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_4:
        //time = 0;
        bp = 45;
        delay(100);
        Serial.println("4");
        servo.write(1);
        break;

      case Key21::KEY_5:
        Serial.println("5");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_6:
        //time = 0;
        bp = 45;
        delay(100);
        Serial.println("6");
        servo.write(180);
        break;

      case Key21::KEY_7:
        Serial.println("7");
        // TODO: YOUR CONTROL
        break;

      case Key21::KEY_8:
        Serial.println("8");
        fnb = (fnb * -1);
        break;

      case Key21::KEY_9:
        Serial.println("9");
        // TODO: YOUR CONTROL
        break;

      default:
        Serial.println("WARNING: undefined key:");
        break;
    }
  } else {
    bp = bp - 0.5;
  }
}