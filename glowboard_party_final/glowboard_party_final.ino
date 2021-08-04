#include <DDBooster.h>
#include <EEPROM.h>

//adjust the following values to fit your setup:

//the length of your ws2812b strips in pixels:
#define LED_COUNT 50

//the arduino pin your mode switch is connected to:
#define switch_pin 7

//the arduino pin that the hall effect sensors data pin is connected to:
#define hall_pin 3

//the arduino pin your button is connected to:
#define button_pin 2 

//wheel diameter in cm:
#define wheel_diameter 7

//number of pixels per meter:
#define pixel_density 60 

//how often the hall effect sensor updates per full rotation:
#define hall_resolution 8

//how many pixels long you want the running strip to be:
#define effect_length 10 

//adjust the above values to fit your setup

const float effect_increment = (pixel_density * wheel_diameter * 0.0314 / hall_resolution);

int pixel0, pixel1, timer, progress, mode, lasttime, timepassed;
const int length = effect_length - 1;
const int last = LED_COUNT - 1;
const int slast = last - length;
const int limit = LED_COUNT + LED_COUNT;
const int ADDRESS = 0;
volatile float position = 22;
float color, color0;
float increment = 360 / limit;
bool switchmode, direction;

DDBooster booster;

void setup() {
  booster.init(LED_COUNT);
  pinMode(switch_pin, INPUT);
  pinMode(button_pin, INPUT);
  switchmode = digitalRead(switch_pin);
  lasttime = millis();
  attachInterrupt(digitalPinToInterrupt(hall_pin), forward, CHANGE);
  noInterrupts();
  runAnimation();
}

void loop() {

  if (digitalRead(button_pin) == HIGH) {

    timer = 0;
    while (digitalRead(button_pin) == HIGH) {
      delay(100);
      timer++;
      if (timer > 14) {
        longPress();
        while (digitalRead(button_pin) == HIGH) {
        }
        delay(100);
        break;
      }
    }

    if (timer < 15) {
      shortPress();
    }

  }

  if (digitalRead(switch_pin) != switchmode) {

    if (mode != 0) {
      longPress();
      shortPress();
    }
    switchmode = digitalRead(switch_pin);

  }

  if (mode < 0) {

    checkTime();

  }

}

void longPress() {

  if (mode != 0) {
    if (mode > 0) {
      EEPROM.put(ADDRESS, mode);
      noInterrupts();
    }
    mode = 0;
  }
  else {
    if (digitalRead(switch_pin) == HIGH) {
      EEPROM.get(ADDRESS, mode);
      interrupts();
    }
    else {
      mode = -1;
    }
  }
  runAnimation();

}

void shortPress() {

  if (mode > 0) {
    mode++;
    if (mode > 6) {
      mode = 1;
    }
  }
  else if (mode < 0) {
    mode--;
    if (mode < -3) {
      mode = -1;
    }
  }
  else {
    if (digitalRead(switch_pin) == HIGH) {
      EEPROM.get(ADDRESS, mode);
      interrupts();
    }
    else {
      mode = -1;
    }
  }
  runAnimation();

}

void forward() {

  position -= effect_increment;
  if (position < 0) {
    position = limit;
  }
  runAnimation();

}

void checkTime() {

  timepassed = millis() - lasttime;

  switch (mode) {

    case -1:

      if (timepassed > 20) {
        runAnimation();
        lasttime = millis();
      }

      break;

    case -2:

      if (timepassed > 20) {
        runAnimation();
        lasttime = millis();
      }

      break;

    case -3:

      if (timepassed > 30) {
        runAnimation();
        lasttime = millis();
      }

      break;

  }

}

void runAnimation() {

  booster.clearAll();

  switch (mode) {

    case -3: //bouncing strip

      color++;
      if (color > 359) {
        color = 0;
      }

      booster.setHSV(color, 255, 255);

      if (direction == true) {
        pixel0++;
        pixel1 = pixel0 + length;
        if (pixel1 > last - 1) {
          direction = false;
        }
      }
      else {
        pixel0--;
        pixel1 = pixel0 + length;
        if (pixel0 < 1) {
          direction = true;
        }
      }

      booster.setRange(pixel0, pixel1);

      break;

    case -2: //unicolor rainbow

      color++;
      if (color > 359) {
        color = 0;
      }
      booster.setHSV(color, 255, 255);
      booster.setAll();

      break;

    case -1: //running rainbow

      color++;
      if (color > 359) {
        color = 0;
      }
      booster.setRainbow(color, 255, 255, 0, 24, 2);

      color0 = color + 50;
      if (color0 > 360) {
        color0 -= 360;
      }
      booster.setRainbow(color0, 255, 255, 25, 49, 2);

      break;

    case 0: //headlights (off)

      booster.setRGB(255, 0, 0);
      booster.setRange(0, length);
      booster.setRGB(255, 255, 255);
      booster.setRange(slast, last);

      break;

    case 1: //highlight red

      drawStrip(255, 0, 0);

      break;

    case 2: //highlight green

      drawStrip(0, 255, 0);

      break;

    case 3: //highlight blue

      drawStrip(0, 0, 255);

      break;

    case 4: //rainbow

      color = position;
      color /= limit;
      color *= 360;
      color = 360 - color;

      booster.setRainbow(color, 255, 255, 0, 24, increment);

      color += ((LED_COUNT / 2) * increment);
      if (color > 359) {
        color -= 360;
      }

      booster.setRainbow(color, 255, 255, 25, last, increment);

      break;

    case 5: //color changing highlights

      color++;
      if (color > 359) {
        color = 0;
      }

      booster.setHSV(color, 255, 255);

      drawStrip(0, 0, 0);

      break;

    case 6: //highlights blue & red

      pixel0 = abs(position);
      pixel1 = pixel0 + length;
      if (pixel1 > limit) {
        pixel1 -= limit;
      }

      booster.setRGB(255, 0, 0);
      if (pixel0 < pixel1) {
        if (pixel1 < LED_COUNT) {
          booster.setRange(pixel0, pixel1);
        }
        else {
          booster.setRange(pixel0, last);
        }
      }
      else {
        booster.setRange(0, pixel1);
      }

      pixel0 += LED_COUNT;
      if (pixel0 > limit) {
        pixel0 -= limit;
      }
      pixel1 = pixel0 + length;
      if (pixel1 > limit) {
        pixel1 -= limit;
      }

      booster.setRGB(0, 0, 255);
      if (pixel0 < pixel1) {
        if (pixel1 < LED_COUNT) {
          booster.setRange(pixel0, pixel1);
        }
        else {
          booster.setRange(pixel0, last);
        }
      }
      else {
        booster.setRange(0, pixel1);
      }

      break;

    default:

      mode = 0;
      runAnimation();

      break;

  }

  booster.show();

}

void drawStrip(int redmode, int bluemode, int greenmode) {
  if ((redmode + bluemode + greenmode) > 0) {
    booster.setRGB(redmode, greenmode, bluemode);
  }

  pixel0 = abs(position);
  if (pixel0 > last) {
    pixel0 -= LED_COUNT;
  }
  pixel1 = pixel0 + length;
  if (pixel1 > last) {
    pixel1 -= LED_COUNT;
  }

  if (pixel0 < pixel1) {
    booster.setRange(pixel0, pixel1);
  }
  else {
    booster.setRange(pixel0, last);
    booster.setRange(0, pixel1);
  }
}