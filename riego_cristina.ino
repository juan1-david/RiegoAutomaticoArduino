//Automitacion de riego para jardin
// Con Arduino UNO,(RTC), Modulo Rele,  
// Conexion RTC :Arduino UNO    GND->GND VCC->5V SCL-> SCL  SDA->SDA los dos pines despues del ...12,13,GND,AREF,SDA,SCL
// Conexion Rele:Arduino UNO GND->GND  VCC->5V  IN->7
// NOTA: se debe cargar dos veces este programa 1. Con la linea  RTC.adjust(DateTime(__DATE__, __TIME__)); 
//                                              2. Sin esa linea

#include <Wire.h> 
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // inicializa la interfaz I2C del LCD 16x2
RTC_DS1307 RTC;                   // inicializa el modulo RTC
const int electroV = 7;             // Pin 7 encargado de activar la electroValvula, se conecta al Rele
int segundo;
int minuto;
int hora;



void setup () { 
  
 pinMode(electroV, OUTPUT);                    // Configura como salida el pin 7
 Wire.begin();                               
 RTC.begin();                                // Inicia la comunicaci¢n con el RTC
 
// RTC.adjust(DateTime(__DATE__, __TIME__)); // Lee la fecha y hora del PC (Solo en la primera carga)
                                             // el anterior se usa solo en la configuracion inicial luego se pone como comentario
                                             // y se vuelve a cargar el programa sin esa linea.
 Serial.begin(9600);                         // Establece la velocidad de datos del puerto serie a 9600
 lcd.init();
 lcd.backlight();                            // Coloca luz de fondo al LCD
 lcd.clear();                                // Borra el  LCD
} 
////////////////////////////////// Void loop() ///////////
void loop(){
 DateTime now = RTC.now();          // Obtiene la fecha y hora del RTC

 int contacto1 = analogRead(A0);    //Lee el valor de los contactos para escoger el horario
 int contacto2 = analogRead(A1);
 int contacto3 = analogRead(A2);
 int contacto4 = analogRead(A3);    // contacto que activa o desactiva los fines de semana

 Serial.print(now.year(), DEC);  // A§o
 Serial.print('/');
 Serial.print(now.month(), DEC); // Mes
 Serial.print('/');
 Serial.print(now.day(), DEC);   // Dia
 Serial.print(' ');
 Serial.print(now.hour(), DEC);  // Horas
 Serial.print(':');
 Serial.print(now.minute(), DEC); // Minutos
 Serial.print(':');
 Serial.print(now.second(), DEC); // Segundos
 Serial.println();
 lcd.setCursor(0,0);
 lcd.print("D:");
 lcd.print(now.year(), DEC);
 lcd.print("/");
 lcd.print(now.month(), DEC);
 lcd.print("/");
 lcd.print(now.day(), DEC);
 lcd.print(" ");
 lcd.setCursor(0,1);
 lcd.print("T: ");
 lcd.print(now.hour(), DEC);
 lcd.print(":");
 lcd.print(now.minute(), DEC);
 lcd.print(":");
 lcd.print(now.second(), DEC);
 segundo=now.second();
 minuto=now.minute();
 hora=now.hour();

   if (hora==4&minuto<30){
    digitalWrite(electroV,HIGH);
    delay(500);
     if (hora==16&minuto<20){
      digitalWrite(electroV,HIGH);
      }
    }
    else {
      digitalWrite(electroV, LOW);
      }
}
