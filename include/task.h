#include <Arduino.h>

//Clase para realizar cualquier tarea que tenga una variable cualquiera de entrada y de salida, ya sea un sensor o un actuador
template<typename T, typename P>  //Se usa template ya que T Y P pueden ser de cualquier tipo (uint,long, bool, etc)
class Task {

private:
    //El atributo de esta clase es la funcion con su entrada P y salida T
    T (*target)(P);

public:
    Task();
    //Los objetos de esta clase tienen 2 funciones: attach y run
    void attach(T (*fun)(P)){    //Its void because function does not return anything--- ej(T=float,*fun = Analogread,P = int)
        this->target = fun;      //El atributo Target va a contener una funcion especifica eg. float(analogread());
    };

    //No se declara "int funcion " ya que la entrada puede ser int o long o string gracias al template
    T run(P var){     //el tipo de variable es P, el valor es var y la salida es T 

        //Se efectua la funcion con el parámetro de entrada var y retorna lo que este definido
        //como salida en (fun)
        return this->target(var); 
    }

};

//Funcion Constructora?
template<typename T, typename P>
Task<T, P>::Task(){}