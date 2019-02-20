#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "unittestFxn.h"

#define DEBUG 0
#define NOISY_TEST 1
#define NUMTESTS 1000

int main(argv, argc){
	srand(NULL); 
	int ii, deckCount, discardCount, handCount, numPlayers, currentPlayer, allPassed; 
	int oppHandCount[MAX_PLAYERS], oppDeckCount[MAX_PLAYERS], oppDiscardCount[MAX_PLAYERS]; 
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
	struct gameState G; 

	printf ("Testing Outpost card fxn.\n");
	printf ("RANDOM TESTS.\n");


	int count = 0; 
	allPassed = 1; 
	while(count < NUMTESTS){
		numPlayers = (rand() % 2) + 2; 
		G.numPlayers = numPlayers;
		currentPlayer = rand() % G.numPlayers; 
		//Initialize a random game scenario to start w/
		initializeGame(numPlayers, k, rand(), &G);
		endTurn(&G);  //End first players turn and then modify gamestate manually

		//Randomize deck and hand counts for selected player
		G.handCount[currentPlayer] = rand() % (MAX_HAND-2); //must hold 2 more drawn treasure
		for (ii = 0; ii < G.handCount[currentPlayer]; ii++){
			drawCard(currentPlayer, &G);
		}
		G.deckCount[currentPlayer] = rand() % MAX_DECK; 
		int cardPosition = rand() % (G.handCount[currentPlayer]); 
		G.hand[currentPlayer][cardPosition] = adventurer; //insert adventurer at cardPosition
		G.whoseTurn = currentPlayer; 

		//Remember states before playing card
		handCount= G.handCount[G.whoseTurn]; 
		deckCount = G.deckCount[G.whoseTurn];
		discardCount = G.discardCount[G.whoseTurn];
		int outposts = G.outpostPlayed; 
		int playedCount= G.playedCardCount; 
		int player = G.whoseTurn; 
		for(ii=0; ii < numPlayers; ii++){
			if(ii != currentPlayer){
				oppHandCount[ii] = G.handCount[ii]; 
				oppDeckCount[ii] = G.deckCount[ii] ; 
				oppDiscardCount[ii] = G.discardCount[ii]; 
			}
		}
		int supplyCounts[treasure_map+1]; 
		for(ii=0; ii < treasure_map+1; ii++){
			supplyCounts[ii] = G.supplyCount[ii]; 
		}

		//Play card and check new game state
		playCard(cardPosition, -1, -1, -1, &G); 
		
	if(!assertFxn(outposts, G.outpostPlayed)){ 
		allPassed = 0; 
		int addedCards = G.outpostPlayed - outposts; 
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
	//Check for no state change in other players. 
		for(ii=1; ii < numPlayers; ii++){
			if(ii != currentPlayer){
				if(!assertFxn(oppDeckCount[ii], G.deckCount[ii] )){
					allPassed = 0; 
					printf("Other players deck was altered by Outpost card fxn.\n"); 
				}
				if(!assertFxn(oppHandCount[ii], G.handCount[ii] )){
					allPassed = 0; 
					printf("Other players hand was altered by Outpost card fxn.\n"); 
				}
				if(!assertFxn(oppDiscardCount[ii], G.discardCount[ii] )){
					allPassed = 0; 
					printf("Other players discard pile was altered by Outpost card fxn.\n"); 
				}
			//Check for no state change in victory card piles and kingdom card piles
				for(ii=0; ii < treasure_map+1; ii++){
					if(!assertFxn(supplyCounts[ii], G.supplyCount[ii] )){
						allPassed = 0; 
						printf("Supply count %i was altered by Outpost card fxn.\n", ii) ; 
					}
				}
			}
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

		
		printf("End of random run %i.\n", count); 
		count++; 
	}
	char fxnName[] = {"Outpost Card"}; 
	passFail(allPassed, fxnName); 

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
