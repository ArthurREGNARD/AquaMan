#ifndef INTERRUPT_cpp
#define INTERRUPT_cpp

    #include "Interrupt.h"

    #define DELAY_MICRO_SEC     500000 //Toute les secondes.
    #define DELAY_MILLI_SEC     500

    #define DELAY_ENCODEUR      20


    // _BV same as shifting 1 by the number of places
    // Timer 0 (8 Bit) Prescaler values
    // Frequency = System Clock (16MHz) / Prescaler / #bits (8 bits)

    #define T0_PS1      _BV(CS00)              // 31.37 khz
    #define T0_PS8      _BV(CS01)              // 5.92 khz
    #define T0_PS64     _BV(CS01) | _BV(CS00)  // 490.19 hz
    #define T0_PS256    _BV(CS02)              // 122.55 hz
    #define T0_PS1024   _BV(CS02) | _BV(CS00)  // 30.64 hz

    //TImer 1 (8 Bit)Prescaler Values
    #define T1_PS1      _BV(CS10)
    #define T1_PS8      _BV(CS11)
    #define T1_PS64     _BV(CS11) | _BV(CS10)
    #define T1_PS256    _BV(CS12)
    #define T1_PS1024   _BV(CS12) | _BV(CS10)

    //TImer 2 (8 Bit)Prescaler Values
    #define T2_PS1      _BV(CS20)
    #define T2_PS8      _BV(CS21)
    #define T2_PS32     _BV(CS21) | _BV(CS20)
    #define T2_PS64     _BV(CS22)
    #define T2_PS128    _BV(CS22) | _BV(CS20)
    #define T2_PS256    _BV(CS22) | _BV(CS21)
    #define T2_PS1024   _BV(CS22) | _BV(CS21) | _BV(CS20)

    #define FREQUENCY           16000000
    #define PRESCALE            64
    #define NB_BIT              256         // 2"8
    #define FREQ_DIVISOR        PRESCALE * NB_BIT
