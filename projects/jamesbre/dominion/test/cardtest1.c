#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// smithy
// Smithy adds three cards to a players hand (and is itself discarded)

void smithyUnitTests(){
	// Check handCount two higher than what player started with (+3 cards - Smithy)
	
	// Check discard count one higher (as long as there were 3 cards to draw from deck)
	
	// Check that the three cards drawn are equal to the three cards that were on the top of the deck
	
	// Check that the card discarded is in fact Smithy 
	
	// Starting with deck empty, ensure that discard pile = 1 and card is Smithy
	// In other words, check that shuffle of discard pile into deck happens BEFORE Smithy is discarded
	
	// check nothing else changes about the state of the game (including other players card piles)
	// check nothing changes with victory card piles or kingdom card piles 
}



int main(){
    smithyUnitTests();
    return 0;
}