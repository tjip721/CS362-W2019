
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "unittestFxn.h"

int main(){
int ii,jj,kk,ll, allPassed, gameOver, result; 

  allPassed = 1; 
//  int k[10] = {adventurer, council_room, feast, gardens, mine,
//	       remodel, smithy, village, baron, great_hall};

  struct gameState G;


	//Tests for if isGameOver fxn works correctly
	//Game is over cases

	//Provinces are empty
	for(ii = 0; ii < treasure_map+1; ii++){
		G.supplyCount[ii] = 10; 
	}
	G.supplyCount[province] = 0; 
	gameOver = isGameOver(&G);
	if(!assertFxn(gameOver, 1)){
		allPassed = 0; 
		printf("isGameOver fxn test failed w/ provinces set to 0\n"); 
	}

	//3 supplies are empty
	for(ii = 0; ii < treasure_map+1; ii++){

		for(kk = ii; kk < treasure_map+1; kk++){
			for(ll = kk; ll < treasure_map+1; ll++){
				//Set every supply back to 1 to run again
				for(jj = 0; jj < treasure_map+1; jj++){
					G.supplyCount[jj] = 1; 
				}
				G.supplyCount[ii] = 0; 
				G.supplyCount[kk] = 0; 
				G.supplyCount[ll] = 0; 
				gameOver = isGameOver(&G);
				result  = !((ii == kk) || (ll == kk)) || (ii==province) || (kk==province) || (ll==province) ;
				if(!assertFxn(gameOver, result)){
					allPassed = 0; 
					printf("isGameOver fxn test failed w/ supplies %i, %i, %i set empty. Expected result of %i got %i\n", ii, kk, ll, result, gameOver); 
				}
			}	
		}
	}
	
	//Game is not over
	//All supplies have 1 in them
	for(jj = 0; jj < treasure_map+1; jj++){
		G.supplyCount[jj] = 1; 
	}
	gameOver = isGameOver(&G);
	if(!assertFxn(gameOver, 0)){
		allPassed = 0; 
		printf("isGameOver fxn test failed w/ 1 in all supplies.\n"); 
	}
	char fxnName[] = {"isGameOver"};
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
/*
int isGameOver(struct gameState *state) {
  int i;
  int j;
	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }
  if ( j >= 3)
    {
      return 1;
    }

  return 0;
}
*/


