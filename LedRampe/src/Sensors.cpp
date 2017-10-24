#ifndef SENSORS_cpp
#define SENSORS_cpp

    #include "Sensors.h"
   
    #define ADC_PS2     _BV(ADPS0)
    #define ADC_PS4     _BV(ADPS1)
    #define ADC_PS8     _BV(ADPS1) | _BV(ADPS0)
    #define ADC_PS16    _BV(ADPS2)
    #define ADC_PS32    _BV(ADPS2) | _BV(ADPS0)
    #define ADC_PS64    _BV(ADPS2) | _BV(ADPS1)
    #define ADC_PS128   _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0)

    Sensors Sensor;


    void Sensors::initialize(void){

        /****** ADC ******/
        // ADMUX – ADC Multiplexer Selection Register
        // Bit  |    7     |    6     |    5     |    4     |   3    |   2    |   1    |    0   |
        //      |  REFS1   |  REFS0   |  ADLAR   |    -     |  MUX3  |  MUX2  |  MUX1  |  MUX0  |
        ADMUX = _BV(REFS0) | TEMP_SENSOR - PIN_A0; //TEMP_SENSOR_HEXA;

        //  ADCSRA – ADC Control and Status Register A
        // Bit  |    7     |    6     |    5     |    4     |    3    |    2    |    1   |    0   |
        //      |   ADEN   |   ADSC   |  ADATE   |   ADIF   |   ADIE  |  ADPS2  |  ADPS1 |  ADPS0 |
        ADCSRA = _BV(ADEN) | ADC_PS16;
        
    }

    // Get the internal temperature of the arduino
    float Sensors::getTemp(void){
    /*
        unsigned int wADC;
        float t;
        ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
        ADCSRA |= _BV(ADEN); // enable the ADC
        delay(20); // wait for voltages to become stable.
        ADCSRA |= _BV(ADSC); // Start the ADC
        while (bit_is_set(ADCSRA,ADSC));
        wADC = ADCW;
        t = (float)(wADC - 324.31 ) / 1.22;
        return (t);
    */
        ADCSRA |= _BV(ADSC);
        while(ADCSRA & _BV(ADSC));

        uint16_t myValueBrute = 0x0000;
        myValueBrute |= ADCL;
        myValueBrute |= ADCH << 8;

        return (float)myValueBrute * (5.0 / 1023.0 * 100.0);
    }

    void Sensors::callBack(void){
        float currentTemp = getTemp();

        Store.addNewValueSeconde(SENSOR_TEMP_LED, currentTemp);

        PilotageLED.newTempValue();
    }

#endif