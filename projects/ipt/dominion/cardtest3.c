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
	       remodel, outpost, village, baron, great_hall};

  struct gameState G;

  initializeGame(2, k, 30, &G);

	printf("Starting outpostFxn test\n");
//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
//int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state) 

	G.hand[0][0] = outpost; //Put outpost into hand at position 0
	G.whoseTurn = 0; 
	int player = G.whoseTurn; 
	handCount= G.handCount[G.whoseTurn]; 
	int deckCount = G.deckCount[G.whoseTurn];
	int playedCount= G.playedCardCount; 
	int discardCount = G.discardCount[player];
	int opp = (G.whoseTurn+1)%2; 
	int oppHandCount = G.handCount[opp]; 
	int oppDeckCount = G.deckCount[opp] ; 
	int oppDiscardCount = G.discardCount[opp]; 
	int supplyCounts[treasure_map+1]; 
	int outposts = G.outpostPlayed; 
	for(ii=0; ii < treasure_map+1; ii++){
		supplyCounts[ii] = G.supplyCount[ii]; 
	}
        playCard(0, -1, -1, -1, &G);
	//Check outposts are incremented
	if(!assertFxn(outposts, G.outpostPlayed)){ 
		allPassed = 0; 
		addedCards = G.outpostPlayed - outposts; 
		printf("%i were added to the outposts played 1 by the outpost card.\n",addedCards); 
	}
	if(!assertFxn(discardCount, G.discardCount[player])){ 
		allPassed = 0; 
		printf("More or less than just the outpost card was discarded from the players hand. Expected = %i, actual = %i\n", discardCount, G.discardCount[player]); 
	}
	
	if(!assertFxn(oppDeckCount, G.deckCount[(G.whoseTurn+1)%2] )){
		allPassed = 0; 
		printf("Other players deck was altered by outpost card fxn.\n"); 
	}
	//Check for no state change in other players. 
	if(!assertFxn(oppHandCount, G.handCount[opp] )){
		allPassed = 0; 
		printf("Other players hand was altered by outpost card fxn.\n"); 
	}
	if(!assertFxn(oppDiscardCount, G.discardCount[opp] )){
		allPassed = 0; 
		printf("Other players discard pile was altered by outpost card fxn.\n"); 
	}
	//Check for no state change in victory card piles and kingdom card piles
	for(ii=0; ii < treasure_map+1; ii++){
	if(!assertFxn(supplyCounts[ii], G.supplyCount[ii] )){
		allPassed = 0; 
		printf("Supply count %i was altered by outpost card fxn.\n", ii); 
	}
	}

	//Check that next turn same player gets turn and hand only contains 3 cards
	endTurn(&G); 
	if(!assertFxn(player, G.whoseTurn ) ){
		allPassed = 0; 
		printf("Outpost did not give player a second turn.\n"); 
	}
	if(!assertFxn(3, G.handCount[player]) ){
		allPassed = 0; 
		printf("Outpost did not give player a 3 card hand.\n"); 
	}

	char fxnName[] = {"outpost Card"};
	passFail(allPassed, fxnName); 
	printf("\n"); 
}

/*int outpostFxn(struct gameState *state, int currentPlayer, int handPos){
      //set outpost flag
      state->outpostPlayed++;
			
      //discard card
      discardCard(handPos, currentPlayer, state, 1); //Assignment 2 BUG, trashflag = 0
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
