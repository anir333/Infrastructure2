# Infrastructure Portfolio README - Term 4 - Anir Aoulad Haddou Saddik - ACS104A - 2023/24

## What you'll find in my portfolio:

1. All Weekly Exercises Completed
2. All Weekly Projects Completed
3. All libraries necessary
4. Final PROJECT

- **Tree Structure**

    ```
    Repository Root
    │
    ├── README file (this)
    │
    ├── ALL LIBRARIES
    │   └── lib
    │       ├── ADC&Timer lib
    │       ├── Buttons lib
    │       ├── Buzzer lib
    │       ├── Display lib
    │       ├── LEDs lib
    │       ├── USART lib
    │       └── LCD (C) lib
    │
    ├── FINAL PROJECT
    │   └── src
    │       └── main.c
    │
    └── WEEKLY ASSIGNMENTS
        ├── WEEK 1
        ├── WEEK 2
        ├── WEEK 3
        └── WEEK 4
            ├── Weekly Exercises
            └── Weekly Projects
    ```


# All Libraries
- **Contains all my personal libraries developed during the semester and other ones used (usart/LCD)**
  - **LEDs**
    - Contains functions to enable LEDs, light up and down LEDs and much more...
  - **Buttons**
    - Contains functions to enable Buttons, to enable Button interrupts and more...
  - **ADC&Timer**
    - Contains functions to initialize the ADC and timer functions
  - **Display**
    - Contains provided and personalized functions to control the 8 segment display
  - **Buzzer**
    - Contains functions to initialize the Buzzer for output and play tones























- Final Project: Piano Tiles; by Anir Aoulad Haddou Saddik - ACS104A
---

# Piano Tiles Game using Arduino

## Overview

This project is an implementation of a Piano Tiles game using an Arduino, an LCD display, and an expansion shield with various components. The game involves pressing buttons corresponding to the tiles displayed on the LCD screen within a certain time limit. It also includes a melody that plays during the game and updates the score based on the player's performance.

## Features

- **LCD Display**: Shows the game tiles and game status.
- **Button Detection**: Detects button presses to interact with the game.
- **Buzzer**: Plays melodies and sound effects.
- **LED Control**: Indicates game status and button presses.
- **8-Segment Display**: Shows game speed and score.
- **ADC (Potentiometer)**: Used to select game speed.
- **Timers and Interrupts**: Manages game timing and button press detection.
- **Serial Communication**: Logs game data for debugging.

## Components

- Arduino Uno
- LCD Display
- Expansion Shield
- Buttons (S1, S2, S3)
- LEDs (D1 - D4)
- Buzzer
- 8-Segment Display
- Potentiometer

## Libraries Used

- `util/delay.h`
- `usart.h`
- `stdlib.h`
- `stdio.h`
- `string.h`
- `avr/io.h`
- `avr/interrupt.h`
- `LCD.h`
- `LEDs.h`
- `button.h`
- `buzzer.h`
- `registersLib.h`
- `display.h`

## Project Structure

- **main.c**: The main file containing the game logic.
- **Libraries**:
  - `LCD.h` and `LCD.c`: Functions to control the LCD display.
  - `LEDs.h` and `LEDs.c`: Functions to control the LEDs.
  - `button.h` and `button.c`: Functions to handle button inputs.
  - `buzzer.h` and `buzzer.c`: Functions to control the buzzer.
  - `registersLib.h` and `registersLib.c`: Functions for timers and ADC.
  - `display.h` and `display.c`: Functions to control the 8-segment display.

## Functionality

### Game Initialization

1. **Initial Setup**: Initialize LCD, 8-segment display, ADC, LEDs, buttons, and button interrupts.
2. **Wait for Start**: Display "Play Piano Tiles" on LCD and "PLAY" on the 8-segment display. Wait for button S1 to start the game.

### Game Start

1. **Speed Selection**: Use the potentiometer to select game speed. Display the selected speed on the LCD and 8-segment display.
2. **Play Game**: Generate random tiles on the LCD, check button presses, update the score, play sounds, and update the 8-segment display with time and score.

### Game End

1. **End Conditions**: Game ends when time is up or score is 0 (if enabled by macro).
2. **Memory Management**: Free allocated memory for game data.
3. **Display Result**: Show final score and time on the LCD and 8-segment display.

## Macros

- `ALLOW_END_GAME`: Enable/disable game end conditions.
- `MAKE_SOUND`: Enable/disable buzzer sound.
- `EMPTY_DIGIT`: Used to turn off digits on the 8-segment display.
- `SPEED1 - SPEED5`: Define the speed of the game based on potentiometer input.
- `MAX_ROW_LENGTH`: Maximum number of characters per row on the LCD.
- `TILE1`, `TILE2`, `TILE3`, `EMPTY_TILE`: Characters representing tiles on the LCD.

## Melody

Predefined melodies are stored as arrays of notes. One of the melodies is chosen randomly at the start of the game and 
































