// library: lib_deps = olikraus/U8g2@^2.36.18

// gnd - gnd
// 3V3 - vcc
// D1 - sck
// D2 - sda


#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(
    U8G2_R0,
    U8X8_PIN_NONE,
    D1,  // SCL
    D2   // SDA
);

void setup() {
    display.begin();
    display.clearBuffer();
    display.setFont(u8g2_font_ncenB08_tr);
    display.drawStr(10, 20, "hello world!");
    display.drawStr(10, 40, "skuska skuska");
    display.sendBuffer();
}

void loop() {
}