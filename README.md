# Chada Tech Clocks

A console clock app built with C++.

Set a starting time, then watch a 12-hour clock and a 24-hour clock update side by side as you add hours, minutes, or seconds.

*Built for CS 210 at SNHU.*

## Overview

Chada Tech Clocks was built around a fictional company scenario. The goal was a program that shows the same time in both 12-hour and 24-hour formats.

The user enters a starting time. Then a menu lets them move the time forward one hour, one minute, or one second at a time.

Both clocks update together and display inside boxed borders.

## Features

- 12-hour clock with A M / P M
- 24-hour clock
- Both clocks shown side by side
- User-set starting time
- Menu to add one hour, minute, or second
- Time rollover
  - Seconds roll into minutes
  - Minutes roll into hours
  - Hours wrap back to 0 after 23
- Input validation for bad or out-of-range entries
- Centered text inside boxed displays
- Named constants instead of magic numbers

## Menu Options

| Option | Action |
|---|---|
| **1** | Add one hour |
| **2** | Add one minute |
| **3** | Add one second |
| **4** | Exit the program |

## Example Output

```
**************************   **************************
*      12-Hour Clock     *   *      24-Hour Clock     *
*     03:22:01 P M       *   *        15:22:01        *
**************************   **************************
```

## Input Validation

The program checks every number the user enters.

If the input is not a number, or is outside the allowed range, the program asks again. Bad input cannot crash it.

Allowed ranges:

- Hours: 0 to 23
- Minutes: 0 to 59
- Seconds: 0 to 59
- Menu choice: 1 to 4

## How the Time Rolls Over

- Adding a second at 59 goes back to 0 and adds a minute
- Adding a minute at 59 goes back to 0 and adds an hour
- Adding an hour at 23 wraps back to 0

On the 12-hour clock, hours 0 and 12 both display as 12. Hours 12 to 23 show as P M.

## Project Structure

| File | Purpose |
|---|---|
| `projectOne.cpp` | Full program: input, formatting, display, and menu logic |

The code is split into small functions for input, formatting, display, and time changes.

## Requirements

- A C++ compiler (g++, clang, or Visual Studio)
- No external libraries

The program uses only the C++ standard library:

- `iostream`
- `iomanip`
- `limits`
- `sstream`
- `string`

## How to Run

Clone the repository:

```bash
git clone https://github.com/Tjordanart/chada-tech-clocks-cpp.git
```

Navigate to the project directory:

```bash
cd chada-tech-clocks-cpp
```

Compile the program:

```bash
g++ projectOne.cpp -o clocks
```

Run it:

```bash
./clocks
```

On Windows, you can also open the file in Visual Studio and run it there.

Enter a starting time, then use the menu to move the clocks forward.

## What I Practiced

This project provided practice with:

- C++ programming
- Functions and prototypes
- Pass by reference
- Constants
- Loops
- Switch statements
- User input with `cin`
- Input validation
- String formatting
- Modular program design

## Author

**Tyler Jordan**

[GitHub](https://github.com/Tjordanart)  
[Portfolio](https://www.tjordanart.com)
