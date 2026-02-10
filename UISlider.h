#ifndef UISLIDER_H
#define UISLIDER_H

#include "UIComponent.h"

class UISlider : public Component {
public:
  int16_t x, y, width, height;
  int16_t minValue, maxValue;
  int16_t value;
  uint16_t bgColor, knobColor;
  void (*onValueChange)(int16_t);

  UISlider(int16_t xPos, int16_t yPos, int16_t w, int16_t h,
           int16_t minVal, int16_t maxVal, int16_t initVal,
           uint16_t bg = WHITE, uint16_t knob = BLACK,
           void (*valueChangeHandler)(int16_t) = nullptr)
    : x(xPos), y(yPos), width(w), height(h),
      minValue(minVal), maxValue(maxVal), value(initVal),
      bgColor(bg), knobColor(knob), onValueChange(valueChangeHandler) {}

  void render(Adafruit_SSD1306 &display) override {
    if (width <= 0 || height <= 0) {
      return;
    }

    display.drawRect(x, y, width, height, bgColor);

    int16_t renderMin = minValue;
    int16_t renderMax = maxValue;
    if (renderMax < renderMin) {
      int16_t temp = renderMin;
      renderMin = renderMax;
      renderMax = temp;
    }

    int16_t knobWidth = (width <= 4) ? width : 4;
    int16_t knobHeight = (height <= 4) ? height : (height - 4);
    int16_t knobY = (height <= 4) ? y : (y + 2);
    int16_t knobX = x;

    if (renderMax > renderMin && width > knobWidth) {
      int16_t clampedValue = constrain(value, renderMin, renderMax);
      knobX = x + ((clampedValue - renderMin) * (width - knobWidth)) / (renderMax - renderMin);
    } else if (width > knobWidth) {
      knobX = x + (width - knobWidth) / 2;
    }

    display.fillRect(knobX, knobY, knobWidth, knobHeight, knobColor);
  }

  void setValue(int16_t newValue) {
    value = constrain(newValue, minValue, maxValue);
    if (onValueChange) onValueChange(value);
  }

  void increase() { setValue(value + 1); }
  void decrease() { setValue(value - 1); }
};

#endif
/*
int brightness = 50;

void onBrightnessChange(int16_t newValue) {
  brightness = newValue;
  Serial.print("Brightness: ");
  Serial.println(brightness);
}

UISlider* brightnessSlider = new UISlider(10, 40, 100, 10, 0, 100, brightness, WHITE, BLACK, onBrightnessChange);
ui.addComponent(brightnessSlider);

*/
