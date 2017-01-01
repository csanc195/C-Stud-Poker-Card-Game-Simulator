/*****************************************************************************/
/* 		"game.h" 						  									 */
/* This file contains the headers for all of the functions used in the 	 	 */
/* game. Notice that all of the deffinitions are declared in this file along */
/* with the libraries being used.											 */
/*****************************************************************************/

#include <stdio.h>	
#include <stdlib.h>					/* Used for rand and srand				  */
#include <time.h>					/* Used to seed rand() with system time	  */
#define NO_PROGRAM_ERRORS 0  		/* Signal a correct program execution 	  */
#define CARDS_IN_A_DECK 52			/* Number of cards in a deck 			  */
#define CARDS_IN_A_SUIT 13			/* Number of cards in a suit 			  */
#define SUITS_IN_A_DECK 4			/* Number of suits in a suit 			  */
#define SPADES   "\xE2\x99\xA0"		/* Icon that represents the suit of Spades*/
#define CLUBS    "\xE2\x99\xA3"		/* Icon that represents the suit of Slubs */
#define HEARTS   "\xE2\x99\xA5"		/* Icon that represents the suit of Hearts*/
#define DIAMONDS "\xE2\x99\xA6"		/* Icon that represents the Diamond suit  */
#define MAX_HAND_LENGTH 5			/* Max hand length for any game hand 	  */
#define MAX_PLAYERS_ALLOW 7			/* Max number of players allowed per game */
#define NUM_ALLOWED_ARGS 3			/* Number of allowed arguments		 	  */
#define ACE_RANK_VAL 12				/* int value, representing the Ace rank   */
#define TWO_RANK_VAL 0				/* int value, representing the Two rank   */
#define KING_RANK_VAL 11			/* int value, representing the Ace rank   */
#define ROYAL_FLUSH 1				/* Number representing a Royal Flush      */
#define STRAIGHT_FLUSH 2			/* Number representing a Straight Flush   */
#define FOUR_OF_A_KIND 3			/* Number representing Four of a Kind 	  */
#define FULL_HOUSE 4				/* Number representing a Full house  	  */
#define FLUSH 5						/* Number representing a Flush 		 	  */
#define STRAIGHT 6					/* Number representing a Straight hand 	  */
#define THREE_OF_A_KIND 7			/* Number representing a Three of a kind  */
#define TWO_PAIR 8					/* Number representing a Two pair         */
#define ONE_PAIR 9					/* Number representing a One Pair 	      */
#define HIGH_CARD 10				/* Number representing a High Card	  	  */
#define NUM_OF_STUD_POKER_RANKS 10  /* The number of ranks on stud poker games*/
typedef enum { FALSE, TRUE } bool;  /* Allow the use of boolean type  		  */

/* Defined Structures that are used throughout the program */
/* Structure defining a card */
typedef struct card {
	int suit;
	int rank;
}Card;

/* Structure defining a player */
typedef struct player {
	Card playerHand[MAX_HAND_LENGTH];
	int handRank;
	int handScore;
	int playerNumber;
}Player;

/* Function Prototype declarations: */
/* game.c functions 				*/

bool validateCommandLineInput(int,char*argsPointer[]);

/* deck.c functions */
void createDeck(Card *deckPointer);
void shuffleBatch(Card batchOfCards[], int);
void shuffleDeck(Card deck[]);
void dealDeck(Card [], Player [], int, int);
void displayDeckInLines();
void displayBatch();
void initializeRandomSeed(void);
int randomizePick(int);
bool validateGameInput(int, int);
void printFillerLine();
void sortHand(Card [], int, int);
void swapPlayers(Player *playerA, Player *playerB);
void swapCards(Card*, Card*);
void sortPlayers(Player playerList[], int, int);

/* player.c functions */
void createAllPlayers(Player *playersInGamePt, int, int);
Player createAlllayers(Player,int,int);
void displayAllPlayersHands();

/* studPokerRules.c functions */
char *printRankTitle(int);
int calculateRank(Player player, int);
void evaluateHand(Player playerList[], int, int);
bool checkIsFlush(Player player, int);
bool checkIsStraight(Player player, int);
bool checkIsStraightFlush(Player player, int);
bool checkIsRoyalFlush(Player player, int);
bool checkIsFourOfAKind(Player player, int);
bool checkIsFullHouse(Player player, int);
bool checkIsThreeOfAKind(Player player, int);
bool checkIsTwoPair(Player player, int);
bool checkIsOnePair(Player player, int);

/* studPokerUnitTest.c functions */
void startTests(int);
void testIsStraightWithRightHand(int);
void testIsFlushWithHighAce(int);
void testIsFlushWithLowAce(int);
void testIsFlushWithNoAce(int);
void testIsRoyalFlushWithRightHand(int);
void testIsRoyalFlushWithWrongHand(int);
void testIsFourOfAKindWithRightHand(int);
void testIsFourOfAKindWithWrongHand(int);
void testIsFullHouseWithRightCards(int);
void testIsFullHouseWithWrongCards(int);
void testIsThreeOfAKindWithRandomCards(int);
void testIsTwoPairWithRightHand(int);
void testIsOnePairWithRightHand(int);
void handWithTestGenerator(int, int);

