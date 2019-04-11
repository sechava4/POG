//Este header se utiliza para guardar las funciones que va a utilizar posteriormente ol objeto Task

//Se define solo una vez para que no hayan errores de redefinición 
#ifndef function_h
    #define function_h

    #include <Arduino.h>

    //Funcion 1 para sensor de temperatura
    float readTemp(int var){
    return (float(analogRead(0)/1023.0)*5.0);
    }

    //Funcion 2 para setear velocidad de servo, en este momento solo imprime la velocidad
    bool setSpeed(uint16_t duty){    //P = uint16_t T = bool
    char buff[50];  
    sprintf(buff, "PWM set to %2d",duty);       //  %2d se usa para signed decimal integer, se agrega duty
    Serial.println(buff);   
    return 0;
    }

    bool digitalPinRead(int pin)
    {
        return(digitalRead(pin));
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

    volatile uint32_t pulses = 0;
    const double degrees_per_pulse = 0.31416;
    const double wheel_radious = 3.1831;
    double dist_cm;
    void rotarydetect ()  {
        pulses++;
        delay(20);

    }



  
#endif