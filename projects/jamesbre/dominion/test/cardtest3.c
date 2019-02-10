#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// village


void villageUnitTests(){
    int numTests = 0, numFailures = 0, i = 0;
    struct gameState * state = NULL;

    printf("Card Under Test: village\n");

    printf("\n");
    printf("TEST FAILURES\n");
    printf("---------------------------\n");

	// Check that drawn card into hand works
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
    state->hand[0][0] = 14;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }

    cardEffect(14, 0, 0, 0, state, 0, NULL);

    // handCount updated
    if (state->handCount[0] == 5){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Village: hand count unchanged (+1 card - village card) - Test FAILED\n");
        printf("Expected cards in hand: 5. Actual handCount: %d\n\n", state->handCount[0]);
    }
    // Card in hand
    if (state->hand[0][0] == 13){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Village: card on top of deck replaces village card in hand - Test FAILED\n");
        printf("Expected card in village's position: 13. Actual card: %d\n\n", state->hand[0][0]);
    }
    // Deck count decremented by 1
    if (state->deckCount[0] == 4){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Village: deckCount down by the one card drawn - Test FAILED\n");
        printf("Expected deckCount: 4. Actual deckCount: %d\n\n", state->deckCount[0]);
    }
    free(state);
    state = NULL;


	// Check that actions = prev actions + 2
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
    state->hand[0][0] = 14;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }

    cardEffect(14, 0, 0, 0, state, 0, NULL);

    // Card in hand
    if (state->numActions == 3){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Village: numActions updated - Test FAILED\n");
        printf("Expected numActions: 3. Actual numActions: %d\n\n", state->numActions);
    }
    free(state);
    state = NULL;
	
	// Check that village card is discarded properly
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
    state->hand[0][0] = 14;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }

    cardEffect(14, 0, 0, 0, state, 0, NULL);

    // Card not in hand
    if (state->hand[0][0] != 14){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Village: card removed from hand after being played - Test FAILED\n");
        printf("Expected card in first position: 13. Actual card: %d\n\n", state->hand[0][0]);
    }
    // Top of discard pile = village
    if (state->discard[0][0] == 14){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Village: card on top of discard pile - Test FAILED\n");
        printf("Expected card: 14. Actual card on top of discard pile: %d\n\n", state->discard[0][0]);
    }
    free(state);
    state = NULL;
		
	// Check that the rest of the gameState is unaffected
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->numActions = 1;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 1;
    state->discard[0][0] = 7;
    state->handCount[0] = 5;
    state->hand[0][0] = 14;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }

    cardEffect(14, 0, 0, 0, state, 0, NULL);

    if (state->whoseTurn == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Village: whoseTurn unaffected - Test FAILED\n");
        printf("Expected whoseTurn: 0. Actual whoseTurn: %d\n\n", state->whoseTurn);
    }
    if (state->numPlayers == 3){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Village: numPlayers unaffected - Test FAILED\n");
        printf("Expected numPlayers: 3. Actual numPlayers: %d\n\n", state->numPlayers);
    }
    if (state->hand[0][1] == 4){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Village: other cards in hand unchanged - Test FAILED\n");
        printf("Expected card in 2nd position to remain 4. Actual card: %d\n\n", state->hand[0][1]);
    }
    if (state->discard[0][0] == 7){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Village: existing discards unchanged - Test FAILED\n");
        printf("Expected card on bottom of discard pile: 7. Actual card: %d\n\n", state->discard[0][0]);
    }

    printf("\nSUMMARY\n");
    printf("---------------------------\n");
    printf("Tests Run: %d, Tests Failed: %d\n\n", numTests, numFailures);
}

int main(int argc, char* argv[]){
	villageUnitTests();
	return 0;
}
