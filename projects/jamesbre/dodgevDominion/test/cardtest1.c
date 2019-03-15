#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// smithy
// Smithy adds three cards to a players hand (and is itself discarded)

void smithyUnitTests(){
    int numTests = 0, numFailures = 0, i = 0;
    struct gameState * state = NULL;

    printf("Card Under Test: smithy\n");

    printf("\n");
    printf("TEST FAILURES\n");
    printf("---------------------------\n");

	// Check handCount two higher than what player started with (+3 cards - Smithy)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = 13;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }
    cardEffect(13, 0, 0, 0, state, 0, NULL);
    if (state->handCount[0] == 7){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Smithy adds two cards (net: +3 cards - Smithy) to hand - Test FAILED\n");
        printf("Expected cards in hand: 7. Actual handCount: %d\n\n", state->handCount[0]);
    }
    free(state);
    state = NULL;
	
	// Check discard count one higher (as long as there were 3 cards to draw from deck so as not to deal with shuffling)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = 13;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }
    cardEffect(13, 0, 0, 0, state, 0, NULL);
    if (state->discardCount[0] == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Discard count one higher after Smithy played - Test FAILED\n");
        printf("Expected discardCount: 1. Actual discardCount: %d\n\n", state->discardCount[0]);
    }
    free(state);
    state = NULL;

    // Check that the card discarded is in fact Smithy
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = 13;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }
    cardEffect(13, 0, 0, 0, state, 0, NULL);
    if (state->discard[0][0] == 13){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Discard card is Smithy - Test FAILED\n");
        printf("Expected discard: 13. Actual discard: %d\n\n", state->discard[0][0]);
    }
    free(state);
    state = NULL;

    // Check that the three cards drawn are equal to the three cards that were on the top of the deck
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < 2; i++){
        state->deck[0][i] = 13;
    }
    state->deck[0][2] = 5;
    state->deck[0][3] = 6;
    state->deck[0][4] = 7;
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = 13;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }
    cardEffect(13, 0, 0, 0, state, 0, NULL);
    if (state->hand[0][0] == 5 && state->hand[0][5] == 7 && state->hand[0][6] == 6){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Drawn cards are from top of deck - Test FAILED\n");
        printf("Expected cards [5, 7, 6]. Actual cards: [%d, %d, %d]\n\n",
               state->hand[0][0], state->hand[0][5], state->hand[0][6]);
    }
    free(state);
    state = NULL;

	
	// Starting with deck empty, ensure that discard pile = 1 and card is Smithy
	// In other words, check that shuffle of discard pile into deck happens BEFORE Smithy is discarded
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 0;
    state->discardCount[0] = 5;
    for (i = 0; i < state->discardCount[0]; i++){
        state->discard[0][i] = 5;
    }
    state->handCount[0] = 5;
    state->hand[0][0] = 13;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }
    cardEffect(13, 0, 0, 0, state, 0, NULL);
    if (state->discardCount[0] == 1 && state->discard[0][0] == 13){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Discard card is Smithy - Test FAILED\n");
        printf("Expected discardCount = 1, discard = 13. Actual discardCount: %d, discard: %d\n\n",
               state->discardCount[0], state->discard[0][0]);
    }
    free(state);
    state = NULL;
	
	// check nothing else changes about the state of the game (including other players card piles)
	// check nothing changes with victory card piles or kingdom card piles



    printf("\nSUMMARY\n");
    printf("---------------------------\n");
    printf("Tests Run: %d, Tests Failed: %d\n\n", numTests, numFailures);
}



int main(){
    smithyUnitTests();
    return 0;
}