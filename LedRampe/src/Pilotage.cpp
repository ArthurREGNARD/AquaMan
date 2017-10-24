#ifndef PILOTAGE_cpp
#define PILOTAGE_cpp

    #include "Pilotage.h"

    Pilotage PilotageLED;

    bool state = 0;

    uint8_t PWM = 255;

    void Pilotage::initialize(void){

    	pinMode(LED_DEBUG,     OUTPUT);
    	pinMode(LED_WHITE,     OUTPUT);
    	pinMode(LED_RED,       OUTPUT);
    	pinMode(LED_GREEN,     OUTPUT);
    	pinMode(LED_BLUE,      OUTPUT);
    	pinMode(LED_DEEP_BLUE, OUTPUT);

        /*** CONFIG MODE DAY ***/
        setLedPower(DAY, WHITE,     0);
        setLedPower(DAY, RED,       0);
        setLedPower(DAY, GREEN,     0);
        setLedPower(DAY, BLUE,      253);
        setLedPower(DAY, DEEP_BLUE, 250);

        /*** CONFIG MODE TRANS_D_N ***/
        setLedPower(TRANS_D_N, WHITE,     INIT_POWER);
        setLedPower(TRANS_D_N, RED,       INIT_POWER);
        setLedPower(TRANS_D_N, GREEN,     INIT_POWER);
        setLedPower(TRANS_D_N, BLUE,      INIT_POWER);
        setLedPower(TRANS_D_N, DEEP_BLUE, INIT_POWER);

        /*** CONFIG MODE NIGHT ***/
        setLedPower(NIGHT, WHITE,     INIT_POWER);
        setLedPower(NIGHT, RED,       INIT_POWER);
        setLedPower(NIGHT, GREEN,     INIT_POWER);
        setLedPower(NIGHT, BLUE,      0);
        setLedPower(NIGHT, DEEP_BLUE, 0);

        /*** CONFIG MODE TRANS_N_D ***/
        setLedPower(TRANS_N_D, WHITE,     INIT_POWER);
        setLedPower(TRANS_N_D, RED,       INIT_POWER);
        setLedPower(TRANS_N_D, GREEN,     INIT_POWER);
        setLedPower(TRANS_N_D, BLUE,      INIT_POWER);
        setLedPower(TRANS_N_D, DEEP_BLUE, INIT_POWER);

        /*** CONFIG MODE USER ***/
        setLedPower(USER, WHITE,     INIT_POWER);
        setLedPower(USER, RED,       INIT_POWER);
        setLedPower(USER, GREEN,     INIT_POWER);
        setLedPower(USER, BLUE,      INIT_POWER);
        setLedPower(USER, DEEP_BLUE, INIT_POWER);

        int i, j;
        for(i=0; i<NB_MODE; i++){
            for(j=0; j<NB_TIMING; j++){
                tab_ModeTimingList[i][j] = 0;
            }
        }

        setDurationDay(NB_MINUTES_12H);
        setDurationDN(NB_MINUTES_2H);
        setDurationND(NB_MINUTES_2H);

        setBeginDay(480);
/*
        setDurationDay( NB_MINUTES_2H);
        setDurationDN(  NB_MINUTES_2H);
        setDurationND(  NB_MINUTES_2H);
        setDurationUser(10);

        setBeginDay(240);        
*/
        setReducePower(INIT_REDUCE);

        tab_paramTrans[WHITE    ].firstColor = TRUE;
        tab_paramTrans[RED      ].firstColor = TRUE;
        tab_paramTrans[GREEN    ].firstColor = TRUE;
        tab_paramTrans[BLUE     ].firstColor = TRUE;
        tab_paramTrans[DEEP_BLUE].firstColor = TRUE;
    }

    void Pilotage::setTestMode(enu_Mode myMode){
        testMode.mode = myMode;
        testMode.compteur = 0;
    }

    enu_Mode Pilotage::getTestMode(void){
        return testMode.mode;
    }

    void Pilotage::setLedPower(enu_Mode myMode, enu_Color myColor, uint8_t myPower){
        tab_ModePowerList[myMode][myColor] = myPower;
        setTestMode(myMode);
        setCurrentState(TEST);
    }

    uint8_t Pilotage::getLedPower(enu_Mode myMode, enu_Color myColor){
        return tab_ModePowerList[myMode][myColor];
    }

    uint8_t Pilotage::getLedPower_Reduce(enu_Mode myMode, enu_Color myColor){
        uint16_t temp = (uint16_t)tab_ModePowerList[myMode][myColor] + getReducePower();

        if(temp >= MIN_POWER)
            temp = MIN_POWER;

        return (uint8_t)temp;
    }

    void Pilotage::setLedTiming(enu_Mode myMode, enu_Timing myTiming, uint16_t myMinutes){
        tab_ModeTimingList[myMode][myTiming] = myMinutes;
    }

    uint16_t Pilotage::getLedTiming(enu_Mode myMode, enu_Timing myTiming){
        return tab_ModeTimingList[myMode][myTiming];
    }

    void Pilotage::recursiveSetEndBegin(enu_Mode myMode, uint8_t compter){
        uint16_t tempTime = 0;
        if(compter < NB_MODE - 1){
            switch (myMode){
                case DAY : 
                    tempTime = formatMinutesForDay(getLedTiming(DAY, BEGIN) + getLedTiming(DAY, DURATION));
                    setLedTiming(DAY,       END,    tempTime);
                    setLedTiming(TRANS_D_N, BEGIN,  tempTime);
                    recursiveSetEndBegin(TRANS_D_N, ++compter);
                    break;

                case TRANS_D_N :
                    tempTime = formatMinutesForDay(getLedTiming(TRANS_D_N, BEGIN) + getLedTiming(TRANS_D_N, DURATION));
                    setLedTiming(TRANS_D_N, END,    tempTime);
                    setLedTiming(NIGHT,     BEGIN,  tempTime);
                    recursiveSetEndBegin(NIGHT, ++compter);
                    break;

                case NIGHT :
                    tempTime = formatMinutesForDay(getLedTiming(NIGHT, BEGIN) + getLedTiming(NIGHT, DURATION));
                    setLedTiming(NIGHT,     END,    tempTime);
                    setLedTiming(TRANS_N_D, BEGIN,  tempTime);
                    recursiveSetEndBegin(TRANS_N_D, ++compter);
                    break;

                case TRANS_N_D :
                    tempTime = formatMinutesForDay(getLedTiming(TRANS_N_D, BEGIN) + getLedTiming(TRANS_N_D, DURATION));
                    setLedTiming(TRANS_N_D, END,    tempTime);
                    setLedTiming(DAY,       BEGIN,  tempTime);
                    recursiveSetEndBegin(DAY, ++compter);
                    break;

                default :
                    break;
            }
        }
    }

    void Pilotage::setBeginDay(uint16_t myMinutes){
        uint16_t tempTime = formatMinutesForDay(myMinutes);
        setLedTiming(DAY,       BEGIN,  tempTime);
        recursiveSetEndBegin(DAY, 0);
    }

    void Pilotage::setDurationDay(uint16_t myMinutes){
        uint16_t tempTime = formatMinutesForDay(myMinutes);

        if(tempTime >= NB_MINUTES_12H)
            tempTime = NB_MINUTES_12H;

        setLedTiming(DAY,       DURATION, tempTime);
        setDurationNight();
        recursiveSetEndBegin(DAY, 0);
    }

    void Pilotage::setDurationDN(uint16_t myMinutes){
        uint16_t tempTime = formatMinutesForDay(myMinutes);

        if(tempTime >= NB_MINUTES_2H)
            tempTime = NB_MINUTES_2H;

        setLedTiming(TRANS_D_N, DURATION, tempTime);
        setDurationNight();
        recursiveSetEndBegin(TRANS_D_N, 0);
    }

    void Pilotage::setDurationNight(void){
        setLedTiming(NIGHT, DURATION,   NB_MINUTES_DAY -
                                        getLedTiming(DAY,       DURATION) -
                                        getLedTiming(TRANS_D_N, DURATION) -
                                        getLedTiming(TRANS_N_D, DURATION));
    }

    void Pilotage::setDurationND(uint16_t myMinutes){
        uint16_t tempTime = formatMinutesForDay(myMinutes);

        if(tempTime >= NB_MINUTES_2H)
            tempTime = NB_MINUTES_2H;

        setLedTiming(TRANS_N_D, DURATION, tempTime);
        setDurationNight();
        recursiveSetEndBegin(TRANS_N_D, 0);
    }

    void Pilotage::setDurationUser(uint16_t myMinutes){
        uint16_t tempTime = formatMinutesForDay(myMinutes);

        setLedTiming(USER, DURATION, tempTime);
    }

    void Pilotage::newTempValue(void){
        setReducePower(0);
        uint16_t myTempAvarage = Store.getAverageMinute(SENSOR_TEMP_LED);

        if(myTempAvarage >= DEFAULT_TEMP_LED)
            setReducePower(128);
        if(myTempAvarage >= WARRNING_TEMP_LED)
            setReducePower(255);
    }

    void Pilotage::setReducePower(uint8_t myPower){
        reducePower = myPower;
    }

    uint8_t Pilotage::getReducePower(void){
        return reducePower;
    }

    void Pilotage::setCurrentState(enu_Mode myCurrentState){
        currentState = myCurrentState;
    }

    enu_Mode Pilotage::getCurrentState(void){
        return currentState;
    }

    void Pilotage::stateDAY(void){
        Interruption.setPWM(LED_WHITE,      getLedPower_Reduce(DAY, WHITE));
        Interruption.setPWM(LED_RED,        getLedPower_Reduce(DAY, RED));
        Interruption.setPWM(LED_GREEN,      getLedPower_Reduce(DAY, GREEN));
        Interruption.setPWM(LED_BLUE,       getLedPower_Reduce(DAY, BLUE));
        Interruption.setPWM(LED_DEEP_BLUE,  getLedPower_Reduce(DAY, DEEP_BLUE));
    }

    void Pilotage::initTransColor(enu_Color myColor, enu_Mode myMode){
        if(tab_paramTrans[myColor].firstColor == TRUE){
            uint16_t nbSecoundDuration = getLedTiming(myMode, DURATION) * NB_SECOUNDS_1MIN;
            uint16_t deltaColor;

            if(getLedPower(DAY, myColor) >= getLedPower(NIGHT, myColor)){
                deltaColor = (uint16_t)(getLedPower(DAY, myColor) - getLedPower(NIGHT, myColor));
                if(myMode == TRANS_D_N){
                    setLedPower(myMode, myColor, getLedPower(DAY, myColor));
                    tab_paramTrans[myColor].signeColor = NEGATIVE;
                } else {
                    setLedPower(myMode, myColor, getLedPower(NIGHT, myColor));
                    tab_paramTrans[myColor].signeColor = POSITIVE;
                }
            } else {
                deltaColor = (uint16_t)(getLedPower(NIGHT, myColor) - getLedPower(DAY, myColor));
                if(myMode == TRANS_D_N){
                    setLedPower(myMode, myColor, getLedPower(DAY, myColor));
                    tab_paramTrans[myColor].signeColor = POSITIVE;
                } else {
                    setLedPower(myMode, myColor, getLedPower(NIGHT, myColor));
                    tab_paramTrans[myColor].signeColor = NEGATIVE;
                }
            }

            tab_paramTrans[myColor].maxSecound = (uint16_t) nbSecoundDuration / deltaColor;
            
            tab_paramTrans[myColor].firstColor = FALSE;
        }
    }

    void Pilotage::nextTransColor(enu_Color myColor, enu_Mode myMode, enu_Mode nextMode){
        if(tab_paramTrans[myColor].currentSecound >= tab_paramTrans[myColor].maxSecound){
            if(tab_paramTrans[myColor].signeColor == POSITIVE){
                if( (getLedPower(myMode, myColor) + 1) <= getLedPower(nextMode, myColor))
                    setLedPower(myMode, myColor, (getLedPower(myMode, myColor) + 1));
            } else {
                if( (getLedPower(myMode, myColor) - 1) >= getLedPower(nextMode, myColor))
                    setLedPower(myMode, myColor, (getLedPower(myMode, myColor) - 1));
            }
            tab_paramTrans[myColor].currentSecound = 0;
        }
        tab_paramTrans[myColor].currentSecound ++;

    }

    void Pilotage::stateTRANS_D_N(void){
        initTransColor(WHITE,       TRANS_D_N);
        initTransColor(RED,         TRANS_D_N);
        initTransColor(GREEN,       TRANS_D_N);
        initTransColor(BLUE,        TRANS_D_N);
        initTransColor(DEEP_BLUE,   TRANS_D_N);

        Interruption.setPWM(LED_WHITE,      getLedPower_Reduce(TRANS_D_N, WHITE));
        Interruption.setPWM(LED_RED,        getLedPower_Reduce(TRANS_D_N, RED));
        Interruption.setPWM(LED_GREEN,      getLedPower_Reduce(TRANS_D_N, GREEN));
        Interruption.setPWM(LED_BLUE,       getLedPower_Reduce(TRANS_D_N, BLUE));
        Interruption.setPWM(LED_DEEP_BLUE,  getLedPower_Reduce(TRANS_D_N, DEEP_BLUE));

        nextTransColor(WHITE,       TRANS_D_N, NIGHT);
        nextTransColor(RED,         TRANS_D_N, NIGHT);
        nextTransColor(GREEN,       TRANS_D_N, NIGHT);
        nextTransColor(BLUE,        TRANS_D_N, NIGHT);
        nextTransColor(DEEP_BLUE,   TRANS_D_N, NIGHT);
    }

    void Pilotage::stateNIGHT(void){
        Interruption.setPWM(LED_WHITE,      getLedPower_Reduce(NIGHT, WHITE));
        Interruption.setPWM(LED_RED,        getLedPower_Reduce(NIGHT, RED));
        Interruption.setPWM(LED_GREEN,      getLedPower_Reduce(NIGHT, GREEN));
        Interruption.setPWM(LED_BLUE,       getLedPower_Reduce(NIGHT, BLUE));
        Interruption.setPWM(LED_DEEP_BLUE,  getLedPower_Reduce(NIGHT, DEEP_BLUE));
    }

    void Pilotage::stateTRANS_N_D(void){
        initTransColor(WHITE,       TRANS_N_D);
        initTransColor(RED,         TRANS_N_D);
        initTransColor(GREEN,       TRANS_N_D);
        initTransColor(BLUE,        TRANS_N_D);
        initTransColor(DEEP_BLUE,   TRANS_N_D);

        Interruption.setPWM(LED_WHITE,      getLedPower_Reduce(TRANS_N_D, WHITE));
        Interruption.setPWM(LED_RED,        getLedPower_Reduce(TRANS_N_D, RED));
        Interruption.setPWM(LED_GREEN,      getLedPower_Reduce(TRANS_N_D, GREEN));
        Interruption.setPWM(LED_BLUE,       getLedPower_Reduce(TRANS_N_D, BLUE));
        Interruption.setPWM(LED_DEEP_BLUE,  getLedPower_Reduce(TRANS_N_D, DEEP_BLUE));

        nextTransColor(WHITE,       TRANS_N_D, DAY);
        nextTransColor(RED,         TRANS_N_D, DAY);
        nextTransColor(GREEN,       TRANS_N_D, DAY);
        nextTransColor(BLUE,        TRANS_N_D, DAY);
        nextTransColor(DEEP_BLUE,   TRANS_N_D, DAY);
    }

    void Pilotage::stateUSER(void){
        static uint32_t compteur = 0;

        if(compteur >= (getLedTiming(USER, DURATION) * NB_SECOUNDS_1MIN) ){
            compteur = 0;
            setCurrentState(DAY);
        } else {
            compteur ++;
        }

        Interruption.setPWM(LED_WHITE,      getLedPower_Reduce(USER, WHITE));
        Interruption.setPWM(LED_RED,        getLedPower_Reduce(USER, RED));
        Interruption.setPWM(LED_GREEN,      getLedPower_Reduce(USER, GREEN));
        Interruption.setPWM(LED_BLUE,       getLedPower_Reduce(USER, BLUE));
        Interruption.setPWM(LED_DEEP_BLUE,  getLedPower_Reduce(USER, DEEP_BLUE));
    }

    void Pilotage::stateTEST(void){
        if(testMode.compteur >= 4){
            testMode.compteur = 0;
            setCurrentState(DAY);
        } else {
            testMode.compteur ++;
        }

        Interruption.setPWM(LED_WHITE,      getLedPower_Reduce(getTestMode(), WHITE));
        Interruption.setPWM(LED_RED,        getLedPower_Reduce(getTestMode(), RED));
        Interruption.setPWM(LED_GREEN,      getLedPower_Reduce(getTestMode(), GREEN));
        Interruption.setPWM(LED_BLUE,       getLedPower_Reduce(getTestMode(), BLUE));
        Interruption.setPWM(LED_DEEP_BLUE,  getLedPower_Reduce(getTestMode(), DEEP_BLUE));
    }

    void Pilotage::callBack(void){
        if( (getCurrentState() != USER) && (getCurrentState() != TEST) ){
            uint16_t myTiming = Timing.getMinutes();
            
            if( ((NB_MINUTES_MIN <= myTiming) && (myTiming <= getLedTiming(NIGHT, END) )) ||
                ((getLedTiming(NIGHT, BEGIN) <= myTiming) && (myTiming <= NB_MINUTES_DAY))  ){
                setCurrentState(NIGHT);
            }
            if((getLedTiming(TRANS_N_D, BEGIN) <= myTiming) && (myTiming <= getLedTiming(TRANS_N_D, END))){
                setCurrentState(TRANS_N_D);
            }
            if((getLedTiming(DAY, BEGIN) <= myTiming) && (myTiming <= getLedTiming(DAY, END))){
                setCurrentState(DAY);
            }
            if((getLedTiming(TRANS_D_N, BEGIN) <= myTiming) && (myTiming <= getLedTiming(TRANS_D_N, END))){
                setCurrentState(TRANS_D_N);
            }
        }
    }

    void Pilotage::controler(void){
        switch (getCurrentState()){

            case DAY :
                tab_paramTrans[WHITE].firstColor = TRUE;
                tab_paramTrans[RED].firstColor = TRUE;
                tab_paramTrans[GREEN].firstColor = TRUE;
                tab_paramTrans[BLUE].firstColor = TRUE;
                tab_paramTrans[DEEP_BLUE].firstColor = TRUE;
                stateDAY();
                break;

            case TRANS_D_N :
                stateTRANS_D_N();
                break;

            case NIGHT :
                tab_paramTrans[WHITE].firstColor = TRUE;
                tab_paramTrans[RED].firstColor = TRUE;
                tab_paramTrans[GREEN].firstColor = TRUE;
                tab_paramTrans[BLUE].firstColor = TRUE;
                tab_paramTrans[DEEP_BLUE].firstColor = TRUE;
                stateNIGHT();
                break;

            case TRANS_N_D :
                stateTRANS_N_D();
                break;

            case USER : 
                stateUSER();
                break;

            case TEST : 
                stateTEST();
                break;

            default : 
                break;
        }
    }

    void Pilotage::print(void){
        /*
        Serial.println("");
        Serial.println("\t\tBEGIN\t\tDURATION\tEND");
        Serial.print("DAY\t\t");
        Serial.print(getLedTiming(DAY, BEGIN));
        Serial.print("\t\t");
        Serial.print(getLedTiming(DAY, DURATION));
        Serial.print("\t\t");
        Serial.println(getLedTiming(DAY, END));

        Serial.print("TRANS_D_N\t");
        Serial.print(getLedTiming(TRANS_D_N, BEGIN));
        Serial.print("\t\t");
        Serial.print(getLedTiming(TRANS_D_N, DURATION));
        Serial.print("\t\t");
        Serial.println(getLedTiming(TRANS_D_N, END));

        Serial.print("NIGHT\t\t");
        Serial.print(getLedTiming(NIGHT, BEGIN));
        Serial.print("\t\t");
        Serial.print(getLedTiming(NIGHT, DURATION));
        Serial.print("\t\t");
        Serial.println(getLedTiming(NIGHT, END));

        Serial.print("TRANS_N_D\t");
        Serial.print(getLedTiming(TRANS_N_D, BEGIN));
        Serial.print("\t\t");
        Serial.print(getLedTiming(TRANS_N_D, DURATION));
        Serial.print("\t\t");
        Serial.println(getLedTiming(TRANS_N_D, END));
        
        */

        static uint16_t oldValueA =0;
        uint16_t currentValueA = getLedPower(TRANS_D_N, WHITE);
        if(oldValueA != currentValueA){
            Serial.print(currentValueA);
            Serial.print("\t");
            Serial.println(tab_paramTrans[TRANS_D_N].maxSecound);
            oldValueA = currentValueA;
        }

        static uint16_t oldValueB =0;
        uint16_t currentValueB = getLedPower(TRANS_N_D, WHITE);
        if(oldValueB != currentValueB){
            Serial.print(currentValueB);
            Serial.print("\t");
            Serial.println(tab_paramTrans[TRANS_N_D].maxSecound);
            oldValueB = currentValueB;
        }
        
    }

#endif