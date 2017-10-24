#ifndef DISPLAY_cpp
#define DISPLAY_cpp

    #include "Display.h"

    Display Screen;

    void Display::initialize(void){
    	
    }

    void Display::paramEncodeur(int8_t myMin, int8_t myCur, int8_t myMax){

    }

    int8_t Display::getCurEncodeur(void){
    	return myEncodeurSetting.Cur;
    }

    void Display::setCurEncodeur(int8_t myCur){
    	myEncodeurSetting.Cur = myCur;
    	if(myCur <= myEncodeurSetting.Min)
    		myEncodeurSetting.Cur = myEncodeurSetting.Min;
    	if(myCur >= myEncodeurSetting.Max)
    		myEncodeurSetting.Cur = myEncodeurSetting.Max;
    }

    void Display::loop(void){
		while(!Interruption.getEncodeurEvent());

		switch(Interruption.getEncodeurAction()){
			case -1 :
				setCurEncodeur(getCurEncodeur() - 1);
				break;
				
		}
    }

#endif