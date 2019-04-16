#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <sensor.h>
#include <actuator.h>
#include <peripheal.h>
#include <trigger.h>
#include <functions.h>
#include <line.h>
#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip

const int LCD_COLS = 16;
const int LCD_ROWS = 2;

#define ROJO 0x00FF0000 

//Creacion de instancias
//Sensores
Sensor encoder_rueda = Sensor(String("KY040"), String("cm"));

Sensor request_button = Sensor(String("Button in"), String("state"));

Sensor finish_button = Sensor(String("Button out"), String("state"));

//Declare object of class HTTPClient
HTTPClient http;

//Se crea una instancia de la clase actuador para crear un objeto llamado "electrovalvula"  con atributos name y type
Actuator valvula = Actuator(String("0.8Mpa"), String("Electrovalvula"));

// //Se crea una instancia de la clase Trigger para crear un objeto llamado "Trigger1"  con atributos comparison y value (==0 ?)
Trigger<int> trigger_valve = Trigger<int>('=', int(0));


// long timer = millis();



void setup() {
  

  Serial.begin(9600);     //Velocidad de la comunicacion serial

  pinMode(CLK, INPUT_PULLUP);
  pinMode(DATA, INPUT_PULLUP);

  attachInterrupt (D6,zerofcn,RISING);    //Interrupcion para zero
  encoder_rueda.attach(count_pulses);  

  request_button.attach(digitalPinRead);
  finish_button.attach(digitalPinRead);

  valvula.attach(dwrite);    //Se añade la función que dispara la válvula conectada al pin digital 0

  lcd.begin(LCD_COLS, LCD_ROWS);

  lcd.print("Hello, World!");


}

void loop() {


  lcd.setCursor(1,1);
  lcd.print("tamo melo");

  //if(trigger_valve.Listen(i1)){
  //  valvula.run(16);       //Se activa la valvula conectada al pin 16

  encoder_rueda.run(0);
  //Serial.println(1);
  // if (request_button.run(D4)){
  //   //
  //   //
  //   Line linea("Rojo",89);  //RGB 
  //   while(linea.getCms() >= encoder_rueda.run(0)){
  //     encoder_rueda.run(0);
  //   }
  //   valvula.run(1);
    
  // }
  
  // if (finish_button.run(D5)){
  //   valvula.run(0);
  //   pulses = 0;
  //   //
  //   //Mande datos s la nube
  // }

  //if(millis() - timer > 1000){
  //  timer = millis();

  //}
  

}





