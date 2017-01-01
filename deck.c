#include "game.h"					/* Including the main header file*/
/******************************************************************************/
/*			"deck.c" 														  */
/*	This file contains a series of functions that allow not only the creation */
/*  and	maintenance but also the interaction with a deck of cards collection, */
/*	the collection selected to represent a deck in this program is an array   */
/*	of cards which is declared in the main function of the program. Each      */ 
/*	card in the array is represented as a structure containing two integers,  */
/*	one indicating the card's rank and another indicating it's suit.          */
/*	Each function is explained in more detail ahead.  						  */
/******************************************************************************/


/**
 * createDeck: This function allows to create a new deck, the function takes a
 * pointer to an array of cards previously declared and populates each one of
 * it's indexed locations with a card, the function creates each card in order,
 * by suit and then rank, starting from rank 0 to 12 and then moving to the 
 * following rank until all cards have been generated for every rank.
 * After the function finishes the deck array will contain all cards for 
 * each of the 4 suits starting from suit 0 and continuing until all cards for
 * suit 3 have been generated. A counter is used to know the numerical 
 * possition of the card currently being generated and is hashed with the 
 * number of cards in a suit to know its possition in the current suit thus 
 * providint the card's value. The card's suit is obtanined in a similar 
 * fashion by dividing the current card's possition by the number of cards in a
 * suit.
 * 
 * @param deckPointer: This parameter indicates the adress to the first 
 * location on the array of cards which is the deck.
 */
void createDeck(Card *deckPointer){

	int count = 0;
	while(count < CARDS_IN_A_DECK){
		Card currentCard;

		currentCard.rank = count % CARDS_IN_A_SUIT;
		currentCard.suit = ((count)/CARDS_IN_A_SUIT) + 1;

		*deckPointer = currentCard;
		count++;
		deckPointer++;
	}
};

/**
 * displayDeckInLines: This function makes use of the helper function
 * displayBatch() which allows to print an array of cards passed as a parameter
 * by rows. In the case of the deck, the function prints the whole deck in 
 * multiple rows, each 13 items long, notice that 13 is the number of cards in 
 * a suit. Therefore a call to this method will result in the contentes of the 
 * deck being printed on screen, where the cards will be desplayed in 4 rows
 * with N cards each where N is defined as hand/suit length.
 * 
 * @param deckPointer: This parameter contains a pointer to the first adress
 * on the array of cards to be printed.
 */
void displayDeckInLines(Card deckPointer[]){
	displayBatch(deckPointer, CARDS_IN_A_SUIT, SUITS_IN_A_DECK);
}

/**
 * displayBatch: This function displays a group of cards, defined as an array 
 * in rows, these rows are specified through the functions parameters. ex: 
 * printing an entire deck of cards will show 4 rows, with 13 cards each.
 * printing a hand of cards however will show only one row with N cards, where 
 * N is the hand length, which is the amount of cards per hand. 
 * The function prints each row of cards line by line, including the cards
 * borders, their ranks and suits. 
 * 
 * @param deckPointer: This parameter contains a pointer to the first adress
 * on the array of cards to be printed.
 * @param handLength: This parameter specifies the length of each row of cards
 * that will be printed.
 * @param numHands: This parameter specifies the number of rows of cards that
 * will be printed.
 */
