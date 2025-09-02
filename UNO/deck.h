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
        case RED: return "RED";
        case GREEN: return "GREEN";
        case BLUE: return "BLUE";
        case YELLOW: return "YELLOW";
        default: return "UNKNOWN";
    }
}

void init_deck( Deck *deck){
    deck->size = 0 ;
    for ( card_color c = RED ; c <= YELLOW ; c = (card_color)(c+1)){
        for( int i = 0 ; i <= 9 ; i++){
            deck->cards[deck->size].color = c ;
            deck->cards[deck->size].number = i ;
            deck->cards[deck->size].type = Number ;
            deck->size ++ ;
        }
    }
    deck->top = deck -> size  ;
}

void shuffle_deck(Deck *deck){
    srand(time(NULL));
    for( int i = deck->size-1 ; i > 0 ; i --){
        int j = rand() % i ;
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp ;
    }
}


Card draw_card(Deck *deck){
    // if(deck -> size == 0){
    //     return  ;
    // }
    deck -> size -- ;
    return deck->cards[--deck->top] ;
}

#endif