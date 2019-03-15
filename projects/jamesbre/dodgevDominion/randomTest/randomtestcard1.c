// VILLAGE RANDOM TESTS
// Brendan James
// CS362 Assignment 4

// Village allows a player to draw one card and get +2 actions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../rngs.h"
#include "../dominion.h"
#include "../dominion_helpers.h"

int main(){
    int plyr = 0, i = 0, j = 0;
    struct gameState * pre = NULL, * post = NULL;

    SelectStream(0);
    PutSeed(5);

    for (i = 0; i < 100000; i++){
        // set up gamestate
        pre = malloc(sizeof(struct gameState));
        post = malloc(sizeof(struct gameState));
        // Fill post with random bytes (code source: testDrawCard.c)
        for (j = 0; j < sizeof(struct gameState); j++) {
            ((char*)post)[j] = floor(Random() * 256);
        }
        plyr = floor(Random() * MAX_PLAYERS);
        post->whoseTurn = plyr;
        post->deckCount[plyr] = floor(Random() * MAX_DECK);
        post->discardCount[plyr] = floor(Random() * (MAX_DECK - post->deckCount[plyr]));
        post->handCount[plyr] = floor(Random() * (MAX_HAND - 2));
        post->playedCardCount = 0;

        for (j = 0; j < post->deckCount[plyr]; j++){
            post->deck[plyr][j] = floor(Random() * 27); // 27 = # of different cards (from ENUM CARD in dominion.h)
        }
        for (j = 0; j < post->discardCount[plyr]; j++){
            post->discard[plyr][j] = floor(Random() * 27);
        }
        for (j = 0; j < post->handCount[plyr]; j++){
            post->hand[plyr][j] = floor(Random() * 27);
        }
        int villageLoc = floor(Random() * post->handCount[plyr]);
        post->hand[plyr][villageLoc] = 14; // Set one card in hand to village

        // copy pre gamestate from post gamestate
        memcpy(pre, post, sizeof(struct gameState));

        // run cardEffect for village
        cardEffect(14, 0, 0, 0, post, villageLoc, NULL);

        // check differences b/w pre and post
        //1. numActions in post 2 higher than pre (numActions is decremented for the card in question after cardEffect function)
        if (post->numActions != pre->numActions + 2){
            printf("TEST #%d FAILED: numActions +2 not implemented properly.\n", i + 1);
            printf("  numActions before playing Village: %d\n", pre->numActions);
            printf("  numActions after playing Village: %d\n", post->numActions);
        }
        //2. handCount the same (since draw one card but discard another)
        if (post->handCount[plyr] != pre->handCount[plyr]){
            printf("TEST #%d FAILED: handCount changed after playing village.\n", i + 1);
            printf("  Expectation is that 1 card is drawn + village is discarded, so handCount remains constant.\n");
            printf("  handCount before playing Village: %d\n", pre->handCount[plyr]);
            printf("  handCount after playing Village: %d\n", post->handCount[plyr]);
        }
        //3. playedCards one higher in post (since village is discarded)
        if (post->playedCardCount != pre->playedCardCount + 1){
            printf("TEST #%d FAILED: playedCardCount should be one higher after playing Village.\n", i + 1);
            printf("  playedCardCount before playing Village: %d\n", pre->playedCardCount);
            printf("  playedCardCount after playing Village: %d\n", post->playedCardCount);
        }
        //4. Then copy over hand, deck, discard, playedCards and make sure pre matches post (aka nothing else changed)
        pre->numActions = post->numActions;
        memcpy(pre->deck[plyr], post->deck[plyr], sizeof(int) * MAX_DECK);
        pre->deckCount[plyr] = post->deckCount[plyr];
        memcpy(pre->discard[plyr], post->discard[plyr], sizeof(int) * MAX_DECK);
        pre->discardCount[plyr] = post->discardCount[plyr];
        memcpy(pre->hand[plyr], post->hand[plyr], sizeof(int) * MAX_DECK);
        pre->handCount[plyr] = post->handCount[plyr];
        memcpy(pre->playedCards, post->playedCards, sizeof(int) * MAX_DECK);
        pre->playedCardCount = post->playedCardCount;

        if (memcmp(pre, post, sizeof(struct gameState)) != 0) { // If test failure
            printf("TEST #%d FAILED: gameState before and after playing Village doesn't match\n", i + 1);
            printf("(outside of hand/deck/discard/playedCards)");
            printf("Something that should not be affected by playing the Village card has changed.\n");
        }

        free(pre);
        free(post);
    }


    return 0;
}
