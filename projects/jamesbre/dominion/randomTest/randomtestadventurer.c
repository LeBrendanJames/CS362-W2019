// ADVENTURER RANDOM TESTS
// Brendan James
// CS362 Assignment 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../rngs.h"
#include "../dominion.h"
#include "../dominion_helpers.h"

int main(){
    int i = 0, j = 0, returnVal = 0, treasureCount = 0, cardSlot = 0;
    int plyr = 0, deckAndDiscard = 0;
    int randCard = 0, randDeckSlot = 0, randDiscardSlot = 0;
    int deckTreasureCount = 0, discardTreasureCount = 0;
    struct gameState * pre = NULL;
    struct gameState * post = NULL;

    SelectStream(0);
    PutSeed(5);

    for (i = 0; i < 1000; i++){
        treasureCount = 0;
        deckTreasureCount = 0;
        discardTreasureCount = 0;

        // SET UP GAME STATE
        pre = malloc(sizeof(struct gameState));
        post = malloc(sizeof(struct gameState));
        // Fill post with random bytes (code source: testDrawCard.c)
        for (j = 0; j < sizeof(struct gameState); j++) {
            ((char*)post)[j] = floor(Random() * 256);
        }
        // Initialize hand/deck/discard sizes and fill with random cards
        plyr = floor(Random() * MAX_PLAYERS);
        post->whoseTurn = plyr;
        post->deckCount[plyr] = floor(Random() * MAX_DECK);
        post->discardCount[plyr] = floor(Random() * (MAX_DECK - post->deckCount[plyr]));
        deckAndDiscard = post->deckCount[plyr] + post->discardCount[plyr];
        post->handCount[plyr] = floor(Random() * (MAX_HAND - 2));
        for (j = 0; j < post->deckCount[plyr]; j++){
            post->deck[plyr][j] = floor(Random() * 27); // 27 = # of different cards (from ENUM CARD in dominion.h)
            if (post->deck[plyr][j] >= 4 && post->deck[plyr][j] <= 6){
                treasureCount++;
                deckTreasureCount++;
            }
        }
        for (j = 0; j < post->discardCount[plyr]; j++){
            post->discard[plyr][j] = floor(Random() * 27);
            if (post->discard[plyr][j] >= 4 && post->discard[plyr][j] <= 6){
                treasureCount++;
                discardTreasureCount++;
            }
        }
        for (j = 0; j < post->handCount[plyr]; j++){
            post->hand[plyr][j] = floor(Random() * 27);
        }
        // Must be at least 2 treasure available in deck + discard combined. Otherwise we enter into infinite loop.
        while (treasureCount < 2){
            cardSlot = floor(Random() * 2);
            if (cardSlot == 0){
                j = 0;
                randDeckSlot = floor(Random() * post->deckCount[plyr]);
                while (post->deck[plyr][randDeckSlot] >= 4 && post->deck[plyr][randDeckSlot] <= 6 && j < 100) {
                    // Chooses a slot in deck to replace w/ treasure
                    randDeckSlot = floor(Random() * post->deckCount[plyr]);
                    j++;
                }
                if (j < 100) { // If loop didn't end by running 100 times
                    randCard = floor(Random() * 3) + 4; // Gives copper/silver/gold randomly
                    post->deck[plyr][randDeckSlot] = randCard;
                    treasureCount++;
                    deckTreasureCount++;
                }
            } else {
                j = 0;
                randDiscardSlot = floor(Random() * post->discardCount[plyr]);
                while (post->discard[plyr][randDiscardSlot] >= 4 && post->deck[plyr][randDiscardSlot] <= 6 && j < 100) {
                    // Chooses a slot in deck to replace w/ treasure
                    randDiscardSlot = floor(Random() * post->discardCount[plyr]);
                    j++;
                }
                if (j < 100) {
                    randCard = floor(Random() * 3) + 4; // Gives copper/silver/gold randomly
                    post->discard[plyr][randDiscardSlot] = randCard;
                    treasureCount++;
                    discardTreasureCount++;
                }
            }
        }

        // COPY 'POST' GAMESTATE TO 'PRE'
        memcpy(pre, post, sizeof(struct gameState));

        // run CardEffect on 'post'
        returnVal = cardEffect(7, 0, 0, 0, post, 0, NULL);

        // Change known things about pre (some can just be copies of post)
        // Add two drawn treasure cards to pre & update hand count
        pre->hand[plyr][pre->handCount[plyr]] = post->hand[plyr][pre->handCount[plyr]];
        pre->hand[plyr][pre->handCount[plyr] + 1] = post->hand[plyr][pre->handCount[plyr] + 1];
        pre->handCount[plyr] += 1; // Draw two treasure + discard adventurer == +1 card in hand

        // Set deck and discard piles to whatever is in post
        memcpy(pre->deck[plyr], post->deck[plyr], sizeof(int) * MAX_DECK);
        pre->deckCount[plyr] = post->deckCount[plyr];
        memcpy(pre->discard[plyr], post->discard[plyr], sizeof(int) * MAX_DECK);
        pre->discardCount[plyr] = post->discardCount[plyr];


        // assert returnVal correct
        if (returnVal != 0){
            printf("TEST FAILED: returnVal != 0. Actual value: %d\n", returnVal);
        }

        // Assert pre == post
        if (memcmp(pre, post, sizeof(struct gameState)) != 0){ // If test failure
            // Do some more digging to find where difference is in two gameStates
            printf("TEST #%d FAILED: pre and post not equal\n", i);
            if (pre->handCount[plyr] != post->handCount[plyr]){
                printf("  Pre handCount != post handCount\n");
            }
            if (pre->deckCount[plyr] != post->deckCount[plyr]){
                printf("  Pre deckCount != post deckCount\n");
            }
            if (pre->discardCount[plyr] != post->discardCount[plyr]){
                printf("  Pre discardCount != post discardCount\n");
            }
            for (j = 0; j < pre->handCount[plyr]; j++){
                if (pre->hand[plyr][j] != post->hand[plyr][j]){
                    printf("  Pre and post hand card at index #%d not equal.\n", i);
                }
            }
            printf("  Hand size = %d\n", pre->handCount[plyr]);
            for (j = 0; j < pre->deckCount[plyr]; j++){
                if (pre->deck[plyr][j] != post->deck[plyr][j]){
                    printf("  Pre and post deck card at index #%d not equal.\n", j);
                }
            }
            printf("  Deck size = %d\n", pre->deckCount[plyr]);
            for (j = 0; j < pre->discardCount[plyr]; j++){
                if (pre->discard[plyr][j] != post->discard[plyr][j]){
                    printf("  Pre and post discard card at index #%d not equal.\n", j);
                }
            }
            printf("  Discard size = %d\n", pre->discardCount[plyr]);
        }

        if (deckAndDiscard - 2 != post->deckCount[plyr] + post->discardCount[plyr]){
            printf("TEST #%d FAILED: Deck and discard NOT two less than at beginning of hand.\n", i);
            printf("  deck and discard before playing Adventurer = %d\n", deckAndDiscard);
            printf("  post deckCount = %d, post discardCount = %d\n", post->deckCount[plyr], post->discardCount[plyr]);
            printf("  Total: %d\n", post->deckCount[plyr] + post->discardCount[plyr]);
        }

        free(pre);
        free(post);
    }

    return 0;
}