# Infrastructure Portfolio README - Term 4 - Anir Aoulad Haddou Saddik - ACS104A - 2023/24

## What you'll find in my portfolio:

1. All Weekly Exercises Completed
2. All Weekly Projects Completed
3. All libraries neccesary
4. Final PROJECT

- **Tree Structure** 
```
    Root Directory
    │
    ├── README file (this)
    │
    ├── ALL LIBRARIES
    │   └── lib
    │       ├── ADC&Timer lib
    │       ├── Buttons lib
    │       ├── Buzzer lib
    │       ├── Display lib
    │       ├── LEDs lib
    │       ├── USART lib
    │       └── LCD (C) lib
    │
    ├── FINAL PROJECT
    │   └── src
    │       └── main.c
    │
    └── WEEKLY ASSIGNMENTS
        ├── WEEK 1
        ├── WEEK 2
        ├── WEEK 3
        └── WEEK 4
            ├── Weekly Exercises
            └── Weekly Projects
    ```



- Final Project: Piano Tiles; by Anir Aoulad Haddou Saddik - ACS104A
---

# Piano Tiles Game using Arduino




## Overview

This project is an implementation of a Piano Tiles game using an Arduino, an LCD display, and an expansion shield with various components. The game involves pressing buttons corresponding to the tiles displayed on the LCD screen within a certain time limit. It also includes a melody that plays during the game and updates the score based on the player's performance.

## Features

- **LCD Display**: Shows the game tiles and game status.
- **Button Detection**: Detects button presses to interact with the game.
- **Buzzer**: Plays melodies and sound effects.
- **LED Control**: Indicates game status and button presses.
- **8-Segment Display**: Shows game speed and score.
- **ADC (Potentiometer)**: Used to select game speed.
- **Timers and Interrupts**: Manages game timing and button press detection.
- **Serial Communication**: Logs game data for debugging.

## Components

- Arduino Uno
- LCD Display
- Expansion Shield
- Buttons (S1, S2, S3)
- LEDs (D1 - D4)
- Buzzer
- 8-Segment Display
- Potentiometer

## Libraries Used

- `util/delay.h`
- `usart.h`
- `stdlib.h`
- `stdio.h`
- `string.h`
- `avr/io.h`
- `avr/interrupt.h`
- `LCD.h`
- `LEDs.h`
- `button.h`
- `buzzer.h`
- `registersLib.h`
- `display.h`

## Project Structure

- **main.c**: The main file containing the game logic.
- **Libraries**:
  - `LCD.h` and `LCD.c`: Functions to control the LCD display.
  - `LEDs.h` and `LEDs.c`: Functions to control the LEDs.
  - `button.h` and `button.c`: Functions to handle button inputs.
  - `buzzer.h` and `buzzer.c`: Functions to control the buzzer.
  - `registersLib.h` and `registersLib.c`: Functions for timers and ADC.
  - `display.h` and `display.c`: Functions to control the 8-segment display.

## Functionality

### Game Initialization

1. **Initial Setup**: Initialize LCD, 8-segment display, ADC, LEDs, buttons, and button interrupts.
2. **Wait for Start**: Display "Play Piano Tiles" on LCD and "PLAY" on the 8-segment display. Wait for button S1 to start the game.

### Game Start

1. **Speed Selection**: Use the potentiometer to select game speed. Display the selected speed on the LCD and 8-segment display.
2. **Play Game**: Generate random tiles on the LCD, check button presses, update the score, play sounds, and update the 8-segment display with time and score.

### Game End

1. **End Conditions**: Game ends when time is up or score is 0 (if enabled by macro).
2. **Memory Management**: Free allocated memory for game data.
3. **Display Result**: Show final score and time on the LCD and 8-segment display.

## Macros

- `ALLOW_END_GAME`: Enable/disable game end conditions.
- `MAKE_SOUND`: Enable/disable buzzer sound.
- `EMPTY_DIGIT`: Used to turn off digits on the 8-segment display.
- `SPEED1 - SPEED5`: Define the speed of the game based on potentiometer input.
- `MAX_ROW_LENGTH`: Maximum number of characters per row on the LCD.
- `TILE1`, `TILE2`, `TILE3`, `EMPTY_TILE`: Characters representing tiles on the LCD.

## Melody

Predefined melodies are stored as arrays of notes. One of the melodies is chosen randomly at the start of the game and played during the game.

## Usage

1. **Setup**: Connect all components to the Arduino as per the circuit diagram.
2. **Upload Code**: Upload the code to the Arduino using your preferred method (e.g., AVRDUDE).
3. **Play**: Start the game by pressing S1. Select speed using the potentiometer and press S1 again to start the game.

## Notes

- The game logic heavily relies on timers and interrupts for real-time functionality.
- Ensure all components are correctly connected to avoid any malfunction.
- The project code does not use the `arduino.h` library as per the course requirements.

## Acknowledgments

- This project was developed as part of the Infrastructure 2 course.
- Special thanks to the instructors and peers for their guidance and support.
