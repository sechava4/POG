#ifndef PERIPHEAL_H
#define PERIPHEAL_H


#include <Arduino.h>


//Se crea la clase periferico para utilizar cualquier sensor o actuador
class Peripheal {
    private:            //Estos son los atributos que posee un objeto de esta clase
        String name;      //nombre
        uint16_t id;      //id
    public:             //Estas son las funciones perimitidas que puede realizar el objeto
        Peripheal();
        Peripheal(String name, uint16_t id);    //Funcion constructora de los objetos de la clase
        String getName();   //retornar el nombre
        uint16_t getId();   //retornar el id
        String setName(String name);    //Setear el ID
        uint16_t setId(uint16_t id);    //Setear el ID

};
//Funcion constructora
Peripheal::Peripheal(String name, uint16_t id=random(0, 0xFFFF)) {
    this->name = name;  //al atributo "name" se le asigna el string name entregado por la entrada de la funcion
    this->id = id;  //al atributo "id" se le asigna el uint16 name entregado por la entrada de la funcion
}


//Funcion get name para entregar el nombre de un objeto existente
String Peripheal::getName() {
    return name;
}

//Funcion get id para entregar el id de un objeto existente
uint16_t Peripheal::getId() {
    return id;
}

//Funcion set name para cambiar el id de un objeto existente
String Peripheal::setName(String name) {
     //al atributo "name" se le asigna el string name entregado por la entrada de la funcion
    this->name = name;
    return name;
}

uint16_t Peripheal::setId(uint16_t id) {
    //al atributo "name" se le asigna el string name entregado por la entrada de la funcion
    this->id = id;
    return id;
}


#endif