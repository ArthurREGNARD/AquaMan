#ifndef PIN_h
#define PIN_h

    #include "Arduino.h"

    #define PIN_RX0     0
    #define PIN_TX1     1
    #define PIN_D2      2
    #define PIN_D3      3
    #define PIN_D4      4
    #define PIN_D5      5
    #define PIN_D6      6
    #define PIN_D7      7
    #define PIN_D8      8
    #define PIN_D9      9
    #define PIN_D10     10
    #define PIN_D11     11
    #define PIN_D12     12
    #define PIN_D13     13
    #define PIN_A0      14
    #define PIN_A1      15
    #define PIN_A2      16
    #define PIN_A3      17
    #define PIN_A4      18
    #define PIN_A5      19
    #define PIN_A6      20
    #define PIN_A7      21
    #define PIN_RST     22

    #define OC0A_PIN    PIN_D6
    #define OC0B_PIN    PIN_D5
    #define OC1A_PIN    PIN_D9
    #define OC1B_PIN    PIN_D10
    #define OC2A_PIN    PIN_D11
    #define OC2B_PIN    PIN_D3


    #define LED_DEBUG       PIN_D13
    #define LED_WHITE       OC1A_PIN
    #define LED_RED         OC1B_PIN
    #define LED_GREEN       OC0A_PIN
    #define LED_BLUE        OC0B_PIN
    #define LED_DEEP_BLUE   OC2B_PIN

    #define TEMP_SENSOR         PIN_A7
    #define TEMP_SENSOR_HEXA    0x07

    /*** I2C ***/
    #define I2C_SDA     PIN_A4
    #define I2C_SDL     PIN_A5

    /*** SPI ***/
    #define SPI_MOSI    PIN_D11
    #define SPI_MISO    PIN_D12
    #define SPI_SCK     PIN_D13

    /*** ENCODEUR ***/
    #define ENCODEUR_A  PIN_A0
    #define ENCODEUR_B  PIN_A1
    #define ENCODEUR_P  PIN_A2

    /*** LCD ***/
    #define LCD_CS      PIN_D7
    #define LCD_DC      PIN_D8
    #define LCD_RESET   PIN_D4
    #define LCD_MOSI    SPI_MOSI
    #define LCD_SCLK    SPI_SCK


#endif