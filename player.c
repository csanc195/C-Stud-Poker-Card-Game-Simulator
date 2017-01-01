 /****************************************************************************/
 /* 	"player.c" 															 */
 /*	This file contains a series of functions that allow the creation of      */
 /* players and also the posibility to print each player's hand on screen.   */ 
 /*	Notice that the function createAllPLayers() is not really needed in order*/
 /*	for the program to work but this function can be used to create sets of  */
 /*	players which abide by specific parameters and thus it was included in   */
 /* this file but not in the needed instructions to recreate the game as it  */
 /* was proposed in the assignement.										 */
 /****************************************************************************/

#include "game.h"						/* Including the main header file*/

/**
 * createAllPlayers: This function creates all the players for the given 
 * game configurations, the function takes a pointer to the first location of 
 * an array of players which is an structure defined in the game.h, and 
 * populates each location of the array with a recently created Player.
 * Notice that this function's purpose is not really evident now as the game
 * can continue to deal the hands to the players as it is without calling
 * createAllPlayers(), but this function could be used to create all palyers 
 * of the game with a unique initial configuration.
 * 
 * @param playersInGamePt: This parameter contains a pointer to the first 
 * location in the array of Players to be populated.
 * @param handLength: This parameter indicates the hand length of the players.
 * @param numHands: This parameter indicates the number of hands/players that 
 * will be initialized.
 */
void createAllPlayers(Player *playersInGamePt, int handLength, int numHands){

	int count = 0;
	while(count < numHands){
		/* Create a new Person element and save it to a location in the array */
		 Player tempPlayer;
		 *playersInGamePt = tempPlayer;		

		playersInGamePt++;
		count++;
	}
	printf("%s %d %s %d %s\n","Created: ", count, "players, each was given",
	 handLength, "card hands.");
}

/**
 * displayAllPlayersHands: This function displays the hands of all the players 
 * in the players array. It iterates through the structure and prints the hand 
 * of cards for each player. Each hand is printed using the helper function 
 * located in the file deck.c which allows to print a batch of cards.
 * 
 * @param playersList: This parameter contains a pointer to the first location 
 * on the players array.
 * @param handLength: This parameter contains the length of each player's hand.
 * @param numHands: This parameter contains the number of hands to be displayed
 */
void displayAllPlayersHands(Player playersList[],
	int handLength, int numHands){
	

	int count = 0;
	while(count < numHands){
		printf("%s %d\n", "Player:", (playersList[count].playerNumber));
		displayBatch(playersList[count].playerHand, handLength, 1);

		count++;
	}
}

/**
 * sortPlayers: This function sorts all of the players in an array of players
 * by their hand rank.(As its stands right now this function is incomplete)
 * @param playerList: The list of players to be sorted.
 * @param handLength: The length of each payers hand.
 * @param numHands: The total number of hands.
 */
void sortPlayers(Player playerList[], int handLength, int numHands){

	bool areThereTies = FALSE;

	int i;
	for(i = 1; i < numHands; i++){
			Player temp = playerList[i];
			int j = i - 1;

			while((temp.handRank < playerList[j].handRank) && (j >= 0)){
				int p = j+1;
				swapPlayers(&playerList[j + 1], &playerList[j]);
				j--;
			}
			playerList[j+1] = temp;
	}

	/*Decide if there are ties*/
	if(playerList[0].handRank == playerList[1].handRank){
		areThereTies = TRUE;
		printf("%s %d\n", "are there ties? ", areThereTies );
	}
}

/**
 * swapPlayers: This function enables to swap Player structures. 
 * @param playerA: The first structure to be swapped. 
 * @param playerB: The second function to be swapped.
 */
void swapPlayers(Player *playerA, Player *playerB){
	Player tempPlayer;

	tempPlayer = *playerA;
	*playerA = *playerB;
	*playerB = tempPlayer;
}

































