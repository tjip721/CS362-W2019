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

	printf("Starting adventurerFxn test\n");
//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
//int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state) 

	G.hand[0][0] = adventurer; //Put adventurer into hand at position 0
	G.whoseTurn = 0; 
	handCount= G.handCount[G.whoseTurn]; 
	int deckCount = G.deckCount[G.whoseTurn];
	int playedCount= G.playedCardCount; 
	int player = G.whoseTurn; 
	int opp = (G.whoseTurn+1)%2; 
	int oppHandCount = G.handCount[opp]; 
	int oppDeckCount = G.deckCount[opp] ; 
	int oppDiscardCount = G.discardCount[opp]; 
	int supplyCounts[treasure_map+1]; 
	for(ii=0; ii < treasure_map+1; ii++){
		supplyCounts[ii] = G.supplyCount[ii]; 
	}
        playCard(0, -1, -1, -1, &G);
	//Check if 2 treasure cards were added to hand and adventurer was sent to played pile
	int treasure1 = (G.hand[G.whoseTurn][G.handCount[player]] == silver || G.hand[G.whoseTurn][G.handCount[player]]== gold || G.hand[G.whoseTurn][G.handCount[player]]);
	int treasure2 = (G.hand[G.whoseTurn][G.handCount[player]-1] == silver || G.hand[G.whoseTurn][G.handCount[player]-1]== gold || G.hand[G.whoseTurn][G.handCount[player]-1]); 
	if(!assertFxn(treasure1, treasure2) && treasure1 == 1 ){ 
		allPassed = 0; 
		addedCards = G.handCount[G.whoseTurn] - handCount; 
		printf("2 treasure cards were not added to the hand by the Adventurer card fxn. Last two cards treasure?: %i, %i\n", G.hand[G.whoseTurn][handCount+1], G.hand[G.whoseTurn][handCount+2]); 
	}
	if(!assertFxn(playedCount+1, G.playedCardCount)){ 
		allPassed = 0; 
		printf("More or less than just the Adventurer card was played from the players hand. Expected = %i, actual = %i\n", playedCount+1, G.playedCardCount); 
	}
	//Check that at least 2 cards were removed from players deck and none from other players
	if(deckCount-2 <= G.deckCount[G.whoseTurn] ){
		allPassed = 0; 
		printf("Players deck did not have at least 2 cards removed by Adventurer card fxn.\n"); 
	}
	if(!assertFxn(oppDeckCount, G.deckCount[(G.whoseTurn+1)%2] )){
		allPassed = 0; 
		printf("Other players deck was altered by Adventurer card fxn.\n"); 
	}
	//Check for no state change in other players. 
	if(!assertFxn(oppHandCount, G.handCount[opp] )){
		allPassed = 0; 
		printf("Other players hand was altered by Adventurer card fxn.\n"); 
	}
	if(!assertFxn(oppDiscardCount, G.discardCount[opp] )){
		allPassed = 0; 
		printf("Other players discard pile was altered by Adventurer card fxn.\n"); 
	}
	//Check for no state change in victory card piles and kingdom card piles
	for(ii=0; ii < treasure_map+1; ii++){
	if(!assertFxn(supplyCounts[ii], G.supplyCount[ii] )){
		allPassed = 0; 
		printf("Supply count %i was altered by Adventurer card fxn.\n", ii); 
	}
	}
	char fxnName[] = {"Adventurer Card"};
	passFail(allPassed, fxnName); 

	printf("\n"); 
}

/*int adventurerFxn(struct gameState *state, int currentPlayer){
  int temphand[MAX_HAND];// moved above the if statement
  int drawntreasure=0;
  int z = 0;// this is the counter for the temp hand
  int cardDrawn;
 
     while(drawntreasure<2){
	if (state->deckCount[currentPlayer] <=1){//if the deck is empty we need to shuffle discard and add to deck //Assignment 2 BUG, should be <1
	  shuffle(currentPlayer, state);
	}
	drawCard(currentPlayer, state);
	cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  drawntreasure++;
	else{
	  temphand[z]=cardDrawn;
	  state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	  z++;
	}
      }
      while(z-1>=0){
	state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
	z=z-1;
      }
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
