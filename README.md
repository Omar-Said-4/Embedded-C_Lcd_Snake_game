# Embedded-C_Lcd_Snake_game
## Used Tools:
- AVR atmega 32 micro controller.
- 16x2 character LCD. 
- 4 push buttons.
- One Potentiometer.
## Game Controls:
Game has 4 push buttons each one is used to move the snake in a certain direction (up-down-right-left).
(The move right and move left push buttons are used to  choose thw game difficulty initially).

## Game Description:
The snake appears initially as a single pixel on the LCD and as it eats more apples it's number of pixels increase (AKA snake length).
This Game version is based on boundaries mode where you can't move through the borders of the visual LCD display screen.
Game is over when the snake eats itself or hits one of the four walls of the LCD display.
You win the game immediately when the snake length reaches 30 (AKA number of pixels).
