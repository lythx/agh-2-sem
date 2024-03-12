#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NUMBER_OF_CARDS 52
#define NUMBER_OF_COLORS 4

enum state { OK = 0, UNDERFLOW = -1, OVERFLOW = -2 };

struct CardQueue {
    int card_count;
    int buff_out;
    int *cards;
};

/**
 * Gracz bierze karte ze stolu
 */
int take_card(struct CardQueue *p, int card_code) {
  if(p->card_count == NUMBER_OF_CARDS) {
    return OVERFLOW;
  }
  p->cards[(p->card_count + p->buff_out) % NUMBER_OF_CARDS] = card_code;
  p->card_count++;
  return OK;
}

/**
 * Gracz kladzie karte na stol
 */
int reveal_card(struct CardQueue *p) {
  if(p->card_count == 0) {
    return UNDERFLOW;
  }
  int value = p->cards[p->buff_out];
  p->buff_out = (p->buff_out + 1) % NUMBER_OF_CARDS;
  p->card_count--;
  return value;
}

int random_from_interval(int a, int b) {
  if(a > b) {
    return INT_MIN;
  }
  if (b - a > RAND_MAX) {
    return INT_MAX;
  }
  if (a == b) {
    return a;
  }
  return rand() % (b - a + 1) + a;
}

void swap(int array[], int i, int k) {
  int temp = array[i];
  array[i] = array[k];
  array[k] = temp;
}

void shuffle(int t[], int size) {
  for(int i = 0; i < size; i++) {
    t[i] = i;
  }
  for(int i = 0; i < size - 1; i++) {
    int k = random_from_interval(i, size - 1);
    swap(t, i, k);
  }
}

/**
 * Porownuje dwie karty
 * @return 0 jesli karty sa takie same, 1 jestli pierwsza wygrala, 2 jesli druga wygrala
 */
int compare_cards(int card1, int card2) {
  int rank_a = card1 / NUMBER_OF_COLORS;
  int rank_b = card2 / NUMBER_OF_COLORS;
  if(rank_a == rank_b) {
    return 0;
  }
  if(rank_a > rank_b) {
    return 1;
  }
  return 2;
}

/**
 * Wypisuje dane na koncu gry
 */
void conclude(int status, int conflict_count, struct CardQueue *p1, struct CardQueue *p2) {
  printf("%d ", status);
  int value;
  switch (status) {
    case 0:
    case 1:
      printf("%d ", p1->card_count);
      printf("%d", p2->card_count);
      break;
    case 2:
      printf("%d", conflict_count);
      break;
    case 3:
      printf("\n");
      while((value = reveal_card(p2)) != UNDERFLOW) {
        printf("%d ", value);
      }
      break;
    default: break;
  }
}

/**
 * Ustawia zmienne w obiekcie gracza
 */
void initialize_queue(struct CardQueue* p, int cards[], int card_count) {
  p->card_count = card_count;
  p->buff_out = 0;
  p->cards = cards;
}

/**
 * Przekazuje wszystkie karty z kolejki b do a
 */
void take_all(struct CardQueue* a, struct CardQueue* b) {
  int card;
  while((card = reveal_card(b)) != UNDERFLOW) {
    take_card(a, card);
  }
}

/**
 * Sprawdza czy ktorys z graczy ma 0 kart i zwraca zwyciezce jesli tak
 * @return 0 jesli nie ma zwyciezcy, 1 jesli p1 wygral, 2 jesli p2 wygral
 */
int get_winner(struct CardQueue* p1, struct CardQueue* p2) {
  if(p1->card_count == 0) {
    return 2;
  }
  if(p2->card_count == 0) {
    return 1;
  }
  return 0;
}

/**
 * Symuluje "konflikt" (i ewentualna "wojne") pomiedzy graczami
 * @return 1 jesli podczas "wojny" jednemu z graczy zabraklo kart, inaczej 0
 */
int conflict(struct CardQueue *p1, struct CardQueue *p2, struct CardQueue *p1_table, struct CardQueue *p2_table, int simplified_mode) {
  int p1_card = reveal_card(p1);
  int p2_card = reveal_card(p2);
  take_card(p1_table, p1_card);
  take_card(p2_table, p2_card);
  int status = compare_cards(p1_card, p2_card);
  if(status == 0) {
    if(simplified_mode) {
      take_card(p1, reveal_card(p1_table));
      take_card(p2, reveal_card(p2_table));
    } else {
      int winner = get_winner(p1, p2);
      if(winner != 0) {
        return 1;
      }
      take_card(p1_table, reveal_card(p1));
      take_card(p2_table, reveal_card(p2));
      winner = get_winner(p1, p2);
      if(winner != 0) {
        return 1;
      }
    }
  } else if(status == 1) {
    take_all(p1, p1_table);
    take_all(p1, p2_table);
  } else {
    take_all(p2, p2_table);
    take_all(p2, p1_table);
  }
  return 0;
}

void game(int n, int player_A[], int player_B[], int max_conflicts, int simplified_mode) {
  int conflict_count = 0;
  int p1_table_cards[NUMBER_OF_CARDS] = {0}, p2_table_cards[NUMBER_OF_CARDS] = {0};
  struct CardQueue p1, p2, p1_table, p2_table;
  initialize_queue(&p1, player_A, NUMBER_OF_CARDS / 2);
  initialize_queue(&p2, player_B, NUMBER_OF_CARDS / 2);
  initialize_queue(&p1_table, p1_table_cards, 0);
  initialize_queue(&p2_table, p2_table_cards, 0);
  while(1) {
    int out_of_cards = conflict(&p1, &p2, &p1_table, &p2_table, simplified_mode);
    conflict_count++;
    if(out_of_cards) {
      take_all(&p1, &p1_table);
      take_all(&p2, &p2_table);
      conclude(1, conflict_count, &p1, &p2);
      return;
    }
    int winner = get_winner(&p1, &p2);
    if(winner == 1) {
      conclude(2, conflict_count, &p1, &p2);
      return;
    } else if(winner == 2) {
      conclude(3, conflict_count, &p1, &p2);
      return;
    }
    if(conflict_count > max_conflicts) {
      conclude(0, conflict_count, &p1, &p2);
      return;
    }
  }
}

int main(void) {
	int player_A[NUMBER_OF_CARDS], player_B[NUMBER_OF_CARDS];
	int deck[NUMBER_OF_CARDS];
	int max_conflicts;
	int simplified_mode;
	int seed;
	scanf("%d", &seed);
	scanf("%d", &simplified_mode);
	scanf("%d", &max_conflicts);

	for(int i = 0; i < NUMBER_OF_CARDS; i++) deck[i] = i;
	srand((unsigned) seed);
	shuffle(deck, NUMBER_OF_CARDS);
	for(int i = 0; i < NUMBER_OF_CARDS / 2; i++) {
		player_A[i] = deck[i];
		player_B[i] = deck[i + NUMBER_OF_CARDS / 2];
	}
	game(NUMBER_OF_CARDS, player_A, player_B, max_conflicts, simplified_mode);
	return 0;
}

