#include <Bounce.h>

Bounce bUp = Bounce(1, 20);
Bounce bDown = Bounce(2, 20);
Bounce bLeft = Bounce(3, 20);
Bounce bRight = Bounce(0, 20);

Bounce bA = Bounce(21, 20);
Bounce bB = Bounce(20, 20);
Bounce bStart = Bounce(19, 20);
Bounce bSelect = Bounce(18, 20);

int hidMode = 0;

boolean mLeft = false;
boolean mRight = false;

void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
}

void loop() {
  updateButtons();
  processFallingEdges();
  processRisingEdges();
}

void updateButtons() {
  bUp.update();
  bDown.update();
  bLeft.update();
  bRight.update();
  bA.update();
  bB.update();
  bStart.update();
  bSelect.update();
}

void processFallingEdges() {
  if ((bSelect.read() == LOW) && (bUp.read() == LOW)) {
    hidMode = ((hidMode) ? 0 : 1);
    Keyboard.set_key1(0);
    Keyboard.set_key2(0);
    Keyboard.set_key3(0);
    Keyboard.set_key4(0);
    Keyboard.set_key5(0);
    Keyboard.set_key6(0);
    Keyboard.send_now();
    delay(500);
  }
  
  if (hidMode == 0) {
    if (bUp.fallingEdge()) {
      Keyboard.set_key1(KEY_U);
      Keyboard.send_now();
    }
    
    if (bDown.fallingEdge()) {
      Keyboard.set_key1(KEY_D);
      Keyboard.send_now();
    }
    
    if (bLeft.fallingEdge()) {
      Keyboard.set_key2(KEY_L);
      Keyboard.send_now();
    }
    
    if (bRight.fallingEdge()) {
      Keyboard.set_key2(KEY_R);
      Keyboard.send_now();
    }
    
    if (bA.fallingEdge()) {
      Keyboard.set_key3(KEY_A);
      Keyboard.send_now();
    }
  
    if (bB.fallingEdge()) {
      Keyboard.set_key4(KEY_B);
      Keyboard.send_now();
    }
  
    if (bStart.fallingEdge()) {
      Keyboard.set_key5(KEY_S);
      Keyboard.send_now();
    }
  
    if (bSelect.fallingEdge()) {
      Keyboard.set_key6(KEY_E);
      Keyboard.send_now();
    }
  }

  if (hidMode == 1) {
    int moveSpeed = max(((bUp.read() == LOW) ? bUp.duration() : 0), ((bDown.read() == LOW) ? bDown.duration() : 0));
    moveSpeed = max(moveSpeed, max(((bLeft.read() == LOW) ? bLeft.duration() : 0), ((bRight.read() == LOW) ? bRight.duration() : 0)));
    moveSpeed = min(1 + (moveSpeed / 250), 10);
    
    if (bUp.read() == LOW) {
      Mouse.move(0, -moveSpeed);
    }
    
    if (bDown.read() == LOW) {
      Mouse.move(0, moveSpeed);
    }
    
    if (bLeft.read() == LOW) {
      Mouse.move(-moveSpeed, 0);
    }
    
    if (bRight.read() == LOW) {
      Mouse.move(moveSpeed, 0);
    }
    
    if (bA.fallingEdge()) {
      mLeft = true;
      Mouse.set_buttons(mLeft, false, mRight);
    }
    
    if (bB.fallingEdge()) {
      mRight = true;
      Mouse.set_buttons(mLeft, false, mRight);
    }
    
    delay(10);
  }
}

void processRisingEdges() {
  if (hidMode == 0) {
    if ((bUp.risingEdge()) || (bDown.risingEdge())) {
      Keyboard.set_key1(0);
      Keyboard.send_now();
    }
  
    if ((bLeft.risingEdge()) || (bRight.risingEdge())) {
      Keyboard.set_key2(0);
      Keyboard.send_now();
    }
  
    if (bA.risingEdge()) {
      Keyboard.set_key3(0);
      Keyboard.send_now();
    }
    
    if (bB.risingEdge()) {
      Keyboard.set_key4(0);
      Keyboard.send_now();
    }
    
    if (bStart.risingEdge()) {
      Keyboard.set_key5(0);
      Keyboard.send_now();
    }
  
    if (bSelect.risingEdge()) {
      Keyboard.set_key6(0);
      Keyboard.send_now();
    }
  }
  
  if (hidMode == 1) {
    if (bA.risingEdge()) {
      mLeft = false;
      Mouse.set_buttons(mLeft, false, mRight);
    }
    
    if (bB.risingEdge()) {
      mRight = false;
      Mouse.set_buttons(mLeft, false, mRight);
    }
  }
}
