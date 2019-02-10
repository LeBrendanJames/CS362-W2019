#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// scoreFor

//int scoreFor (int player, struct gameState *state) {

void scoreForUnitTests(){
    struct gameState * state = NULL;
    int scoreReturn = 0;
    int numTests = 0, numFailures = 0;

    printf("Function Under Test: scoreFor\n");

    printf("\n");
    printf("TEST FAILURES\n");
    printf("---------------------------\n");

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
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Hand With No Scoring Cards Test FAILED\n");
        printf("--> Expected score = 0, score returned = %d\n\n", scoreReturn);
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
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Single Scoring Card in Hand Test FAILED\n");
        printf("--> Expected score = 1, score returned = %d\n\n", scoreReturn);
    }
    free(state);
    state = NULL;

  // Single card in discard, no other cards
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 0;
    state->discardCount[0] = 1;
	state->discard[0][0] = estate;
    state->deckCount[0] = 0;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Single Scoring Card in Discard Test FAILED\n");
        printf("--> Expected score = 1, score returned = %d\n\n", scoreReturn);
    }
    free(state);
    state = NULL;
	
  // Single card in deck, no other cards
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 0;
    state->discardCount[0] = 0;
    state->deckCount[0] = 1;
	state->deck[0][0] = estate;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Single Scoring Card in Deck Test FAILED\n");
        printf("--> Expected score = 1, score returned = %d\n\n", scoreReturn);
    }
    free(state);
    state = NULL;

  // Normal hand (multiple cards), with scoring cards in hand
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
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Normal Hand (multiple cards) Test with Scoring in Hand FAILED\n");
        printf("--> Expected score = 3, score returned = %d\n\n", scoreReturn);
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
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Normal Hand (scoring cards in discard) Test FAILED\n");
        printf("--> Expected score = 2, score returned = %d\n\n", scoreReturn);
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
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Normal Hand (Scoring Cards in Deck) Test FAILED\n");
        printf("--> Expected score = 13, score returned = %d\n\n", scoreReturn);
    }
    free(state);
    state = NULL;


  // has gardens but full deck < 10
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 3;
    state->hand[0][0] = gardens;
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
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Normal Hand (Gardens, but <10 cards) Test FAILED\n");
        printf("--> Expected score = 0, score returned = %d\n\n", scoreReturn);
    }
    free(state);
    state = NULL;
	
  // has gardens and full deck == 10
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 3;
    state->hand[0][0] = gardens;
    state->hand[0][1] = smithy;
    state->hand[0][2] = smithy;
    state->discardCount[0] = 2;
    state->discard[0][0] = smithy;
    state->discard[0][1] = smithy;
    state->deckCount[0] = 5;
    state->deck[0][0] = smithy;
    state->deck[0][1] = smithy;
    state->deck[0][2] = smithy;
	state->deck[0][3] = smithy;
	state->deck[0][4] = smithy;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Normal Hand (Gardens, = 10 cards) Test FAILED\n");
        printf("--> Expected score = 1, score returned = %d\n\n", scoreReturn);
    }
    free(state);
    state = NULL;

  // has gardens and full deck > 10
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 3;
    state->hand[0][0] = gardens;
    state->hand[0][1] = smithy;
    state->hand[0][2] = smithy;
    state->discardCount[0] = 5;
    state->discard[0][0] = smithy;
    state->discard[0][1] = smithy;
	state->discard[0][2] = smithy;
	state->discard[0][3] = smithy;
	state->discard[0][4] = smithy;
    state->deckCount[0] = 5;
    state->deck[0][0] = smithy;
    state->deck[0][1] = smithy;
    state->deck[0][2] = smithy;
	state->deck[0][3] = smithy;
	state->deck[0][4] = smithy;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Normal Hand (Gardens, >10 cards) Test FAILED\n");
        printf("--> Expected score = 1, score returned = %d\n\n", scoreReturn);
    }
    free(state);
    state = NULL;
	
  // has gardens and full deck == 20
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 8;
    state->hand[0][0] = gardens;
    state->hand[0][1] = smithy;
    state->hand[0][2] = smithy;
	state->hand[0][3] = smithy;
	state->hand[0][4] = smithy;
	state->hand[0][5] = smithy;
	state->hand[0][6] = smithy;
	state->hand[0][7] = smithy;
    state->discardCount[0] = 7;
    state->discard[0][0] = smithy;
    state->discard[0][1] = smithy;
	state->discard[0][2] = smithy;
	state->discard[0][3] = smithy;
	state->discard[0][4] = smithy;
	state->discard[0][5] = smithy;
	state->discard[0][6] = smithy;
    state->deckCount[0] = 5;
    state->deck[0][0] = smithy;
    state->deck[0][1] = smithy;
    state->deck[0][2] = smithy;
	state->deck[0][3] = smithy;
	state->deck[0][4] = smithy;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 2){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Normal Hand (Gardens, >10 cards) Test FAILED\n");
        printf("--> Expected score = 2, score returned = %d\n\n", scoreReturn);
    }
    free(state);
    state = NULL;

  // Has all types of scoring cards in hand
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 6;
    state->hand[0][0] = curse;
    state->hand[0][1] = estate;
    state->hand[0][2] = duchy;
	state->hand[0][3] = province;
	state->hand[0][4] = great_hall;
	state->hand[0][5] = gardens;
    state->discardCount[0] = 2;
    state->discard[0][0] = smithy;
    state->discard[0][1] = smithy;
    state->deckCount[0] = 2;
    state->deck[0][0] = smithy;
    state->deck[0][1] = smithy;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 11){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Normal Hand (All scoring Cards in Hand) Test FAILED\n");
        printf("--> Expected score = 11, score returned = %d\n\n", scoreReturn);
    }
    free(state);
    state = NULL;
	
  // has all types of scoring cards in discard
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 6;
    state->hand[0][0] = smithy;
    state->hand[0][1] = smithy;
    state->hand[0][2] = smithy;
	state->hand[0][3] = smithy;
	state->hand[0][4] = smithy;
	state->hand[0][5] = smithy;
    state->discardCount[0] = 6;
    state->discard[0][0] = curse;
    state->discard[0][1] = estate;
	state->discard[0][2] = duchy;
	state->discard[0][3] = province;
	state->discard[0][4] = great_hall;
	state->discard[0][5] = gardens;
    state->deckCount[0] = 2;
    state->deck[0][0] = smithy;
    state->deck[0][1] = smithy;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 11){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Normal Hand (All scoring Cards in Discard) Test FAILED\n");
        printf("--> Expected score = 11, score returned = %d\n\n", scoreReturn);
    }
    free(state);
    state = NULL;
	
  // Has all types of scoring cards in deck
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 6;
    state->hand[0][0] = smithy;
    state->hand[0][1] = smithy;
    state->hand[0][2] = smithy;
	state->hand[0][3] = smithy;
	state->hand[0][4] = smithy;
	state->hand[0][5] = smithy;
    state->discardCount[0] = 6;
    state->discard[0][0] = smithy;
    state->discard[0][1] = smithy;
	state->discard[0][2] = smithy;
	state->discard[0][3] = smithy;
	state->discard[0][4] = smithy;
	state->discard[0][5] = smithy;
    state->deckCount[0] = 6;
    state->deck[0][0] = curse;
    state->deck[0][1] = estate;
	state->deck[0][2] = duchy;
	state->deck[0][3] = province;
	state->deck[0][4] = great_hall;
	state->deck[0][5] = gardens;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 11){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Normal Hand (All scoring Cards in Deck) Test FAILED\n");
        printf("--> Expected score = 11, score returned = %d\n\n", scoreReturn);
    }
    free(state);
    state = NULL;

  // Has all scoring cards in all 3 categories
    state = malloc(sizeof(struct gameState));
    state->numPlayers = 3;
    state->handCount[0] = 6;
    state->hand[0][0] = curse;
    state->hand[0][1] = estate;
    state->hand[0][2] = duchy;
	state->hand[0][3] = province;
	state->hand[0][4] = great_hall;
	state->hand[0][5] = gardens;
    state->discardCount[0] = 6;
    state->discard[0][0] = curse;
    state->discard[0][1] = estate;
	state->discard[0][2] = duchy;
	state->discard[0][3] = province;
	state->discard[0][4] = great_hall;
	state->discard[0][5] = gardens;
    state->deckCount[0] = 6;
    state->deck[0][0] = curse;
    state->deck[0][1] = estate;
	state->deck[0][2] = duchy;
	state->deck[0][3] = province;
	state->deck[0][4] = great_hall;
	state->deck[0][5] = gardens;
    scoreReturn = scoreFor(0, state);
    if (scoreReturn == 33){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Normal Hand (All scoring Cards in all three areas) Test FAILED\n");
        printf("--> Expected score = 33, score returned = %d\n\n", scoreReturn);
    }
    free(state);
    state = NULL;

  // Checks that nothing about state changes with this function
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
    scoreReturn = scoreFor(0, state);
    if (state->numPlayers == stateCopy->numPlayers){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("No Change in numPlayers Variable Test FAILED\n");
        printf("--> state numPlayers = %d, stateCopy numPlayers = %d\n\n", state->numPlayers, stateCopy->numPlayers);
    }
    if (state->handCount[0] == stateCopy->handCount[0]){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("No Change in handCount[0] Variable Test FAILED\n");
        printf("--> state handCount[0] = %d, stateCopy handCount[0] = %d\n\n", state->handCount[0], stateCopy->handCount[0]);
    }
    if (state->hand[0][0] == stateCopy->hand[0][0]){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("No Change in hand[0][0] Variable Test FAILED\n");
        printf("--> state hand[0][0] = %d, stateCopy hand[0][0] = %d\n\n", state->hand[0][0], stateCopy->hand[0][0]);
    }
    if (state->discardCount[0] == stateCopy->discardCount[0]){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("No Change in discardCount[0] Variable Test FAILED\n");
        printf("--> state discardCount[0] = %d, stateCopy discardCount[0] = %d\n\n",
               state->discardCount[0], stateCopy->discardCount[0]);
    }
    if (state->discard[0][0] == stateCopy->discard[0][0]){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("No Change in discard[0][0] Variable Test FAILED\n");
        printf("--> state discard[0][0] = %d, stateCopy discard[0][0] = %d\n\n",
               state->discard[0][0], stateCopy->discard[0][0]);
    }
    if (state->deckCount[0] == stateCopy->deckCount[0]){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("No Change in deckCount[0] Variable Test FAILED\n");
        printf("--> state deckCount[0] = %d, stateCopy deckCount[0] = %d\n\n",
               state->deckCount[0], stateCopy->deckCount[0]);
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
    scoreForUnitTests();
    return 0;
}