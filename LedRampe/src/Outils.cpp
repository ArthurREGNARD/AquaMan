#ifndef OUTILS_cpp
#define OUTILS_cpp

	#include "Outils.h"

	uint16_t formatMinutesForDay(uint16_t myMinutes){
		if(myMinutes <= 0)
			myMinutes = 0;
		return myMinutes % NB_MINUTES_DAY;
	}

	 void debugBlink(int nbBlink){
        int i;
        for(i=0; i < nbBlink; i++){
            digitalWrite(LED_DEBUG, digitalRead(LED_DEBUG)^1);
            delay(5000);
            digitalWrite(LED_DEBUG, digitalRead(LED_DEBUG)^1);
            delay(5000);
        }
        //delay(50000);
    }

    uint16_t uint8_TO_uint16(uint8_t MSB, uint8_t LSB){
        return ( (uint16_t)MSB << 8 | (uint16_t)LSB );
    }

    str_uint16 uint16_TO_uint8(uint16_t myUint16){
        str_uint16 myStruct;
        myStruct.MSB = (uint8_t)((myUint16 & 0xFF00) >> 8);
        myStruct.LSB = (uint8_t)( myUint16 & 0x00FF);

        return myStruct;
    }

#endif