#ifndef TIME_h
#define TIME_h

    #include "Arduino.h"

    class Time {

        private:

            struct str_Time{
                uint8_t     hour;
                uint8_t     minute;
                uint16_t    minutes;
            };

            str_Time myTime;

        public:

            /* Methodes */
            void initialize(uint8_t myHour, uint8_t myMinute);

            uint8_t getHour(void);

            uint8_t getMinute(void);

            uint16_t getMinutes(void);

            void setTime(uint8_t myHour, uint8_t myMinute);

            void setHour(uint8_t myHour);

            void setMinute(uint8_t myMinute);

            void setMinutes(uint8_t myMinutes);

            void addMinutes(uint8_t myMinutes);


    };

extern Time Timing;

#endif