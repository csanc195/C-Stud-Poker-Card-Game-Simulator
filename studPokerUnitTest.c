/******************************************************************************/
/* 	"studPokerUnitTest.c" 													  */
/* The following file contains a family of functions that further test the 	  */
/* correct operation of the functions that compose the rules for 5 card stud  */
/* poker games. The functions test each hand determining function with 2 to 3 */
/* possible variants to really prove that the functions work as intended. 	  */
/* each function is of type void and operate independent of the functions 	  */
/* being tested. Each function creates a hand and proceeds to test functions  */
/* and print their results, then the expected value can be visualized and 	  */
/* since the cards are shown the function can be effectvely tested 			  */
/******************************************************************************/

#include "game.h"						/* Including the main header file*/

/**
 * startTests: This method starts the functions that test studPokerRules.c
 * functions.
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem.
 */
void startTests(int handLength){
	testIsStraightWithRightHand(handLength);
	testIsFlushWithHighAce(handLength);
	testIsFlushWithLowAce(handLength);
	testIsFlushWithNoAce(handLength);
	testIsRoyalFlushWithRightHand(handLength);
	testIsRoyalFlushWithWrongHand(handLength);
	testIsFourOfAKindWithRightHand(handLength);
	testIsFullHouseWithRightCards(handLength);
	testIsFullHouseWithWrongCards(handLength);
	testIsThreeOfAKindWithRandomCards(handLength);
	testIsTwoPairWithRightHand(handLength);
	testIsOnePairWithRightHand(handLength);
}


/**
 * testIsStraightWithRightHand: Test the function isStraight() with a correct 
 * hand
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem.
 */
void testIsStraightWithRightHand(int handLength){
	initializeRandomSeed();

	Player isStraight;
	
	isStraight.playerHand[0].rank = 7;
	isStraight.playerHand[0].suit = 1;

	isStraight.playerHand[1].rank = 6;
	isStraight.playerHand[1].suit = 2;

	isStraight.playerHand[2].rank = 5;
	isStraight.playerHand[2].suit = 3;

	isStraight.playerHand[3].rank = 4;
	isStraight.playerHand[3].suit = 4;

	isStraight.playerHand[4].rank = 3;
	isStraight.playerHand[4].suit = 1;

	sortHand(isStraight.playerHand, handLength, 1);

	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test  isStraight() with a right Hand");
	displayBatch(isStraight.playerHand, handLength, 1);

	
	printf("%s %d\n","Is straight? ",checkIsStraight(isStraight, handLength));
}



/**
 * testIsFlushWithHighAce: Test the function isFlush() with a correct hand that 
 * has an Ace that is the highest card.
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem.
 */
void testIsFlushWithHighAce(int handLength){

	Player flushWithHighAce;
	
	flushWithHighAce.playerHand[0].rank = 12;
	flushWithHighAce.playerHand[0].suit = 1;

	int count = 1;
	while(count < handLength){
		flushWithHighAce.playerHand[count].rank = 12 - count;
		flushWithHighAce.playerHand[count].suit = 1;
		count++;
	}
	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test isFlush() with a hand with high Ace:");
	displayBatch(flushWithHighAce.playerHand, handLength, 1);

	printf("%s %d\n","Is flush? ",checkIsFlush(flushWithHighAce, handLength));
}

/**
 * testIsFlushWithLowAce: Test the function is flush with a correct hand which 
 * has a low Ace. Ex 5 3 2 A of the same suit.
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem.
 */
void testIsFlushWithLowAce(int handLength){

	Player flushWithLowAce;

	flushWithLowAce.playerHand[0].rank = 12;
	flushWithLowAce.playerHand[0].suit = 1;

	int count = 1;
	int cardCount = 0;
	while(count < handLength){

		flushWithLowAce.playerHand[count].rank = cardCount;
		flushWithLowAce.playerHand[count].suit = 1;
		count++;
		cardCount++;
	}

	sortHand(flushWithLowAce.playerHand, handLength, 1);

	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test isFlush() with a hand with a low Ace:");
	displayBatch(flushWithLowAce.playerHand, handLength, 1);

	printf("%s %d\n","Is flush? ",checkIsFlush(flushWithLowAce, handLength));

}


/**
 * testIsFlushWithNoAce: Test the fucntion isFlush() with a hand that contains 
 * no Ace.
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem.
 */
void testIsFlushWithNoAce(int handLength){

	Player flushWithNoAce;

	initializeRandomSeed();
	

	int count = 0;
	int cardCount = 4;
	
	while(count < handLength){

		flushWithNoAce.playerHand[count].rank = cardCount;
		flushWithNoAce.playerHand[count].suit = 1 + randomizePick(3);;
		count++;
		cardCount++;
	}

	sortHand(flushWithNoAce.playerHand, handLength, 1);

	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test isFlush() with a hand with No Ace:");
	displayBatch(flushWithNoAce.playerHand, handLength, 1);

	printf("%s %d\n","Is flush? ",checkIsFlush(flushWithNoAce, handLength));

}


/**
 * testIsRoyalFlushWithRightHand: Test the function is royalFlush() with a 
 * correct hand.
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem.
 */
