#ifndef DISPLAY_h
#define DISPLAY_h

    #include "Arduino.h"
    #include "Interrupt.h"
	#include "Pin.h"
	#include "SPI.h"
	#include "TFT.h"

    #define NB_ITEM_MAIN    4
    #define NB_COLONE       20
    class Display {

        private:
			const char* menuMain[NB_ITEM_MAIN + 1][NB_COLONE] = {   {" ", "*", "*", "*", "*", "*", " ", " ", "M", "E", "N", "U", " ", " ", " ", "*", "*", "*", "*", " "}, 
                                                                    {" ", "F", "I", "R", "S", "T", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}, 
                                                                    {" ", "S", "E", "C", "O", "U", "N", "D", "E", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}, 
                                                                    {" ", "T", "H", "I", "R", "D", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}, 
                                                                    {" ", "F", "O", "U", "R", "T", "H", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}   };

            struct str_MenuEncodeur{
                int8_t Min;
                int8_t Cur;
                int8_t Max;
            };

            str_MenuEncodeur myEncodeurSetting;

            void paramEncodeur(int8_t myMin, int8_t myCur, int8_t myMax);

            int8_t getCurEncodeur(void);

            void setCurEncodeur(int8_t myCur);

        public:

            /* Methodes */
            void initialize(void);

            void loop(void);

    };

extern Display Screen;

#endif