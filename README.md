#📘 Timbre Escolar Automático con Arduino

🛠 Descripción
Este proyecto tiene como objetivo automatizar el timbre de una institución educativa utilizando una placa Arduino UNO, un módulo RTC para controlar las horas de activación, una pantalla LCD para visualizar la hora actual y un relé para controlar el timbre industrial a 110V.

🎯 Funcionalidades: 

- Sonar el timbre automáticamente en horas específicas (ej: 7:00 a.m., 7:55 a.m., etc.).

- Mostrar la hora actual en una pantalla LCD.

- Programación semanal (lunes a viernes).

- Separación segura entre la lógica de bajo voltaje y el timbre de 110V.

🔌 Materiales
Componente	Cantidad
Arduino UNO	1
Módulo RTC DS1302	1
Pantalla LCD 16x2 I2C	1
Módulo relé JQC-3FF-S-Z	1
Timbre industrial 110V	1
Protoboard o PCB	1
Cables Dupont	Varios
Fuente de alimentación	5V y fuente 110V para el timbre

🔗 Conexiones
🕒 RTC DS1302
DS1302 Pin	Arduino Pin
VCC	5V
GND	GND
CLK	6
DAT	7
RST	8

⚠ Puedes ajustar estos pines según tu código.

🖥 LCD I2C
LCD Pin	Arduino Pin
VCC	5V
GND	GND
SDA	A4
SCL	A5

🔔 Relé
Relé Pin	Arduino Pin
IN (señal)	9
VCC	5V
GND	GND

🔌 Conexión del Timbre (110V)
Advertencia: Esta parte trabaja con corriente alterna. Asegúrate de tomar precauciones.

COM (relé) → Línea directa del 110V

NO (Normalmente Abierto) → Al timbre

El otro cable del timbre → Neutro del 110V

💻 Librerías necesarias:

Asegúrate de incluir estas librerías en tu entorno de desarrollo (Arduino IDE):

DS1302.h o RTClib compatible con el módulo RTC

Adafruit_LiquidCrystal.h o LiquidCrystal_I2C.h para la pantalla LCD
