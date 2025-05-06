#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "sorting_hat_model.h"  // ML Model

// OLED Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button Pins
#define BUTTON_A  13  // Button for Answer A
#define BUTTON_B  12  // Button for Answer B
#define BUTTON_C  14  // Button for Answer C
#define BUTTON_D  27  // Button for Answer D

// Sorting Hat Questions
const char* questions[] = {
    "1. How do you respond when others are in danger?",
    "2. What’s your favorite type of puzzle?",
    "3. How far would you go for a friend?",
    "4. What motivates you the most?",
    "5. How do you prefer to spend free time?",
    "6. How competitive are you?",
    "7. Do you take risks?",
    "8. What kind of work do you enjoy?",
    "9. Do you follow your instincts or logic?",
    "10. What do you value most?"
};

// Answer Options
const char* options[][4] = {
    {"A) Stay safe", "B) Call help", "C) Help directly", "D) Rush in first"},
    {"A) None", "B) Word puzzles", "C) Logic puzzles", "D) Abstract problems"},
    {"A) Not far", "B) Depends", "C) Pretty far", "D) All the way"},
    {"A) Comfort", "B) Success", "C) Respect", "D) Power"},
    {"A) Alone", "B) With friends", "C) Exploring", "D) Learning"},
    {"A) Not at all", "B) Somewhat", "C) Very", "D) Must win"},
    {"A) Never", "B) Sometimes", "C) Often", "D) Always"},
    {"A) Fast-paced", "B) Collaborative", "C) Challenging", "D) Creative"},
    {"A) Instinct", "B) Gut + logic", "C) Logic", "D) Pure logic"},
    {"A) Bravery", "B) Loyalty", "C) Wit", "D) Ambition"}
};

// Store user responses (1-4)
int responses[10] = {0};
int questionIndex = 0;  // Current question index

// Initialize Machine Learning Model
Eloquent::ML::Port::DecisionTree clf;

void setup() {
    Serial.begin(115200);

    // Initialize OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println("SSD1306 allocation failed");
        for (;;);
    }
    display.clearDisplay();

    // Welcome Message
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 10);
    display.println("Sorting Hat Ready!");
    display.display();
    delay(2000);

    // Initialize buttons as input
    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);
    pinMode(BUTTON_D, INPUT_PULLUP);

    // Show the first question
    showQuestion();
}

void loop() {
    checkButtons();// Check for user input
}

// Function to display questions on OLED
void showQuestion() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(questions[questionIndex]);
    
    // Display answer choices
    for (int i = 0; i < 4; i++) {
        display.setCursor(10, 20 + (i * 10));
        display.println(options[questionIndex][i]);
    }

    display.display();
}

// Function to check button presses and record response
// Your should complete this function to handle button presses
void checkButtons() {
    bool answered = false;

    while (!answered) {
        if (digitalRead(BUTTON_A) == LOW) {
            responses[questionIndex] = 1;
            answered = true;
        }
        else if (digitalRead(BUTTON_B) == LOW) {
            responses[questionIndex] = 2;
            answered = true;
        }
        else if (digitalRead(BUTTON_C) == LOW) {
            responses[questionIndex] = 3;
            answered = true;
        }
        else if (digitalRead(BUTTON_D) == LOW) {
            responses[questionIndex] = 4;
            answered = true;
        }

        if (answered) {
            delay(200);  // Debounce delay
            nextQuestion();
        }

        delay(20);  // Polling interval
    }
}


// Move to the next question or classify the house
void nextQuestion() {
    questionIndex++;
    if (questionIndex < 10) {
        showQuestion();  // Show next question
    } else {
        classifyHouse();  // Run ML model prediction
    }
}

// Function to classify the user into a Hogwarts house
void classifyHouse() {
    display.clearDisplay();
    display.setCursor(10, 10);
    display.println("Sorting...");

    // Convert responses into ML input format
    float features[] = { 
        (float)responses[0], (float)responses[1], (float)responses[2], (float)responses[3], 
        (float)responses[4], (float)responses[5], (float)responses[6], (float)responses[7], 
        (float)responses[8], (float)responses[9] 
    };

    int house = clf.predict(features);  // Use ML model

    // Display house result
    display.setCursor(10, 30);
    display.print("House: ");
    switch (house) {
        case 0: display.println("Gryffindor"); break;
        case 1: display.println("Hufflepuff"); break;
        case 2: display.println("Ravenclaw"); break;
        case 3: display.println("Slytherin"); break;
    }

    display.display();
    Serial.println("Sorting complete!");
    Serial.print("Predicted House: ");
    switch (house) {
        case 0: Serial.println("Gryffindor"); break;
        case 1: Serial.println("Hufflepuff"); break;
        case 2: Serial.println("Ravenclaw"); break;
        case 3: Serial.println("Slytherin"); break;
    }
}
