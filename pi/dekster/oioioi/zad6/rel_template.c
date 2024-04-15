#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 100
#define MAX_RANGE 100

typedef struct {
	int first;
	int second;
} pair;

// Add pair to existing relation if not already there
int add_relation (pair *tab, int n, pair new_pair) { }

int cmp(const void* a, const void* b) {
  return *((int*)a) - *((int*)b);
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *relation) {
  int n;
  pair p;
  scanf("%d", &n);
  for (int i = 0; i < n; i++){
    scanf("%d %d", &p.first, &p.second);
    relation[i] = p;
  }
  return n;
}

void print_int_array(int *array, int n) {
	printf("%d\n", n);
	for (int i = 0; i < n; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

//------------------------------------------------

// Case 1:

// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair *tab, int n) {
  for(int i = 0; i < n; i++) {
    int x = tab[i].first;
    int found_xrx = 0;
    for(int j = 0; j < n; j++) {
      if(tab[j].first == x && tab[j].second == x) {
        found_xrx = 1;
        break;
      }
    }
    if(!found_xrx) {
      return 0;
    }
  }
  return 1;
}

// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair *tab, int n) {
  for(int i = 0; i < n; i++) {
    int x = tab[i].first;
    int found_xrx = 0;
    for(int j = 0; j < n; j++) {
      if(tab[j].first == x && tab[j].second == x) {
        found_xrx = 1;
        break;
      }
    }
    if(found_xrx) {
      return 0;
    }
  }
  return 1;
}

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair *tab, int n) {
  for(int i = 0; i < n; i++) {
    int x = tab[i].first;
    int y = tab[i].second;
    int found_yrx = 0;
    for(int j = 0; j < n; j++) {
      if(tab[j].first == y && tab[j].second == x) {
        found_yrx = 1;
        break;
      }
    }
    if(!found_yrx) {
      return 0;
    }
  }
  return 1;
}

// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair *tab, int n) {
  for(int i = 0; i < n; i++) {
    int x = tab[i].first;
    int y = tab[i].second;
    if(x == y) {
      continue;
    }
    int found_yrx = 0;
    for(int j = 0; j < n; j++) {
      if(tab[j].first == y && tab[j].second == x) {
        found_yrx = 1;
        break;
      }
    }
    if(found_yrx) {
      return 0;
    }
  }
  return 1;
}

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair *tab, int n) {
  for(int i = 0; i < n; i++) {
    int x = tab[i].first;
    int y = tab[i].second;
    if(x == y) {
      return 0;
    }
    int found_yrx = 0;
    for(int j = 0; j < n; j++) {
      if(tab[j].first == y && tab[j].second == x) {
        found_yrx = 1;
        break;
      }
    }
    if(found_yrx) {
      return 0;
    }
  }
  return 1;
}

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair *tab, int n) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if(tab[i].second != tab[j].first) {
        continue;
      }
      int x = tab[i].first;
      int z = tab[j].second;
      int found_xrz = 0;
      for(int k = 0; k < n; k++) {
        if(tab[k].first == x && tab[k].second == z) {
          found_xrz = 1;
          break;
        }
      }
      if(!found_xrz) {
        return 0;
      }
    }
  }
  return 1;
}

//------------------------------------------------

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair *tab, int n) {
  return is_reflexive(tab, n) && is_transitive(tab, n) && is_antisymmetric(tab, n);
}

int find_max_elements(pair *tab, int n, int *max_elements) { // tab - partial order
  int max_ind = 0;
  for(int i = 0; i < n; i++) {
    int mx = tab[i].second;
    int already_found = 0;
    for(int j = 0; j < max_ind; j++) {
      if(max_elements[j] == mx) {
        already_found = 1;
        break;
      }
    }
    if(already_found) {
      continue;
    }
    int is_max = 1;
    for(int j = 0; j < n; j++) {
      if(tab[j].first == mx && tab[j].second != mx) {
        is_max = 0;
      }
    }
    if(is_max) {
      max_elements[max_ind++] = mx;
    }
  }
  qsort(max_elements, max_ind, sizeof(int), cmp);
  return max_ind;
}

