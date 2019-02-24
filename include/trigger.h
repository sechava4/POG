#ifndef TRIGGER_H
    #define TRIGGER_H

        #include <Arduino.h>


        class Trigger {

        private:
            // T (*fun)(P);

            //
            int comparison;
            int value;


        public:


            Trigger();
            Trigger(int comparison_code, int value );
            
            
            
            void Listen( int var){     
                switch (comparison)
                {
                    case 0:
                        if(var==value){
                            
                        }
                        
                        break;
                    case 1:
                        ///=
                        break;
                    case 2:
                        //<
                        break;
                    case 3:
                        //>
                        break;
                }
            
                
                //return this->target(var); 
            }

        };

        Trigger::Trigger(int comparison_code, int value ) {
                this->value = value; 
                this->comparison = comparison_code;  
            }


#endif