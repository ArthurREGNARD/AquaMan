#ifndef OUTILS_h
#define OUTILS_h

    #include "Arduino.h"
	#include "stdint.h"
	#include "Pin.h"

	#define NB_MINUTES_DAY	1440
	#define NB_MINUTES_2H	120
	#define NB_MINUTES_12H	720
	#define	NB_MINUTES_MIN	0

	#define NB_SECOUNDS_1MIN	60

    //bool EVENT_ON_ENCODEUR = false;

    enum enu_States{
        TRUE, 
        FALSE
    };

    enum enu_Color{
        WHITE, 
        RED, 
        GREEN, 
        BLUE, 
        DEEP_BLUE
    };

    enum enu_Mode{
        DAY,
        TRANS_D_N,
        NIGHT,
        TRANS_N_D,
        USER, 
        TEST
    };

    enum enu_Signe{
        POSITIVE, 
        NEGATIVE
    };

    enum enu_Timing{
        BEGIN,
        DURATION, 
        END
    };

    struct str_uint16 {
        uint8_t MSB; 
        uint8_t LSB;
    };

    enum listSensors{
        SENSOR_TEMP_LED,
        SENSOR_CURRENT
    };

	uint16_t formatMinutesForDay(uint16_t myMinutes);

	void debugBlink(int nbBlink);

    uint16_t uint8_TO_uint16(uint8_t MSB, uint8_t LSB);

    str_uint16 uint16_TO_uint8(uint16_t myUint16);

#endif