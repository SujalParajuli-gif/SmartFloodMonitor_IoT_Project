// Starting of code
// Importing required libraries for I2C communication and LCD display
#include <Wire.h>              // Library for I2C communication (used by LCD)
#include <LiquidCrystal_I2C.h> // Library for controlling the LCD display

// Defining the LCD address and size (16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address: 0x27, 16x2 display

// Defining pins for the sensor and buzzer
#define SENSOR_PIN A0   // Analog pin connected to the sensor
#define BUZZER_PIN D4   // Digital pin connected to the buzzer
#define SDA_PIN D2      // I2C data pin for LCD
#define SCL_PIN D1      // I2C clock pin for LCD

// Defining a threshold value to detect water presence
#define THRESHOLD 600   // Sensor value below this indicates water presence

// Variable to keep track of whether the buzzer is on or off
bool buzzerOn = false; // Initially, the buzzer is off

// Setup function runs once when the system starts
void setup() {
  // Initialize I2C communication for the LCD using the defined pins
  Wire.begin(SDA_PIN, SCL_PIN); 

  // Initialize the LCD display
  lcd.init();        // Start the LCD
  lcd.backlight();   // Turn on the LCD backlight

  // Set the buzzer pin as an output so it can be turned on or off
  pinMode(BUZZER_PIN, OUTPUT);

  // Start serial communication to print values for debugging
  Serial.begin(115200); // Set baud rate to 115200 (speed of communication)

  // Display "Normal Day!" at startup on the LCD
  displayMessage("Normal Day!"); // Shows "Normal Day!" initially
}

// Loop function runs continuously after setup
void loop() {
  // Step 1: Read the sensor value (measures water level)
  int sensorValue = analogRead(SENSOR_PIN); // Get the value from the sensor
  Serial.println(sensorValue);              // Print the sensor value to the serial monitor

  // Step 2: Check if the sensor value is below the threshold (indicates water is present)
  if (sensorValue < THRESHOLD) { // Water detected (low sensor value)
    if (!buzzerOn) {             // If the buzzer is off, turn it on
      digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer
      buzzerOn = true;                // Update buzzer status to "on"
      displayMessage("FLOOD DETECTED!"); // Show warning message on LCD and serial
    }
  } 
  // Step 3: Check if the sensor value is above the threshold (no water detected)
  else { // No water detected (high sensor value)
    if (buzzerOn) {              // If the buzzer is on, turn it off
      digitalWrite(BUZZER_PIN, LOW);  // Turn off the buzzer
      buzzerOn = false;               // Update buzzer status to "off"
      displayMessage("Normal Day!");  // Show normal message on LCD and serial
    }
  }

  // Step 4: Add a short delay for system stability
  delay(10); // Delay of 10 milliseconds to prevent too frequent updates
}

// Function to display a message on the LCD and print it to the serial monitor
void displayMessage(const char* message) {
  lcd.clear();         // Clear any previous message on the LCD
  lcd.setCursor(0, 0); // Set the cursor to the first line, first column
  lcd.print(message);  // Display the given message on the LCD
  Serial.println(message); // Also print the message to the serial monitor
}
// End of Code
