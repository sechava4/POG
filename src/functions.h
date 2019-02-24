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

#endif