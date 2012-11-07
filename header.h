#ifndef HEADER_H_
#define HEADER_H_

#define NUM_IMAGES 20

//#define ROW_NUM 15
//#define COLUMN_NUM 15

//#define X_START 10
//#define Y_START 10

// item identifiers
// Buttons will have the highest bit set to one, i.e identifier will be greater than 0x80
#define SQUARE 0x00
#define GRID   0x01
#define CHANGE_GAME_STATE_BUTTON 0x80
#define FLAG_BUTTON 0x81

// mouse stuff
#define NORMAL 0x00
#define FLAG 0x01

// Screen identifiers
#define GAME 0x00

#endif
