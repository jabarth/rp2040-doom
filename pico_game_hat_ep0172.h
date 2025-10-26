// Hardware definition for the 52pi Pico Game HAT (EP-0172)
#ifndef _PICO_GAME_HAT_EP0172_H
#define _PICO_GAME_HAT_EP0172_H

// --- DISPLAY ---
// We are using a 320x480 ST7796S display
#define ST7796_DRIVER
#define TFT_WIDTH 320
#define TFT_HEIGHT 480

// GPIO pins for the display (based on 52pi wiki)
#define TFT_MOSI 3  // DIN
#define TFT_SCLK 2  // CLK
#define TFT_CS 5
#define TFT_DC 6
#define TFT_RST 7
// #define TFT_BL 13 // Backlight pin is not specified in the wiki for this model.

// --- BUTTONS ---
// Pico Game HAT uses an ADC for the joystick and discrete pins for buttons
#define ADC_JOYSTICK
#define ADC_CHAN_X 0  // ADC0 is GPIO 26 (X-axis)
#define ADC_CHAN_Y 1  // ADC1 is GPIO 27 (Y-axis)

// GPIO pins for the buttons (mapping old names to new pins)
#define PIN_BTN_A 14 // BTN2 on wiki
#define PIN_BTN_SELECT 15 // BTN1 on wiki
// The following buttons are not available on the new EP-0172 pinout and are commented out.
// #define PIN_BTN_B 17
// #define PIN_BTN_X 19
// #define PIN_BTN_Y 21
// #define PIN_BTN_L 16
// #define PIN_BTN_R 20

// --- AUDIO ---
// GPIO Pin for Audio PWM (Beeper on wiki)
#define AUDIO_PIN 13

// --- UART ---
// Define default UART pins for stdio, which is required by the build.
// These can be unused pins if you don't plan to use the UART feature.
#define PICO_DEFAULT_UART 0
#define PICO_DEFAULT_UART_TX_PIN 0
#define PICO_DEFAULT_UART_RX_PIN 1

// --- I2S AUDIO (for compatibility) ---
// Define I2S pins to satisfy the compiler, even though we use PWM audio.
#define PICO_AUDIO_I2S_DATA_PIN 22
#define PICO_AUDIO_I2S_CLOCK_PIN_BASE 23

#endif