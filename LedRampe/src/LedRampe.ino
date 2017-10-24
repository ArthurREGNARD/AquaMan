
#include "StoreData.h"
//#include "Display.h"
#include "Interrupt.h"
#include "Pilotage.h"
#include "Time.h"
#include "Communicate.h"
#include "Outils.h"

#define BAUD_RATE       9600

void setup(void){

	Interruption.stop();

    /* Configuration de Interruption */
    Interruption.initialize();

    /* Configuration de Dispaly */
    //Screen.initialize();

    /* Configuration de StoreData */
    Store.initialize(); 

    /* Configuration de Sensors */
    Sensor.initialize(); 

    /* Configuration de Pilotage */
    PilotageLED.initialize();

    /* Configuration de Comunicate */
    Communication.initialize();

    /* Configuration du port Série */
    Serial.begin(BAUD_RATE);

    /* Configuration du port Time */
    Timing.initialize(12, 00);

    /* Lancement des interruptions */
    Interruption.start();

}

void loop(void){
    //PilotageLED.controler();
    //Serial.print(Timing.getHour());
    //Serial.print(" : ");
    //Serial.println(Timing.getMinutes());
    //PilotageLED.print();
    /*
    static int8_t value = 0;
    while(!Interruption.getEncodeurEvent());
    if(Interruption.getEncodeurAction() == 0)
        value = 0;
    if(Interruption.getEncodeurAction() == -1)
        value--;
    if(Interruption.getEncodeurAction() == 1)
        value++;
    Serial.println(value);
    */
    //Screen.loop();
}