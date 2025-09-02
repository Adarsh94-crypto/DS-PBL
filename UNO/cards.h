#ifndef CARDS_H   
#define CARDS_H   

#include <stdio.h>


typedef enum {
    RED ,
    GREEN ,
    BLUE ,
    YELLOW 
}card_color ;

typedef enum {
    Number ,
    Skip ,
    Wild_draw_4 ,
    Draw_2 ,
    Reverse ,
    Wild 
}card_type ;

typedef struct{
    card_color color ;
    card_type type ;
    int number ;
}Card;

#endif