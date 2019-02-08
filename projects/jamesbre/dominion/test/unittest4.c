#include <stdio.h>
#include <stdlib.h>
#include "../dominion.h"
#include "../dominion_helpers.h"

// endTurn


void endTurnUnitTests(){
	// NOT END OF GAME SCENARIO
		// Check that players hand is empty after running
		
		// Check that players discard increased by # of card in hand
		
		// Check that cards moved from hand to discard are correct
		
		// check that all the rest of the state looks correct
		
		// Check that next player is correct 
			// (I'm pretty sure there is an off-by-one error here)
		
		// Check that next player draws hand correctly (5 cards, right?)
		
		// check that coins are correct (whatever correct means)
		
	
	// END OF GAME SCENARIO
		// (Per comment in .h file, this shouldn't advance player, but there doesn't seem to be any code that implements that)
}


int main(int argc, char* argv[]){
	endTurnUnitTests();
	return 0;
}