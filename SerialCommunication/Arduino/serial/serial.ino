const int kSerialBufferSize = 32;
char serial_buffer[kSerialBufferSize];

#define LED_PIN 13
void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (receiveSerial()) {
    sendSerial();
  }
}

bool receiveSerial() {
  int count = 0;
  if (Serial.available() > 0) {
    digitalWrite(LED_PIN, HIGH);
    while (true) {
      if (Serial.available() > 0) {
        char c = Serial.read();
        if (c == '\0') {
          break;
        } else if (count < kSerialBufferSize-1) {
          serial_buffer[count] = c;
          count++;
        }
      }
    }    
  }
  serial_buffer[count] = '\0';
  return count > 0;
}

void sendSerial() {
  Serial.print("Aruduino received = ");  
  Serial.println(serial_buffer);
  digitalWrite(LED_PIN, LOW);
}

