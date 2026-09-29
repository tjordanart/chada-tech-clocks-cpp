/*
 * File:    Clocks.cpp
 * Author:  Tyler
 * Course:  CS 210 - Project One
 * Purpose: Chada Tech Clocks. Shows a 12-hour clock and a 24-hour clock
 *          side by side. The user sets the start time, then uses a menu
 *          to add one hour, minute, or second, or to exit.
 */

#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

// ---------- Constants (no "magic numbers" in the code below) ----------
const int HOURS_PER_DAY = 24;
const int HOURS_PER_HALF_DAY = 12;
const int MINUTES_PER_HOUR = 60;
const int SECONDS_PER_MINUTE = 60;

const int BOX_WIDTH = 26;                 // total width of one clock box
const int BOX_TEXT_WIDTH = BOX_WIDTH - 2; // space between the two border stars
const string BOX_GAP = "   ";             // space between the two clock boxes

const int MENU_ADD_HOUR = 1;
const int MENU_ADD_MINUTE = 2;
const int MENU_ADD_SECOND = 3;
const int MENU_EXIT = 4;

// ---------- Function prototypes ----------
int GetIntInRange(const string& prompt, int minValue, int maxValue);
void GetInitialTime(int& hours, int& minutes, int& seconds);
string TwoDigits(int value);
string FormatTime12(int hours, int minutes, int seconds);
string FormatTime24(int hours, int minutes, int seconds);
string CenterText(const string& text, int width);
string BuildBoxLine(const string& text);
void DisplayClocks(int hours, int minutes, int seconds);
void DisplayMenu();
void AddHour(int& hours);
void AddMinute(int& hours, int& minutes);
void AddSecond(int& hours, int& minutes, int& seconds);
void HandleChoice(int choice, int& hours, int& minutes, int& seconds);

// ---------- Input ----------

// Ask for a whole number between minValue and maxValue.
// Keeps asking until the input is valid, so bad input cannot break the program.
int GetIntInRange(const string& prompt, int minValue, int maxValue) {
    int value = 0;

    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            // Input was not a number: clear the error and throw away the bad line
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number." << endl;
        }
        else {
            // Throw away anything left on the line (for example "3abc")
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (value >= minValue && value <= maxValue) {
                return value;
            }
            cout << "Please enter a number from " << minValue
                << " to " << maxValue << "." << endl;
        }
    }
}

// Get the starting time from the user (24-hour values).
void GetInitialTime(int& hours, int& minutes, int& seconds) {
    cout << "Enter the starting time." << endl;
    hours = GetIntInRange("Hours (0-23): ", 0, HOURS_PER_DAY - 1);
    minutes = GetIntInRange("Minutes (0-59): ", 0, MINUTES_PER_HOUR - 1);
    seconds = GetIntInRange("Seconds (0-59): ", 0, SECONDS_PER_MINUTE - 1);
    cout << endl;
}

// ---------- Formatting ----------

// Turn a number into two digits, like 5 -> "05".
string TwoDigits(int value) {
    ostringstream out;
    out << setw(2) << setfill('0') << value;
    return out.str();
}

// Build the 12-hour string, like "03:22:01 P M".
string FormatTime12(int hours, int minutes, int seconds) {
    // 0 and 12 both show as 12 on a 12-hour clock
    int displayHour = hours % HOURS_PER_HALF_DAY;
    if (displayHour == 0) {
        displayHour = HOURS_PER_HALF_DAY;
    }

    // Hours 12-23 are P M, hours 0-11 are A M
    string period = (hours >= HOURS_PER_HALF_DAY) ? " P M" : " A M";

    return TwoDigits(displayHour) + ":" + TwoDigits(minutes) + ":" +
        TwoDigits(seconds) + period;
}

// Build the 24-hour string, like "15:22:01".
string FormatTime24(int hours, int minutes, int seconds) {
    return TwoDigits(hours) + ":" + TwoDigits(minutes) + ":" +
        TwoDigits(seconds);
}

// Center text inside a given width by padding with spaces.
string CenterText(const string& text, int width) {
    int totalPadding = width - static_cast<int>(text.length());
    if (totalPadding < 0) {
        totalPadding = 0;
    }
    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;

    return string(leftPadding, ' ') + text + string(rightPadding, ' ');
}

// Build one row of a clock box: "*   centered text   *".
string BuildBoxLine(const string& text) {
    return "*" + CenterText(text, BOX_TEXT_WIDTH) + "*";
}

// ---------- Display ----------

// Show both clocks side by side.
void DisplayClocks(int hours, int minutes, int seconds) {
    string border(BOX_WIDTH, '*');

    cout << border << BOX_GAP << border << endl;
    cout << BuildBoxLine("12-Hour Clock") << BOX_GAP
        << BuildBoxLine("24-Hour Clock") << endl;
    cout << BuildBoxLine(FormatTime12(hours, minutes, seconds)) << BOX_GAP
        << BuildBoxLine(FormatTime24(hours, minutes, seconds)) << endl;
    cout << border << BOX_GAP << border << endl;
    cout << endl;
}

// Show the menu.
void DisplayMenu() {
    string border(BOX_WIDTH, '*');

    cout << border << endl;
    cout << "* 1 - Add One Hour       *" << endl;
    cout << "* 2 - Add One Minute     *" << endl;
    cout << "* 3 - Add One Second     *" << endl;
    cout << "* 4 - Exit Program       *" << endl;
    cout << border << endl;
}

// ---------- Time changes ----------

// Add one hour. After 23 it wraps back to 0.
void AddHour(int& hours) {
    hours = (hours + 1) % HOURS_PER_DAY;
}

// Add one minute. After 59 it goes back to 0 and adds an hour.
void AddMinute(int& hours, int& minutes) {
    minutes = (minutes + 1) % MINUTES_PER_HOUR;
    if (minutes == 0) {
        AddHour(hours);
    }
}

// Add one second. After 59 it goes back to 0 and adds a minute.
void AddSecond(int& hours, int& minutes, int& seconds) {
    seconds = (seconds + 1) % SECONDS_PER_MINUTE;
    if (seconds == 0) {
        AddMinute(hours, minutes);
    }
}

// Do the action for the menu choice, then show both clocks again.
void HandleChoice(int choice, int& hours, int& minutes, int& seconds) {
    switch (choice) {
    case MENU_ADD_HOUR:
        AddHour(hours);
        break;
    case MENU_ADD_MINUTE:
        AddMinute(hours, minutes);
        break;
    case MENU_ADD_SECOND:
        AddSecond(hours, minutes, seconds);
        break;
    default:
        break;
    }

    DisplayClocks(hours, minutes, seconds);
}

// ---------- Main ----------

int main() {
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int choice = 0;

    GetInitialTime(hours, minutes, seconds);
    DisplayClocks(hours, minutes, seconds);

    // Loop until the user picks Exit (see the flowchart)
    do {
        DisplayMenu();
        choice = GetIntInRange("Enter your choice: ", MENU_ADD_HOUR, MENU_EXIT);
        cout << endl;

        if (choice != MENU_EXIT) {
            HandleChoice(choice, hours, minutes, seconds);
        }
    } while (choice != MENU_EXIT);

    cout << "Goodbye!" << endl;
    return 0;
}