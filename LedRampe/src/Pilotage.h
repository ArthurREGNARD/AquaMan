#ifndef PILOTAGE_h
#define PILOTAGE_h

    #include "Arduino.h"
    #include "Pin.h"
    #include "Interrupt.h"
    #include "Time.h"
    #include "Outils.h"
    #include "StoreData.h"


    #define NB_CANAL    5
    #define NB_MODE     5
    #define NB_COLOR    5
    #define NB_TIMING   3

    #define MIN_POWER   255
    #define INIT_POWER  MIN_POWER
    #define INIT_REDUCE 0
    #define MAX_POWER   0
    #define NB_POWER    255

    #define DEFAULT_TEMP_LED    1023
    #define WARRNING_TEMP_LED   DEFAULT_TEMP_LED + 5

    class Pilotage {

        private:

            uint8_t reducePower;

            struct str_Param_Trans_D_N{
                bool        firstColor;
                uint16_t    maxSecound;
                uint16_t    currentSecound;
                enu_Signe   signeColor;
            };

            struct str_ConfigTestMode{
                enu_Mode mode;
                uint16_t compteur;
            };

            uint8_t tab_ModePowerList[NB_MODE][NB_COLOR];

            uint16_t tab_ModeTimingList[NB_MODE][NB_TIMING];

            enu_Mode currentState;

            str_ConfigTestMode testMode;

            str_Param_Trans_D_N tab_paramTrans[NB_COLOR];

            enu_Mode getCurrentState(void); 

            void stateDAY(void);

            void stateTRANS_D_N(void);

            void stateNIGHT(void);

            void initTransColor(enu_Color myColor, enu_Mode myMode);

            void stateTRANS_N_D(void);

            void stateUSER(void);

            void stateTEST(void);

            void nextTransColor(enu_Color myColor, enu_Mode myMode, enu_Mode nextMode);

            void recursiveSetEndBegin(enu_Mode myMode, uint8_t compter);

            void setDurationNight(void);

            void setTestMode(enu_Mode myMode);

            enu_Mode getTestMode(void);

        public:

            /* Methodes */
            void initialize(void);

            void setLedPower(enu_Mode myMode, enu_Color myColor, uint8_t myPower);

            uint8_t getLedPower(enu_Mode myMode, enu_Color myColor);

            uint8_t getLedPower_Reduce(enu_Mode myMode, enu_Color myColor);

            void setLedTiming(enu_Mode myMode, enu_Timing myTiming, uint16_t myMinutes);

            uint16_t getLedTiming(enu_Mode myMode, enu_Timing myTiming);

            void setBeginDay(uint16_t myMinutes);

            void setDurationDay(uint16_t myMinutes);

            void setDurationDN(uint16_t myMinutes);

            void setDurationND(uint16_t myMinutes);

            void setDurationUser(uint16_t myMinutes);

            void newTempValue(void);

            void setReducePower(uint8_t myPower);

            uint8_t getReducePower(void);

            void setCurrentState(enu_Mode myCurrentState);

            void callBack(void);

            void controler(void);

            void print(void);
    };

extern Pilotage PilotageLED;

#endif