//    #define MAX_COMPTEUR_SEC    (FREQUENCY - (FREQUENCY % FREQ_DIVISOR)) / FREQ_DIVISOR
    #define MAX_COMPTEUR_SEC    FREQUENCY / (PRESCALE * NB_BIT)

    static long ISR_compter_A;
    static long ISR_compter_B;

    Interrupt Interruption;

    void Interrupt::initialize(void){
        ISR_compter_A = 0;
        ISR_compter_B = 0;

        setEncodeurEvent(false);
        setEncodeurTime(millis());


        /****** TIMER 0 ******/
        // TCCR0A - Timer/Counter control register A
        // Bit  |    7     |    6     |    5     |    4     |  3  |  2  |    1    |    0    |
        //      |  COM0A1  |  COM0A0  |  COM0B1  |  COM0B0  |  -  |  -  |  WGM01  |  WGM00  |
        TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);

        // TCCR0B - Timer/Counter control register B
        // Bit  |    7     |    6     |    5     |    4     |    3    |    2    |    1   |    0   |
        //      |  FOC0A   |  FOC0B   |    -     |    -     |  WGM02  |  CS02   |  CS01  |  CS00  |
        TCCR0B = T0_PS64;

        // Output Compare Registers //
        OCR0A = MAX_COMPARE_REGISTER;
        OCR0B = MAX_COMPARE_REGISTER;

        /****** TIMER 1 ******/

        // TCCR1A - Timer/Counter control register A
        // Bit  |    7     |    6     |    5     |    4     |  3  |  2  |    1    |    0    |
        //      |  COM1A1  |  COM1A0  |  COM1B1  |  COM1B0  |  -  |  -  |  WGM11  |  WGM10  |
        TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);

        // TCCR1B - Timer/Counter control register B
        // Bit  |    7     |    6     |    5     |    4     |    3    |    2    |    1   |    0   |
        //      |  ICNC1   |  ICES1   |    -     |  WGM13   |  WGM12  |  CS12   |  CS11  |  CS10  |
        TCCR1B = _BV(WGM12) | T1_PS64;
    
        // Output Compare Registers //
        OCR1A = MAX_COMPARE_REGISTER;
        OCR1B = MAX_COMPARE_REGISTER;
    
        /****** TIMER 2 ******/

        // TCCR2A - Timer/Counter control register A
        // Bit  |    7     |    6     |    5     |    4     |  3  |  2  |    1    |    0    |
        //      |  COM2A1  |  COM2A0  |  COM2B1  |  COM2B0  |  -  |  -  |  WGM21  |  WGM20  |
        TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);

        // TCCR2B - Timer/Counter control register B
        // Bit  |    7     |    6     |    5     |    4     |    3    |    2    |    1   |    0   |
        //      |  FOC2A   |  FOC2B   |    -     |    -     |  WGM22  |  CS22   |  CS21  |  CS20  |
        TCCR2B = T2_PS64;

        // TIMSK2
        // Bit  |    7     |    6     |    5     |    4     |    3    |    2    |    1   |    0   |
        //      |    -     |    -     |    -     |    -     |    -    | OCIE2B  | OCIE2A |  TOIE2 |
        TIMSK2 = _BV(OCIE2B);

        // Output Compare Registers //
        OCR2A = MAX_COMPARE_REGISTER;
        OCR2B = MAX_COMPARE_REGISTER;


        /****** INTERRUPT ******/
        // DDRC – The Port C Data Direction Register
        // Bit  |    7    |    6    |    5    |    4    |    3    |    2    |    1     |    0     |
        //      |    -    |  DDC6   |  DDC5   |  DDC4   |  DDC3   |  DDC2   |  DDC1    |  DDC0    |
        DDRC |= _BV(DDC2) | _BV(DDC1) | _BV(DDC0);

        // PORTC – The Port C Data Register
        // Bit  |    7    |    6   |    5   |    4   |    3   |    2   |    1   |    0   |
        //      |    -    | PORTC6 | PORTC5 | PORTC4 | PORTC3 | PORTC2 | PORTC1 | PORTC0 |
        PORTC |= _BV(PORTC2) | _BV(PORTC1) | _BV(PORTC0);

        // PCICR – Pin Change Interrupt Control Register
        // Bit  |    7    |    6     |    5     |    4     |    3    |    2    |    1   |    0   |
        //      |    -    |    -     |    -     |    -     |    -    |  PCIE2  |  PCIE1 |  PCIE0 |
        PCICR = _BV(PCIE1);

        // PCMSK1 – Pin Change Mask Register 1
        // Bit  |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
        //      |    -    | PCINT14 | PCINT13 | PCINT12 | PCINT11 | PCINT10 | PCINT9  | PCINT8  |
        PCMSK1 = _BV(PCINT10) | _BV(PCINT9) | _BV(PCINT8);

        // EICRA – External Interrupt Control Register A
        // Bit  |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
        //      |    -    |    -    |    -    |    -    |  ISC11  |  ISC10  |  ISC01  |  ISC00  |
        EICRA = _BV(ISC10);
    }

    void Interrupt::start(void){
        sei();
    }

    void Interrupt::stop(void){
        cli();
    }

    void Interrupt::setPWM(uint8_t pin, uint8_t PWM){

        if(PWM <= MIN_COMPARE_REGISTER)
            PWM = MIN_COMPARE_REGISTER;

        if(PWM >= MAX_COMPARE_REGISTER)
            PWM = MAX_COMPARE_REGISTER;

        switch (pin){
            case OC0A_PIN : 
                OCR0A = PWM;
                break;

            case OC0B_PIN : 
                OCR0B = PWM;
                break;

            case OC1A_PIN : 
                OCR1A = PWM;
                break;

            case OC1B_PIN : 
                OCR1B = PWM;
                break;

            case OC2A_PIN : 
                OCR2A = PWM;
                break;

            case OC2B_PIN : 
                OCR2B = PWM;
                break;

            default : ;
        }
    }

    ISR(TIMER2_COMPB_vect){
        if (ISR_compter_B >= 100 ){ //MAX_COMPTEUR_SEC){
            PilotageLED.callBack();
            PilotageLED.controler();

            Sensor.callBack();
            
            if(ISR_compter_A >= 60){
                Timing.addMinutes(1);
                ISR_compter_A = 0;
            }
            ISR_compter_A ++;
            ISR_compter_B = 0;
        }
        ISR_compter_B ++;
    }

    bool Interrupt::getEncodeurEvent(void){
        return myEncodeur.event;
    }

    void Interrupt::setEncodeurEvent(bool myEvent){
        myEncodeur.event = myEvent;
    }

    uint32_t Interrupt::getEncodeurTime(void){
        return myEncodeur.time;
    }

    void Interrupt::setEncodeurTime(uint32_t myTime){
        myEncodeur.time = myTime;
    }

    int8_t Interrupt::getEncodeurAction(void){
        setEncodeurEvent(false);
        return myEncodeur.action;
    }
    void Interrupt::setEncodeurAction(int8_t myAction){
        myEncodeur.action = myAction;
        setEncodeurEvent(true);
    }

    ISR (PCINT1_vect){
        static uint8_t oldPortC;
        static bool encodeurP = true;
        static bool oldA = true;
        static bool oldB = true;
        bool newA = oldA;
        bool newB = oldB;
        uint8_t changePortC = PINC ^ oldPortC;
        oldPortC = PINC;
        
        if(changePortC & (1 << PINC0)){
            encodeurP = !encodeurP;
            if(encodeurP)
                Interruption.setEncodeurAction(0);
        }
        if(changePortC & (1 << PINC1)){
            newA = !oldA;
        }
        if(changePortC & (1 << PINC2)){
            newB = !oldB;
        }

        if( ( oldA &&  oldB && !newA &&  newB) ||
            (!oldA &&  oldB && !newA && !newB) ||
            ( oldA && !oldB &&  newA &&  newB) ||
            (!oldA && !oldB &&  newA && !newB)      )
            Interruption.setEncodeurAction(1);
        if( ( oldA &&  oldB &&  newA && !newB) ||
            (!oldA &&  oldB &&  newA &&  newB) ||
            ( oldA && !oldB && !newA && !newB) ||
            (!oldA && !oldB && !newA &&  newB)      )
            Interruption.setEncodeurAction(-1);

        if(oldA != newA)
            oldA = newA;
        if(oldB != newB)
            oldB = newB;
    }

#endif