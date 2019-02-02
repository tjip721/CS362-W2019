#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "unittestFxn.h"


int main(){
int ii, jj, cardVal, allPassed; 
allPassed = 1; 
//  int k[10] = {adventurer, council_room, feast, gardens, mine,
//	       remodel, smithy, village, baron, great_hall};

  struct gameState G;


	//Tests for enum value of card in players hand
	for(ii = 0; ii< MAX_PLAYERS; ii++){
	for(jj = 0; jj <= MAX_HAND; jj++){
		G.hand[ii][jj] = jj%(treasure_map+1); 
		G.whoseTurn = ii; 

		cardVal = handCard(jj, &G);
		/* enum value of indexed card in player's hand */

		if(!assertFxn(jj%(treasure_map+1), cardVal)){
			allPassed = 0; 
		}
	}
	char fxnName[] = {"handCard"};
	passFail(allPassed, fxnName); 
	}
/*
		assert(cardVal==jj%(treasure_map+1)); 
		printf("Test passed for Player %i card index %i w/ card enum value %i handCard Fxn\n", ii, jj, jj%(treasure_map+1)); 
	}
	} */

}
/*
 *enum CARD
  {curse = 0,
   estate,
   duchy,
   province,

   copper,
   silver,
   gold,

   adventurer,
   // If no/only 1 treasure found, stop when full deck seen //
   council_room,
   feast, // choice1 is supply # of card gained) //
   gardens,
   mine, // choice1 is hand# of money to trash, choice2 is supply# of
	    money to put in hand //
   remodel, // choice1 is hand# of card to remodel, choice2 is supply# //
   smithy,
   village,

   baron, // choice1: boolean for discard of estate //
   // Discard is always of first (lowest index) estate //
   great_hall,
   minion, // choice1:  1 = +2 coin, 2 = redraw //
   steward, // choice1: 1 = +2 card, 2 = +2 coin, 3 = trash 2 (choice2,3) //
   tribute,

   ambassador, // choice1 = hand#, choice2 = number to return to supply //
   cutpurse,
   embargo, // choice1 = supply# //
   outpost,
   salvager, // choice1 = hand# to trash //
   sea_hag,
   treasure_map
  };


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
