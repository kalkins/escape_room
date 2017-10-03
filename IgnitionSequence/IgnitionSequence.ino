const int lightPin = 8;

const int input_pins_length = 3;
const int input_pins[] = {7, 4, 3};

const int start_state[] = {1, 0, 1};
const int end_state[] = {0, 1, 0};

const int switch_time = 200;

int last_values[input_pins_length];
bool last_was_start_state = false;
int last_change;

void setup() {
  Serial.begin(9600);
  
  pinMode(lightPin, OUTPUT);
  
  for (int i = 0; i < input_pins_length; i++) {
    pinMode(input_pins[i], INPUT);
  }

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
    digitalWrite(lightPin, HIGH);
    Serial.println("Success");
  }
  
  if (is_start_state) {
    last_was_start_state = true;
  } else if ((millis() - last_change) > switch_time) {
    last_was_start_state = false;
  }
}