void displayBatch(Card deckPointer[], int handLength, int numHands){

	// Declaring utilities that will be used to print the cards.
	char *suitIcons[] = {" ",HEARTS,CLUBS,SPADES,DIAMONDS}; 
	char *ranks[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
	char *simLine = "+-------+";

	int count = 0;
	int tempCount = 0;

	int i;
	for(i = 0; i < numHands; i++){
		int j;
		tempCount = count;
		printFillerLine(simLine,handLength);
		for(j = 0; j < handLength; j++){
			int rankListIndex = deckPointer[count].rank;
			int suitIndex = deckPointer[count].suit;
			printf("%s %-2s %4s %s ","|",ranks[rankListIndex],
				suitIcons[suitIndex],"|");
			count++;
		}
		printf("\n");
		for(j = 0; j < handLength; j++){
			printf("%s %s %6s ","|","", "|" );
		}
		printf("\n");
		for(j = 0; j < handLength; j++){
			printf("%s %s %6s ","|","", "|" );
		}
		printf("\n");
		for(j = 0; j < handLength; j++){
			int rankListIndex = deckPointer[tempCount].rank;
			int suitIndex = deckPointer[tempCount].suit;
			printf("%s %3s %3s %s ","|",suitIcons[suitIndex],
				ranks[rankListIndex],"|");
			tempCount++;
		}
		printf("\n");
		printFillerLine(simLine,handLength);
		printf("\n");
	}

}

/**
 * dealDeck: This function allows to deal to each player their cards the same 
 * way cards are dealt in a normal game of cards, starting with any player x
 * each player is given or "dealt" one card in every iteration for a given N
 * amount of times, notice that N is the length of the hand of cards to be 
 * dealt. After this function is done executing, each player in the player 
 * array should have an array containing the cards that compose their dealt 
 * hand.
 * @param deck: This parameter contains a pointer to the first location
 * on the array of cards that compose the deck of cards.
 * @param playersInGame: This parameter contains a pointer to the first 
 * location on the aray of players.
 * @param handLength: This parameter indicates the length of the hands of cards 
 * that will be dealt.
 * @param numHands: This parameter indicates the number of hands that will be 
 * dealt.
 */
void dealDeck(Card deck[], Player playersInGame[], int handLength,
	 int numHands){

	int count = 0;
	int i;

	for(i = 0; i < handLength; i++){
		int j;
		for(j = 0;j < numHands;j++){
			playersInGame[j].playerHand[i] = deck[count];
			count++;
		}
	}
	for(i = 0; i < numHands; i++){
		sortHand((playersInGame[i].playerHand), handLength, 1);
		playersInGame[i].playerNumber = i + 1;
	}
	printf("%d %s\n\n", count,"card(s) dealt." );
}

/**
 * printFillerLine: This function prints a line of specified length containing 
 * any entered string pattern, this is useful when creating special formatting 
 * like the one used in this program to represent the cards. This function 
 * allows for code clarity and readability by reducing the complexity of the 
 * printBatch() function when printing any group of cards.
 * 
 * @param lineString: This parameter contains a string that will be printed to
 * screen in the same line a given number of times.
 * @param numOfHeaders: This parameter indicates the number of times that the 
 * entered string will be printed to screen.
 */
void printFillerLine(char *lineString, int numOfHeaders){

	int numLines = numOfHeaders;
	while(numLines--){
		printf("%s ",lineString);
	}
	printf("\n");
}

/**
 * initializeRandomSeed: This program creates the number which seeds the 
 * random number generator used by rand(). This number is used by the function
 * rand() allowing to create a unique random number on each call. Notice that
 * this function should be called once per any running program instance in 
 * order to obtain true unique random numbers on each rand() call.
 * 
 */
void initializeRandomSeed(){
	srand(time(NULL));
}

/**
 * randomizePick: This function creates a random number from 0 to a given 
 * number entered by parameters and returns it.
 * 
 * @param  bound: This parameter indicates the interval in which the random 
 * number will be created. ex given a bound of 10 this function will only 
 * generate a number from 0 to 10, etc.
 * 
 * @return: This function will return a true generated random number within 
 * the specified interval.
 */
int randomizePick(int bound){
	return rand() % bound;
}

/**
 * swapCards: This function is a clasic swapping function that uses pointers 
 * to swap the contents of two memory adresses, in this case it takes two 
 * pointers to adresses containing cards and swaps their contents.
 * 
 * @param cardA: This parameter contains a pointer to the first card value 
 * to be swapped.
 * @param cardB: This parameter contains a pointer to the second card value 
 * to be swapped.
 */
void swapCards(Card *cardA, Card *cardB){
	Card tempCard;

	tempCard = *cardA;
	*cardA = *cardB;
	*cardB = tempCard;
}

/**
 * shuffleDeck:This function relies on the helper function "shuffleBatch()"
 * which takes a batch of cards and shuffles them in the same way a 
 * regular deck of cards would be shuffled. The function goes through the 
 * deck and shuffles each card with another card on the deck, the function
 * starts shuffling at possition one and stops once the end of the deck is 
 * reached. Notice that what makes this function a good shuffle is that
 * each card is shuffled with another card at random, this is achieved by 
 * determining a true random number from 0 to 51 which dictates the index of 
 * the card to be shuffled on every iteration.
 * 
 * @param deckPointer: This parameter contains an adress to the first location 
 * of the deck of cards, which allows the function access to the array.
 */
void shuffleDeck(Card deckOfCards[]){
	shuffleBatch(deckOfCards, CARDS_IN_A_DECK);
}



/**
 * shuffleBatch:This function takes a batch of card and shuffles it the way a 
 * regular deck of cards would be shuffled. The function goes through the 
 * batch and shuffles each card with another card on the batch, the function
 * starts shuffling at possition one and stops once the end of the batch is 
 * reached. Notice that what makes this function a good shuffle is that
 * each card is shuffled with another card at random, this is achieved by 
 * determining a true random number from 0 to batch-size which dictates the 
 * index of the card to be shuffled on every iteration.
 * 
 * @param deckPointer: This parameter contains an adress to the first location 
 * of the batch of cards, which allows the function access to the array.
 */
void shuffleBatch(Card batchOfCards[], int batchSize){

	initializeRandomSeed();
	int i;
	for(i = 0; i < batchSize; i++){
		int nextRandomIndex = randomizePick(batchSize - 1);
		swapCards(&batchOfCards[i], &batchOfCards[nextRandomIndex]);
	}
}



/**
 * validateGameInput: This function validates that the numbers provided to the
 * game are valid, that is: The function checks that both numbers are under the 
 * specified max values, which were given on the program specs/instructions, 
 * and also that the the number of cards being dealt is within the deck size,
 * ex: a deck has 52 cards so dealing 10 players 14 cards wouldn't be possible 
 * as there are not enough cards in this deck to fulfill this request 
 * (52 <  140), in contrast dealing 10 players hands that are 3 cards long 
 * would be possible as there are enough cards to fulfill this request. 
 * (52 > 30). The program will print meaningful error messages for any error
 * that might occur.
 * 
 * @param  handLength: This parameter contains the tentative hand length 
 * entered to the game.
 * @param  numHands: This parameter contains the number tentative number of 
 * hands to be used by the game.
 * 
 * @return: This program returns TRUE if the imput entered throught the 
 * parameters has been validated as viable, or FALSE otherwise.
 */
bool validateGameInput(int handLength, int numHands){

	int totalNumberOfCards = handLength * numHands;
	bool answer = TRUE;

	if(handLength != MAX_HAND_LENGTH){
		printf("%s","ERROR! The hand length entered is not valid, ");
		printf("%d %s", handLength, "was entered, hand must be of length ");
		printf("%d\n",MAX_HAND_LENGTH );

		answer = FALSE;
	}
	if((numHands <= 0) || (numHands > MAX_PLAYERS_ALLOW)){
		printf("%s","ERROR! The number of players entered is not valid, ");
		printf("%d %s\n", numHands, "is not within the allowed range.");

		answer = FALSE;
	}

	if((totalNumberOfCards > CARDS_IN_A_DECK)
		&&	((handLength + numHands) > 0 )){
		printf("%s","ERROR! The deck could not be created, current ");
		printf("%s %d","configurations would require", totalNumberOfCards);
		printf("%s \n%s %d"," cards","the current deck is ",CARDS_IN_A_DECK);
		printf("%s\n"," cards long." );

		answer = FALSE;
	}
	return answer;
}

/**
 * sortHand: Simple clasic insertion sort that is used to sort the 
 * elements in the Card array using integers values as a mean for comparison.
 * The value one passed thrugh sortOrder will guarantee that the fucntion 
 * orders the passed array playerHand using one of two criterias for sorting
 * '1' will ensure the Card array is ordered by rank. Anything else will ensure
 * that the passed arrray will be sorted using its suit. Notice that this 
 * algorithm uses the helper function swap to swap values.
 * 
 * @param playerHand: This parameter contains an adress to the first location 
 * of the array that contains the elements to be sorted.
 * @param handLength: This parameter defines the length of the array that will 
 * be sorted.
 * @param sortOrder: This parameter dictates what parameter will be used as a
 * for rule for comparison sorting. 
 */
void sortHand(Card playerHand[], int handLength, int sortOrder){
	int i;
	if(sortOrder == 1){
		for(i = 1; i < handLength; i++){
			Card temp = playerHand[i];
			int j = i - 1;
			while((temp.rank > playerHand[j].rank) && (j >= 0)){
				swapCards(&playerHand[j+1], &playerHand[j]);
				j--;
			}
			playerHand[j+1] = temp;
		}
	}else {
		for(i = 1; i < handLength; i++){
			Card temp = playerHand[i];
			int j = i - 1;
			while((temp.suit > playerHand[j].suit) && (j >= 0)){
				swapCards(&playerHand[j+1], &playerHand[j]);
				j--;
			}
			playerHand[j+1] = temp;
		}
	}
}











