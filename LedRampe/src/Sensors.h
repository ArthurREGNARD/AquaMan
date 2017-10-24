#ifndef SENSORS_h
#define SENSORS_h

    #include "Arduino.h"
    #include "Outils.h"
    #include "Pilotage.h"
    #include "StoreData.h"
    #include "Pin.h"

    class Sensors {

        private:
            /* Methodes */
            float getTemp(void);

        public:

            /* Methodes */
            void initialize(void);

            void callBack(void);
    };

extern Sensors Sensor;

#endif