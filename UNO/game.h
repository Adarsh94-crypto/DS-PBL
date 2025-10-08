#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"

#define MAX_PLAYERS 4  

typedef struct {
    Deck draw_pile;
    Deck discard_pile;    
    Player players[MAX_PLAYERS];
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
    game->discard_pile.cards[game->discard_pile.top]=draw_card(&(game->draw_pile));
    game->discard_pile.size++;
    game->current_turn = 0 ;
    game->direction = 1 ;
}

Player* get_current_player(Game *game){
    return &(game->players[game->current_turn]);
}

void next_turn(Game *game){
    game->current_turn = (game->current_turn + game->direction + game->num_players) % game->num_players ;
}

int play_card(Game *game, Player *player){
    int draw=0;
    player = get_current_player(game);
    Card playeable[player->hand.size];
    int count = get_valid_cards(&(player->hand), game->discard_pile.cards[game->discard_pile.top],playeable);

    if(count !=  0){
        display_hand(&player->hand);
        printf("\nvalid cards : \n");
        for(int i = 0 ; i < count ; i++ ){
            printf("%d) ",i+1);
            if (playeable[i].color == COLOR_NONE) {
                printf("%s\n", type_to_string(playeable[i].type));
                continue;
            }
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
            game->discard_pile.cards[++game->discard_pile.top] = playeable[choice-1];
            game->discard_pile.size++;
            if( playeable[choice-1].type == Skip){
                printf("player skipped \n");
                next_turn(game) ;
            }else if(playeable[choice-1].type == Draw_2){
                printf("next player draw 2 cards \n");
                
                next_turn(game);

                player = get_current_player(game); 

                add_card(&player->hand,&game->draw_pile );
                add_card(&player->hand,&game->draw_pile );

                // next_turn(game);
            }else if(playeable[choice-1].type == Reverse){
                printf("table is reversed \n");
                game->direction *= -1 ;
                if (game->num_players == 2) {
                    next_turn(game);
                }
            }else if(playeable[choice-1].type == Wild){
                printf("Wild card played! Choose a color (0=Red,1=Green,2=Blue,3=Yellow): ");
                int Color;
                scanf("%d", &Color);
                game->discard_pile.cards[game->discard_pile.top].color = (card_color)Color ;
            }else if(playeable[choice-1].type == Wild_draw_4){
                printf("Wild card played! Choose a color (0=Red,1=Green,2=Blue,3=Yellow): ");
                int Color;
                scanf("%d", &Color);
                game->discard_pile.cards[game->discard_pile.top].color = (card_color)Color ;

                printf("next player (0)draw 4 cards or (1)challenge : \n");
                next_turn(game);

                Player *n_player = get_current_player(game); 

                int ch ;
                scanf("%d",&ch);
                if(ch==1){
                    int can = 0 ;
                    hand_node *temp = player->hand.head;
                    for(int i = 0 ; i < player->hand.size ; i++){
                        if(temp->card.color == game->discard_pile.cards[game->discard_pile.top].color){
                            can = 1 ;
                            break ;
                        }
                        temp = temp->next ;
                    }
                    if(can){
                        printf("challenge successfull. player draws 6 cards \n");
                        
                        for(int i = 0 ; i < 6 ; i++){
                            add_card(&player->hand,&game->draw_pile );
                        }
                    }else{
                        printf("challenge failed. player draws 4 cards \n");
                        
                        for(int i = 0 ; i < 4 ; i++){
                            add_card(&n_player->hand,&game->draw_pile );
                        }
                    }
                }else{
                    for(int i = 0 ; i < 4 ; i++){
                        add_card(&n_player->hand,&game->draw_pile );
                    }
                }
            }
        }
    }else{
        printf("\nno valid cards. Draw!!!");
        add_card(&player->hand ,&game->draw_pile);
        draw++;
    }
    if( game->draw_pile.size == 0 ){
        printf("reshuffling the discard pile into draw pile\n");
        Card top_card = game->discard_pile.cards[game->discard_pile.top];
        game->discard_pile.top--;
        game->discard_pile.size--;
        for(int i = 0 ; i < game->discard_pile.size ; i++){
            game->draw_pile.cards[i] = game->discard_pile.cards[i];
        }
        game->draw_pile.size = game->discard_pile.size ;
        game->draw_pile.top = game->draw_pile.size -1 ; 
        shuffle_deck(&game->draw_pile);
        game->discard_pile.size = 0 ;   
        game->discard_pile.top = 0 ;
        game->discard_pile.cards[game->discard_pile.top] = top_card ;
        game->discard_pile.size++ ;
    }
    if (player->hand.size == 0) {
        return 2; 
    }
    return draw ? 1 : 0;
}


#endif