void testIsRoyalFlushWithRightHand(int handLength){

	initializeRandomSeed();
	int suitToUse = 1 + randomizePick(3);

	Player royalFlushHand;
	royalFlushHand.playerHand[0].rank = ACE_RANK_VAL;
	royalFlushHand.playerHand[0].suit = suitToUse;

	int count = 1;
	int rankCount = KING_RANK_VAL;

	while(count < handLength){

		royalFlushHand.playerHand[count].rank = rankCount;
		royalFlushHand.playerHand[count].suit = suitToUse;

		rankCount--;
		count++;
	}
	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test isRoyalFlush() with a correct Hand");
	displayBatch(royalFlushHand.playerHand, handLength, 1);

	printf("%s %d\n","Is Royal flush?",
		checkIsRoyalFlush(royalFlushHand, handLength));

}



/**
 * testIsRoyalFlushWithWrongHand: Test the function is royalFlush() with an 
 * incorrect hand.
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem.
 */
void testIsRoyalFlushWithWrongHand(int handLength){

	initializeRandomSeed();
	int suitToUse = 1 + randomizePick(3);

	Player royalFlushHand;
	royalFlushHand.playerHand[0].rank = ACE_RANK_VAL;
	royalFlushHand.playerHand[0].suit = suitToUse;

	royalFlushHand.playerHand[1].rank = TWO_RANK_VAL;
	royalFlushHand.playerHand[1].suit = suitToUse;

	int count = 2;
	int rankCount = KING_RANK_VAL - 1;

	while(count < handLength){

		royalFlushHand.playerHand[count].rank = rankCount;
		royalFlushHand.playerHand[count].suit = suitToUse;

		rankCount--;
		count++;
	}
	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test isRoyalFlush() with a wrong Hand");
	displayBatch(royalFlushHand.playerHand, handLength, 1);

	printf("%s %d\n","Is royal flush?",
		checkIsRoyalFlush(royalFlushHand, handLength));

}

/**
 * testIsFourOfAKindWithRightHand: Test the function four of a kind with a 
 * correct hand
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem.
 */
void testIsFourOfAKindWithRightHand(int handLength){
	
	initializeRandomSeed();
	Player fourOfAKind;

	fourOfAKind.playerHand[0].suit = 1 + randomizePick(3);
	fourOfAKind.playerHand[0].rank = randomizePick(12);

	int rankToUse = randomizePick(12);
	//int suitToUse = 1 + randomizePick(3);

	int count = 1;
	while(count < handLength){
		fourOfAKind.playerHand[count].rank = rankToUse;
		fourOfAKind.playerHand[count].suit = handLength - count;
		count++;
	}

	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test  isFourOfAkind() with a right Hand");
	displayBatch(fourOfAKind.playerHand, handLength, 1);

	
	printf("%s %d\n","is four of a kind? ",
		checkIsFourOfAKind(fourOfAKind, handLength));
	
}


/**
 * testIsFourOfAKindWithWrongHand: Test the function four of a kind with an 
 * incorrect hand
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem.
 */
void testIsFourOfAKindWithWrongHand(int handLength){
	
	initializeRandomSeed();
	Player fourOfAKind;

	int count = 0;
	while(count < handLength){
		fourOfAKind.playerHand[count].suit = 1 + randomizePick(3);
		fourOfAKind.playerHand[count].rank = randomizePick(12);
		count++;
	}

	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test  isFourOfAkind() with a wrong Hand");
	displayBatch(fourOfAKind.playerHand, handLength, 1);

	
	printf("%s %d\n","is four of a kind? ",
		checkIsFourOfAKind(fourOfAKind, handLength));

}


/**
 * testIsFullHouseWithRightCards: Test the function isFullHouse() with a correct 
 * hand.
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem. 
 */
void testIsFullHouseWithRightCards(int handLength){
	initializeRandomSeed();

	Player fullHouse;

	int firstRank = randomizePick(12);
	int firstSuit = 4;

	int secondRank = randomizePick(12);
	int secondSuit = 4;

	int firstGroupLength = (2 + randomizePick(2));
	int i;
	for(i = 0; i < firstGroupLength; i++){
		fullHouse.playerHand[i].rank = firstRank;
		fullHouse.playerHand[i].suit = firstSuit--;
	}

	int j;
	for(j = i; j < handLength; j++){
		fullHouse.playerHand[j].rank = secondRank;
		fullHouse.playerHand[j].suit = secondSuit--;
	}

	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test  isFullHouse() with a right Hand");
	displayBatch(fullHouse.playerHand, handLength, 1);


	printf("%s %d\n","is full house?",
		checkIsFullHouse(fullHouse, handLength));

}


/**
 * testIsFullHouseWithWrongCards: Test the function isFullHouse() with an 
 * incorrect hand.
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem. 
 */
