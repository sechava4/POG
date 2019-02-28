#ifndef TRIGGER_H
    #define TRIGGER_H

        #include <Arduino.h>

        template<typename T> 
        class Trigger {

        private:
            // T (*fun)(P);

            const char* comparison;
            T value;
            

        public:

            Trigger();
            Trigger(const char* comparison_code,T some_var );
            
            
            int Listen( int var){ 
                //Si el valor medido es igual al valor de disparo    
                if (strcmp(comparison, "=") == 0) 
                    {
                        if (var==value){
                            return 1;
                        }
                        else {return 0;}
                    } 
                //Si el valor medido es menor al valor de disparo
                else if (strcmp(comparison, "<") == 0) 
                    {
                        if (var<value){
                            return 1;
                        }
                        else {return 0;}
                    }    
                //Si el valor medido es mayor al valor de disparo
                else if (strcmp(comparison, ">") == 0) 
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

        };


        template<typename T> 
        Trigger<T>::Trigger(const char* comparison_code,T some_val ) {
                this->value = some_val; 
                this->comparison = comparison_code;  
            }

        
#endif