# Arduino_lab_project_1_multigames

Game Description:

  The game consists in 3 games, from whom only 2 are available in the free version and only 1 entirely.
The games available for free trial are Snake and Frogger. Snake is a casual game known far and wide, thus for I will not waste time with detailed characteristics of the gameplay. Standard rules, you change the snake’s direction and eat gold/food/etc how you want to call it. From the menu you can choose from 2 options to make the game more challenging. The first option is difficulty. It’s got 3 states: 1(easiest), 2(medium), 3 (hardest). The higher the difficulty, the faster the snake moves. The second game has only 1 level available. The game consists in passing by the lights that move following a certain pattern and reaching the top and then back to the bottom without getting hit.  The difficulty works the same as does in snake.

Software & Hardware:

  The software used to program it is Arduino IDE. The program implemented consists in 3 classes and adequate functions for them. The 3 classes are: snakeBody, snake and frogger. The snake body is like a linear dynamic list, that’s why it has it’s own class unlike frogger, and has only the coordinates of the current body piece and next body piece memory allocation. The other 2 classes contain the menu and the rest of the needed gameplay through variables and functions.
 (see the MultiGames_8x8_lcd_buzzer.ino file for more details on the software)
	As for the hardware, I use the following:
- Arduino UNO (1 x piece)
- Matrix 8x8 (1 x piece)
- Driver 7219 (1 x piece)
- Buzzer (1 x piece)
- LCD (Liquid – crystal display) (1 x piece)
- Joystick (1 x piece)
- Jumper wires (as many as needed)
- Rezistors (1 x 330 Ohm, 1 x 30k Ohm, 1 x 1k Ohm)
- Capacitor (1 x 104, 1 x 100 microF)
- Breadboard (2 x pieces)
