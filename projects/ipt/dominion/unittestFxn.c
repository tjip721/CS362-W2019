#include <stdio.h>
#include <string.h> 

int passFail(int allPassed, char *fxnName){
	if(allPassed){
		printf("All tests passed for %s Fxn\n", fxnName ); 
		return 1; 
	} else {
		printf("Test FAILED for %s Fxn\n", fxnName); 
		return 0; 
	}
}


int assertFxn(int test, int actual){
	if(test == actual){
		return 1; 
	} else { 
		return 0; 
	}
}
