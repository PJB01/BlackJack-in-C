#include <stdio.h>

#include <time.h>

#include <stdlib.h>

void deck(int cards[]);
void shuffle(int cards[], size_t n);
int checkValue(int cards[], int i);
char *checkSuit(int cards[], int i);
char *checkFace(int cards[], int i);
void initGame(int * cards, int * deckTop);
int play(int cards[], int * deckTop, int dealerSum, int playerSum);
int checkWin(int dealerSum, int playerSum);
int changeAceValue(int cards[], int index, int playerSum);

int main() {
  char menu = '0';
  int cards[52];
  int deckTop = 51;
  deck(cards);
  shuffle(cards, 52);
  initGame(cards, & deckTop);
  while (menu != 'c' && menu != 'x') {
    if (deckTop < 3) {
      shuffle(cards, 52);
      deckTop = 51;
    }
    printf("\n\nPress x to exit or c to continue: ");

    scanf(" %c", & menu);

    if (menu == 'c') {
      initGame(cards, & deckTop);
      menu = '0';
    }
    if (menu == 'x')
      break;
  }

  return 0;
}

//checks numerical value of card
int checkValue(int cards[], int cardsIndex) {
  //int *cardLoc = cards+n;
  int value;

  if (cards[cardsIndex] < 40)
    value = (cards[cardsIndex] / 4) + 1;

  if (cards[cardsIndex] >= 40 && cards[cardsIndex] <= 52)
    value = 10;

  return value;
}

//Checks suit of cards (only aesthetic) based on array index
char *checkSuit(int cards[], int cardsIndex) {
    char * cSuit;
    int nSuit;
    if (cards[cardsIndex] <= 52)
      nSuit = cards[cardsIndex] % 4;

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

//Checks face cards (only aesthetic) based on array index
char *checkFace(int cards[], int cardsIndex) {
    int nFace;
    char * cFace;
    if (cards[cardsIndex] <= 3)
      nFace = 1;
    else if (cards[cardsIndex] >= 40 && cards[cardsIndex] <= 52)
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

//assigns values of cards elements == to that elements index
void deck(int cards[]) {
  int i;
  for (i = 0; i <= 52; ++i)
    cards[i] = i;
}

//randomly organizes the cards
void shuffle(int cards[], size_t n) {
  int temp;
  int i = 0;
  int j = 0;
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = cards[j];
      cards[j] = cards[i];
      cards[i] = t;
    }
  }
  for (j = 0; j < 1; ++j) {
    for (i = 0; i < 52; ++i) {
      if (cards[i] > cards[i + 1]) {
        temp = cards[i + 1];
        cards[i + 1] = cards[i];
        cards[i] = temp;
      }

    }
  }

}

//index is current element array
void
initGame(int cards[], int * deckTop) {
  int index = * deckTop;
  int dealerSum = 0;
  int playerSum = 0;
  //player start
  if (cards[index] < 4 || cards[index] > 40)
    printf("You're dealt a %s of %s worth %d ", checkFace(cards, index), checkSuit(cards, index), checkValue(cards, index) + changeAceValue(cards, index, dealerSum));
  else
    printf("You're dealt a %d of %s ", checkValue(cards, index) + changeAceValue(cards, index, dealerSum), checkSuit(cards, index));

  playerSum += (checkValue(cards, index) + changeAceValue(cards, index, playerSum));

  --index;
  if (cards[index] < 4 || cards[index] > 40)
    printf("and a %s of %s worth %d.\n", checkFace(cards, index), checkSuit(cards, index), checkValue(cards, index) + + changeAceValue(cards, index, dealerSum));
  else
    printf("and a %d of %s.\n", checkValue(cards, index) + changeAceValue(cards, index, dealerSum), checkSuit(cards, index));
  playerSum += (checkValue(cards, index) + changeAceValue(cards, index, playerSum));
  --index;
  //dealer start
  if (cards[index] < 4 || cards[index] > 40)
    printf("Dealer starts with a %s  of %s worth %d. ", checkFace(cards, index), checkSuit(cards, index), checkValue(cards, index) + changeAceValue(cards, index, dealerSum));
  else
    printf("Dealer starts with a %d  of %s. ", checkValue(cards, index) + changeAceValue(cards, index, dealerSum), checkSuit(cards, index));
  dealerSum += (checkValue(cards, index) + changeAceValue(cards, index, dealerSum));
  --index;
  *deckTop -= 3;
  printf("\n\nYou have a total card value of %d.\nThe dealer has a total card value of %d.", playerSum, dealerSum);
    play(cards, deckTop, dealerSum, playerSum);

}

