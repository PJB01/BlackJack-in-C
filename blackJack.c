#include <stdio.h>

#include <time.h>

#include <stdlib.h>

#include <process.h>

//Used for Menu Images
#define spade 06
#define club 05
#define diamond 04
#define heart 03

#define MAXVALUE 21
#define DEALERTURN 1
#define PLAYERTURN 2
#define SPOTCARDS 39
#define ACES 1

void deck(int cards[]);
void shuffle(int cards[], size_t n);
int checkValue(int cards[], int cardsIndex);
int changeAceValue(int cards[], int index, int sumOfCards);
char *checkSuit(int cards[], int cardsIndex);
char *checkFace(int cards[], int cardsIndex);
void cardImage(int cards[], int index);
void bet(int *chips, int betValue,int initGameValue);
int betValue(int *chips);
int initGame(int cards[], int *deckTop);
int checkWin(int dealerSum, int playerSum);
void dealCard(int cards[],int index,int sumOfCards,int turn);


int main() {
  char menu = '0';
  int cards[52];
  int deckTop = 51;
  int chips = 500;
  int initGameValue;
  int playersBet;
  deck(cards);
  shuffle(cards, 52);
  system("cls");
  //Menu Image
    printf("\n%c%c%c%c%c     %c%c            %c%c         %c%c%c%c%c    %c    %c                ", club, club, club, club, club, spade, spade, diamond, diamond, heart, heart, heart, heart, heart, club, club);
    printf("\n%c    %c    %c%c           %c  %c       %c     %c   %c   %c              ", club, club, spade, spade, diamond, diamond, heart, heart, club, club);
    printf("\n%c    %c    %c%c          %c    %c     %c          %c  %c               ", club, club, spade, spade, diamond, diamond, heart, club, club);
    printf("\n%c%c%c%c%c     %c%c          %c %c%c %c     %c          %c %c              ", club, club, club, club, club, spade, spade, diamond, diamond, diamond, diamond, heart, club, club);
    printf("\n%c    %c    %c%c         %c %c%c%c%c %c    %c          %c%c %c             ", club, club, spade, spade, diamond, diamond, diamond, diamond, diamond, diamond, heart, club, club, club);
    printf("\n%c     %c   %c%c         %c      %c    %c          %c   %c               ", club, club, spade, spade, diamond, diamond, heart, club, club);
    printf("\n%c     %c   %c%c        %c        %c    %c     %c   %c    %c             ", club, club, spade, spade, diamond, diamond, heart, heart, club, club);
    printf("\n%c%c%c%c%c%c    %c%c%c%c%c%c%c   %c        %c     %c%c%c%c%c    %c     %c            ", club, club, club, club, club, club, spade, spade, spade, spade, spade, spade, spade, diamond, diamond, heart, heart, heart, heart, heart, club, club);
    printf("\n");
    printf("\n     %c%c%c%c%c%c%c%c      %c%c         %c%c%c%c%c    %c    %c                ", diamond, diamond, diamond, diamond, diamond, diamond, diamond, diamond, heart, heart, club, club, club, club, club, spade, spade);
    printf("\n        %c%c        %c  %c       %c     %c   %c   %c              ", diamond, diamond, heart, heart, club, club, spade, spade);
    printf("\n        %c%c       %c    %c     %c          %c  %c               ", diamond, diamond, heart, heart, club, spade, spade);
    printf("\n        %c%c       %c %c%c %c     %c          %c %c              ", diamond, diamond, heart, heart, heart, heart, club, spade, spade);
    printf("\n        %c%c      %c %c%c%c%c %c    %c          %c%c %c             ", diamond, diamond, heart, heart, heart, heart, heart, heart, club, spade, spade, spade);
    printf("\n        %c%c      %c      %c    %c          %c   %c               ", diamond, diamond, heart, heart, club, spade, spade);
    printf("\n     %c  %c%c     %c        %c    %c     %c   %c    %c             ", diamond, diamond, diamond, heart, heart, club, club, spade, spade);
    printf("\n      %c%c%c      %c        %c     %c%c%c%c%c    %c     %c            ", diamond, diamond, diamond, heart, heart, club, club, club, club, club, spade, spade);
    printf("\n");
  printf("\n");
  printf("\t  Welcome to the Black Jack Table! ");
  while (menu != 'c' && menu != 'x') {
    if (deckTop < 3) {
      shuffle(cards, 52);
      deckTop = 51;
    }
    printf("\n\t\tPress X to leave\n\t\tPress C to play\n\t\tPress H for help\n");
    scanf(" %c", &menu);
    if (menu == 'c') {
      playersBet = 0;
      initGameValue = 0;
      playersBet = betValue(&chips);
      system("cls");
      initGameValue = initGame(cards, &deckTop);
      bet(&chips, playersBet, initGameValue);
      menu = '0';
    }
    if (menu == 'x')
      break;
    if (menu == 'h'){
        printf("\nYou dont know how to play black jack? Well thats okay. The goal is to have more points \nthan the dealer but no more than 21 points. Once the cards are dealt you ");
        printf("can either hit or stand.\n If you stand you wont be dealt anymore cards. If you hit, you're dealt another card. \nBe careful though! You dont want more than 21 points.\n");
    continue;
    }
    else if(menu != '0')
    printf("Invalid Input");
  }
printf("\nThanks for playing!");
  return 0;
}