void testIsFullHouseWithWrongCards(int handLength){
	initializeRandomSeed();

	Player fullHouse;

	int firstRank = randomizePick(12);
	int firstSuit = 4;

	int secondRank = randomizePick(12);
	int secondSuit = 4;

	int firstGroupLength = (2 + randomizePick(2));
	int i;
	for(i = 0; i < firstGroupLength; i++){
		fullHouse.playerHand[i].rank = randomizePick(12);
		fullHouse.playerHand[i].suit = 1 + randomizePick(3);
	}

	int j;
	for(j = i; j < handLength; j++){
		fullHouse.playerHand[j].rank = randomizePick(12);
		fullHouse.playerHand[j].suit = 1 + randomizePick(3);
	}

	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test  isFullHouse() with a wrong Hand");
	displayBatch(fullHouse.playerHand, handLength, 1);

	printf("%s %d\n","is full house?",
		checkIsFullHouse(fullHouse, handLength));

}

/**
 * testIsThreeOfAKindWithRandomCards: Test the function isThreeOfAkind() with a
 * hand composed of completelly random cards.
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem. 
 */
void testIsThreeOfAKindWithRandomCards(int handLength){
	initializeRandomSeed();

	Player threeOfAKind;

	int firstRank = randomizePick(12);
	int firstSuit = 4;

	int secondRank = randomizePick(12);
	int secondSuit = 4;

	int firstGroupLength = (2 + randomizePick(2));
	int i;
	for(i = 0; i < firstGroupLength; i++){
		threeOfAKind.playerHand[i].rank = firstRank;
		threeOfAKind.playerHand[i].suit = 1 + randomizePick(3);
	}

	int j;
	for(j = i; j < handLength; j++){
		threeOfAKind.playerHand[j].rank = randomizePick(12);
		threeOfAKind.playerHand[j].suit = 1 + randomizePick(3);
	}

	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test  isThreeOfAKind() with a right Hand");
	displayBatch(threeOfAKind.playerHand, handLength, 1);

	printf("%s %d\n","is three of a kind?",
		checkIsThreeOfAKind(threeOfAKind, handLength));

}

/**
 * testIsTwoPairWithRightHand: Test the function isTwoPair() with a correct
 * hand.
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem. 
 */
void testIsTwoPairWithRightHand(int handLength){
	initializeRandomSeed();

	Player twoPair;
	
	twoPair.playerHand[0].rank = 12;
	twoPair.playerHand[0].suit = 1;

	twoPair.playerHand[1].rank = 12;
	twoPair.playerHand[1].suit = 1;

	twoPair.playerHand[2].rank = 5;
	twoPair.playerHand[2].suit = 1;

	twoPair.playerHand[3].rank = 5;
	twoPair.playerHand[3].suit = 1;

	twoPair.playerHand[4].rank = 1;
	twoPair.playerHand[4].suit = 1;
	sortHand(twoPair.playerHand, handLength, 1);

	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test  isTwoPair() with a right Hand");
	displayBatch(twoPair.playerHand, handLength, 1);

	printf("%s %d\n","is two pair?", 
		checkIsTwoPair(twoPair, handLength));
}

/**
 * testIsOnePairWithRightHand: Test the function isOnePair() with a correct 
 * hand.
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem. 
 */
void testIsOnePairWithRightHand(int handLength){
	initializeRandomSeed();

	Player onePair;
	
	onePair.playerHand[0].rank = 2;
	onePair.playerHand[0].suit = 1;

	onePair.playerHand[1].rank = 2;
	onePair.playerHand[1].suit = 2;

	onePair.playerHand[2].rank = 6;
	onePair.playerHand[2].suit = 3;

	onePair.playerHand[3].rank = 5;
	onePair.playerHand[3].suit = 4;

	onePair.playerHand[4].rank = 7;
	onePair.playerHand[4].suit = 1;
	sortHand(onePair.playerHand, handLength, 1);

	printf("\n%s\n", "@Test: ");
	printf("%s\n", " Test  isOnePair() with a right Hand");
	displayBatch(onePair.playerHand, handLength, 1);

	printf("%s %d\n","is one pair?",
		checkIsOnePair(onePair, handLength));
}

/**
 * handWithTestGenerator: Simple function that creates a completely random hand 
 * and evaluates it. The function takes a desired target and stops whenever a 
 * random card matching the desired target has been created and evaluated.
 * @param desiredRank: This is the desired target, this parameter dictates how 
 * is it that the function stops. The when is left to chance.
 * @param handLength: This is the specified hand lenght, which is 5 for this 
 * problem. 
 */
void handWithTestGenerator(int desiredRank, int handLength){

	Player currentPlayer;
	initializeRandomSeed();
	currentPlayer.handRank = 0;
	int count = 0;
	while(currentPlayer.handRank != desiredRank){

		int j;	
		for(j = 0; j < handLength; j++){
			currentPlayer.playerHand[j].rank = randomizePick(12);
			currentPlayer.playerHand[j].suit = 1 + randomizePick(3);

		}
		currentPlayer.handRank = 
			calculateRank(currentPlayer, handLength);
		count++;
	}

	displayBatch(currentPlayer.playerHand, handLength, 1);

	printf("%s %d %s\n","Took ", count, " Calcualtions" );
	printf("%s \n", printRankTitle(currentPlayer.handRank));
}











