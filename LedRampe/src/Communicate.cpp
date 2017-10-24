#ifndef COMMUNICATE_cpp
#define COMMUNICATE_cpp

    #include "Communicate.h"

    Communicate Communication;

    void Communicate::initialize(void){
        resetBuffer();

    	Wire.begin(SLAVE_ADDRESS);
        Wire.onReceive(receiveEvent);
        Wire.onRequest(requestEvent);
    }

    void Communicate::resetBuffer(void){
        int i;
        for(i=0; i<NB_BITS_BUFFER; i++)
            tab_RequestBuffer[i] = 0;
    }

    void Communicate::requestEvent(void){
        Communication.makeAction_onRequest();
    }

    void Communicate::receiveEvent(int nbOctets){
        uint8_t header = ERROR;

        if(Wire.available() > 0)
            header = Wire.read();

        uint8_t MSB = 0; 
        uint8_t LSB = 0;
        if ( Wire.available() == 2 ){
            MSB = Wire.read();
            LSB = Wire.read();
        }

        Communication.makeAction_onReceive(header, uint8_TO_uint16(MSB, LSB));
    }

    void Communicate::makeAction_onRequest(void){
        Wire.write(tab_RequestBuffer, NB_BITS_BUFFER);
        resetBuffer();
    }

    void Communicate::makeAction_onReceive(uint8_t myHeader, uint16_t myQueu){
        uint8_t compt;
        uint16_t myValue;
        str_uint16 myPreparedValue;

        switch(myHeader){

            case ERROR :
                break;

            case TIME_SET_HOUR :
                Timing.setHour(myQueu);
                break; 

            case TIME_SET_MINUTE :
                Timing.setMinute(myQueu);
                break;

            case TIME_SET_MINUTES : 
                Timing.setMinutes(myQueu);
                break;

            case TIME_ADD_MINUTES :
                Timing.addMinutes(myQueu);
                break;

            case PILOTAGE_SET_DAY_WHITE :
                PilotageLED.setLedPower(DAY,        WHITE,      myQueu);
                break;

            case PILOTAGE_SET_DAY_RED :
                PilotageLED.setLedPower(DAY,        RED,        myQueu);
                break;

            case PILOTAGE_SET_DAY_GREEN :
                PilotageLED.setLedPower(DAY,        GREEN,      myQueu);
                break;

            case PILOTAGE_SET_DAY_BLUE :
                PilotageLED.setLedPower(DAY,        BLUE,       myQueu);
                break;

            case PILOTAGE_SET_DAY_DEEP_BLUE :
                PilotageLED.setLedPower(DAY,        DEEP_BLUE,  myQueu);
                break;


            case PILOTAGE_SET_NIGHT_WHITE :
                PilotageLED.setLedPower(NIGHT,      WHITE,      myQueu);
                break;

            case PILOTAGE_SET_NIGHT_RED :
                PilotageLED.setLedPower(NIGHT,      RED,      myQueu);
                break;

            case PILOTAGE_SET_NIGHT_GREEN : 
                PilotageLED.setLedPower(NIGHT,      GREEN,      myQueu);
                break;

            case PILOTAGE_SET_NIGHT_BLUE :
                PilotageLED.setLedPower(NIGHT,      BLUE,       myQueu);
                break;

            case PILOTAGE_SET_NIGHT_DEEP_BLUE : 
                PilotageLED.setLedPower(NIGHT,      DEEP_BLUE,  myQueu);
                break;


            case PILOTAGE_SET_USER_WHITE :
                PilotageLED.setLedPower(USER,       WHITE,      myQueu);
                break;

            case PILOTAGE_SET_USER_RED :
                PilotageLED.setLedPower(USER,       RED,        myQueu);
                break;

            case PILOTAGE_SET_USER_GREEN : 
                PilotageLED.setLedPower(USER,       GREEN,      myQueu);
                break;

            case PILOTAGE_SET_USER_BLUE :
                PilotageLED.setLedPower(USER,       BLUE,       myQueu);
                break;

            case PILOTAGE_SET_USER_DEEP_BLUE : 
                PilotageLED.setLedPower(USER,       DEEP_BLUE,  myQueu);
                break;


            case PILOTAGE_SET_DURATION_DAY :
                PilotageLED.setDurationDay(myQueu);
                break;

            case PILOTAGE_SET_DURATION_TRANS_D_N :
                PilotageLED.setDurationDN(myQueu);
                break;

            case PILOTAGE_SET_DURATION_TRANS_N_D :
                PilotageLED.setDurationND(myQueu);
                break;

            case PILOTAGE_SET_DURATION_USER :
                PilotageLED.setDurationUser(myQueu);
                break;

            case PILOTAGE_SET_BEGIN_DAY :
                PilotageLED.setBeginDay(myQueu);
                break;

            case PILOTAGE_SET_MODE_USER :
                PilotageLED.setCurrentState(USER);
                break;


            case PILOTAGE_GET_DAY :
                for(compt = 0; compt < NB_COLOR; compt++){
                    myValue = (uint16_t)PilotageLED.getLedPower(DAY, (enu_Color)compt);
                    myPreparedValue = uint16_TO_uint8(myValue);
                    tab_RequestBuffer[compt*2]      = myPreparedValue.MSB;
                    tab_RequestBuffer[compt*2+1]    = myPreparedValue.LSB;
                }
                break;

            case PILOTAGE_GET_NIGHT :
                for(compt = 0; compt < NB_COLOR; compt++){
                    myValue = (uint16_t)PilotageLED.getLedPower(NIGHT, (enu_Color)compt);
                    myPreparedValue = uint16_TO_uint8(myValue);
                    tab_RequestBuffer[compt*2]      = myPreparedValue.MSB;
                    tab_RequestBuffer[compt*2+1]    = myPreparedValue.LSB;
                }
                break;

            case PILOTAGE_GET_USER :
                for(compt = 0; compt < NB_COLOR; compt++){
                    myValue = (uint16_t)PilotageLED.getLedPower(USER, (enu_Color)compt);
                    myPreparedValue = uint16_TO_uint8(myValue);
                    tab_RequestBuffer[compt*2]      = myPreparedValue.MSB;
                    tab_RequestBuffer[compt*2+1]    = myPreparedValue.LSB;
                }
                break;

            case PILOTAGE_GET_DURATION :
                for(compt = 0; compt < NB_MODE; compt++){
                    myValue = (uint16_t)PilotageLED.getLedTiming((enu_Mode)compt, DURATION);
                    myPreparedValue = uint16_TO_uint8(myValue);
                    tab_RequestBuffer[compt*2]      = myPreparedValue.MSB;
                    tab_RequestBuffer[compt*2+1]    = myPreparedValue.LSB;
                }
                break;

            case PILOTAGE_GET_BEGIN_DAY :
                uint16_t myValue;
                str_uint16 myPreparedValue;

                myValue = (uint16_t)PilotageLED.getLedTiming(DAY, BEGIN);
                myPreparedValue = uint16_TO_uint8(myValue);
                tab_RequestBuffer[0] = myPreparedValue.MSB;
                tab_RequestBuffer[1] = myPreparedValue.LSB;
                break;

            default :
                break;
        }
    }

#endif