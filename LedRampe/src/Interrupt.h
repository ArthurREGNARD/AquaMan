#ifndef INTERRUPT_h
#define INTERRUPT_h

    #include "Arduino.h"
    //#include <MsTimer2.h>
    //#include "TimerOne.h"
    #include "Pilotage.h"
    #include "Sensors.h"
    #include "StoreData.h"
    #include "Pin.h"
    #include "Time.h"
    #include "Outils.h"

    #define MIN_COMPARE_REGISTER    0
    #define CURRENT_VALUE           0
    #define MAX_COMPARE_REGISTER    255

    class Interrupt {

        private:

            static void callBack(void);

            struct str_Encodeur{
                bool event;
                int8_t action;
                uint32_t time;
            };

            str_Encodeur myEncodeur;

            /* Methodes */

        public:

            /* Methodes */
            void initialize(void);

            void start(void);

            void stop(void);

            void setPWM(uint8_t pin, uint8_t PWM);

            bool getEncodeurEvent(void);

            int8_t getEncodeurAction(void);

            uint32_t getEncodeurTime(void);

            void setEncodeurAction(int8_t myAction);

            void setEncodeurEvent(bool myEvent);

            void setEncodeurTime(uint32_t myTime);
    };

    extern Interrupt Interruption;

#endif