//Este header se utiliza para guardar las funciones que va a utilizar posteriormente ol objeto Task

//Aca se define la primera funcion llamada function_h si no esta definida anteriormente
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
    sprintf(buff, "PWM set to %2d");       //  %2d se usa para signed decimal integer
    Serial.print(buff);
}

#endif