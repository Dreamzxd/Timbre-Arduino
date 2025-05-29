#include <RtcDS1302.h>
#include <ThreeWire.h>
#include <LiquidCrystal_I2C.h>

// Configuración de la pantalla LCD y RTC
LiquidCrystal_I2C lcd(0x27, 16, 2);// La referencia dependiendo el LCD puede cambiar en este caso es 0x27,
                                   //pero puede cambiar a 3f
ThreeWire myWire(7, 6, 8); // IO, SCLK, CE para el DS1302
RtcDS1302<ThreeWire> Rtc(myWire);

// Definir el pin del relé
const int relayPin = 2;

// Horario del timbre (horas y minutos)
int bellHours[] = {7, 7, 8, 9, 10, 11, 12, 13};
int bellMinutes[] = {0, 55, 50, 45, 30, 10, 5, 0};

// Función para verificar si es hora del timbre
bool isBellTime(int hour, int minute) {
  for (int i = 0; i < 8; i++) { // Dependiendo de la cantidad de datos ingresados en las horas de timbrado 
                                //cambiar también el número de parametros en esta linea. EJEMPLO: Cambiar de 8 a 9
    
    if (hour == bellHours[i] && minute == bellMinutes[i]) {
      return true;
    }
  }
  return false;
}

// Función para verificar si es día de semana (lunes a viernes)
bool isWeekday(int dayOfWeek) {
  return dayOfWeek >= 2 && dayOfWeek <= 6; // Lunes a viernes (2 a 6)
}

void setup() {
  // Inicializar LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  // Inicializar RTC
  Rtc.Begin();
  //RtcDateTime dt (2024, 10, 17, 10, 49, 00); //Para que a profe pueda cambiar la fecha y hora,
                                               // si en llegado caso se desconecte el RTC DS1302.
  //Rtc.SetDateTime(dt);

  // Inicializar pin del relé
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Mantener el relé apagado inicialmente
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime(); 
  
  // Mostrar la fecha en el LCD
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Fecha:");
  lcd.print(now.Day() < 10 ? "0" : ""); 
  lcd.print(now.Day());
  lcd.print("/");
  lcd.print(now.Month() < 10 ? "0" : ""); 
  lcd.print(now.Month());
  lcd.print("/");
  lcd.print(now.Year() < 1000 ? "20" : ""); 
  lcd.print(now.Year());

  // Mostrar la hora en el LCD
  lcd.setCursor(0, 1);
  lcd.print("Hora: ");
  lcd.print(now.Hour() < 10 ? "0" : ""); 
  lcd.print(now.Hour());
  lcd.print(":");
  lcd.print(now.Minute() < 10 ? "0" : ""); 
  lcd.print(now.Minute());
  lcd.print(":");
  lcd.print(now.Second() < 10 ? "0" : ""); 
  lcd.print(now.Second());

  // Obtener el día de la semana (1 = domingo, 2 = lunes, ..., 7 = sábado)
  int dayOfWeek = now.DayOfWeek();

  // Verificar si es día entre lunes y viernes
  if (isWeekday(dayOfWeek)) {
    // Verificar si es hora del timbre
    if (isBellTime(now.Hour(), now.Minute())) {
      digitalWrite(relayPin, HIGH); // Activar relé para sonar el timbre
      delay(3000); // Sonar durante 3 segundos
      digitalWrite(relayPin, LOW);  // Apagar el relé
    }
  }

  delay(1000); // Esperar 1 segundo antes del siguiente ciclo
}
