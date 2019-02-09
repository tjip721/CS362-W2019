#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "unittestFxn.h"

/*
int fullDeckCount(int player, int card, struct gameState *state) {
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
}
*/

int main(){
int jj,kk,ll,ii, allPassed, deckCount, player, card;

  allPassed = 1; 
//  int k[10] = {adventurer, council_room, feast, gardens, mine,
//	       remodel, smithy, village, baron, great_hall};

  struct gameState G;


	//Tests for player's full deck count of a card
	for(player = 0; player < MAX_PLAYERS; player++){
	for(card = 0; card < treasure_map+1; card++){
	for(jj = 0; jj < MAX_DECK; jj+=50){
	for(kk = 0; kk < MAX_HAND; kk+=50){
	for(ll = 0; ll < MAX_HAND; ll+=50){

		G.deckCount[player] = jj; 
		G.handCount[player] = kk; 
		G.discardCount[player] = ll; 
		for(ii=0; ii < G.deckCount[player]; ii++){
			G.deck[player][ii] = card; 
		}
		for(ii=0; ii < G.handCount[player]; ii++){
			G.hand[player][ii] = card; 
		}
		for(ii=0; ii < G.discardCount[player]; ii++){
			G.discard[player][ii] = card; 
		}
		deckCount = fullDeckCount(player, card, &G);
		/* Here deck = hand + discard + deck */

		if(!assertFxn(jj+kk+ll, deckCount)){
			allPassed = 0; 
			printf("fullDeckCount failed on player %i, card %i, deck count %i, hand count %i, discard count %i. deckCount = %i.\n", player, card, jj, kk, ll, deckCount);
		}
	}
	}
	}
	}
	}
	char fxnName[] = {"fullDeckCount"};
	passFail(allPassed, fxnName); 
	printf("\n"); 
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
*/
