#ifndef DECK_H   
#define DECK_H   

#include <stdio.h>
#include "cards.h"
#include <stdlib.h>
#include <time.h>
// #include "player_hand.h"

typedef struct {
    Card cards[108] ;
    int top ;
    int size ;
}Deck;

const char* get_color_name(card_color c) {
    switch(c) {
        case COLOR_RED: return "RED";
        case COLOR_GREEN: return "GREEN";
        case COLOR_BLUE: return "BLUE";
        case COLOR_YELLOW: return "YELLOW";
        default: return "UNKNOWN";
    }
}

void init_deck( Deck *deck){
    deck->size = 0 ;
    for ( card_color c = COLOR_RED ; c <= COLOR_YELLOW ; c = (card_color)(c+1)){
        for( card_type t = Number ; t <= Reverse ; t= (card_type)(t+1)){
            for ( int j = 0 ; j  < 2 ; j++){
                if(t==Number){
                    for( int i = 0 ; i <= 9 ; i++){
                        if(j == 1 && i == 0) continue ;
                        deck->cards[deck->size].color = c ;
                        deck->cards[deck->size].number = i ;
                        deck->cards[deck->size].type = Number ;
                        deck->size ++ ;
                    }
                }else if( t != Wild_draw_4 && t != Wild){               
                    deck->cards[deck->size].color = c ;
                    deck->cards[deck->size].type = t ;
                    deck->size ++ ;
                }
            }
        }
    }
    for( card_type t = Wild_draw_4 ; t <= Wild ; t = (card_type)(t+1)){
        for( int i = 0 ; i <= 3 ; i ++){
            deck->cards[deck->size].color = COLOR_NONE ;
            deck->cards[deck->size].type = t ;
            deck->size ++ ;
        }                        
    }
    deck->top = deck -> size -1 ;
}

void shuffle_deck(Deck *deck){
    srand(time(0));
    //knuth shuffle
    for( int i = deck->size-1 ; i > 0 ; i --){
        int j = rand() % i ;
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp ;
    }
}

Card draw_card(Deck *deck){
    deck -> size -- ;
    return deck->cards[--deck->top] ;
}


#endif