#include <stdio.h>
#include "cards.h"
#include "deck.h"
#include "player_hand.h"
#include "player.h"
#include "game.h"
#include <unistd.h>

int main() {
    Game game;
    char player_names[2][32] = {"Alice", "Bob"}; // test with 2 players first

    init_game(&game, 2, player_names);

    printf("UNO Game started with %d players!\n", game.num_players);

    // Show starting hands
    for (int i = 0; i < game.num_players; i++) {
        printf("\nPlayer %d (%s) starting hand:\n", game.players[i].id, game.players[i].name);
        display_hand(&(game.players[i].hand));
    }

    // Game loop
    int winner = -1;
    sleep(2);
    while (winner == -1) {
        sleep(1);
        printf("\033[2J\033[H");
        player *current = get_current_player(&game);

        printf("\n=============================\n");
        printf("It's %s's turn!\n", current->name);

        // Print top of discard pile
        Card top = game.discard_pile.cards[game.discard_pile.top - 1];
        printf("Top of discard pile: %s %s", color_to_string(top.color), type_to_string(top.type));
        if (top.type == Number) {
            printf(" %d", top.number);
        }
        printf("\n");

        // Player plays
        int status = play_card(&game, current);

        if (status == 2) { // 2 means current player won
            winner = current->id;
            break;
        }

        // Next turn
        next_turn(&game);
    }

    printf("\n=============================\n");
    printf("🎉 Winner is %s!\n", game.players[winner].name);

}