int find_min_elements(pair *tab, int n, int *min_elements) { // tab - strong partial order
  int min_ind = 0;
  for(int i = 0; i < n; i++) {
    int mn = tab[i].first;
    int already_found = 0;
    for(int j = 0; j < min_ind; j++) {
      if(min_elements[j] == mn) {
        already_found = 1;
        break;
      }
    }
    if(already_found) {
      continue;
    }
    int is_min = 1;
    for(int j = 0; j < n; j++) {
      if(tab[j].second == mn && tab[j].first != mn) {
        is_min = 0;
      }
    }
    if(is_min) {
      min_elements[min_ind++] = mn;
    }
  }
  qsort(min_elements, min_ind, sizeof(int), cmp);
  return min_ind;
}

int get_domain(pair *tab, int n, int *domain) {
  int domain_ind = 0;
  for(int i = 0; i < n; i++) {
    int elem = tab[i].first;
    int already_found = 0;
    for(int j = 0; j < domain_ind; j++) {
      if(domain[j] == elem) {
        already_found = 1;
        break;
      }
    }
    if(!already_found) {
      domain[domain_ind++] = elem;
    }
    elem = tab[i].second;
    already_found = 0;
    for(int j = 0; j < domain_ind; j++) {
      if(domain[j] == elem) {
        already_found = 1;
        break;
      }
    }
    if(!already_found) {
      domain[domain_ind++] = elem;
    }
  }
  qsort(domain, domain_ind, sizeof(int), cmp);
  return domain_ind;
}

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair *tab, int n) {
  int domain[MAX_REL_SIZE];
  int domain_size = get_domain(tab, n, domain);
  for(int i = 0; i < domain_size; i++) {
    int x = domain[i];
    for(int j = i + 1; j < domain_size; j++) {
      int y = domain[j];
      int found_xry_yrx = 0;
      for(int k = 0; k < n; k++) {
        if((tab[k].first == x && tab[k].second == y) ||
        (tab[k].first == y && tab[k].second == x)) {
          found_xry_yrx = 1;
        }
      }
      if(!found_xry_yrx) {
        return 0;
      }
    }
  }
  return 1;
}

// A total order relation is a partial order relation that is connected
int is_total_order(pair *tab, int n) {
  return is_partial_order(tab, n) && is_connected(tab, n);
}

//------------------------------------------------

// Case 3:

// x(S o R)z iff exists y: xRy and ySz
int composition (pair *rel_1, int n1, pair *rel_2, int n2, pair *rel_3) {
  int n3 = 0;
  int domain[MAX_REL_SIZE];
  int domain_size = get_domain(rel_1, n1, domain);
  int range[MAX_REL_SIZE];
  int range_size = get_domain(rel_2, n2, range);
  for(int i = 0; i < domain_size; i++) {
    int x = domain[i];
    for(int j = 0; j < range_size; j++) {
      int z = range[j];
      for(int k = 0; k < n1; k++) {
        if(rel_1[k].first != x) {
          continue;
        }
        int y = rel_1[k].second;
        int found_xry_yrz = 0;
        for(int m = 0; m < n2; m++) {
          if(rel_2[m].first == y && rel_2[m].second == z) {
            pair p;
            p.first = x;
            p.second = z;
            rel_3[n3++] = p;
            found_xry_yrz = 1;
            break;
          }
        }
        if(found_xry_yrz) {
          break;
        }
      }
    }
  }
  return n3;
}

int main(void) {
	int to_do;
	pair relation[MAX_REL_SIZE];
	pair relation_2[MAX_REL_SIZE];
	pair comp_relation[MAX_REL_SIZE];
	int domain[MAX_REL_SIZE];
	int max_elements[MAX_REL_SIZE];
	int min_elements[MAX_REL_SIZE];

	scanf("%d",&to_do);
	int size = read_relation(relation);
	int ordered, size_2, n_domain;

	switch (to_do) {
		case 1:
			printf("%d ", is_reflexive(relation, size));
			printf("%d ", is_irreflexive(relation, size));
			printf("%d ", is_symmetric(relation, size));
			printf("%d ", is_antisymmetric(relation, size));
			printf("%d ", is_asymmetric(relation, size));
			printf("%d\n", is_transitive(relation, size));
			break;
		case 2:
			ordered = is_partial_order(relation, size);
			n_domain = get_domain(relation, size, domain);
			printf("%d %d\n", ordered, is_total_order(relation, size));
			print_int_array(domain, n_domain);
			if (!ordered) break;
			int no_max_elements = find_max_elements(relation, size, max_elements);
			int no_min_elements = find_min_elements(relation, size, min_elements);
			print_int_array(max_elements, no_max_elements);
			print_int_array(min_elements, no_min_elements);
			break;
		case 3:
			size_2 = read_relation(relation_2);
			printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	
	return 0;
}

