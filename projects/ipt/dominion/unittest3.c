#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "unittestFxn.h"

/*
int passFail(int allPassed){
	if(allPassed){
		printf("All tests passed for whoseTurn Fxn\n" ); 
		return 1; 
	} else {
		printf("Test FAILED for whoseTurn Fxn\n"); 
		return 0; 
	}
}*/

int main(){
int ii, player, allPassed;  

  allPassed = 1; 
//  int k[10] = {adventurer, council_room, feast, gardens, mine,
//	       remodel, smithy, village, baron, great_hall};

  struct gameState G;


	//Tests for player 1 hand count
	for(ii = -5; ii< MAX_PLAYERS+1; ii++){
		G.whoseTurn = ii; 

		player = whoseTurn(&G);

		if(!assertFxn(ii, player)){
			allPassed = 0; 
		}
	}
	char fxnName[] = {"whoseTurn"};
	passFail(allPassed, fxnName); 
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
