#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// scoreFor

//int scoreFor (int player, struct gameState *state) {

void scoreForUnitTests(){ //**ARE THERE OTHER CARDS THAT SHOULD SCORE THAT THE FUNCTION IS MISSING?**
    struct gameState * state = NULL;
    int scoreReturn = 0;

    // Normal hand, no scoring cards
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 3;
    state->hand[0][0] = smithy;
    state->hand[0][1] = smithy;
    state->hand[0][2] = smithy;
    state->discardCount[0] = 2;
    state->discard[0][0] = smithy;
    state->discard[0][1] = smithy;
    state->deckCount[0] = 3;
    state->deck[0][0] = smithy;
    state->deck[0][1] = smithy;
    state->deck[0][2] = smithy;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 0){
        printf("Normal Hand Test Passed\n");
    } else {
        printf("Normal Hand Test Failed\n");
        printf("Expected score = 0, score returned = %d\n", scoreReturn);
    }
    free(state);
    state = NULL;

    // Single scoring card in hand, no other cards
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 1;
    state->hand[0][0] = estate;
    state->discardCount[0] = 0;
    state->deckCount[0] = 0;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 1){
        printf("Single Scoirng Card in Hand Test PASSED\n");
    } else {
        printf("Single Scoring Card in Hand Test FAILED\n");
        printf("Expected score = 1, score returned = %d\n", scoreReturn);
    }
    free(state);
    state = NULL;

    // Single card in discard, no other cards

    // Single card in deck, no other cards


    // Normal hand, with scoring cards in hand
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 3;
    state->hand[0][0] = curse;
    state->hand[0][1] = duchy;
    state->hand[0][2] = great_hall;
    state->discardCount[0] = 2;
    state->discard[0][0] = smithy;
    state->discard[0][1] = smithy;
    state->deckCount[0] = 3;
    state->deck[0][0] = smithy;
    state->deck[0][1] = smithy;
    state->deck[0][2] = smithy;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 3){
        printf("Normal Hand Test with Scoring in Hand Passed\n");
    } else {
        printf("Normal Hand Test with Scoring in Hand Failed\n");
        printf("Expected score = 3, score returned = %d\n", scoreReturn);
    }
    free(state);
    state = NULL;

    // Normal hand, with scoring cards in discard
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 3;
    state->hand[0][0] = smithy;
    state->hand[0][1] = smithy;
    state->hand[0][2] = smithy;
    state->discardCount[0] = 2;
    state->discard[0][0] = estate;
    state->discard[0][1] = estate;
    state->deckCount[0] = 3;
    state->deck[0][0] = smithy;
    state->deck[0][1] = smithy;
    state->deck[0][2] = smithy;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 2){
        printf("Normal Hand Test Passed\n");
    } else {
        printf("Normal Hand Test Failed\n");
        printf("Expected score = 2, score returned = %d\n", scoreReturn);
    }
    free(state);
    state = NULL;

    // Normal hand, with scoring cards in deck
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 3;
    state->hand[0][0] = smithy;
    state->hand[0][1] = smithy;
    state->hand[0][2] = smithy;
    state->discardCount[0] = 2;
    state->discard[0][0] = smithy;
    state->discard[0][1] = smithy;
    state->deckCount[0] = 3;
    state->deck[0][0] = province;
    state->deck[0][1] = province;
    state->deck[0][2] = great_hall;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 13){
        printf("Normal Hand Test Passed\n");
    } else {
        printf("Normal Hand Test Failed\n");
        printf("Expected score = 13, score returned = %d\n", scoreReturn);
    }
    free(state);
    state = NULL;


    // has gardens but full deck < 10

    // has gardens and full deck == 10

    // has gardens and full deck > 10

    // Has all types of scoring cards in hand

    // has all types of scoring cards in discard

    // Has all types of scoring cards in deck

    // Has all scoring cards in all 3 categories

    // Checks that nothing about state changes with this function
}



int main(int argc, char* argv[]){
    scoreForUnitTests();
    return 0;
}