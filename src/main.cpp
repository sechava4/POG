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
#include <WiFiClient.h>





#define ROJO 0x00FF0000 
uint8_t state = 0;

//Creacion de instancias
//Sensores
Sensor encoder_rueda = Sensor(String("KY040"), String("cm"));

Sensor request_button = Sensor(String("Button in"), String("state"));

Sensor finish_button = Sensor(String("Button out"), String("state"));

//Declare object of class HTTPClient

//Se crea una instancia de la clase actuador para crear un objeto llamado "electrovalvula"  con atributos name y type
Actuator valvula = Actuator(String("0.8Mpa"), String("Electrovalvula"));

// //Se crea una instancia de la clase Trigger para crear un objeto llamado "Trigger1"  con atributos comparison y value (==0 ?)
Trigger<int> trigger_valve = Trigger<int>('=', int(0));


// long timer = millis();



void setup() {
  

  Serial.begin(9600);     //Velocidad de la comunicacion serial


  attachInterrupt (D6,zerofcn,RISING);    //Interrupcion para zero
  encoder_rueda.attach(pulseReading);  

  request_button.attach(digitalPinRead);
  finish_button.attach(digitalPinRead);

  valvula.attach(dwrite);    //Se añade la función que dispara la válvula conectada al pin digital 0

  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.clear();

  WiFi.mode(WIFI_STA);
  WiFi.begin("HOME-A9BC", "2024AA4E158B3787");    //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection
 
    delay(500);
    lcd.setCursor(0,0);
    lcd.print("Connecting");
 
  }
  lcd.setCursor(0,0);
  lcd.print("WiFi Connected");
  delay(1000);
}

void loop() {
  
  //Finite state switch
  switch (state)
  {
    case 0:  //Antes de solicitar una tarea
      lcd.setCursor(0,0);
      lcd.print("Solicitar Linea");  
      if (request_button.run(D5)){
        state = 1;  
      }

      break;

    case 1:  //Solicitando tarea
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Solicitando"); 
      delay(200); 
      if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
        Serial.println("conecto");
        WiFiClient client;

        HTTPClient http;

        if (http.begin(client, "http://192.168.1.53:8080/helloesp")) { // HTTP
          Serial.println("accedio a la pagina");
          int httpCode = http.GET(); //Send the request
    
          if (httpCode > 0) { //Check the returning code
            Serial.println("leyo el contenido");
            String payload = http.getString();   //Get the request response payload
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(payload); 
            delay(2000);
          }
          else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }
        }
      http.end();   //Close connection
      delay(2000);
      }
      state = 0;
      break;
  
  }
  
  // SIempre Lea el encoder
  
  lcd.setCursor(0,1);
  lcd.print(static_cast<int>(encoder_rueda.run(0)));   

  // if(trigger_valve.Listen(i1)){
  //  valvula.run(16);       //Se activa la valvula conectada al pin 16

  // if (request_button.run(D5)){
  //   //
  //   //
  //   Line linea("Rojo",89);  //RGB 
  //   while(linea.getCms() >= encoder_rueda.run(0)){
  //     encoder_rueda.run(0);
  //   }
  //   valvula.run(1);
    
  // }
  
  // if (finish_button.run(D6)){
  //   valvula.run(0);
  //   pulses = 0;
  //   //
  //   //Mande datos s la nube
  // }

  
  

}





