#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"

#define MAX_PLAYERS 4  

typedef struct {
    Deck draw_pile;
    Deck discard_pile;    
    player players[MAX_PLAYERS];
    int num_players;
    int current_turn; 
    int direction;        
} Game;

void init_game(Game *game, int num_players, char player_names[][32]){
    init_deck(&(game->draw_pile));
    shuffle_deck(&(game->draw_pile));
    init_deck(&(game->discard_pile));
    game->discard_pile.size=0;
    game->discard_pile.top=0;
    game->num_players = num_players ;
    for(int i = 0 ; i < num_players ; i++){
        init_player(&(game->players[i]),player_names[i]);
        init_card_draw(&(game->players[i]),&(game->draw_pile));
    }
    game->discard_pile.cards[game->discard_pile.top++]=draw_card(&(game->draw_pile));
    game->discard_pile.size++;
    game->current_turn = 0 ;
    game->direction = 1 ;
}

player* get_current_player(Game *game){
    return &(game->players[game->current_turn]);
}

void next_turn(Game *game){
    game->current_turn = (game->current_turn + game->direction + game->num_players) % game->num_players ;
}

int play_card(Game *game, player *player){
    int draw=0;
    player = get_current_player(game);
    // printf("%s ",color_to_string(game->discard_pile.cards[game->discard_pile.top-1].color));
    // printf("%s ",type_to_string(game->discard_pile.cards[game->discard_pile.top-1].type));
    // if(game->discard_pile.cards[game->discard_pile.top].type==Number){
    //     printf("%d ",game->discard_pile.cards[game->discard_pile.top-1].number);
    // }
    Card playeable[player->hand.size];
    int count = get_valid_cards(&(player->hand), game->discard_pile.cards[game->discard_pile.top-1],playeable);

    if(count !=  0){
        display_hand(&player->hand);
        printf("\nvalid cards : \n");
        for(int i = 0 ; i < count ; i++ ){
            printf("%d) ",i+1);
            printf("%s ",color_to_string(playeable[i].color));
            printf("%s ",type_to_string(playeable[i].type));
            if(playeable[i].type==Number){
                printf("%d ",playeable[i].number);
            }
            printf("\n");
        }
        int choice ;
        printf("%d) Draw ",count+1);
        printf("\nChoose : ");
        scanf("%d",&choice);
        if(choice==count+1){ 
            add_card(&player->hand ,&game->draw_pile);
            draw++;
        }else{
            remove_card(&player->hand, playeable[choice-1]);
            game->discard_pile.cards[game->discard_pile.top++] = playeable[choice-1];
            game->discard_pile.size++;
        }
    }else{
        printf("\nno valid cards. Draw!!!");
        add_card(&player->hand ,&game->draw_pile);
        draw++;
    }
    if (player->hand.size == 0) {
        return 2; 
    }
    return draw ? 1 : 0;
}


#endif