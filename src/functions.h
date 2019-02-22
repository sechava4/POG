//Este header se utiliza para guardar las funciones que va a utilizar posteriormente ol objeto Task

//Aca se define la primera funcion llamada function_h si no esta definida anteriormente
#ifndef function_h
    #define function_h

    #include <Arduino.h>

    float readTemp(int var){
    return (float(analogRead(0)/1023.0)*5.0);
    }

#endif