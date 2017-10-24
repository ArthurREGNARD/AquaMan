#ifndef STOREDATA_cpp
#define STOREDATA_cpp

    #include "StoreData.h"

    #define NOMBER_SENSOR   2

    #define SENSOR_TEMP_LED 0
    #define SENSOR_CURRENT  1

    #define NOMBER_SECONDES 60
    #define NOMBER_MINUTES  60
    #define NOMBER_HOURS    24
    #define NOMBER_DAYS     7

    float myHistoryMinute[NOMBER_SENSOR][NOMBER_SECONDES+1]; 
    float myHistoryHour[NOMBER_SENSOR][NOMBER_MINUTES+1]; 
    float myHistoryDay[NOMBER_SENSOR][NOMBER_HOURS+1]; 
    float myHistoryWeek[NOMBER_SENSOR][NOMBER_DAYS+1]; 

    char myOlderSeconde = 0; 
    char myOlderMinute  = 0; 
    char myOlderHour    = 0; 
    char myOlderDay     = 0; 

    
    StoreData Store;


    void initialisedTabular(void){

        /* Mise à 0 des tableaux. */
        for (char h=0; h<NOMBER_SENSOR; h++){
            for (char i=0; i<NOMBER_SECONDES; i++){
                myHistoryMinute[h][i] = 0;
            }

            for (char i=0; i<NOMBER_MINUTES; i++){
                myHistoryHour[h][i] = 0;
            }

            for (char i=0; i<NOMBER_HOURS; i++){
                myHistoryDay[h][i] = 0;
            }

            for (char i=0; i<NOMBER_DAYS; i++){
                myHistoryWeek[h][i] = 0;
            }
        }
    }


    void StoreData::initialize(void){
        initialisedTabular();
    }

    void StoreData::serialPrintHistoryMinute(listSensors sensor){
        Serial.print("Tab myHistoryMinute ( CurrentSeconde :");
        Serial.print(myOlderSeconde);
        Serial.print("- AverageMinute :");
        Serial.print(getAverageMinute(sensor));
        Serial.print(")\n");
        Serial.print("[");
        for (char i=0; i<NOMBER_SECONDES-1; i++){
            Serial.print(myHistoryMinute[sensor][i]);
            Serial.print("; ");
        }
        Serial.print(myHistoryMinute[sensor][NOMBER_SECONDES-1]);
        Serial.print("]\n");
    }

    /*
    def printHistoryHour(self):
        print("Tab myHistoryHour ( Size :", len(self.myHistoryHour), "- CurrentMinute :", self.myOlderMinute, "- AverageHour :", self. getAverageHour(), ")")
        print(self.myHistoryHour)

    def printHistoryDay(self):
        print("Tab myHistoryDay ( Size :", len(self.myHistoryDay), "- CurrentMinute :", self.myOlderHour, "- AverageHour :", self.getAverageDay(), ")")
        print(self.myHistoryDay)

    def printHistoryWeek(self):
        print("Tab myHistoryWeek ( Size :", len(self.myHistoryWeek), "- CurrentDay :", self.myOlderDay, "- AverageWeek :", self.getAverageWeek(), ")")
        print(self.myHistoryWeek)
    */

    void StoreData::addNewValueSeconde(listSensors sensor, float newValue){
        myHistoryMinute[sensor][NOMBER_SECONDES+1] = myHistoryMinute[sensor][NOMBER_SECONDES+1] - myHistoryMinute[sensor][myOlderSeconde] + newValue;
        myHistoryMinute[sensor][myOlderSeconde] = newValue;
        myOlderSeconde++;
        if (myOlderSeconde == NOMBER_SECONDES){
            myOlderSeconde = 0;
            //addNewValueMinute(getAverageMinute());
        }
    }

    /*
    def addNewValueMinute(self, newValue):
        # Calcul de la Somme
        self.mySumHour = self.mySumHour - self.myHistoryHour[self.myOlderMinute] + newValue
        self.myHistoryHour[self.myOlderMinute] = newValue
        if (self.myOlderMinute + 1 == NOMBER_MINUTES):
            self.myOlderMinute = 0
            self.addNewValueHour(self.getAverageHour())
        else:
            self.myOlderMinute += 1

    def addNewValueHour(self, newValue):
        # Calcul de la Somme
        self.mySumDay = self.mySumDay - self.myHistoryDay[self.myOlderHour] + newValue
        self.myHistoryDay[self.myOlderHour] = newValue
        if (self.myOlderHour + 1 == NOMBER_HOURS):
            self.myOlderHour = 0
            self.addNewValueDay(self.getAverageDay())
        else:
            self.myOlderHour += 1

    def addNewValueDay(self, newValue):
        # Calcul de la Somme
        self.mySumWeek = self.mySumWeek - self.myHistoryWeek[self.myOlderDay] + newValue
        self.myHistoryWeek[self.myOlderDay] = newValue
        self.myOlderDay = (self.myOlderDay + 1) % NOMBER_DAYS
    */

    float StoreData::getAverageMinute(listSensors sensor){
        return myHistoryMinute[sensor][NOMBER_SECONDES+1] / NOMBER_SECONDES;
    }

    /*
    def getAverageHour(self):
        return self.mySumHour / NOMBER_MINUTES

    def getAverageDay(self):
        return self.mySumDay / NOMBER_HOURS

    def getAverageWeek(self):
        return self.mySumWeek / NOMBER_DAYS
    */

    float StoreData::getLastData(listSensors sensor){
        char currentTime = myOlderSeconde - 1;
        if (currentTime <0){
            currentTime = NOMBER_SECONDES;
        }
        return myHistoryMinute[sensor][currentTime]; 
    }

#endif