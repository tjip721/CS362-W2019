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
	       remodel, village, village, baron, great_hall};

  struct gameState G;

  initializeGame(2, k, 30, &G);

	printf("Starting village card test\n");
//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
//int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state) 

	G.hand[0][0] = village; //Put village into hand at position 0
	G.whoseTurn = 0; 
	int player= G.whoseTurn; 
	G.numActions = 1; 
  	G.playedCardCount = 0;
	G.discardCount[player] = 0; 
	handCount= G.handCount[G.whoseTurn]; 
	int deckCount = G.deckCount[G.whoseTurn];
	int playedCount= G.playedCardCount; 
	int actions = G.numActions; 
	int opp = (G.whoseTurn+1)%2; 
	int oppHandCount = G.handCount[opp]; 
	int oppDeckCount = G.deckCount[opp] ; 
	int oppDiscardCount = G.discardCount[opp]; 
	int playerDiscardCount = G.discardCount[player]; 
	int supplyCounts[treasure_map+1]; 
	for(ii=0; ii < treasure_map+1; ii++){
		supplyCounts[ii] = G.supplyCount[ii]; 
	}
        playCard(0, -1, -1, -1, &G);
	//Check if 1 card was added to hand and 1 was discarded
	if(!assertFxn(handCount, G.handCount[G.whoseTurn])){ 
		allPassed = 0; 
		addedCards = G.handCount[G.whoseTurn] - handCount; 
		printf("%i cards were added to the players hand instead of net 0 by village card fxn.\n",addedCards); 
	}
	if(!assertFxn(playerDiscardCount+1, G.discardCount[player])){ 
		allPassed = 0; 
		printf("More or less than just the village card was discarded from the players hand. Expected = %i, actual = %i\n", playerDiscardCount+1, G.discardCount[player]); 
	}
	if(!assertFxn(playedCount+1, G.playedCardCount)){ 
		allPassed = 0; 
		printf("More or less than just the village card was played from the players hand. Expected = %i, actual = %i\n", playedCount+1, G.playedCardCount); 
	}
	//Check that 1 cards were removed from players deck and none from other players
	if(!assertFxn(deckCount-1,G.deckCount[G.whoseTurn]) ){
		allPassed = 0; 
		printf("Players deck did not have exactly 1 card removed by village card.\n"); 
	}
	if(!assertFxn(oppDeckCount, G.deckCount[(G.whoseTurn+1)%2] )){
		allPassed = 0; 
		printf("Other players deck was altered by village card fxn.\n"); 
	}
	//Check that 2 actions are added to state
	if(!assertFxn(actions+1, G.numActions )){
		allPassed = 0; 
		printf("2 Actions were not added to the game state by village card.\n"); 
	}
	
	//Check for no state change in other players. 
	if(!assertFxn(oppHandCount, G.handCount[opp] )){
		allPassed = 0; 
		printf("Other players hand was altered by village card fxn.\n"); 
	}
	if(!assertFxn(oppDiscardCount, G.discardCount[opp] )){
		allPassed = 0; 
		printf("Other players discard pile was altered by village card fxn.\n"); 
	}
	//Check for no state change in victory card piles and kingdom card piles
	for(ii=0; ii < treasure_map+1; ii++){
	if(!assertFxn(supplyCounts[ii], G.supplyCount[ii] )){
		allPassed = 0; 
		printf("Supply count %i was altered by village card fxn.\n", ii); 
	}
	}
	char fxnName[] = {"village Card"};
	passFail(allPassed, fxnName); 
	printf("\n"); 

}

/*   case village:
      //+1 Card
      drawCard(currentPlayer, state);
			
      //+2 Actions
      state->numActions = state->numActions + 2;
			
      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
		
	
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
