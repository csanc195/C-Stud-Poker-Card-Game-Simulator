/******************************************************************************/
/* 	"studPokerRules.c" 													 	  */
/* This file contains the functions which are needed in order describe a game */
/* of stud poker, mainly the functions which evaluate hands of cards and      */
/* decide to what rank they belong. See each function's documentation ahead.  */
/******************************************************************************/

#include "game.h"						/* Including the main header file*/

/**
 * printRankTitle: This function takes in an integer number and returns a string
 * representing its stud poker rank.
 * @param  handRank: The integer number representing the hand rank.
 * @return: The string representation of the numerical ran given.
 */
char *printRankTitle(int handRank){

	/*Stud poker hand rank names in order from highest to lowest*/
	char *studPokerHand[] ={
		"No Rank",			/*	0	means no rank  */
		"Royal Flush", 		/*	1	is first rank  */
		"Straight Flush",	/*	2	is second rank */
		"Four of a Kind",	/*	3	is third rank  */
		"Full House",		/*	4	is fourth rank */
		"Flush",			/*	5	is fifth rank  */
		"Straight",			/*	6   is sixth rank  */
		"Three of a Kind",	/*	7	is seventh rank*/
		"Two Pair",			/*	8	is eight rank  */
		"One Pair",			/*	9	is nineth rank */
		"High Card"			/*	10	is tenth rank  */
	};
	/* control that the given rank is valid if its not, then assign no rank.*/
	if((handRank > NUM_OF_STUD_POKER_RANKS) || (handRank < 0)){
		handRank = 0;
	}

	return studPokerHand[handRank];
}

/**
 * calculateRank: This function takes in a player and proceeds to evaluate its 
 * Hand. The functions used in this process are all contained in this file.
 * @param  player: The player whose hand's rank is to be evaluated.
 * @param  handLength: The length of the player's rank.
 * @return: An integer value representing of the poker rank to which the 
 * player's hand belongs to.
 */
int calculateRank(Player player, int handLength){

	sortHand(player.playerHand, handLength, 1);

	int calculatedRank = HIGH_CARD;
	if(checkIsStraight(player, handLength)){

		if(checkIsFlush(player, handLength)){

			if(checkIsRoyalFlush(player, handLength)){
				calculatedRank = ROYAL_FLUSH;
			}else{
				calculatedRank = STRAIGHT_FLUSH;
			}
		}else{
			calculatedRank = STRAIGHT;
		}
	}else if(checkIsFlush(player, handLength)){
		calculatedRank = FLUSH;
	}else if(checkIsFourOfAKind(player, handLength)){
		calculatedRank = FOUR_OF_A_KIND;
	}else if(checkIsFullHouse(player, handLength)){
		calculatedRank = FULL_HOUSE;
	}else if(checkIsThreeOfAKind(player, handLength)){
		calculatedRank = THREE_OF_A_KIND;
	}else if(checkIsTwoPair(player, handLength)){
		calculatedRank = TWO_PAIR;
	}else if(checkIsOnePair(player, handLength)){
		calculatedRank = ONE_PAIR;
	}
	return calculatedRank;
}


/**
 * evaluateHand: The following function determines the rank of every player in 
 * a given player array structure.
 * @param playerList: The list of players whose card hands will be evalauted.
 * @param handLength: The length of each one of the player's hands.
 * @param numHands: The total number of hands.
 */
void evaluateHand(Player playerList[], int handLength, int numHands){

	int i;
	for(i = 0; i < numHands; i++){
		playerList[i].handRank = 
		calculateRank(playerList[i], handLength);

		printf("%s %d", "Player:", (playerList[i].playerNumber));
		printf(" %s \n", printRankTitle(playerList[i].handRank));
		displayBatch(playerList[i].playerHand, handLength, 1);
	}
}

/**
 * checkIsFlush: The following function determined if the player's hand given is
 * a flush.
 * @param  player: Player whose hand will be evaluated.
 * @param  handLength: The length of the player's hand.
 * @return: A number, 1 if is flush, 0 if is not flush.
 */
