#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// consider chars from [FIRST_CHAR, LAST_CHAR)
#define FIRST_CHAR 33
#define LAST_CHAR 127
#define MAX_CHARS (LAST_CHAR - FIRST_CHAR)
#define MAX_BIGRAMS ((LAST_CHAR - FIRST_CHAR) * (LAST_CHAR - FIRST_CHAR))

#define EOL '\n'
#define IN_WORD 1
#define MAX_LINE 128

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2

int count[MAX_BIGRAMS] = { 0 };

// sort indices according to their respective counts.
// sort alphabetically if counts equal
int cmp (const void *a, const void *b) {
	int va = *(int*)a;
	int vb = *(int*)b;
	if (count[va] == count[vb]) return va - vb;	return count[vb] - count[va];
}

// sort indices according to their respective counts.
// sort alphabetically if counts equal
int cmp_di (const void *a, const void *b) {
	int va = *(int*)a;
	int vb = *(int*)b;
	// sort according to second char if counts and the first char equal
	if (count[va] == count[vb] && va / MAX_CHARS == vb / MAX_CHARS) return va % MAX_CHARS - vb % MAX_CHARS;
	// sort according to first char if counts equal
	if (count[va] == count[vb]) return va / MAX_CHARS - vb / MAX_CHARS;
	return count[vb] - count[va];
}

// count lines, words & chars in a given text file
void wc(int *nl, int *nw, int *nc) {
  *nl=*nw=*nc=0;
  char c = (char)fgetc(stdin);
  int in_space = 1;
  while(c != EOF) {
    *nc += 1;
    if(c == EOL) {
      *nl += 1;
      in_space = 1;
    }
    else if(isspace(c)) {
      in_space = 1;
    }
    else {
      if(in_space) {
        *nw += 1;
        in_space = 0;
      }
    }
    c = (char)fgetc(stdin);
  }
}

void char_count(int char_no, int *n_char, int *cnt) {
  int chars[MAX_CHARS];
  for(int i = 0; i < MAX_CHARS; i++) {
    chars[i] = i;
    count[i] = 0;
  }
  char c = (char)fgetc(stdin);
  while(c != EOF) {
    if(c >= FIRST_CHAR && c < LAST_CHAR) {
      count[c - FIRST_CHAR] += 1;
    }
    c = (char)fgetc(stdin);
  }
  qsort(chars, MAX_CHARS, sizeof(int), cmp);
  *n_char = FIRST_CHAR + chars[char_no - 1];
  *cnt = count[*n_char - FIRST_CHAR];
}

void bigram_count(int bigram_no, int bigram[]) {
  int bigrams[MAX_BIGRAMS];
  for(int i = 0; i < MAX_CHARS; i++) {
    for(int j = 0; j < MAX_CHARS; j++) {
      bigrams[i*MAX_CHARS + j] = i*MAX_CHARS + j;
    }
  }
  char c1 = (char)fgetc(stdin);
  char c2 = (char)fgetc(stdin);
  while(c2 != EOF) {
    if(!isspace(c1) && !isspace(c2)) {
      count[((int)c1 - FIRST_CHAR)*MAX_CHARS + (int)c2 - FIRST_CHAR]++;
    }
    c1 = c2;
    c2 = (char)fgetc(stdin);
  }
  qsort(bigrams, MAX_BIGRAMS, sizeof(int), cmp_di);
  bigram[0]= FIRST_CHAR + bigrams[bigram_no - 1] / MAX_CHARS;
  bigram[1]= FIRST_CHAR + bigrams[bigram_no - 1] % MAX_CHARS;
  bigram[2]= count[(bigram[0] - FIRST_CHAR) * MAX_CHARS + bigram[1] - FIRST_CHAR];
}

void find_comments(int *line_comment_counter, int *block_comment_counter) {
  *line_comment_counter = 0;
  *block_comment_counter = 0;
  char c1 = fgetc(stdin);
  char c2 = fgetc(stdin);
  int comment = 0;
  do {
    if(comment == 0) {
      if (c1 == '/' && c2 == '/') {
        (*line_comment_counter)++;
        comment = IN_LINE_COMMENT;
        c2 = fgetc(stdin);
      }
      else if(c1 == '/' && c2 == '*'){
        (*block_comment_counter)++;
        comment = IN_BLOCK_COMMENT;
        c2 = fgetc(stdin);
      }
    } else {
      if ((comment == IN_LINE_COMMENT && (c1 == '\n' || c2 == '\n')) ||
              (comment == IN_BLOCK_COMMENT && (c1 == '*' && c2 == '/'))){
        comment = 0;
      }
    }
    c1 = c2;
    c2 = fgetc(stdin);
  } while(c2 != EOF);
}

int read_int() {
	char line[MAX_LINE];
	fgets(line, MAX_LINE, stdin); // to get the whole line
	return (int)strtol(line, NULL, 10);
}

int main(void) {
	int to_do;
	int nl, nw, nc, char_no, n_char, cnt;
	int line_comment_counter, block_comment_counter;
	int bigram[3];

	to_do = read_int();
	switch (to_do) {
		case 1: // wc()
			wc (&nl, &nw, &nc);
			printf("%d %d %d\n", nl, nw, nc);
			break;
		case 2: // char_count()
			char_no = read_int();
			char_count(char_no, &n_char, &cnt);
			printf("%c %d\n", n_char, cnt);
			break;
		case 3: // bigram_count()
			char_no = read_int();
			bigram_count(char_no, bigram);
			printf("%c%c %d\n", bigram[0], bigram[1], bigram[2]);
			break;
		case 4:
			find_comments(&line_comment_counter, &block_comment_counter);
			printf("%d %d\n", block_comment_counter, line_comment_counter);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

