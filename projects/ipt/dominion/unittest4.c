
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
int ii,jj, allPassed, count; 

  allPassed = 1; 
//  int k[10] = {adventurer, council_room, feast, gardens, mine,
//	       remodel, smithy, village, baron, great_hall};

  struct gameState G;


	//Tests for player 1 hand count
	for(ii = 0; ii < treasure_map+1; ii++){
		for(jj = -50; jj < MAX_DECK + 50; jj++){
			G.supplyCount[ii] = jj; 
			count = supplyCount(ii, &G);
	
			if(!assertFxn(jj, count)){
				allPassed = 0; 
			}
		}
	}
	char fxnName[] = {"supplyCount"};
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
*/