bool checkIsFlush(Player player, int handLength){

	sortHand(player.playerHand, handLength, 0);

	bool isFlush = TRUE;
	int count = 0;

	sortHand(player.playerHand, handLength, 0);

	while((isFlush == TRUE) && (count < handLength - 1)){
		if(player.playerHand[count].suit != player.playerHand[count + 1].suit){
			isFlush = FALSE;
		}
		count++;
	}

	/*Assign a hand score if is flush*/
	if(isFlush){
		if(player.playerHand[0].rank == ACE_RANK_VAL){
			if(player.playerHand[handLength].rank == TWO_RANK_VAL){
				player.handScore = player.playerHand[1].rank;
			}else{
				player.handScore = ACE_RANK_VAL;
			}
		}
	}
	return isFlush;
}

/**
 * checkIsStraight: This function checks if the player's hand is Straight.
 * @param  player: A player whose hand will be tested to check if its straight.
 * @param  handLength: The length of the player's hand.
 * @return: A number 1 if it is straight 0 if it is not.
 */
bool checkIsStraight(Player player, int handLength){

	sortHand(player.playerHand, handLength, 1);

	bool isStraight = TRUE;
	int count = 0;

	if(player.playerHand[0].rank == ACE_RANK_VAL){
		count++;
	}

	while((isStraight == TRUE) && (count < handLength - 1)){

		int verifyDifference;
		verifyDifference = (player.playerHand[count].rank)
		 - (player.playerHand[count + 1].rank);

		if(verifyDifference != 1){
				isStraight = FALSE;
		}
		count++;
	}

	if((player.playerHand[0].rank == ACE_RANK_VAL)
		 && (isStraight)
		 && (player.playerHand[1].rank != KING_RANK_VAL)
		 && (player.playerHand[handLength-1].rank != TWO_RANK_VAL)){
		isStraight = FALSE;
	}

	/* Assign a hand score if is straight */
	if(isStraight){
		if(player.playerHand[0].rank == ACE_RANK_VAL){
			if(player.playerHand[handLength].rank == KING_RANK_VAL){
				player.handScore = ACE_RANK_VAL;
			}else{
				player.handScore = player.playerHand[1].rank;
			}
		}
	}
	return isStraight;
}

/**
 * checkIsStraightFlush: This function checks if a given player's hand is a 
 * Straight flush.
 * @param  player: PLayer whose hand of cards will be tested.
 * @param  handLength: The length of the player's hand.
 * @return: A number 1 if its a stright flush, a 0 if its not.            
 */
bool checkIsStraightFlush(Player player, int handLength){
	bool isStrFlush = FALSE;
	if((checkIsFlush(player, handLength))
		&& (checkIsStraight(player, handLength))){
		isStrFlush = TRUE;
	}
	return isStrFlush;
}

/**
 * checkIsRoyalFlush: This function checks if the given player's hand is a royal
 * flush.
 * @param  player: A player whose hand will be tested.
 * @param  handLength: The length of the player's hand.
 * @return: A number 1 if its a Royal flush, a 0 if its not.
 */
bool checkIsRoyalFlush(Player player, int handLength){
/* this method requires a previous check for straight and flush*/
	sortHand(player.playerHand, handLength, 1);
	bool isRoyalFlush = FALSE;

	if(player.playerHand[0].rank == ACE_RANK_VAL 
		&& player.playerHand[1].rank == KING_RANK_VAL){
		isRoyalFlush = TRUE;
		/*Assign the proper hand rank for royal flush*/
		player.handRank = ACE_RANK_VAL;
	}
	return isRoyalFlush;
}



/**
 * checkIsFourOfAKind: This function checks if the given player's hand is a four 
 * of a kind. The function counts occurrences and sees that there were exaclty 
 * 4 cards of the same kind.
 * @param  player: A player whose hand will be tested.
 * @param  handLength: The length of the given player's hand.
 * @return: A number 1 if its a four of a kind, a 0 if its not.
 */
bool checkIsFourOfAKind(Player player, int handLength){
	/* Sort by its rank */
	sortHand(player.playerHand, handLength, 1);

	int similarCardsCount = 1;
	int currentRank = player.playerHand[0].rank;
	int count = 1;
	int indexOfOcurrence = 0;
	bool isfourOfAKind =  FALSE;

	while(count < handLength && (similarCardsCount < handLength - 1)){
		if((player.playerHand[count].rank) == (currentRank)){
			similarCardsCount++;
			indexOfOcurrence = count;
		}else{
			similarCardsCount = 1;
			currentRank = player.playerHand[count].rank;
		}
		count++;
	}

	isfourOfAKind = (similarCardsCount == 4) ? (TRUE) : (FALSE);

	if(isfourOfAKind){
		player.handRank = player.playerHand[indexOfOcurrence].rank;
	}

	return isfourOfAKind;
}