//checks numerical value of card based on its value determined by deck function
int checkValue(int cards[], int cardsIndex) {
  int value;

  if (cards[cardsIndex] <= SPOTCARDS)
    value = (cards[cardsIndex] / 4) + 1;

  if (cards[cardsIndex] > SPOTCARDS && cards[cardsIndex] < 52)
    value = 10;

  return value;
}

//checks suit of cards (only aesthetic) based on its value determined by deck function
char *checkSuit(int cards[], int cardsIndex) {
    char *cSuit;
    int nSuit = cards[cardsIndex] % 4;

    switch (nSuit) {
    case 0:
      cSuit = "Spade";
      break;
    case 1:
      cSuit = "Hearts";

      break;
    case 2:
      cSuit = "Clubs";
      break;
    case 3:
      cSuit = "Diamonds";
      break;
    default:
      cSuit = "0";
    }

    return cSuit;
  }

//Checks face cards (only aesthetic) based on its value determined by deck function
char *checkFace(int cards[], int cardsIndex) {
    int nFace;
    char *cFace;
    if (cards[cardsIndex] <= 3)
      nFace = ACES;
    else if (cards[cardsIndex] > SPOTCARDS && cards[cardsIndex] < 52)
      nFace = (((cards[cardsIndex]) % 3) + 4) * 2;
    else
      nFace = 0;
    switch (nFace) {
    case 1:
      cFace = "Ace";
      break;
    case 8:
      cFace = "Jack";
      break;
    case 10:
      cFace = "King";
      break;
    case 12:
      cFace = "Queen";
      break;
    default:
      cFace = "0";
    }
    return cFace;
  }

//assigns values of cards elements == to that elements index. This way each card will have its own characteristics (face, value and suit) assigned to it
void deck(int cards[]) {
  int i;
  for (i = 0; i < 52; ++i)
    cards[i] = i;
}

//randomly organizes the cards using a bubble sort and the rand function
void shuffle(int cards[], size_t n) {
  int temp;
  int i = 0;
  int j = 0;
    for (j = 0; j < 7; ++j) {
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = cards[j];
      cards[j] = cards[i];
      cards[i] = t;
    }
  }
    for (i = 0; i < 52; ++i) {
      if (cards[i] > cards[i + 1]) {
        temp = cards[i + 1];
        cards[i + 1] = cards[i];
        cards[i] = temp;
      }

    }
  }
    printf("\nThe deck has been shuffled.\n");
}

