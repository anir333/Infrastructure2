# Infrastructure Portfolio README - Term 4 - Anir Aoulad Haddou Saddik - ACS104A - 2023/24

## What you'll find in my portfolio:

1. All Weekly Exercises Completed
2. All Weekly Projects Completed
3. All libraries necessary with extra functions I added for personal use
4. Final PROJECT completed

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



# FINAL PROJECT
## Piano Tiles Game with an LCD display

- **Overview**
  - This project is an implementation of a Piano Tiles game using an Arduino, an LCD display, and an expansion shield with various components. The game involves pressing buttons corresponding to the tiles displayed on the LCD screen within a certain time limit. It also includes a melody that plays during the game and updates the score based on the player's performance.

- **Materials**
  1. Arduino UNO
  2. Multifunctional Expansion Shield
  3. Small and Long Breadboard
  4. Buttons (on expansion shield)
  5. Potentiometer
  6. LCD display 16x2 // two rows of 16 segments each
  7. One Resistor for the LCD display LED
  9. Jump Wires
  10. Buzzer


## Features

- **LCD Display**: Shows the game tiles as they move downwards.
- **Button Detection**: Detects button presses to interact with the game tiles.
- **Buzzer**: Plays melodies and error sound effects during the game.
- **LED Control**: Indicates button presses (correct/wrong).
- **8-Segment Display**: Shows the time left for the game in seconds and the score.
- **ADC (Potentiometer)**: Used to select game speed.
- **Timers and Interrupts**: Manages game timing and button press detection.
- **Serial Communication**: Logs game data at the end with JavaFX UI.


## Libraries Used

- `util/delay.h`
- `usart.h`
- `stdlib.h`
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

1. **Speed Selection**: Use the potentiometer to select game speed. Display the selected speed on the LCD and 8-segment display, click S1 to start the game.
2. **Play Game**: Generate random tiles on the LCD, check button presses, update the score, play sounds, and update the 8-segment display with time and score.

## Melody

Predefined melodies are stored as arrays of notes. One of the melodies is chosen randomly at the start of the game and 


### Game End

1. **End Conditions**: Game ends when time is up or score is 0 (if enabled by macro).
2. **Memory Management**: Dynamically allocated memory for game data.
3. **Display Result**: Show final score and result on the LCD and 8-segment display.
4. **LEDs dance**: LEDs move forward (dancing) on and off.



## How the game Works:
1. First a play game screen appears
2. Once user has clicked button 1 he has to decide speed of game with potentiometer
3. Once S1 clicked again, the game starts, defualt time = 60 seconds and default score = 90
4. The tiles are randomly generated at the speed chosen previosuly
5. As the tiles move downwards the player must click on the button that belongs to the row of the lowest tile
6. If wrong button clicked, -10 points are deducted from score and an error sound is played by the buzzer
7. If tiles reach the bottom, for each tile with no button click, the score is reduced by -5 points
8. If the correct  button is clicked a melody plays the next sound available to it
9. If the time ends (60 seconds) and the player still has a score bigger than 0, the player won the game
10. If the score reaches 0 before the time of the game is up, the player loses
11. The information of the game is shown via the serial monitor by using JavaFX


## Pictures at start and during the game
![alt text](<WhatsApp Image 2024-06-06 at 23.45.22.jpeg>)

![alt text](<WhatsApp Image 2024-06-06 at 23.45.23.jpeg>)

![alt text](<WhatsApp Image 2024-06-06 at 23.45.24.jpeg>)

![alt text](<WhatsApp Image 2024-06-06 at 23.45.25.jpeg>)

![alt text](<WhatsApp Image 2024-06-06 at 23.45.26.jpeg>)



## Game End Picture of results in JavaFX:
![alt text](<Screenshot from 2024-06-06 21-02-32.png>)






