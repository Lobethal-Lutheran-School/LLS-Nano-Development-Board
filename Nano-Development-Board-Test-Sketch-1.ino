//
// Copyright 2021
// Dr Erich S. Heinzle
//
// GPL v2.0
//
// used with Lobethal Lutheran School Arduino Nano development board
// use Arduino IDE and set board to Arduino Nano, and select correct USB port

void setup() {
  // setup code goes here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void read_buttons_and_pot(int *sweepSpeed, int *sweepDirection, int *flash, int *cylon, int *sweep) {
  *sweepSpeed = analogRead(A7);
  int A0_pressed = analogRead(A0) < 500;
  if (*sweep && A0_pressed) {
    *sweepDirection = !*sweepDirection;
  }
  if (!*sweep && A0_pressed) {
    *sweep = A0_pressed;
  }
  *cylon = *cylon - (analogRead(A1) < 500);
  *flash = *flash - (analogRead(A2) < 500);
}

int sweep_leds(int *sweepSpeed, int *sweepDirection, int *flash, int *cylon, int *sweep) {
  while (!*flash && !*cylon && *sweep) {
    if (*sweepDirection) {
      for (int i = 2; i < 8; i++) {
        digitalWrite(i, HIGH);
        delay(*sweepSpeed);
        digitalWrite(i, LOW);
        delay(*sweepSpeed);
        read_buttons_and_pot(sweepSpeed, sweepDirection, flash, cylon, sweep);
        if (*flash || *cylon || !*sweep) {
          delay(80);
          *sweep = 0;
          return 0;
        }
      }
    } else {
      for (int i = 7; i > 1; i--) {
        digitalWrite(i, HIGH);
        delay(*sweepSpeed);
        digitalWrite(i, LOW);
        delay(*sweepSpeed);
        read_buttons_and_pot(sweepSpeed, sweepDirection, flash, cylon, sweep);
        if (*flash || *cylon || !*sweep) {
          delay(80);
          *sweep = 0;
          return 0;
        }
      }
    }
  }
  return 0;
}

void led_switch(int on) {
  if (on) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
}

int flash_leds(int *sweepSpeed, int *sweepDirection, int *flash, int *cylon, int *sweep) {
  while (*flash && !*cylon && !*sweep) {
    read_buttons_and_pot(sweepSpeed, sweepDirection, flash, cylon, sweep);
    if (!*flash || *cylon || *sweep) {
      delay(80);
      *flash = 0;
      return 0;
    }
    led_switch(1);
    delay(*sweepSpeed);
    read_buttons_and_pot(sweepSpeed, sweepDirection, flash, cylon, sweep);
    if (!*flash || *cylon || *sweep) {
      delay(80);
      *flash = 0;
      return 0;
    }
    led_switch(0);
    delay(*sweepSpeed);
  }
  return 0;
}

int cylon_sweep(int *sweepSpeed, int *sweepDirection, int *flash, int *cylon, int *sweep) {
  while (!*flash && *cylon && !*sweep) {
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(*sweepSpeed);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(*sweepSpeed);
    read_buttons_and_pot(sweepSpeed, sweepDirection, flash, cylon, sweep);
    if (!*cylon || *flash || *sweep) {
      *cylon = 0;
      return 0;
    }
    digitalWrite(3, HIGH);
    digitalWrite(6, HIGH);
    delay(*sweepSpeed);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
    delay(*sweepSpeed);
    read_buttons_and_pot(sweepSpeed, sweepDirection, flash, cylon, sweep);
    if (!*cylon || *flash || *sweep) {
      *cylon = 0;
      return 0;
    }
    digitalWrite(2, HIGH);
    digitalWrite(7, HIGH);
    delay(*sweepSpeed);
    digitalWrite(2, LOW);
    digitalWrite(7, LOW);
    delay(*sweepSpeed);
    read_buttons_and_pot(sweepSpeed, sweepDirection, flash, cylon, sweep);
    if (!*cylon || *flash || *sweep) {
      *cylon = 0;
      return 0;
    }
    digitalWrite(3, HIGH);
    digitalWrite(6, HIGH);
    delay(*sweepSpeed);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
    delay(*sweepSpeed);
    read_buttons_and_pot(sweepSpeed, sweepDirection, flash, cylon, sweep);
    if (!*cylon || *flash || *sweep) {
      delay(80);
      *cylon = 0;
      return 0;
    }
  }
  return 0;
}

void loop() {
  // main code here, runs repeatedly:
  int sweepSpeed = 0;
  int sweepDirection = 0;
  int flash = 0;
  int cylon = 0;
  int sweep = 1;
  read_buttons_and_pot(&sweepSpeed, &sweepDirection, &flash, &cylon, &sweep);
  while (1) {
    while (flash) {
      flash_leds(&sweepSpeed, &sweepDirection, &flash, &cylon, &sweep);
    }
    while (cylon) {
      cylon_sweep(&sweepSpeed, &sweepDirection, &flash, &cylon, &sweep);
    }
    while (sweep) {
      sweep_leds(&sweepSpeed, &sweepDirection, &flash, &cylon, &sweep);
    }
    read_buttons_and_pot(&sweepSpeed, &sweepDirection, &flash, &cylon, &sweep);
  }
}
