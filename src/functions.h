//Este header se utiliza para guardar las funciones que va a utilizar posteriormente el objeto Task
//Se define solo una vez para que no hayan errores de redefinición 
#ifndef function_h
    #define function_h

    #include <Arduino.h>
    #include <Encoder.h>
    #include <Wire.h>
    #include <hd44780.h>                       // main hd44780 header
    #include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

    hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip

    const int LCD_COLS = 16;
    const int LCD_ROWS = 2;


    float digitalPinRead(int pin)
    {
        return(digitalRead(pin));
    }


    Encoder myEnc(D3, D4);
    long oldPosition  = -999;
    int pulses;
    float pulseReading(int )
    {
        long pulses = (myEnc.read())/4;   //Incrementos de a 1
        if (pulses != oldPosition) 
        {
            oldPosition = pulses;
            lcd.clear();  
        }                         //Para que no queden valores montados en el lcd
        return(pulses);
    }


    bool dwrite(uint16_t val)
    {
        digitalWrite(16,val);
        return(val);

    }

    template<typename T,typename P> 
    bool funtrig (char comparison, P var,T value){
        if (comparison == '=') 
            {
                if (var==value){
                    return 1;
                }
                else {return 0;}
            } 
        else if (comparison == '<') 
            {
                if (var<value){
                    return 1;
                }
                else {return 0;}
            }    
        //Si el valor medido es mayor al valor de disparo
        else if (comparison == '>') 
            {
                if (var>value){
                    return 1;
                }
                else {return 0;}
            }   
        else {
            return 0;
        }
    }



    void zerofcn(){
        myEnc.write(0);
    }
















  
#endif