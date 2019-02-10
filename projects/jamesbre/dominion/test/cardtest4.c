#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// great_hall


void greatHallUnitTests(){
    int numTests = 0, numFailures = 0, i = 0;
    struct gameState * state = NULL;

    printf("Card Under Test: great_hall\n");

    printf("\n");
    printf("TEST FAILURES\n");
    printf("---------------------------\n");

	// Check that card is drawn correctly (deck has cards)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->numActions = 1;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = 16;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }

    cardEffect(16, 0, 0, 0, state, 0, NULL);

    if (state->handCount[0] == 5){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Great_hall hand count unchanged (+1 card - great_hall card) - Test FAILED\n");
        printf("Expected cards in hand: 5. Actual handCount: %d\n\n", state->handCount[0]);
    }
    if (state->deckCount[0] == 4){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Great_hall deck count one fewer - Test FAILED\n");
        printf("Expected cards in deck: 4. Actual deckCount: %d\n\n", state->deckCount[0]);
    }
    if (state->deck[0][0] == 13){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Great_hall card drawn replaces it - Test FAILED\n");
        printf("Expected card in great_hall's place: 13. Actual card: %d\n\n", state->hand[0][0]);
    }
    free(state);
    state = NULL;
	
	// Check that card is drawn correctly (deck has no cards, so shuffle required)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->numActions = 1;
    state->deckCount[0] = 0;
    state->discardCount[0] = 5;
    for (i = 0; i < state->discardCount[0]; i++){
        state->discard[0][i] = 13;
    }
    state->handCount[0] = 5;
    state->hand[0][0] = 16;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }

    cardEffect(16, 0, 0, 0, state, 0, NULL);

    if (state->handCount[0] == 5){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Great_hall hand count unchanged (+1 card - great_hall card) - Test FAILED\n");
        printf("Expected cards in hand: 5. Actual handCount: %d\n\n", state->handCount[0]);
    }
    if (state->deckCount[0] == 4){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Great_hall deck count one fewer - Test FAILED\n");
        printf("Expected cards in deck: 4. Actual deckCount: %d\n\n", state->deckCount[0]);
    }
    if (state->discardCount[0] == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Great_hall: cards moved form discard into deck to draw so discard only has great_hall - Test FAILED\n");
        printf("Expected cards in discard: 1. Actual discard: %d\n\n", state->discardCount[0]);
    }
    if (state->deck[0][0] == 13){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Great_hall card drawn replaces it - Test FAILED\n");
        printf("Expected card in great_hall's place: 13. Actual card: %d\n\n", state->hand[0][0]);
    }
    free(state);
    state = NULL;
	
	// Check that actions gets updated properly (+1)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->numActions = 1;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = 16;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }

    cardEffect(16, 0, 0, 0, state, 0, NULL);

    if (state->numActions == 2){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Great_hall: numActions updated - Test FAILED\n");
        printf("Expected numActions: 2. Actual numActions: %d\n\n", state->numActions);
    }
    free(state);
    state = NULL;

	// Check that discard works properly (Out of player hand)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->numActions = 1;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = 16;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }

    cardEffect(16, 0, 0, 0, state, 0, NULL);

    int ghMatch = 0;
    for (i = 0; i < state->handCount[0]; i++){
        if (state->hand[0][i] == 16){
            ghMatch = 1;
        }
    }

    if (ghMatch == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Great_hall: card no longer in hand after playing it - Test FAILED\n");
    }
    free(state);
    state = NULL;
		
	// Check that nothing else with the game state/ kingdom cards/ supply cards changes



    printf("\nSUMMARY\n");
    printf("---------------------------\n");
    printf("Tests Run: %d, Tests Failed: %d\n\n", numTests, numFailures);
}

int main(int argc, char* argv[]){
	greatHallUnitTests();
	return 0;
}