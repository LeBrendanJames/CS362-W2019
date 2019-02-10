#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// drawCard

void drawCardUnitTests(){
    int numTests = 0, numFailures = 0, i = 0;
    struct gameState * state = NULL;
    int returnVal = 0;

    printf("Function Under Test: drawCard\n");

    printf("\n");
    printf("TEST FAILURES\n");
    printf("---------------------------\n");

	// DECK EMPTY TESTS
	
		// Empty deck, empty discard, make sure -1 is returned
        state = malloc(sizeof(struct gameState));
        state->deckCount[0] = 0;
        state->discardCount[0] = 0;
        returnVal = drawCard(0, state);
        if (returnVal == -1){
            numTests++;
        } else {
            numTests++;
            numFailures++;
            printf("No deck/discard to draw from Test FAILED\n");
            printf("Expected return value of -1. Actual return value: %d\n\n", returnVal);
        }


	
    // One card in discard
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 0;
    state->discardCount[0] = 1;
    state->discard[0][0] = 2;
    state->handCount[0] = 5;
    for (i = 0; i < state->handCount[0]; i++){
        state->hand[0][i] = 13;
    }
    returnVal = drawCard(0, state);
    // Check discard empty after call to function
    if (state->discardCount[0] == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("One card in discard - card moved out of discard pile in order to draw Test FAILED\n");
        printf("Expected discardCount = 0. Actual value: %d\n\n", state->discardCount[0]);
    }
    // Check deck empty after call to function (since the one card will be drawn)
    if (state->deckCount[0] == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("One card in discard - card moved to hand then drawn - deck count = 0 Test FAILED\n");
        printf("Expected deckCount = 0. Actual value: %d\n\n", state->deckCount[0]);
    }
    // Check hand 1 larger after call to function
    if (state->handCount[0] == 6){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("One card in discard - card moved to hand then drawn - hand count one greater Test FAILED\n");
        printf("Expected handCount = 6. Actual value: %d\n\n", state->handCount[0]);
    }
    // Check correct card moved through
    if (state->hand[0][5] == 2){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("One card in discard - card moved to deck then drawn - hand has card from discard Test FAILED\n");
        printf("Expected hand to contain card 2. Actual value of where that card should be: %d\n\n", state->hand[0][5]);
    }
    free(state);
    state = NULL;
			
    // Multiple cards in discard
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 0;
    state->discardCount[0] = 3;
    state->discard[0][0] = 2;
    state->discard[0][1] = 3;
    state->discard[0][2] = 4;
    state->handCount[0] = 5;
    for (i = 0; i < state->handCount[0]; i++){
        state->hand[0][i] = 13;
    }

    returnVal = drawCard(0, state);

    // Check discard empty
    if (state->discardCount[0] == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Multiple cards in discard - cards moved out of discard pile in order to draw Test FAILED\n");
        printf("Expected discardCount = 0. Actual value: %d\n\n", state->discardCount[0]);
    }
    // Check deck is one less than what was in discard
    if (state->deckCount[0] == 2){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Three cards in discard - cards moved to hand then one drawn - deck count Test FAILED\n");
        printf("Expected deckCount = 2. Actual value: %d\n\n", state->deckCount[0]);
    }
    // Check hand has one extra card
    if (state->handCount[0] == 6){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Three cards in discard - cards moved to deck then drawn - hand has card from discard Test FAILED\n");
        printf("Expected hand to contain six cards. Actual number: %d\n\n", state->handCount[0]);
    }
    free(state);
    state = NULL;

    // Max cards in discard
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 0;
    state->discardCount[0] = MAX_DECK;
    for (i = 0; i < MAX_DECK; i++){
        state->discard[0][i] = 13; // Add all smithy's
    }
    state->handCount[0] = 0;

    returnVal = drawCard(0, state);

    // Check discard empty
    if (state->discardCount[0] == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Max cards in discard - cards moved out of discard pile in order to draw Test FAILED\n");
        printf("Expected discardCount = 0. Actual value: %d\n\n", state->discardCount[0]);
    }
    // Check deck is one less that what was in discard
    if (state->deckCount[0] == MAX_DECK - 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Max cards in discard - cards moved to hand then one drawn - deck count Test FAILED\n");
        printf("Expected deckCount = MAX_DECK - 1 (399). Actual value: %d\n\n", state->deckCount[0]);
    }
    // Check hand has one extra card
    if (state->handCount[0] == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Max cards in discard - cards moved to deck then drawn - hand has card from discard Test FAILED\n");
        printf("Expected hand to contain one card. Actual number: %d\n\n", state->handCount[0]);
    }
    free(state);
    state = NULL;
	
	// DECK NOT EMPTY TESTS
	
    // One card in deck
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 1;
    state->deck[0][0] = 12;
    state->discardCount[0] = 1;
    state->discard[0][0] = 2;
    state->handCount[0] = 5;
    for (i = 0; i < state->handCount[0]; i++){
        state->hand[0][i] = 13;
    }
    returnVal = drawCard(0, state);
    // Check deck empty after function call
    if (state->deckCount[0] == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("One card in deck - card moved to hand - deck count = 0 Test FAILED\n");
        printf("Expected deckCount = 0. Actual value: %d\n\n", state->deckCount[0]);
    }
    // Check hand has one more card
    if (state->handCount[0] == 6){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("One card in deck - card moved to hand Test FAILED\n");
        printf("Expected hand to contain 6 cards. Actual number: %d\n\n", state->handCount[0]);
    }
    // Check discard unaffected
    if (state->discardCount[0] == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("One card in deck and one in discard - discard unaffected Test FAILED\n");
        printf("Expected discardCount = 1. Actual value: %d\n\n", state->discardCount[0]);
    }
    // Check that card moved was correct
    if (state->hand[0][5] == 12){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("One card in deck - card moved to hand - hand has correct card Test FAILED\n");
        printf("Expected hand to contain card 12. Actual value of where that card should be: %d\n\n", state->hand[0][5]);
    }
    free(state);
    state = NULL;

    // Multiple cards in deck
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 3;
    state->deck[0][0] = 5;
    state->deck[0][1] = 6;
    state->deck[0][2] = 7;
    state->discardCount[0] = 3;
    state->discard[0][0] = 2;
    state->discard[0][1] = 3;
    state->discard[0][2] = 4;
    state->handCount[0] = 5;
    for (i = 0; i < state->handCount[0]; i++){
        state->hand[0][i] = 13;
    }

    returnVal = drawCard(0, state);

    // Check deck has one fewer card
    if (state->deckCount[0] == 2){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Three cards in deck - one card moved to hand - deck count Test FAILED\n");
        printf("Expected deckCount = 2. Actual value: %d\n\n", state->deckCount[0]);
    }
    // Check hand has one more card
    if (state->handCount[0] == 6){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Three cards in deck - one card moved to hand Test FAILED\n");
        printf("Expected hand to contain 6 cards. Actual number: %d\n\n", state->handCount[0]);
    }
    // Check discard unaffected
    if (state->discardCount[0] == 3){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Three cards in deck and three in discard - discard unaffected Test FAILED\n");
        printf("Expected discardCount = 3. Actual value: %d\n\n", state->discardCount[0]);
    }
    free(state);
    state = NULL;

    // Max cards in deck
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = MAX_DECK;
    for (i = 0; i < MAX_DECK; i++) {
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 0;

    returnVal = drawCard(0, state);
    // Check deck has one fewer card
    if (state->deckCount[0] == MAX_DECK - 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Max cards in deck - one card moved to hand - deck count Test FAILED\n");
        printf("Expected deckCount = MAX_DECK - 1 (399). Actual value: %d\n\n", state->deckCount[0]);
    }
    // Check hand has one more card
    if (state->handCount[0] == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Max cards in deck - one card moved to hand Test FAILED\n");
        printf("Expected hand to contain 1 card. Actual number: %d\n\n", state->handCount[0]);
    }
    // Check discard unaffected
    if (state->discardCount[0] == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Max cards in deck and zero in discard - discard unaffected Test FAILED\n");
        printf("Expected discardCount = 0. Actual value: %d\n\n", state->discardCount[0]);
    }
    free(state);
    state = NULL;


	
	// Check that nothing else about gameState has changed
    state = malloc(sizeof(struct gameState));
    struct gameState * stateCopy = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    stateCopy->numPlayers = 3;
    state->handCount[0] = 1;
    stateCopy->handCount[0] = 1;
    state->hand[0][0] = curse;
    stateCopy->hand[0][0] = curse;
    state->discardCount[0] = 1;
    stateCopy->discardCount[0] = 1;
    state->discard[0][0] = curse;
    stateCopy->discard[0][0] = curse;
    state->deckCount[0] = 1;
    stateCopy->deckCount[0] = 1;
    state->deck[0][0] = curse;
    stateCopy->deck[0][0] = curse;
    shuffle(0, state);
    if (state->numPlayers == stateCopy->numPlayers){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("No Change in numPlayers Variable Test FAILED\n");
        printf("--> state numPlayers = %d, stateCopy numPlayers = %d\n\n", state->numPlayers, stateCopy->numPlayers);
    }
    if (state->hand[0][0] == stateCopy->hand[0][0]){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("No Change in hand[0][0] Variable Test FAILED\n");
        printf("--> state hand[0][0] = %d, stateCopy hand[0][0] = %d\n\n", state->hand[0][0], stateCopy->hand[0][0]);
    }
    if (state->deck[0][0] == stateCopy->deck[0][0]){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("No Change in deck[0][0] Variable Test FAILED\n");
        printf("--> state deck[0][0] = %d, stateCopy deck[0][0] = %d\n\n",
               state->deck[0][0], stateCopy->deck[0][0]);
    }
    free(state);
    state = NULL;
    free(stateCopy);
    stateCopy = NULL;



    printf("\nSUMMARY\n");
    printf("---------------------------\n");
    printf("Tests Run: %d, Tests Failed: %d\n\n", numTests, numFailures);
}

int main(int argc, char* argv[]){
	drawCardUnitTests();
	return 0;
}
