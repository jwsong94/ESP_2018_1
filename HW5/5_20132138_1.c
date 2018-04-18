#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "8x8font.h"

#define BOARD_ROW 8     // board의 Row
#define PADDING 0     // 문자간의 기본간격

// HW5 : 
// 20132138
// Jungwoo Song
// Usage : gcc -Wall -W make 5_2013213_1.c -o 5_20132138_1.out


uint8_t *board[BOARD_ROW];      // board
int     board_size;

// board에 문자 writing, margin-이전 문자와의 간격
void boardWriter(int fontidx, int margin);

int main(void)
{
    char str[1000] = {'\0'};
    int length = -1;
    
    scanf("%s", str);
    length = strlen(str);

    for(int i = 0; i < length; i++){
        if(str[i] >= 'A' && str[i] <= 'Z')
            boardWriter(str[i] - 'A', 0);
        else if(str[i] >= 'a' && str[i] <= 'z')
            boardWriter(str[i] - 'a' + 26, 0);
        else if(str[i] >= '0' && str[i] <= '9')
            boardWriter(str[i] - '0' + 52, 0);
        else
            boardWriter(62, 0);
    }

    for(int i = 0 ; i < BOARD_ROW ; i++){
        for(int j = 0 ; j < board_size ; j++)
            printf("%c ", board[i][j]);
        printf("\n");
    }

    return 0;
}

void boardWriter(int fontidx, int margin)
{
    int i, j;
    static int board_offset = 0; // 현재 문자의 offset
    uint8_t mask;
    uint8_t *new_board[BOARD_ROW];

    int new_board_size = board_offset + margin + FONT_COL + PADDING;

    for(i = 0 ; i < BOARD_ROW ; i++){
        new_board[i] = (uint8_t*)calloc(1, new_board_size);
        memset(new_board[i], ' ', new_board_size);
        memcpy(new_board[i], board[i], board_size);
        free(board[i]);
        board[i] = new_board[i];
    }

    board_size = new_board_size;
    board_offset += margin;

    // writing on the board
    for(i = 0 ; i < FONT_ROW ; i++){      // row
        for(j = 0 ; j < FONT_COL ; j++){  // col
            mask = 0b1 << (7-j);
            if((mask & FONT88[fontidx][i]))
                board[i][j+board_offset] = 'o';
            else
                board[i][j+board_offset] = ' ';
        }
    }
    board_offset = board_size;;
}

