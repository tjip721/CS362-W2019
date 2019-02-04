#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "unittestFxn.h"

int main(){
  int ii, handCount, addedCards;
  int allPassed = 1; 

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  initializeGame(2, k, 30, &G);

	printf("Starting smithyFxn test\n");
//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
//int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state) 

	G.hand[0][0] = smithy; //Put smithy into hand at position 0
	G.whoseTurn = 0; 
	handCount= G.handCount[G.whoseTurn]; 
	int deckCount = G.deckCount[G.whoseTurn];
	int playedCount= G.playedCardCount; 
	int opp = (G.whoseTurn+1)%2; 
	int oppHandCount = G.handCount[opp]; 
	int oppDeckCount = G.deckCount[opp] ; 
	int oppDiscardCount = G.discardCount[opp]; 
	int supplyCounts[treasure_map+1]; 
	for(ii=0; ii < treasure_map+1; ii++){
		supplyCounts[ii] = G.supplyCount[ii]; 
	}
        playCard(0, -1, -1, -1, &G);
	//Check if 3 cards were added to hand and smithy was discarded
	if(!assertFxn(handCount+2, G.handCount[G.whoseTurn])){ 
		allPassed = 0; 
		addedCards = G.handCount[G.whoseTurn] - handCount; 
		printf("%i cards were added to the players hand instead of net 2 by Smithy card fxn.\n",addedCards); 
	}
	if(!assertFxn(playedCount+1, G.playedCardCount)){ 
		allPassed = 0; 
		printf("More or less than just the smithy card was discarded from the players hand. Expected = %i, actual = %i\n", playedCount+1, G.playedCardCount); 
	}
	//Check that 3 cards were removed from players deck and none from other players
	if(!assertFxn(deckCount-3,G.deckCount[G.whoseTurn]) ){
		allPassed = 0; 
		printf("Players deck did not have exactly 3 cards removed by Smithy card fxn.\n"); 
	}
	if(!assertFxn(oppDeckCount, G.deckCount[(G.whoseTurn+1)%2] )){
		allPassed = 0; 
		printf("Other players deck was altered by Smithy card fxn.\n"); 
	}
	//Check for no state change in other players. 
	if(!assertFxn(oppHandCount, G.handCount[opp] )){
		allPassed = 0; 
		printf("Other players hand was altered by Smithy card fxn.\n"); 
	}
	if(!assertFxn(oppDiscardCount, G.discardCount[opp] )){
		allPassed = 0; 
		printf("Other players discard pile was altered by Smithy card fxn.\n"); 
	}
	//Check for no state change in victory card piles and kingdom card piles
	for(ii=0; ii < treasure_map+1; ii++){
	if(!assertFxn(supplyCounts[ii], G.supplyCount[ii] )){
		allPassed = 0; 
		printf("Supply count %i was altered by Smithy card fxn.\n", ii); 
	}
	}
	char fxnName[] = {"Smithy Card"};
	passFail(allPassed, fxnName); 

}

/*int smithyFxn(int handPos, int currentPlayer, struct gameState *state) {
	//+3 Cards
      int i=0; 
      for (i = 0; i <= 3; i++) //Assignment 2 BUG, should be < 3; 
	{
	  drawCard(currentPlayer, state);
	}
			
      //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
}
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
