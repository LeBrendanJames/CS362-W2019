#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// drawCard

void drawCardUnitTests(){
	// DECK EMPTY TESTS
	
		// Empty deck, empty discard, make sure -1 is returned
	
		// One card in discard
			// Check discard empty after call to function
			// Check deck empty after call to function (since the one card will be drawn)
			// Check hand 1 larger after call to function
			// Check correct card moved through
			
		// Multiple cards in discard
			// Check discard empty
			// Check deck is one less than what was in discard
			// Check hand has one extra card
			
		// Max cards in discard
			// Check discard empty
			// Check deck is one less that what was in discard
			// Check hand has one extra card
			
	
	// DECK NOT EMPTY TESTS
	
		// One card in deck
			// Check deck empty after function call
			// Check hand has one more card
			// Check discard unaffected
			// Check that card moved was correct 
			
		// Multiple cards in deck
			// Check deck has one fewer card
			// Check hand has one more card
			// Check discard unaffected
			
		// Max cards in deck
			// Check deck has one fewer card
			// Check hand has one more card
			// Check discard unaffected


	
	// Check that nothing else about gameState has changed
}

int main(int argc, char* argv[]){
	drawCardUnitTests();
	return 0;
}