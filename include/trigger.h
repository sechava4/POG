#ifndef TRIGGER_H
    #define TRIGGER_H

        #include <Arduino.h>
        #include <functions.h>

        template<typename T> 
        class Trigger {

        private:
            char comparison;
            T value;           
        public:

            Trigger();
            Trigger(char comparison_code,T some_var );   //Funcion constructora
            
            template<typename P> 
            bool Listen( P var){ 
                return(funtrig(comparison,var,value));

            }

        };


        template<typename T> 
        Trigger<T>::Trigger(char comparison_code,T comp_val) {
                this->value = comp_val; 
                this->comparison = comparison_code;  
            }

        
#endif