//index is current element array
//starts game
int initGame(int cards[], int *deckTop) {
  int index = *deckTop;
  int dealerSum = 0;
  int playerSum = 0;
  char choice;

  //player start
 dealCard(cards,index,playerSum,PLAYERTURN);
  playerSum += (checkValue(cards, index) + changeAceValue(cards, index, playerSum));
  --index;

 dealCard(cards,index,playerSum,PLAYERTURN);
  playerSum += (checkValue(cards, index) + changeAceValue(cards, index, playerSum));
  --index;
  //dealer start
 dealCard(cards,index,dealerSum,DEALERTURN);
  dealerSum += (checkValue(cards, index) + changeAceValue(cards, index, dealerSum));
  --index;

  *deckTop -= 3;
  printf("\nYou have a total card value of %d.\nThe dealer has a total card value of %d.", playerSum, dealerSum);

  while (checkWin(dealerSum, playerSum == 0)) {
    do {
      printf("\n\nType h to hit or s to stand:");
      scanf(" %c", &choice);
    }
    while (choice != 'h' && choice != 's');
    if (choice == 'h') {
    dealCard(cards,index,playerSum,PLAYERTURN);
      playerSum += (checkValue(cards, index) + changeAceValue(cards, index, playerSum));
      --index;
      --*deckTop;

      if (*deckTop == 0) {
        shuffle(cards, 52);
        *deckTop = 51;
      }
      printf("\nYou have a total card value of %d.\nThe dealer has a total card value of %d.", playerSum, dealerSum);
      checkWin(dealerSum, playerSum);
      if (checkWin(dealerSum, playerSum) == 3) {
        printf("\nValue over 21, you busted. :(\n");
        return 1;
      }
    } else if (choice == 's') {
      while (dealerSum < 17) {
        dealCard(cards,index,dealerSum,DEALERTURN);
        dealerSum += (checkValue(cards, index) + changeAceValue(cards, index, dealerSum));
        --index;
        --*deckTop;

        if (*deckTop == 0) {
          shuffle(cards, 52);
          *deckTop = 51;
        }
      }
      printf("\nYou have a total card value of %d.\nThe dealer has a total card value of %d.", playerSum, dealerSum);
      if (checkWin(dealerSum, playerSum) == 3) {
        return 1;
      } else if (checkWin(dealerSum, playerSum) == 4) {
        return 2;
      } else if (checkWin(dealerSum, playerSum) == 5) {
        return 3;
      }
    }
}
return 0;
}
//checks to see who won
int checkWin(int dealerSum, int playerSum) {
//if 3 dealer won, if 4 player won, if 5 tie
  if (((playerSum > MAXVALUE) || (dealerSum > playerSum)) && (dealerSum <= MAXVALUE))
    return 3;
  if (((dealerSum > MAXVALUE) || (playerSum > dealerSum)) && (playerSum <= MAXVALUE))
    return 4;
  else if (playerSum == dealerSum)
    return 5;
  return 0;
}
//changes value of ace to 11 (10 will be added to normal value of ace which is 1 to create 11) only if beneficial
int changeAceValue(int cards[], int index, int sumOfCards) {
  int aceValue10 = 0;
  if (checkValue(cards, index) == ACES && sumOfCards + 11 < 22)
    aceValue10 = 10;
  return aceValue10;
}
//deals cards to player or dealer
void dealCard(int cards[],int index,int sumOfCards,int turn){
    char *cardReciever = (turn == DEALERTURN) ? "The dealer got" : "You got";
      if (checkValue(cards,index) == ACES || cards[index] > SPOTCARDS)
          printf("%s a %s of %s worth %d:\n", cardReciever, checkFace(cards, index), checkSuit(cards, index), checkValue(cards, index) + changeAceValue(cards, index, sumOfCards));
        else
          printf("%s a %d of %s:\n", cardReciever, checkValue(cards, index) + changeAceValue(cards, index, sumOfCards), checkSuit(cards, index));
    cardImage(cards,index);
}
//determines if you get or lose chips based off your bet value
void bet(int *chips, int betValue,int initGameValue){
if(initGameValue == 1){
    *chips -= betValue;
    printf("\nDealer won, you lost %d chips.\nYou have %d chips remaining.\n",betValue, *chips);
} else if(initGameValue == 2){
    *chips += betValue;
    printf("\nYou won, you got %d chips.\nYou now have %d chips.\n",betValue, *chips);
}  else if(initGameValue == 3){
    printf("\nIts a tie, you still have %d chips.\n", *chips);
}
}
//gets the bet value
//looping scanf plus a user input of a character causes the game to break without additional code
//so I decided against an input loop because of this if anything other than a number is added bet defaults to 0
int betValue(int *chips){
  if(*chips == 0){
    printf("\nA friendly looking fellow notices you're struggling to find financial freedom. \n\"Heres some chips, they're on me.\"\n");
    *chips = 100;
  }
  int betValue = 0;
  printf("How much would you like to bet? You have %d chips: ",*chips);
    scanf(" %d", &betValue);
  if(betValue <= 0 || betValue > *chips){
    printf("\nInvalid input. You must bet a number greater than 0 and less than your current amount of chips.\n");
      scanf(" %d", &betValue);
  }
return betValue;
}
//creates a card image
void cardImage(int cards[], int index){
    int nSuit = 0, nFace;
    char cSuit, cFace;

    if (cards[index] < 52)
     nSuit = cards[index] % 4;
    switch (nSuit) {
    case 0:
      cSuit = spade;
      break;
    case 1:
      cSuit = heart;

      break;
    case 2:
      cSuit = club;
      break;
    case 3:
      cSuit = diamond;
      break;
    default:
      cSuit = '0';
    }

    if (cards[index] <= 3)
      nFace = ACES;
    else if (cards[index] > SPOTCARDS && cards[index] < 52)
      nFace = (((cards[index]) % 3) + 4) * 2;
    else
      nFace = 0;
    switch (nFace) {
    case 1:
      cFace = 'A';
      break;
    case 8:
      cFace = 'J';
      break;
    case 10:
      cFace = 'K';
      break;
    case 12:
      cFace = 'Q';
      break;
    default:
      cFace = '0';
    }


if(checkValue(cards,index) < 10){
    printf("-------\n");
    printf("|    %c|\n", cSuit);
    printf("|     |\n");
    printf("|  %d  |\n", checkValue(cards,index));
    printf("|     |\n");
    printf("|%c    |\n", cSuit);
    printf("-------\n");
} else {
    printf("-------\n");
    printf("|    %c|\n", cSuit);
    printf("|     |\n");
    printf("|  %c  |\n", cFace);
    printf("|     |\n");
    printf("|%c    |\n", cSuit);
    printf("-------\n");
}
}
