#include <Servo.h>

Servo servo;

int servo_locked_pos = 80;
int servo_unlocked_pos = 170;

const int servoPin = 5;

const int input_pins_length = 3;
const int input_pins[] = {2, 3, 4};

const int start_state[] = {1, 0, 1};
const int end_state[] = {0, 1, 0};

const int switch_time = 200;

int last_values[input_pins_length];
bool last_was_start_state = false;
unsigned long last_change;

void setup() {
  Serial.begin(9600);

  servo.attach(servoPin);
  servo.write(servo_unlocked_pos);
  
  for (int i = 0; i < input_pins_length; i++) {
    pinMode(input_pins[i], INPUT);
  }

  bool should_lock = false;
  while (!should_lock) {
    delay(50);
    for (int i = 0; i < input_pins_length; i++) {
      int pin = input_pins[i];
      int val = digitalRead(pin);
      if (val == 1) {
        fshould_lock = true;
      } else {
        should_lock = false;
        break;
      }
    }
  }

  servo.write(servo_locked_pos);

  last_change = millis();
}


void loop() {
  delay(50);

  bool is_start_state = true;
  bool is_end_state = true;
  
  for (int i = 0; i < input_pins_length; i++) {
    int pin = input_pins[i];
    int val = digitalRead(pin);
    
    if (val != last_values[i]) {
      last_change = millis();
    }
    if (val != start_state[i]) {
      is_start_state = false;
    }
    if (val != end_state[i]) {
      is_end_state = false;
    }
  }

  if (last_was_start_state && is_end_state && (millis() - last_change) < switch_time) {
    servo.write(servo_unlocked_pos);
    Serial.println("Success");
  }
  
  if (is_start_state) {
    last_was_start_state = true;
  } else if ((millis() - last_change) > switch_time) {
    last_was_start_state = false;
  }
}
