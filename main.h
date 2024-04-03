#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

// TODO: Create any necessary structs

/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/

struct player {
    const u16 *image;
    int row;
    int col;
};

struct target {
    int row;
    int col;
};

struct box {
    int row;
    int col;
    int size;
    int velRow;
};

#endif
