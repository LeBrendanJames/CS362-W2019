// SMITHY RANDOM TESTS
// Brendan James
// CS362 Assignment 4

// With Smithy, a player draws 3 cards and then discards smithy

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

    for (i = 0; i < 1000; i++){
        // set up gamestate
        pre = malloc(sizeof(struct gameState));
        post = malloc(sizeof(struct gameState));
        // Fill post with random bytes (code source: testDrawCard.c)
        for (j = 0; j < sizeof(struct gameState); j++) {
            ((char*)post)[j] = floor(Random() * 256);
        }
        // Set whoseTrun + hand/deck/discard
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
        int smithyLoc = floor(Random() * post->handCount[plyr]);
        post->hand[plyr][smithyLoc] = 13; // Set one card in hand to smithy

        // copy pre gamestate from post gamestate
        memcpy(pre, post, sizeof(struct gameState));

        // run cardEffect for village
        cardEffect(13, 0, 0, 0, post, smithyLoc, NULL);

        // check differences b/w pre and post
        //1. handCount the same (since draw one card but discard another)
        if (post->handCount[plyr] != pre->handCount[plyr] + 2){ // Draw 3, discard 1, so post should = pre + 2
            printf("TEST #%d FAILED: handCount after playing Smithy is not two higher.\n", i + 1);
            printf("Should draw 3 cards + discard Smithy, leaving hand with 2 more cards.\n");
            printf("  handCount before playing Smithy: %d\n", pre->handCount[plyr]);
            printf("  handCount after playing Smithy: %d\n", post->handCount[plyr]);
        }
        //2. playedCards one higher in post (since village is discarded)
        if (post->playedCardCount != pre->playedCardCount + 1){
            printf("TEST #%d FAILED: playedCardCount not one higher after playing Smithy.\n", i + 1);
            printf("Smithy should be discarded into the playedCards pile.\n");
            printf("  playedCardCount before playing Smithy: %d\n", pre->playedCardCount);
            printf("  playedCardCount after playing Smithy: %d\n", post->playedCardCount);
        }
        //3. Then copy over hand, deck, discard, playedCards and make sure pre matches post (aka nothing else changed)
        memcpy(pre->deck[plyr], post->deck[plyr], sizeof(int) * MAX_DECK);
        pre->deckCount[plyr] = post->deckCount[plyr];
        memcpy(pre->discard[plyr], post->discard[plyr], sizeof(int) * MAX_DECK);
        pre->discardCount[plyr] = post->discardCount[plyr];
        memcpy(pre->hand[plyr], post->hand[plyr], sizeof(int) * MAX_DECK);
        pre->handCount[plyr] = post->handCount[plyr];
        memcpy(pre->playedCards, post->playedCards, sizeof(int) * MAX_DECK);
        pre->playedCardCount = post->playedCardCount;

        if (memcmp(pre, post, sizeof(struct gameState)) != 0) { // If test failure
            printf("TEST #%d FAILED: gameState before and after playing Smithy doesn't match\n", i + 1);
            printf("(outside of hand/deck/discard/playedCards)");
            printf("Something that should not be affected by playing the Smithy card has changed.\n");
        }

        free(pre);
        free(post);
    }


    return 0;
}