/*
*       COMP340 - Operating Systems
*       Assignment 2
*       Group 4
*/

#ifndef HEADER_DISPLAY
#define HEADER_DISPLAY

#define WIDTH 10
#define HEIGHT 10

void set(char buf[HEIGHT][WIDTH], int, int, char);
void fill(char buf[HEIGHT][WIDTH]);
void display(char buf[HEIGHT][WIDTH]);
void copy_frame(char[], char buf[HEIGHT][WIDTH]);

#endif
