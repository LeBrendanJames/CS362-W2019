#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// adventurer

void adventurerUnitTests(){
	int numTests = 0, numFailures = 0, i = 0;
	struct gameState * state = NULL;

    printf("Card Under Test: adventurer\n");

	printf("\n");
	printf("TEST FAILURES\n");
	printf("---------------------------\n");

	// Check that player hand has two more treasure after running function
    // Of each type too (like make sure it works regardless of whether the treasure is copper/silver/gold)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 4;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = 7;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 13;
    }

    cardEffect(7, 0, 0, 0, state, 0, NULL);
    //printf("Finished first cardEffect call\n");

    if (state->handCount[0] == 6){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer adds one card (+2 cards - Adventurer) to hand - Test FAILED\n");
        printf("Expected cards in hand: 6. Actual handCount: %d\n\n", state->handCount[0]);
    }
    int copperCount = 0;
    for (i = 0; i < state->handCount[0]; i++){
        if (state->hand[0][i] == copper){
            copperCount++;
        }
    }
    if (copperCount == 2){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer adds two coppers somewhere in hand - Test FAILED\n");
        printf("Expected num coppers: 2. Actual coppers: %d\n\n", copperCount);
    }
    if (state->hand[0][0] == 4 && state->hand[0][5] == 4){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer adds two coppers to correct place in hand - Test FAILED\n");
        printf("Expected cards in hand (first and last position): [4, 4]. Actual cards: [%d, %d]\n\n",
               state->hand[0][0], state->hand[0][5]);
    }
    if (state->discardCount[0] == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Discard pile ends with one more card - Test FAILED\n");
        printf("Expected cards in discard: 1. Actual number of cards: %d\n\n", state->discardCount[0]);
    }
    if (state->discard[0][0] == 7){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer on top of discard pile - Test FAILED\n");
        printf("Actual card on top: %d\n\n", state->discard[0][0]);
    }
    free(state);
    state = NULL;
	
	// With two treasure directly on top, check that nothing else changes (those are just drawn into hand)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < 3; i++){
        state->deck[0][i] = 10;
    }
    state->deck[0][3] = 4;
    state->deck[0][4] = 4;
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = 7;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 13;
    }

    cardEffect(7, 0, 0, 0, state, 0, NULL);
    //printf("Finished second cardEffect call\n");

    if (state->deckCount[0] == 3){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Top two cards drawn are coppers, drawing then stops - Test FAILED\n");
        printf("Expected deckCount: 3. Actual count: %d\n\n", state->deckCount[0]);
    }
    free(state);
    state = NULL;
	
	// With one other card then two treasure, check that the 1st card gets discarded and the two treasure are drawn
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < 3; i++){
        state->deck[0][i] = 10;
    }
    state->deck[0][2] = 4;
    state->deck[0][3] = 4;
    state->deck[0][4] = 10;
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = 7;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 13;
    }

    cardEffect(7, 0, 0, 0, state, 0, NULL);
    //printf("Finished third cardEffect call\n");

    if (state->deckCount[0] == 2){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Top three cards of deck are drawn (non-treasure card then two coppers) - Test FAILED\n");
        printf("Expected deckCount after play: 2. Actual count: %d\n\n", state->deckCount[0]);
    }
    copperCount = 0;
    for (i = 0; i < state->handCount[0]; i++){
        if (state->hand[0][i] == copper){
            copperCount++;
        }
    }
    if (copperCount == 2){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer adds two coppers in hand even though top card of deck not copper - Test FAILED\n");
        printf("Expected num coppers: 2. Actual coppers: %d\n\n", copperCount);
    }
    if (state->discardCount[0] == 2){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer and card on top of deck end up in discard pile (count correct) - Test FAILED\n");
        printf("Expected discardCount after play: 2. Actual count: %d\n\n", state->discardCount[0]);
    }
    if ((state->discard[0][0] == 10 || state->discard[0][0] == 7) && (state->discard[0][1] == 10 || state->discard[0][1] == 7)){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer and card on top of deck end up in discard pile (cards correct) - Test FAILED\n");
        printf("Expected discard pile: [10, 7] or [7, 10]. Actual pile: [");
        for (i = 0; i < state->discardCount[0] - 1; i++){
            printf("%d,", state->discard[0][i]);
        }
        printf("%d]\n\n", state->discard[0][state->discardCount[0] - 1]);
    }
    free(state);
    state = NULL;
	
	// With other card/treasure/other card/treasure make sure it works correctly
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    state->deck[0][0] = 13;
    state->deck[0][1] = 4;
    state->deck[0][2] = 10;
    state->deck[0][3] = 4;
    state->deck[0][4] = 10;
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    state->hand[0][0] = 7;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 13;
    }

    cardEffect(7, 0, 0, 0, state, 0, NULL);
    //printf("Finished fourth cardEffect call\n");

    if (state->deckCount[0] == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Top four cards of deck are drawn (non-treasure card then two coppers) - Test FAILED\n");
        printf("Expected deckCount after play: 2. Actual count: %d\n\n", state->deckCount[0]);
    }
    copperCount = 0;
    for (i = 0; i < state->handCount[0]; i++){
        if (state->hand[0][i] == copper){
            copperCount++;
        }
    }
    if (copperCount == 2){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer adds two coppers in hand even though top & 3rd card of deck not copper - Test FAILED\n");
        printf("Expected num coppers: 2. Actual coppers: %d\n\n", copperCount);
    }
    free(state);
    state = NULL;

    // With a shuffle in the middle and one treasure drawn either side of the shuffle, make sure that it all works
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 2;
    state->deck[0][0] = 13;
    state->deck[0][1] = 10;
    state->discardCount[0] = 2;
    state->discard[0][0] = 4;
    state->discard[0][1] = 4;
    state->handCount[0] = 5;
    state->hand[0][0] = 7;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 13;
    }

    cardEffect(7, 0, 0, 0, state, 0, NULL);
    //printf("Finished fifth cardEffect call\n");

    if (state->deckCount[0] == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Deck fully drawn, then shuffle, then fully drawn again - Test FAILED\n");
        printf("Expected deckCount after play: 0. Actual count: %d\n\n", state->deckCount[0]);
    }
    copperCount = 0;
    for (i = 0; i < state->handCount[0]; i++){
        if (state->hand[0][i] == copper){
            copperCount++;
        }
    }
    if (copperCount == 2){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer adds two coppers in hand which began in discard - Test FAILED\n");
        printf("Expected num coppers: 2. Actual coppers: %d\n\n", copperCount);
    }
    if (state->discardCount[0] == 3){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Discard ends with three cards (two non-treasure from deck + Adventurer) - Test FAILED\n");
        printf("Expected discardCount after play: 3. Actual count: %d\n\n", state->discardCount[0]);
    }
    free(state);
    state = NULL;
	
	// If there's only one treasure remaining in deck + discard pile, make sure it just picks up that one treasure
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 2;
    state->deck[0][0] = 4;
    state->deck[0][1] = 10;
    state->discardCount[0] = 2;
    state->discard[0][0] = 13;
    state->discard[0][1] = 13;
    state->handCount[0] = 5;
    state->hand[0][0] = 7;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 13;
    }

    cardEffect(7, 0, 0, 0, state, 0, NULL);
    //printf("Finished sixth cardEffect call\n");

    if (state->deckCount[0] == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Deck fully drawn, then shuffle, then fully drawn again - Test FAILED\n");
        printf("Expected deckCount after play: 0. Actual count: %d\n\n", state->deckCount[0]);
    }
    copperCount = 0;
    for (i = 0; i < state->handCount[0]; i++){
        if (state->hand[0][i] == copper){
            copperCount++;
        }
    }
    if (copperCount == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer adds only one copper in hand if that's all that is available - Test FAILED\n");
        printf("Expected num coppers in hand: 1. Actual coppers: %d\n\n", copperCount);
    }
    if (state->discardCount[0] == 4){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Discard ends with four cards");
        printf("two non-treasure from deck + 1 non-treasure from discard + Adventurer) - Test FAILED\n");
        printf("Expected discardCount after play: 4. Actual count: %d\n\n", state->discardCount[0]);
    }
    free(state);
    state = NULL;

	// Check that game state/ other player hands/ kingdom cards/ victory piles are unaffected
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->numActions = 1;
    state->deckCount[0] = 5;
    state->deckCount[1] = 5;
    state->deckCount[2] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
        state->deck[1][i] = 12;
        state->deck[2][i] = 11;
    }
    state->discardCount[0] = 1;
    state->discardCount[1] = 0;
    state->discardCount[2] = 0;
    state->discard[0][0] = 7;
    state->handCount[0] = 5;
    state->hand[0][0] = 14;
    for (i = 1; i < state->handCount[0]; i++){
        state->hand[0][i] = 4;
    }

    cardEffect(7, 0, 0, 0, state, 0, NULL);
    //printf("Finished seventh cardEffect call\n");

    if (state->whoseTurn == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer: whoseTurn unaffected - Test FAILED\n");
        printf("Expected whoseTurn: 0. Actual whoseTurn: %d\n\n", state->whoseTurn);
    }
    if (state->numPlayers == 3){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer: numPlayers unaffected - Test FAILED\n");
        printf("Expected numPlayers: 3. Actual numPlayers: %d\n\n", state->numPlayers);
    }
    if (state->hand[0][1] == 4){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer: other cards in hand unchanged - Test FAILED\n");
        printf("Expected card in 2nd position to remain 4. Actual card: %d\n\n", state->hand[0][1]);
    }
    if (state->discard[0][0] == 7){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer: existing discards unchanged - Test FAILED\n");
        printf("Expected card on bottom of discard pile: 7. Actual card: %d\n\n", state->discard[0][0]);
    }
    if (state->deckCount[1] == 5 && state->deckCount[2] == 5){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Adventurer: other player's decks unaffected - Test FAILED\n");
        printf("Expected deckCount for each player: 5. Actual counts: [%d, %d]\n\n",
               state->deckCount[1], state->deckCount[2]);
    }



	printf("\nSUMMARY\n");
	printf("---------------------------\n");
	printf("Tests Run: %d, Tests Failed: %d\n\n", numTests, numFailures);
}



int main(int argc, char* argv[]){
	adventurerUnitTests();
	return 0;
}

