#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// endTurn


void endTurnUnitTests(){
    int numTests = 0, numFailures = 0, i = 0;
    struct gameState * state = NULL;

    printf("Function Under Test: endTurn\n");

    printf("\n");
    printf("TEST FAILURES\n");
    printf("---------------------------\n");

	// NOT END OF GAME SCENARIO
	// Check that players hand is empty after running (starts with empty hand)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 0;
    endTurn(state);
    if (state->handCount[0] == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn with no cards in hand - Test FAILED\n");
        printf("Expected cards in hand to remain = 0. Actual handCount: %d\n\n", state->handCount[0]);
    }
    free(state);
    state = NULL;

    // Check that players hand is empty after running (starts with cards in hand)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    for (i = 0; i < state->handCount[0]; i++){
        state->hand[0][i] = 12;
    }
    endTurn(state);
    if (state->handCount[0] == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn with 5 cards in hand - Test FAILED\n");
        printf("Expected cards in hand to be = 0. Actual handCount: %d\n\n", state->handCount[0]);
    }
    free(state);
    state = NULL;

	// Check that players discard increased by # of card in hand
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 5;
    for (i = 0; i < state->handCount[0]; i++){
        state->hand[0][i] = 12;
    }
    endTurn(state);
    if (state->discardCount[0] == 5){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn with 5 cards in hand - discard check - Test FAILED\n");
        printf("Expected cards in discard to be = 5. Actual discardCount: %d\n\n", state->handCount[0]);
    }
    free(state);
    state = NULL;

	// Check that cards moved from hand to discard are correct
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 3;
    state->hand[0][0] = 4;
    state->hand[0][1] = 5;
    state->hand[0][2] = 6;
    endTurn(state);
    if (state->discard[0][0] == 4 && state->discard[0][1] == 5 && state->discard[0][2] == 6){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn with 3 cards in hand - corrrect cards end up in discard - Test FAILED\n");
        printf("Expected cards in discard to be [4, 5, 6]. Actual discard: [%d, %d, %d]\n\n",
               state->discard[0][0], state->discard[0][1], state->discard[0][2]);
    }
    free(state);
    state = NULL;

	// Check that cards moved don't overwrite anything already in discard
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 2;
    state->discard[0][0] = 0;
    state->discard[0][1] = 17;
    state->handCount[0] = 3;
    state->hand[0][0] = 4;
    state->hand[0][1] = 5;
    state->hand[0][2] = 6;
    endTurn(state);
    if (state->discardCount[0] == 5){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn with 3 cards in hand and 2 in discard - discard ends up with 5 - Test FAILED\n");
        printf("Expected discardCount: 5. Actual discardCount: %d\n\n", state->discardCount[0]);
    }
    if (state->discard[0][0] == 0 && state->discard[0][1] == 17){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn with 3 cards in hand and two in discard - previously discarded not overwritten - Test FAILED\n");
        printf("Expected cards at bottom of discard to be [0, 17]. Actual discard: [%d, %d]\n\n",
               state->discard[0][0], state->discard[0][1]);
    }
    free(state);
    state = NULL;

	// check that all the rest of the state looks correct
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;

    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 2;
    state->discard[0][0] = 0;
    state->discard[0][1] = 17;
    state->handCount[0] = 3;
    state->hand[0][0] = 4;
    state->hand[0][1] = 5;
    state->hand[0][2] = 6;
    state->deckCount[2] = 3;
    for (i = 0; i < state->deckCount[2]; i++){
        state->deck[2][i] = 13;
    }
    state->discardCount[2] = 3;
    for (i = 0; i < state->discardCount[2]; i++){
        state->discard[2][i] = 4;
    }
    state->handCount[2] = 0;

    endTurn(state);

    if (state->deckCount[0] == 5){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Deck unaffected by endTurn - Test FAILED\n");
        printf("Expected deckCount of 5. Actual count: %d\n\n", state->deckCount[0]);
    }
    if (state->numPlayers == 3){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("numPlayers unaffected by endTurn - Test FAILED\n");
        printf("Expected numPlayers of 3. Actual count: %d\n\n", state->numPlayers);
    }
    if (state->numPlayers == 3){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("numPlayers unaffected by endTurn - Test FAILED\n");
        printf("Expected numPlayers of 3. Actual count: %d\n\n", state->numPlayers);
    }
    if (state->deckCount[2] == 3 && state->discardCount[2] == 3 && state->handCount[2] == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Other player (not next to act) unaffected by endTurn - Test FAILED\n");
        printf("Expected player #3 deckCount = 3, discardCount = 3, handCount = 0\n");
        printf("Ended function with deckCount = %d, discardCount = %d, handCount = %d\n\n",
               state->deckCount[2], state->discardCount[2], state->handCount[2]);
    }
    free(state);
    state = NULL;

	// Check that next player is correct (player 0 -> player 1)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 0;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 3;
    state->hand[0][0] = 4;
    state->hand[0][1] = 5;
    state->hand[0][2] = 6;
    endTurn(state);
    if (state->whoseTurn == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn - next player (player 0 -> player 1) - Test FAILED\n");
        printf("Expected next player = 1. Actual next player: %d\n\n", state->whoseTurn);
    }
    free(state);
    state = NULL;

    // Check that next player is correct (player 2 -> player 0)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 2;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 3;
    state->hand[0][0] = 4;
    state->hand[0][1] = 5;
    state->hand[0][2] = 6;
    endTurn(state);
    if (state->whoseTurn == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn - next player (player 2 -> player 0 in 3-person game) - Test FAILED\n");
        printf("Expected next player = 0. Actual next player: %d\n\n", state->whoseTurn);
    }
    free(state);
    state = NULL;

	// Check that next player draws hand correctly (5 cards, right?)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 2;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 0;
    endTurn(state);
    if (state->handCount[0] == 5){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn - next player draws hand correctly - Test FAILED\n");
        printf("Expected next player handCount = 5. Actual next player handCount: %d\n\n", state->handCount[0]);
    }
    free(state);
    state = NULL;

	// check that coins and other stuff are correct (whatever correct means)
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->whoseTurn = 2;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 0;
    state->outpostPlayed = 1;
    state->phase = 3;
    state->numActions = 0;
    state->coins = 12;
    state->numBuys = 0;
    state->playedCardCount = 5;
    endTurn(state);
    if (state->outpostPlayed == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn - outpostPlayed reset - Test FAILED\n");
        printf("Expected outpostPlayed = 0. Actual outpostPlayed: %d\n\n", state->outpostPlayed);
    }
    if (state->phase == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn - phase reset - Test FAILED\n");
        printf("Expected phase = 0. Actual phase: %d\n\n", state->phase);
    }
    if (state->numActions == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn - numActions reset - Test FAILED\n");
        printf("Expected numActions = 1. Actual numActions: %d\n\n", state->numActions);
    }
    if (state->coins == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn - coins reset - Test FAILED\n");
        printf("Expected coins = 0. Actual coins: %d\n\n", state->coins);
    }
    if (state->numBuys == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn - numBuys reset - Test FAILED\n");
        printf("Expected numBuys = 1. Actual numBuys: %d\n\n", state->numBuys);
    }
    if (state->playedCardCount == 0){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn - playedCardCount reset - Test FAILED\n");
        printf("Expected playedCardCount = 0. Actual playedCardCunt: %d\n\n", state->numBuys);
    }
    free(state);
    state = NULL;
		
	
	// END OF GAME SCENARIO
	// (Per comment in .h file, this shouldn't advance player, but there doesn't seem to be any code that implements that)
    state = malloc(sizeof(struct gameState));
    state->supplyCount[province] = 0;
    state->numPlayers = 3;
    state->whoseTurn = 2;
    state->deckCount[0] = 5;
    for (i = 0; i < state->deckCount[0]; i++){
        state->deck[0][i] = 13;
    }
    state->discardCount[0] = 0;
    state->handCount[0] = 0;
    endTurn(state);
    if (state->whoseTurn == 2){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("End Turn - player should not advance if game is over - Test FAILED\n");
        printf("Expected whoseTurn to remain 2. Actual whoseTurn: %d\n\n", state->whoseTurn);
    }
    free(state);
    state = NULL;



    printf("\nSUMMARY\n");
    printf("---------------------------\n");
    printf("Tests Run: %d, Tests Failed: %d\n\n", numTests, numFailures);
}


int main(int argc, char* argv[]){
	endTurnUnitTests();
	return 0;
}