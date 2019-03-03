#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "unittestFxn.h"

int main(){
int ii, jj, handCount;
int allPassed = 1; 

//  int k[10] = {adventurer, council_room, feast, gardens, mine,
//	       remodel, smithy, village, baron, great_hall};

  struct gameState G;


	//Tests for players hand count
	for(ii = 0; ii< MAX_PLAYERS; ii++){
	for(jj = -50; jj <= MAX_HAND+100; jj+=50){
		G.handCount[ii] = jj; 
		G.whoseTurn = ii; 
		handCount = numHandCards(&G);
	//	assert(handCount==jj); 
	//	printf("Test passed for Player %i w/ %i cards numHandCards Fxn\n", ii, jj); 
	/* How many cards current player has in hand */

		if(!assertFxn(jj, handCount)){
			allPassed = 0; 
		}
	}
	}

	char fxnName[] = {"numHandCards"};
	passFail(allPassed, fxnName); 
	printf("\n"); 
}
/*
struct gameState {
  int numPlayers; //number of players
  int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
  int embargoTokens[treasure_map+1];
  int outpostPlayed;
  int outpostTurn;
  int whoseTurn;
  int phase;
  int numActions; // Starts at 1 each turn //
  int coins; // Use as you see fit! //
  int numBuys; // Starts at 1 each turn //
  int hand[MAX_PLAYERS][MAX_HAND];
  int handCount[MAX_PLAYERS];
  int deck[MAX_PLAYERS][MAX_DECK];
  int deckCount[MAX_PLAYERS];
  int discard[MAX_PLAYERS][MAX_DECK];
  int discardCount[MAX_PLAYERS];
  int playedCards[MAX_DECK];
  int playedCardCount;
};
*/
