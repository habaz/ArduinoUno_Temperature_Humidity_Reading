/*
Author: Danny van den Brande, Arduinosensors.nl. BlueCore Tech.
Simple Temp and Humidity Sensor with the LCD 1602A.
You can also use the I2C for the LCD 1602A i 
already put the required Lines in the CODE.
All you need to do is find the right address for your I2C @ #define I2C_ADDR
in the code you can find the most used addresses.
by HAA
Added OLED Display
 */
//#include <Wire.h> Uncomment when using the I2C!
#include <LiquidCrystal_I2C.h> //if you are using a LCD 1602A with a I2C.
//#include <LiquidCrystal.h> // Uncomment this to used LCD1602 without I2C
#include <DHT.h>  // For Temeprature Sensor
#include <Adafruit_GFX.h> //For OLED display
#include <Adafruit_SSD1306.h> //For OLED display

#define OLED_RESET 4 //For OLED display

//Uncomment all #define here below when using LCD1602 with a I2C.
#define I2C_ADDR          0x27   //<< I2C address look at the back of you I2C to see which on you have.
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7
//*************

int DHT11Sensor = 7; 
int DHT11value; 
#define DHTPIN 8
#define DHTTYPE DHT11

Adafruit_SSD1306 display(OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);

//Uncomment the line LiquidCrystal_I2C and remove LiquidCrystal when using a I2C.  
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//<Remove when using the I2C.
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin); //<<Uncomment when using the I2C.

byte degree[8] ={ B00001100,
                  B00010010,
                  B00010010,
                  B00001100,
                  B00000000,
                  B00000000,
                  B00000000,
                  B00000000,};
 
void setup()
{
Serial.begin(9600); 
lcd.begin(16,2); //For LCD1602
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // For Oled
//display.display();
//delay(2000);
// Clear the buffer.
display.clearDisplay();
// draw a single pixel
//display.drawPixel(10, 10, WHITE);
// Show the display buffer on the hardware.
// NOTE: You _must_ call display after making any drawing commands
// to make them visible on the display hardware!
//display.display();
//delay(2000);
//display.clearDisplay();

// Switch on the backlight by HAA
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.clear(); 
lcd.createChar(0, degree);
}
 
void loop()
{
float h = dht.readHumidity(); 
float t = dht.readTemperature(); 

//***********FOR LCD1602*******
lcd.setCursor(0,0);
lcd.print("Sicaklik : ");
lcd.print(" ");
lcd.setCursor(10,0);
lcd.print(t,1);
Serial.println(t);
lcd.setCursor(15,0);
lcd.write((byte)0);
//lcd.print((char)223);// Print degree symbol.
 
lcd.setCursor(0,1);
lcd.print("Nem      : ");
lcd.print(" ");
lcd.setCursor(10,1);
lcd.print(h,1);
Serial.println(h);
lcd.setCursor(15,1);
lcd.print("%");

//************For OLED************
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.print("Sicaklik : ");
display.print(" ");
//display.setCursor(60,0);
//display.print("     ");
display.print(t);
//display.setCursor(100,0);
display.print(" ");
display.print("C");

display.setCursor(0,10);
display.print("Nem      : ");
display.print(" ");
//display.setCursor(60,10);
//display.print("     ");
display.print(h);
display.print(" ");
display.print("%");
display.display(); 
display.clearDisplay();
delay(2000);
}
