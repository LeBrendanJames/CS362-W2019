#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// shuffle

void shuffleUnitTests(){
	// **Seed random before each test so that unit tests are deterministic**
		// Will need to find seeds that have the effect I want (like actually change order of cards or not)
		
	// Pass in deck of 0 and make sure function returns -1
	
	// Pass in hand of 5 (or whatever size), make sure resulting state has deckCount of 5
		
	// Pass in hand of size 5 (or whatever size), make sure resulting hand still has 5 cards
	
	// Pass in hand of all the same cards, make sure resulting hand is the same (in size and card values)
	
	// Pass in hand of all different cards - make sure they're all still there
		// Maybe do this by passing in a sorted hand and sorting the resulting hand then check equality
		
	// Pass in deck of different cards, make sure they end up in a different order (random seed permitting)
	
	// Pass in deck of max size, made sure all cards are still there after shuffle
	
	// Pass in deck of max size, make sure first and last card are part of the sort 
		
	// Have some cards in player hand & some in deck. Make sure player hand doesn't change.
	
	// Have a card in played & some in deck. Make sure played doesn't change.
	
	// Check that nothing else in game state has been changed
		// Including other player hands
}

int main(int argc, char* argv[]){
	shuffleUnitTests();
	return 0;
}