int
play(int cards[], int *deckTop, int dealerSum, int playerSum) {
  int index = *deckTop;
  //lets player hit or stand
  char choice;
  while (checkWin(dealerSum, playerSum == 0)) {
    do {
      printf("\nType h to hit or s to stand: ");

      scanf(" %c", & choice);

    }
    while (choice != 'h' && choice != 's');
    if (choice == 'h') {
      if (cards[index] < 4 || cards[index] > 40)
        printf("You're dealt a %s of %s worth %d.\n",
          checkFace(cards, index), checkSuit(cards, index), checkValue(cards, index) + changeAceValue(cards, index, dealerSum));
      else
        printf("You're dealt a %d  of %s.\n", checkValue(cards, index) + changeAceValue(cards, index, dealerSum), checkSuit(cards, index));
      playerSum += (checkValue(cards, index) + changeAceValue(cards, index, playerSum));
      --index;
      --*deckTop;
      if (*deckTop == 0) {
        shuffle(cards, 52);
        *deckTop = 51;
      }
      printf
        ("\n\nYou have a total card value of %d.\nThe dealer has a total card value of %d.",
          playerSum, dealerSum);
      checkWin(dealerSum, playerSum);
      if (checkWin(dealerSum, playerSum) == 3) {
        printf("\n\nValue over 21, you busted. :(\n");
        return 1;
      }
    } else if (choice == 's') {
      if (cards[index] < 4 || cards[index] > 40)
        printf("Dealer get a %s of %s worth %d.", checkFace(cards, index), checkSuit(cards, index), checkValue(cards, index) + changeAceValue(cards, index, dealerSum));
      else
        printf("Dealer gets a %d of %s.", checkValue(cards, index) + changeAceValue(cards, index, dealerSum), checkSuit(cards, index));
      dealerSum += (checkValue(cards, index) + changeAceValue(cards, index, dealerSum));
      --index;
      --*deckTop;
      if (*deckTop == 0) {
        shuffle(cards, 52);
        *deckTop = 51;
      }
      while (dealerSum <= 17) {
        if (cards[index] < 4 || cards[index] > 40)
          printf("\nDealer gets a %s of %s worth %d.\n", checkFace(cards, index) + changeAceValue(cards, index, dealerSum), checkSuit(cards, index), checkValue(cards, index));
        else
          printf("\nDealer gets a %d of %s.\n", checkValue(cards, index) + changeAceValue(cards, index, dealerSum), checkSuit(cards, index));
        dealerSum += (checkValue(cards, index) + changeAceValue(cards, index, dealerSum));
        --index;
        --*deckTop;
        if (*deckTop == 0) {
          shuffle(cards, 52);
          *deckTop = 51;
        }
      }
      printf
        ("\n\nYou have a total card value of %d.\nThe dealer has a total card value of %d.",
          playerSum, dealerSum);
      if (checkWin(dealerSum, playerSum) == 3) {
        printf("\n\nYou lose this round.");
        return 1;
      } else if (checkWin(dealerSum, playerSum) == 4) {
        printf("\n\nYou win this round.");
        return 2;
      } else if (checkWin(dealerSum, playerSum) == 5) {
        printf("\n\nYour sum is equal to the dealers no one wins.");
        return 3;
      }
    }
  }

  return 0; //if return 1, dealer wins, return 2, player wins, return 3, no one wins
}

int
checkWin(int dealerSum, int playerSum) {
  //if 3 after standing dealer won, if 4 player won, if 5 tie
  if (((playerSum > 21) || (dealerSum > playerSum)) && (dealerSum < 22))
    return 3;
  if (((dealerSum > 21) || (playerSum > dealerSum)) && (playerSum < 22))
    return 4;
  else if (playerSum == dealerSum)
    return 5;
  return 0;
}

int
changeAceValue(int cards[], int index, int sum) {
  int aceValue10 = 0;
  if (checkValue(cards, index) == 1 && sum + 11 < 22)
    aceValue10 = 10;
  return aceValue10;
}

//This version implements a working system.
/**************It is Missing ****************/
/*
5.) Random shuffler not random once compiled
6.) must add chips
*/
