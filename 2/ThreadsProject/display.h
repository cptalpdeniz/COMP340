/*
*       COMP340 - Operating Systems
*       Assignment 2
*       Group 4
*       Alp Deniz Senyurt - 300203734 & Mithun Krishnaprasad 300184390 & Urvashi & Shengfu Wang
*		Please keep in mind that almost NO CODE was written by Urvashi and Shengfu Wang. We split tasks evenly and talked for days in the group chat however they were not able to deliver ANYTHING at all. I hope this is taken into consideration when assignment is marked.
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
