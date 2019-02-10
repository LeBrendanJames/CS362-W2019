#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"

// shuffle

int compareForSort(const void* a, const void* b) {
    if (*(int*)a > *(int*)b)
        return 1;
    if (*(int*)a < *(int*)b)
        return -1;
    return 0;
}

void shuffleUnitTests(){
    int numTests = 0, numFailures = 0;
    struct gameState * state = NULL;
    int returnVal = 0;

	printf("\n");
	printf("TEST FAILURES\n");
	printf("---------------------------\n");


	// Pass in deck of 0 and make sure function returns -1
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 0;
    returnVal = shuffle(0, state);
    if (returnVal == -1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("No deck to shuffle (deckCount == 0) Test FAILED\n");
        printf("Expected return value of -1. Actual return value: %d\n\n", returnVal);
    }
    free(state);
    state = NULL;
	
	// Pass in hand of 5 (or whatever size), make sure resulting state has deckCount of 5
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 5;
    state->deck[0][0] = 1;
    state->deck[0][1] = 1;
    state->deck[0][2] = 1;
    state->deck[0][3] = 1;
    state->deck[0][4] = 1;
    shuffle(0, state);
    if (state->deckCount[0] == 5){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("deckCount remains the same through shuffle Test FAILED\n");
        printf("Initial deckCount = 5, deckCount after shuffle = %d\n\n", state->deckCount[0]);
    }
    free(state);
    state = NULL;
		
	// Pass in hand of size 5 (or whatever size), make sure resulting hand still has 5 cards
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 5;
    state->deck[0][0] = 0;
    state->deck[0][1] = 0;
    state->deck[0][2] = 13;
    state->deck[0][3] = 13;
    state->deck[0][4] = 13;
    shuffle(0, state);
    int i = 0, curseCount = 0, smithyCount = 0;
    for (i = 0; i < 5; i++){
        if (state->deck[0][i] == 0){
            curseCount++;
        } else if (state->deck[0][i] == 13){
            smithyCount++;
        }
    }
    if (curseCount == 2 && smithyCount == 3){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Deck contents remains the same through shuffle Test FAILED\n");
        printf("Initial deck contained 2 curses (int 0) & 3 smithys (int 13), deck after shuffle = [%d, %d, %d, %d, %d]\n\n",
               state->deck[0][0], state->deck[0][1], state->deck[0][2], state->deck[0][3], state->deck[0][4]);
    }
    free(state);
    state = NULL;
	
	// Pass in hand of all the same cards, make sure resulting hand is the same (in size and card values)
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 5;
    state->deck[0][0] = 1;
    state->deck[0][1] = 1;
    state->deck[0][2] = 1;
    state->deck[0][3] = 1;
    state->deck[0][4] = 1;
    shuffle(0, state);
    int correctCount = 0;
    for (i = 0; i < 5; i++){
        if (state->deck[0][i] == 1){
            correctCount++;
        }
    }
    if (correctCount == 5){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Deck contents remains the same through shuffle (all same cards to start) Test FAILED\n");
        printf("Initial deck contained 5 estates (int 1), deck after shuffle = [%d, %d, %d, %d, %d]\n\n",
               state->deck[0][0], state->deck[0][1], state->deck[0][2], state->deck[0][3], state->deck[0][4]);
    }
    free(state);
    state = NULL;
	
	// Pass in hand of all different cards - make sure they're all still there
		// Maybe do this by passing in a sorted hand and sorting the resulting hand then check equality
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 5;
    state->deck[0][0] = 1;
    state->deck[0][1] = 2;
    state->deck[0][2] = 3;
    state->deck[0][3] = 4;
    state->deck[0][4] = 5;
    // Shuffle then sort back
    shuffle(0, state);
    qsort ((void*)(state->deck[0]), state->deckCount[0], sizeof(int), compareForSort);
    int correctCards[5] = {1, 2, 3, 4, 5};
    int allMatch = 1;
    for (i = 0; i < 5; i++){
        if (correctCards[i] != state->deck[0][i]){
            allMatch = 0;
        }
    }
    if (allMatch == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Deck contents remains the same through shuffle (all different cards to start) Test FAILED\n");
        printf("Initial deck contained [1, 2, 3, 4, 5], deck after shuffle and re-sort = [%d, %d, %d, %d, %d]\n\n",
               state->deck[0][0], state->deck[0][1], state->deck[0][2], state->deck[0][3], state->deck[0][4]);
    }
    free(state);
    state = NULL;

	// Pass in deck of different cards, make sure they end up in a different order (random seed permitting)
    SelectStream(1);
    PutSeed(1000000000); // This is known to produce ~0.93, which will select 2nd of 2 cards
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 2;
    state->deck[0][0] = 1;
    state->deck[0][1] = 2;
    shuffle(0, state);
    if (state->deck[0][0] == 2 && state->deck[0][1] == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Two-Card Deck Order Reversed (Known Random Seed) Test FAILED\n");
        printf("Cards remained in same order when they should have swapped.\n\n");
    }
    free(state);
    state = NULL;


    // Pass in deck of 1, make sure deck returned is unchanged
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 1;
    state->deck[0][0] = 12;
    shuffle(0, state);
    if (state->deckCount[0] == 1 && state->deck[0][0] == 12){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("One-Card Deck Unchanged After Shuffle Test FAILED\n");
        printf("Initial deck contained int 12, after shuffle card was: %d\n\n", state->deck[0][0]);
    }
    free(state);
    state = NULL;

	// Pass in deck of max size, made sure all cards are still there after shuffle
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = MAX_DECK;
    for (i = 0; i < MAX_DECK; i++){
        state->deck[0][0] = 12;
    }
    shuffle(0, state);
    if (state->deckCount[0] == MAX_DECK){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Max Deck deckCount Boundry Test FAILED\n");
        printf("Initial deck contained MAX_DECK slots, after shuffle deckCount was: %d\n\n", state->deckCount[0]);
    }
    free(state);
    state = NULL;

    // Pass in MAX_DECK size with a variety of cards. Make sure they are all still there at end.
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = MAX_DECK;
    for (i = 0; i < MAX_DECK; i++){
        state->deck[0][i] = i % 5; // So, just rotating between cards [0, 4]
    }
    shuffle(0, state);
    int fiveCardCount[5] = {0};
    for (i = 0; i < MAX_DECK; i++){
        if (state->deck[0][i] == 0){
            fiveCardCount[0]++;
        } else if (state->deck[0][i] == 1){
            fiveCardCount[1]++;
        } else if (state->deck[0][i] == 2){
            fiveCardCount[2]++;
        } else if (state->deck[0][i] == 3){
            fiveCardCount[3]++;
        } else if (state->deck[0][i] == 4){
            fiveCardCount[4]++;
        }
    }
    if (fiveCardCount[0] == fiveCardCount[1] && fiveCardCount[0] == fiveCardCount[2] &&
        fiveCardCount[0] == fiveCardCount[3] && fiveCardCount[0] == fiveCardCount[4] &&
        fiveCardCount[0] == MAX_DECK / 5){
        numTests++;
    } else {
        for (i = 0; i < 5; i++){
            printf("fiveCardCount[%d]: %d\n", i, fiveCardCount[i]);
        }
        numTests++;
        numFailures++;
        printf("Max Deck Maintains All Cards Boundry Test FAILED\n");
        printf("Initial deck contained MAX_DECK slots rotating through 5 different cards,\n");
        printf("after shuffle they were not all there.\n\n");
    }
    free(state);
    state = NULL;
	
	// Pass in deck of max size, make sure first card is part of the sort
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = MAX_DECK;
    state->deck[0][0] = 1;
    for (i = 1; i < MAX_DECK; i++){
        state->deck[0][0] = 12;
    }
    int cardIncludedInSort = 0;
    i = 0;
    // Can be extremely confident after 1000 shuffles that if the card in first position
    // has never changed that it is not included in sort
    while (i < 1000){
        shuffle(0, state);
        if (state->deck[0][0] != 1){
            cardIncludedInSort = 1;
            break;
        }
        i++;
    }

    if (cardIncludedInSort){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Max Deck sort - first card included in sort Test FAILED\n\n");
    }
    free(state);
    state = NULL;

    // Pass in deck of max size, make sure first card is part of the sort
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = MAX_DECK;
    state->deck[0][MAX_DECK - 1] = 1;
    for (i = 0; i < MAX_DECK - 1; i++){
        state->deck[0][0] = 12;
    }
    cardIncludedInSort = 0;
    i = 0;
    // Can be extremely confident after 1000 shuffles that if the card in first position
    // has never changed that it is not included in sort
    while (i < 1000){
        shuffle(0, state);
        if (state->deck[0][MAX_DECK - 1] != 1){
            cardIncludedInSort = 1;
            break;
        }
        i++;
    }

    if (cardIncludedInSort){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Max Deck sort - last card included in sort Test FAILED\n\n");
    }
    free(state);
    state = NULL;

    // Have a card in played & some in deck. Make sure played doesn't change.
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 2;
    state->deck[0][0] = 1;
    state->deck[0][1] = 2;
    state->playedCardCount = 1;
    state->playedCards[0] = 3;
    shuffle(0, state);
    if (state->playedCardCount == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Played Cards Pile Unaffected By Shuffle Test FAILED\n");
        printf("Played Card Count was 1, after shuffle was: %d\n\n", state->playedCardCount);
    }
    free(state);
    state = NULL;

    // Have a card in played & some in deck. Make sure played doesn't change.
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 2;
    state->deck[0][0] = 1;
    state->deck[0][1] = 2;
    state->playedCardCount = 1;
    state->playedCards[0] = 3;
    shuffle(0, state);
    if (state->playedCards[0] == 3){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Played Cards Pile Unaffected By Shuffle Test FAILED\n");
        printf("Played Card was 3, after shuffle was: %d\n\n", state->playedCards[0]);
    }
    free(state);
    state = NULL;

    // Have some cards in player hand & some in deck. Make sure player hand doesn't change.
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 2;
    state->deck[0][0] = 1;
    state->deck[0][1] = 2;
    state->handCount[0] = 1;
    state->hand[0][0] = 3;
    shuffle(0, state);
    if (state->handCount[0] == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Hand Unaffected By Shuffle Test FAILED\n");
        printf("Hand Count was 1, after shuffle was: %d\n\n", state->handCount[0]);
    }
    free(state);
    state = NULL;

    // Have some cards in player hand & some in deck. Make sure player hand doesn't change.
    state = malloc(sizeof(struct gameState));
    state->deckCount[0] = 2;
    state->deck[0][0] = 1;
    state->deck[0][1] = 2;
    state->handCount[0] = 1;
    state->hand[0][0] = 3;
    shuffle(0, state);
    if (state->handCount[0] == 1){
        numTests++;
    } else {
        numTests++;
        numFailures++;
        printf("Hand Unaffected By Shuffle Test FAILED\n");
        printf("Hand Contained only card 3, after shuffle was: %d\n\n", state->hand[0][0]);
    }
    free(state);
    state = NULL;
	
	// Check that nothing else in game state has been changed
		// Including other player hands
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
	shuffleUnitTests();
	return 0;
}