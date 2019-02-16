#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1
#define NUMTESTS 1000

int main(argv, argc){
	srand(NULL); 
	 int i, n, r, p, deckCount, discardCount, handCount, numPlayers, currentPlayer; 
	int[MAX_PLAYERS] oppHandCount, oppDeckCount, oppDiscardCount; 
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
	struct gameState G; 

	printf ("Testing adventurer card fxn.\n");
	printf ("RANDOM TESTS.\n");



	int currentPlayer; 
	while(count < NUMTESTS){
		numPlayers = rand() % 3 + 1; 
		currentPlayer = rand() % G.numPlayers; 
		//Initialize a random game scenario to start w/
		initializeGame(numPlayers, k, rand(), &G);
		endTurn(G); 
		//Randomize deck and hand counts for selected player
		G.handCount[currentPlayer] = rand() % (MAX_HAND-2); //must hold 2 more drawn treasure
		for (ii = 0; ii < G.handCount[currentPlayer]; ii++){
			drawCard(currentPlayer, G);
		}
		G.deckCount[currentPlayer] = rand() % MAX_DECK; 
		int cardPosition = rand()%G.handCount; 
		G.hand[currentPlayer][cardPosition] = adventurer; 
		G.whoseTurn = currentPlayer; 

		//Remember states before playing card
		handCount= G.handCount[G.whoseTurn]; 
		deckCount = G.deckCount[G.whoseTurn];
		discardCount = G.discardCount[G.whoseTurn];
		int playedCount= G.playedCardCount; 
		int player = G.whoseTurn; 
		for(ii=0; ii < numPlayers; ii++){
			if(ii != currentPlayer){
				oppHandCount[ii] = G.handCount[ii]; 
				oppDeckCount[ii] = G.deckCount[ii] ; 
				oppDiscardCount[ii] = G.discardCount[ii]; 
			}
		}
		supplyCounts[treasure_map+1]; 
		for(ii=0; ii < treasure_map+1; ii++){
			supplyCounts[ii] = G.supplyCount[ii]; 
		}

		//Play card and check new game state
		playCard(cardPosition, -1, -1, -1, &G); 
		
		//Confirm 2 treasure were added to players hand
		int treasure1 = (G.hand[G.whoseTurn][G.handCount[player]] == silver || G.hand[G.whoseTurn][G.handCount[player]]== gold || G.hand[G.whoseTurn][G.handCount[player]]);
		int treasure2 = (G.hand[G.whoseTurn][G.handCount[player]-1] == silver || G.hand[G.whoseTurn][G.handCount[player]-1]== gold || G.hand[G.whoseTurn][G.handCount[player]-1]); 
		if(!assertFxn(treasure1, treasure2) && treasure1 == 1 ){ 
			allPassed = 0; 
			addedCards = G.handCount[G.whoseTurn] - handCount; 
			printf("2 treasure cards were not added to the hand by the Adventurer card fxn. Last two cards treasure?: %i, %i\n", G.hand[G.whoseTurn][handCount+1], G.hand[G.whoseTurn][handCount+2]); 
		}	
	}
}

/*struct gameState {
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
*/
