#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define SCREEN_WIDTH 84
#define SCREEN_HEIGHT 48

// Pin definitions for Nokia 5110 LCD
#define LCD_RST 7
#define LCD_CE 8
#define LCD_DC 9
#define LCD_DIN 10
#define LCD_CLK 12

// Initialize the LCD
Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_CLK, LCD_DIN, LCD_DC, LCD_CE, LCD_RST);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Initialize the LCD
  display.begin();
  display.setContrast(50); // Adjust the contrast
  
  // Set up ADC
  pinMode(A3, INPUT);
}

void loop() {
  // Clear the display
  display.clearDisplay();

  // Read the analog input (voltage)
  int voltage = analogRead(A3);
  
  // Map the voltage to screen coordinates (Y-axis)
  int yCoord = map(voltage, 0, 1023, SCREEN_HEIGHT, 0);
  
  // Draw Y-axis label
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Voltage");

  // Draw X-axis label
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT - 8);
  display.println("Current");

  // Draw axes
  display.drawLine(0, 0, 0, SCREEN_HEIGHT, BLACK);  // Y-axis
  display.drawLine(0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);  // X-axis
  
  // Draw a line representing the voltage
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    display.drawPixel(x, yCoord, BLACK);
  }

  // Display the plot on the LCD
  display.display();

  // Display the values on Serial Monitor
  Serial.print("Voltage (ADC): ");
  Serial.println(voltage);

  // Delay for a short time before next reading
  delay(100);
}