/**
 * checkIsFullHouse: This fucntion evaluates a given player's hand and decides 
 * if its a full house.
 * @param  player: A pplayer whose hand will be evaluated to check if its 
 * a full house or not.
 * @param  handLength: The lenght of the player's hand.
 * @return:
 */
bool checkIsFullHouse(Player player, int handLength){

	/* Prepare the given batch of cards sorting it by its rank */
	sortHand(player.playerHand, handLength, 1);

	int currentRank = player.playerHand[0].rank;
	bool onlyTwoGroups = TRUE;

	int firstOccurrences = 1;
	int secondOccurences = 0;
	int *currentOccurenceCount = &firstOccurrences;

	int count = 1;

	while(count < handLength){

		if(currentRank == player.playerHand[count].rank){
			(*currentOccurenceCount)++;
		}
		else{
			currentOccurenceCount = &secondOccurences;

			if(*currentOccurenceCount > 0){
				onlyTwoGroups = FALSE;
			}else{
				currentRank = player.playerHand[count].rank;
				(*currentOccurenceCount)++;
			}
		}
		count++;
	}
	
	/* Take care of a false true*/
	if(onlyTwoGroups){
		int cardinalityDifference = firstOccurrences - secondOccurences;
		onlyTwoGroups = (abs(cardinalityDifference) == 1) ? (TRUE) : (FALSE);
	}

	return onlyTwoGroups;
}


/**
 * checkIsThreeOfAKind: This function checks if a given palyer's hand is a three
 * of a kind. The function counts occurrences and see if there were exaclty 3 
 * cards of the same kind.
 * @param  player: A player whose hand will be tested.
 * @param  handLength: The length of the payer's hand.
 * @return: A number 1 if its a three of a kind, a 0 if it is not.
 */
bool checkIsThreeOfAKind(Player player, int handLength){
	/* Prepare the given batch of cards sorting it by its rank */
	sortHand(player.playerHand, handLength, 1);

	bool foundThreeOfAKind = FALSE;
	int kindCounter = 0;
	int currentRank = player.playerHand[0].rank;

	int count = 0;
	while((count < handLength) && (kindCounter < 3)){
		if(player.playerHand[count].rank == currentRank){
			kindCounter++;
		}else {
			kindCounter = 1;
			currentRank = player.playerHand[count].rank;
		}
		count++;
	}
	foundThreeOfAKind = (kindCounter == 3) ? (TRUE) : (FALSE);

	return foundThreeOfAKind;
}

/**
 * checkIsTwoPair: This function checks a given player's hand to verify if it is 
 * a two pair. The function counts pairs and checks that there are 2 pairs.
 * @param  player: The player whose hand will be evaluated.
 * @param  handLength: The length of the given player's hand.
 * @return: A number 1 if the hand is a two pair, a 0 if it is not.
 */
bool checkIsTwoPair(Player player, int handLength){
	/* Prepare the given batch of cards sorting it by its rank */
	sortHand(player.playerHand, handLength, 1);

	int count = 1;
	int currentRank = player.playerHand[0].rank;

	int currentPairCount = 0;

	while(count < handLength){

		if((player.playerHand[count].rank) == currentRank){
			currentPairCount++;
			currentRank = player.playerHand[count+1].rank;
			count+=2;
		}else{
			currentRank = player.playerHand[count].rank;
			count++;
		}
	}
	return (currentPairCount == 2);
}

/**
 * checkIsOnePair: This function checks if  agiven player's hand is a one pair.
 * @param  player: The player whose hand  will be evalauted.
 * @param  handLength: The length of the player's hand.
 * @return: A number 1 if the hand is a one pair, a 0 if its not.
 */
bool checkIsOnePair(Player player, int handLength){
	
	sortHand(player.playerHand, handLength, 1);

	bool isOnePair = FALSE;
	int count = 1;
	int currentRank = player.playerHand[0].rank;

	while((count < handLength) && (!isOnePair)){
		if(player.playerHand[count].rank == currentRank){
			isOnePair = TRUE;
		}else{
			currentRank = player.playerHand[count].rank;
		}
		count++;
	}

	return isOnePair;
}







