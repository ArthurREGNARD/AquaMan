#ifndef TIME_cpp
#define TIME_cpp

    #include "Time.h"

    Time Timing;

    void Time::initialize(uint8_t myHour, uint8_t myMinute){
    	setTime(myHour, myMinute);
    }

    uint8_t Time::getHour(void){
    	return myTime.hour;
    }

    uint8_t Time::getMinute(void){
    	return myTime.minute;
    }

    uint16_t Time::getMinutes(void){
    	return myTime.minutes;
    }

    void Time::setTime(uint8_t myHour, uint8_t myMinute){
    	myTime.hour = myHour;
    	myTime.minute = myMinute;
    	myTime.minutes = ((myTime.hour * 60) + myTime.minute) % 1440;
    }

    void Time::setHour(uint8_t myHour){
        myTime.hour = myHour;
        myTime.minutes = ((myTime.hour * 60) + myTime.minute) % 1440;
    }

    void Time::setMinute(uint8_t myMinute){
        myTime.minute = myMinute;
        myTime.minutes = ((myTime.hour * 60) + myTime.minute) % 1440;
    }

    void Time::setMinutes(uint8_t myMinutes){
        uint8_t tempMinute = myMinutes % 60;
        uint8_t tempHour = myMinutes /60;

        myTime.hour = tempHour % 24;
        myTime.minute = tempMinute;
        myTime.minutes = (myTime.minutes + myMinutes) % 1440;
    }

    void Time::addMinutes(uint8_t myMinutes){
        uint8_t tempMinute = (myTime.minute + myMinutes) % 60;
        uint8_t tempHour = myTime.hour + ((myTime.minute + myMinutes) /60);

        myTime.hour = tempHour % 24;
        myTime.minute = tempMinute;
        myTime.minutes = (myTime.minutes + myMinutes) % 1440;
    }

#endif