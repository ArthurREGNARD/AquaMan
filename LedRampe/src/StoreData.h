#ifndef STOREDATA_h
#define STOREDATA_h

    #include "Arduino.h"
    #include "Outils.h"

    class StoreData {

        public:

            /* Methodes */
            void initialize(void);

            void serialPrintHistoryMinute(listSensors sensor);

            void addNewValueSeconde(listSensors sensor, float newValue);

            float getAverageMinute(listSensors sensor);

            float getLastData(listSensors sensor);
    };

    extern StoreData Store;

#endif