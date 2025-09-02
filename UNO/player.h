#ifndef PLAYER_H
#define PLAYER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "player_hand.h"
#include "deck.h"

typedef struct player{
    int id ; 
    char name[32] ;
    hand hand ;
}player;

void init_player(player *p , char *p_name){
    static int n_id = 0;
    p->id = n_id++ ;
    strcpy(p->name , p_name);
    init_hand(&(p->hand));
}

void init_card_draw(player * p , Deck *deck){
    for(int i = 0 ; i < 7 ; i ++){
        add_card(&(p->hand) , deck);
    }
}

#endif