import processing.serial.*;
Serial port;

String input_str = "";
String receive_str = "";
boolean wait_receive = false;
boolean reset = false;

void setup() {
  size(300, 300);
  frameRate(10);
  String[] ports = Serial.list();

  // for check device
  //for (int i = 0; i < ports.length; i++) {
  //  println(i + ": " + ports[i]);
  //}
  port = new Serial(this, ports[0], 9600);
}

void draw() {
  background(0);
  textSize(14);
  text("Send : " + input_str, 10, 20);
  text("Receive : " + receive_str, 10, 50);
}

void keyPressed() {
  if (!wait_receive) {
    if (keyCode == DELETE) {
      input_str = "";            
    } else if (keyCode == ENTER) {
      sendSerial();
      input_str = input_str + " -> Send";
      receive_str = "";
      reset = true;
    } else if ((key >= 'A' && key <= 'z') || (key >= '0' && key <= '9') || key == ' ') {
      if (reset) {
        reset = false;
        input_str = "";
      }
      input_str = input_str + key;
    }
  }
}

void sendSerial() {
  port.write(input_str + "\0");
  wait_receive = true;
}

void serialEvent(Serial port) {
  if (port.available() > 0) {
    receive_str = port.readStringUntil('\n');
    wait_receive = false;
  }
}
