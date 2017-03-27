const int lightPin = 8;

const int input_pins_length = 3;
int input_pins[] = {3, 4, 7};
int last_values[input_pins_length];

int sequence[3];
int sequence_index = 0;

const int correct_sequence_length = 6;
int correct_sequence[] = {0, 1, 2, 2, 1, 0};

void setup() {
  Serial.begin(9600);
  
  pinMode(lightPin, OUTPUT);
  
  for (int i = 0; i < input_pins_length; i++) {
    pinMode(input_pins[i], INPUT);
    last_values[i] = digitalRead(input_pins[i]);
  }
}

void loop() {
  for (int i = 0; i < input_pins_length; i++) {
    delay(150);
    int pin = input_pins[i];
    int val = digitalRead(pin);
    if (val != last_values[i]) {
      Serial.print("Read ");Serial.print(val);Serial.print(" on pin ");Serial.print(pin);Serial.println();
      last_values[i] = val;
      if (i == correct_sequence[sequence_index]) {
        Serial.print("Pin "); Serial.print(i); Serial.print(" is correct\n");
        sequence[sequence_index] = i;
        sequence_index++;
        if (sequence_index == correct_sequence_length) {
          digitalWrite(lightPin, HIGH);
          Serial.println("Success");
        }
      } else {
        sequence_index = 0;
        Serial.write("Abort");
      }
    }
  }
}
