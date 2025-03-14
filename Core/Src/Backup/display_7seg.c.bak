// This file contains code, authored by Amir, to drive the HT16K33 display
#include "main.h"

#define HT16K33_ADDRESS 0x70 << 1 // Shift left for HAL I2C

// Function prototypes
void HT16K33_Init();
void HT16K33_DisplayInteger(int number);


// Array for 7 segment digits
uint8_t digitToSegment[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

// Initialize the I2C display
void HT16K33_Init() {
    uint8_t command;

    // Turn on the oscillator
    command = 0x21; // System setup command
    HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDRESS, &command, 1, HAL_MAX_DELAY);

    // Set brightness (e.g., medium brightness level)
    command = 0xE7; // Brightness 7/15
    HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDRESS, &command, 1, HAL_MAX_DELAY);

    // Enable display
    command = 0x81; // Display on, no blinking
    HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDRESS, &command, 1, HAL_MAX_DELAY);
}




// Function to display an integer (max 4 digits)
void HT16K33_DisplayInteger(int number) {
    uint8_t displayBuffer[10] = {0}; // Initialize all positions to 0 (clear display)
    int position;

    // Handle the case when number is 0 (to avoid blank display)
    if (number == 0) {
        displayBuffer[8] = digitToSegment[0]; // Right-most position for "0"
    } else {
        // Extract digits into an array
        int digits[4] = {0}; // Array to hold up to 4 digits
        int count = 0;

        while (number > 0 && count < 4) {
            digits[count++] = number % 10; // Extract digits in reverse order
            number /= 10;
        }

        // Map the digits to the correct display buffer indices
        for (position = 0; position < count; position++) {
            int bufferIndex;

            // Determine the correct buffer index based on position
            switch (position) {
                case 0: bufferIndex = 8; break; // Right-most digit
                case 1: bufferIndex = 6; break; // Third digit
                case 2: bufferIndex = 2; break; // Second digit
                case 3: bufferIndex = 0; break; // Left-most digit
                default: continue; // Should not happen for 4 digits
            }

            displayBuffer[bufferIndex] = digitToSegment[digits[position]];
        }
    }

    // Send the updated buffer to the HT16K33
    HAL_I2C_Mem_Write(&hi2c1, HT16K33_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, displayBuffer, 10, HAL_MAX_DELAY);
}
