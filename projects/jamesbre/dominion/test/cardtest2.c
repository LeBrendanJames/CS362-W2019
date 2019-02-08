#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// adventurer

void adventurerUnitTests(){
	// Check that player hand has two more treasure after running function
		// Of each type too (like make sure it works regardless of whether the treasure is copper/silver/gold)
	
	// With two treasure directly on top, check that nothing else changes (those are just drawn into hand)
	
	// With one other card then two treasure, check that the 1st card gets discarded and the two treasure are drawn 
	
	// With other card/treasure/other card/treasure make sure it works correctly
	
	// With a shuffle in the middle of drawing, make sure the drawn cards that aren't treasure aren't involved in the shuffle/don't show up in the deck
	
	// With a shuffle in the middle and one treasure drawn either side of the shuffle, make sure that it all works  
	
	// If there's only one treasure remaining in deck + discard pile, make sure it just picks up that one treasure

	// Check that game state/ other player hands/ kingdom cards/ victory piles are unaffected
	
}



int main(int argc, char* argv[]){
	adventurerUnitTests();
	return 0;
}

