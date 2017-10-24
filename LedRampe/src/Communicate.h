#ifndef COMMUNICATE_h
#define COMMUNICATE_h

    #include "Arduino.h"
    #include "Outils.h"
    #include "Wire.h"
    #include "Time.h"
    #include "Pilotage.h"

    #define NB_BITS_BUFFER  12

    #define SLAVE_ADDRESS   0x08


    class Communicate {

        private:

            enum enu_ListHeader{
                ERROR,                              // 0

                TIME_SET_HOUR, 
                TIME_SET_MINUTE, 
                TIME_SET_MINUTES, 
                TIME_ADD_MINUTES,
                
                PILOTAGE_SET_DAY_WHITE,             // 5 
                PILOTAGE_SET_DAY_RED, 
                PILOTAGE_SET_DAY_GREEN, 
                PILOTAGE_SET_DAY_BLUE, 
                PILOTAGE_SET_DAY_DEEP_BLUE, 

                PILOTAGE_SET_NIGHT_WHITE,           // 10
                PILOTAGE_SET_NIGHT_RED, 
                PILOTAGE_SET_NIGHT_GREEN, 
                PILOTAGE_SET_NIGHT_BLUE, 
                PILOTAGE_SET_NIGHT_DEEP_BLUE, 

                PILOTAGE_SET_USER_WHITE,            // 15
                PILOTAGE_SET_USER_RED, 
                PILOTAGE_SET_USER_GREEN, 
                PILOTAGE_SET_USER_BLUE, 
                PILOTAGE_SET_USER_DEEP_BLUE,

                PILOTAGE_SET_DURATION_DAY,          // 20
                PILOTAGE_SET_DURATION_TRANS_D_N, 
                PILOTAGE_SET_DURATION_TRANS_N_D, 
                PILOTAGE_SET_DURATION_USER, 

                PILOTAGE_SET_BEGIN_DAY,

                PILOTAGE_SET_MODE_USER,             // 25

                PILOTAGE_GET_DAY, 
                PILOTAGE_GET_NIGHT, 
                PILOTAGE_GET_USER, 
                PILOTAGE_GET_DURATION, 
                PILOTAGE_GET_BEGIN_DAY              // 30
            };

            uint8_t tab_RequestBuffer[NB_BITS_BUFFER];

            static void receiveEvent(int nbOctets);

            static void requestEvent(void);

            void resetBuffer(void);

        public:

            /* Methodes */
            void initialize(void);

            void makeAction_onReceive(uint8_t myHeader, uint16_t myQueu);

            void makeAction_onRequest(void);
    };

extern Communicate Communication;

#endif