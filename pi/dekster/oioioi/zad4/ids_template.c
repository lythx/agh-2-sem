#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2
#define IN_STRING 4
#define IN_ID 8

#define MAX_ID_LEN 64
#define MAX_IDS 1024
#define KEYWORD_COUNT 32

int index_cmp(const void*, const void*);
int cmp(const void*, const void*);

char identifiers[MAX_IDS][MAX_ID_LEN];

const char *keywords[] = {
	"auto", "break", "case", "char",
	"const", "continue", "default", "do",
	"double", "else", "enum", "extern",
	"float", "for", "goto", "if",
	"int", "long", "register", "return",
	"short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union",
	"unsigned", "void", "volatile", "while"
};

int is_new_identifier(int k) {
  for(int i = 0; i < KEYWORD_COUNT; i++) {
    if(strcmp(keywords[i], identifiers[k]) == 0) {
      return 0;
    }
  }
  for(int i = 0; i < k; i++) {
    if(strcmp(identifiers[i], identifiers[k]) == 0) {
      return 0;
    }
  }
  return 1;
}

int find_idents() {
  char c = fgetc(stdin);
  int i = 0;
  while(c != EOF) {
    if(isalpha(c) || c == '_') {
      int j = 0;
      do {
        identifiers[i][j] = c;
        j += 1;
        c = fgetc(stdin);
      } while(isalnum(c) || c == '_');
      if(is_new_identifier(i)) {
        i += 1;
      } else {
        memset(identifiers[i], 0, sizeof(identifiers[i]));
      }
    }
    else if(c == '"') {
      do {
        if (c=='\\') {
          fgetc(stdin);
        }
        c = fgetc(stdin);
      } while(c != '"');
    }
    else if(c == '\'') {
      do {
        if (c=='\\') {
          fgetc(stdin);
        }
        c = fgetc(stdin);
      } while(c != '\'');
    }
    else if(c == '/') {
      char c2 = fgetc(stdin);
      if(c2 == '/') {
        while(c2 != '\r' && c2 != '\n') {
          c2 = fgetc(stdin);
        }
      }
      else if(c2 == '*') {
        while(c != '*' || c2 != '/') {
          c = c2;
          c2 = fgetc(stdin);
        }
      }
    }
    c = fgetc(stdin);
  }
  return i;
}

int cmp(const void* first_arg, const void* second_arg) {
	char *a = *(char**)first_arg;
	char *b = *(char**)second_arg;
	return strcmp(a, b);
}

int index_cmp(const void* first_arg, const void* second_arg) {
	int a = *(int*)first_arg;
	int b = *(int*)second_arg;
	return strcmp(identifiers[a], identifiers[b]);
}

int main(void) {
	printf("%d\n", find_idents());
	return 0;
}

