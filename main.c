#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "images/game_background.h"
#include "images/buzz2.h"
#include "images/victory.h"
#include "images/buzz_start.h"
#include "images/sad_buzz.h"
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  START,
  PLAY,
  WIN,
  LOSE,
};

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;
  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;

  struct player buzzSprite;
  buzzSprite.col = 12;
  buzzSprite.row = 15;
  buzzSprite.image = buzz2;

  struct box b1;
  b1.row = 15;
  b1.col = 40;
  b1.size = 10;
  b1.velRow = 3;

  struct box b2;
  b2.row = 135;
  b2.col = 60;
  b2.size = 10;
  b2.velRow = -3;

  struct box b3;
  b3.row = 15;
  b3.col = 80;
  b3.size = 10;
  b3.velRow = 3;

  struct box b4;
  b4.row = 135;
  b4.col = 100;
  b4.size = 10;
  b4.velRow = -3;

  struct box b5;
  b5.row = 15;
  b5.col = 120;
  b5.size = 10;
  b5.velRow = 3;

  struct box b6;
  b6.row = 135;
  b6.col = 140;
  b6.size = 10;
  b6.velRow = -3;

  struct box b7;
  b7.row = 125;
  b7.col = 150;
  b7.size = 10;
  b7.velRow = 1;

  struct box b8;
  b8.row = 100;
  b8.col = 200;
  b8.size = 10;
  b8.velRow = 1;

  struct box b9;
  b9.row = 75;
  b9.col = 150;
  b9.size = 10;
  b9.velRow = 1;

  struct box b10;
  b10.row = 50;
  b10.col = 200;
  b10.size = 10;
  b10.velRow = 1;

  struct box goal;
  goal.row = 80;
  goal.col = 215;
  goal.size = 10;

  int startText;
  startText = 0;

  int failText;
  failText = 0;

  int winThing;
  winThing = 0;

  int playVal;
  playVal = 0;

  int time;
  time = 0;

  int counter;
  counter = 0;

  int collisionDetect(struct player p, struct box b);

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw
    waitForVBlank();

    switch (state) {
      case START:
        waitForVBlank();
        waitForVBlank();
        if (startText == 0) {
          fillScreenDMA(BLACK);
          drawFullScreenImageDMA(buzz_start);
          drawString(50, 30, "Press enter to start", GREEN);
          drawString(70, 30, "Make it before the timer hits 10", GREEN);
          buzzSprite.col = 12;
          buzzSprite.row = 15;
          startText += 1;
        }
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          playVal = 0;
          state = PLAY;
        }
        // state = ?
        break;
      case PLAY:
        //drawFullScreenImageDMA(game_background);
        if (playVal == 0) {
          fillScreenDMA(BLACK);
          drawRectDMA(goal.row, goal.col, goal.size, goal.size, GREEN);
          playVal += 1;
        }

        drawString(20, 180, "Time: ", GREEN);
        drawChar(20, 220, time + 48, BLACK);
        counter += 1;
        if (counter % 100 == 0) {
          time += 1;
        }

        if (time > 9) {
          failText = 0;
          state = LOSE;
        }

        drawRectDMA(buzzSprite.row, buzzSprite.col, BUZZ2_WIDTH, BUZZ2_HEIGHT, BLACK);
        drawRectDMA(b1.row, b1.col, b1.size, b1.size, BLACK);
        drawRectDMA(b2.row, b2.col, b2.size, b2.size, BLACK);
        drawRectDMA(b3.row, b3.col, b3.size, b3.size, BLACK);
        drawRectDMA(b4.row, b4.col, b4.size, b4.size, BLACK);
        drawRectDMA(b5.row, b5.col, b5.size, b5.size, BLACK);
        drawRectDMA(b6.row, b6.col, b6.size, b6.size, BLACK);
        drawRectDMA(b7.row, b7.col, b7.size, b7.size, BLACK);
        drawRectDMA(b8.row, b8.col, b8.size, b8.size, BLACK);
        drawRectDMA(b9.row, b9.col, b9.size, b9.size, BLACK);
        drawRectDMA(b10.row, b10.col, b10.size, b10.size, BLACK);
        drawChar(20, 220, time + 48, GREEN);

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          startText = 0;
          time = 0;
          counter = 0;
          state = START;
        }
        if (KEY_DOWN(BUTTON_DOWN, currentButtons)) {
          if (buzzSprite.row + 5 > 140) {
            buzzSprite.row = 142;
          } else {
            buzzSprite.row += 1;
          }
        }
        if (KEY_DOWN(BUTTON_UP, currentButtons)) {
          if (buzzSprite.row - 5 < 10) {
            buzzSprite.row = 10;
          } else {
            buzzSprite.row -= 1;
          }
        }
        if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
          if (buzzSprite.col - 5 < 0) {
            buzzSprite.col = 5;
          } else {
            buzzSprite.col -= 1;
          }
        }
        if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
          if (buzzSprite.col + 5 > 220) {
            buzzSprite.col = 220;
          } else {
            buzzSprite.col += 1;
          }
        }

        if (b1.row > 140) {
          b1.velRow = (-1 * b1.velRow);
        }
        if (b1.row < 10) {
          b1.velRow = (-1 * b1.velRow);
        }

        if (b2.row > 140) {
          b2.velRow = (-1 * b2.velRow);
        }
        if (b2.row < 10) {
          b2.velRow = (-1 * b2.velRow);
        }

        if (b3.row > 140) {
          b3.velRow = (-1 * b3.velRow);
        }
        if (b3.row < 10) {
          b3.velRow = (-1 * b3.velRow);
        }

        if (b4.row > 140) {
          b4.velRow = (-1 * b4.velRow);
        }
        if (b4.row < 10) {
          b4.velRow = (-1 * b4.velRow);
        }

        if (b5.row > 140) {
          b5.velRow = (-1 * b5.velRow);
        }
        if (b5.row < 10) {
          b5.velRow = (-1 * b5.velRow);
        }

        if (b6.row > 140) {
          b6.velRow = (-1 * b6.velRow);
        }
        if (b6.row < 10) {
          b6.velRow = (-1 * b6.velRow);
        }

        if (b7.col < 150) {
          b7.velRow *= -1;
        }
        if (b7.col > 200) {
          b7.velRow *= -1;
        }

        if (b8.col < 150) {
          b8.velRow *= -1;
        }
        if (b8.col > 200) {
          b8.velRow *= -1;
        }

        if (b9.col < 150) {
          b9.velRow *= -1;
        }
        if (b9.col > 200) {
          b9.velRow *= -1;
        }

        if (b10.col < 150) {
          b10.velRow *= -1;
        }
        if (b10.col > 200) {
          b10.velRow *= -1;
        }

        b1.row += b1.velRow;
        b2.row += b2.velRow;
        b3.row += b3.velRow;
        b4.row += b4.velRow;
        b5.row += b5.velRow;
        b6.row += b6.velRow;
        b7.col += b7.velRow;
        b8.col += b8.velRow;
        b9.col += b9.velRow;
        b10.col += b10.velRow;
        

        if (collisionDetect(buzzSprite, b1)) {
          buzzSprite.row = 15;
          buzzSprite.col = 12;
          state = LOSE;
        }

        if (collisionDetect(buzzSprite, b2)) {
          buzzSprite.row = 15;
          buzzSprite.col = 12;
          state = LOSE;
        }

        if (collisionDetect(buzzSprite, b3)) {
          buzzSprite.row = 15;
          buzzSprite.col = 12;
          state = LOSE;
        }

        if (collisionDetect(buzzSprite, b4)) {
          buzzSprite.row = 15;
          buzzSprite.col = 12;
          state = LOSE;
        }

        if (collisionDetect(buzzSprite, b5)) {
          buzzSprite.row = 15;
          buzzSprite.col = 12;
          state = LOSE;
        }

        if (collisionDetect(buzzSprite, b6)) {
          buzzSprite.row = 15;
          buzzSprite.col = 12;
          state = LOSE;
        }

        if (collisionDetect(buzzSprite, b7)) {
          buzzSprite.row = 15;
          buzzSprite.col = 12;
          state = LOSE;
        }

        if (collisionDetect(buzzSprite, b8)) {
          buzzSprite.row = 15;
          buzzSprite.col = 12;
          state = LOSE;
        }

        if (collisionDetect(buzzSprite, b9)) {
          buzzSprite.row = 15;
          buzzSprite.col = 12;
          state = LOSE;
        }

        if (collisionDetect(buzzSprite, b10)) {
          buzzSprite.row = 15;
          buzzSprite.col = 12;
          state = LOSE;
        }

        drawImageDMA(buzzSprite.row, buzzSprite.col, BUZZ2_WIDTH, BUZZ2_HEIGHT, buzz2);
        drawRectDMA(b1.row, b1.col, b1.size, b1.size, RED);
        drawRectDMA(b2.row, b2.col, b2.size, b2.size, RED);
        drawRectDMA(b3.row, b3.col, b3.size, b3.size, RED);
        drawRectDMA(b4.row, b4.col, b4.size, b4.size, RED);
        drawRectDMA(b5.row, b5.col, b5.size, b5.size, RED);
        drawRectDMA(b6.row, b6.col, b6.size, b6.size, RED);
        drawRectDMA(b7.row, b7.col, b7.size, b7.size, RED);
        drawRectDMA(b8.row, b8.col, b8.size, b8.size, RED);
        drawRectDMA(b9.row, b9.col, b9.size, b9.size, RED);
        drawRectDMA(b10.row, b10.col, b10.size, b10.size, RED);

        if (collisionDetect(buzzSprite, goal)) {
          winThing = 0;
          state = WIN;
        }
        // state = ?
        break;
      case WIN:
        if (winThing == 0) {
          drawFullScreenImageDMA(victory);
          waitForVBlank();
          drawString(50, 50, "YOU WIN!", GREEN);
          drawString(70, 50, "Press Backspace to play again!", GREEN);
          winThing += 1;
        }
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          undrawImageDMA(1,1,240,260,BLACK);
          buzzSprite.row = 15;
          buzzSprite.col = 12;
          winThing = 0;
          startText = 0;
          time = 0; 
          counter = 0;
          state = START;
        }
        // state = ?
        break;
      case LOSE:
        if (failText == 0) {
          drawFullScreenImageDMA(sad_buzz);
          drawString(50, 50, "You Lose", GREEN);
          drawString(70, 50, "Press Backspace to try again!", GREEN);
          failText += 1;
        }
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          startText = 0;
          failText = 0;
          time = 0;
          counter = 0;
          state = START;
        }

        // state = ?
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}

int collisionDetect(struct player p, struct box b) {
  return p.col < b.col + b.size &&
  p.col + BUZZ2_WIDTH > b.col &&
  p.row < b.row + b.size &&
  p.row + BUZZ2_HEIGHT > b.row;
}