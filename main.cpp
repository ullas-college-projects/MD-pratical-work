#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "set.h"
#include "/home/ullas/Programming/Competitive-Programming/cp/debug.h"

typedef struct {
  int number_of_values;
  int* values;
  pair_set pairs;
} relationship_t;

pair_vector get_reflexive_ausent_pairs(relationship_t* relationship) {
  pair_vector vector = new_pair_vector();

  for(int i = 0; i < relationship->number_of_values; i++) {
    pair_t pair = { relationship->values[i], relationship->values[i] };
    if(!has(&relationship->pairs, pair)) {
      push_back(&vector, pair);
    }
  }

  return vector;
}

pair_vector get_symetric_ausent_pairs(relationship_t* relationship) {
  pair_vector vector = new_pair_vector();

  for(int i = 1; i < MAX_SIZE_SET; i++) {
    for(int j = 1; j < MAX_SIZE_SET; j++) {
      pair_t pair = { i, j }, symetric_pair = { j, i };
      if(has(&relationship->pairs, pair)) {
        if(!has(&relationship->pairs, symetric_pair)) {
          push_back(&vector, symetric_pair);
        }
      }
    }
  }

  return vector;
}

pair_vector get_transitive_ausent_pairs(relationship_t* relationship) {
  pair_set values = new_pair_set();

  for(int i = 0; i < relationship->number_of_values; i++) {
      for(int j = 0; j < relationship->number_of_values; j++) {
          for(int k = 0; k < relationship->number_of_values; k++) {
            pair_t a = { relationship->values[i], relationship->values[j] }, b = { relationship->values[j], relationship->values[k] }, c = { relationship->values[i], relationship->values[k] };
            if(has(&relationship->pairs, a) && has(&relationship->pairs, b)) {
              if(!has(&relationship->pairs, c)) {
                add(&values, c);  
              }
            }
          }
      }
  }

  pair_vector vector = get_all_values(&values);

  return vector;
}

pair_vector get_ireflexive_present_pairs(relationship_t* relationship) {
  pair_vector vector = new_pair_vector();

  for(int i = 0; i < relationship->number_of_values; i++) {
    pair_t pair = { relationship->values[i], relationship->values[i] };
    if(has(&relationship->pairs, pair)) {
      push_back(&vector, pair);
    }
  }

  return vector;
}

pair_pair_vector get_antisymetric_present_pairs(relationship_t* relationship) {
  pair_set visited = new_pair_set();
  pair_pair_vector vector = new_pair_pair_vector();

  for(int i = 0; i < relationship->number_of_values; i++) {
      for(int j = 0; j < relationship->number_of_values; j++) {
        if(relationship->values[i] != relationship->values[j]) {
          pair_t a = { relationship->values[i], relationship->values[j] }, b = { relationship->values[j], relationship->values[i] };
          if(has(&relationship->pairs, a) && has(&relationship->pairs, b)) {
            pair_pair_t pair = { a, b };  
            if(!has(&visited, a) && !has(&visited, b)) {
               append(&vector, pair);  
               add(&visited, a);
               add(&visited, b);
            }
          }
        }
      }
  }

  return vector;
}

bool is_asymetric(relationship_t* relationship) {
  pair_vector ireflexive = get_ireflexive_present_pairs(relationship);
  pair_pair_vector antisymetric = get_antisymetric_present_pairs(relationship);

  if(ireflexive.size == 0 && antisymetric.size == 0) {
    return true;
  }

  return false;
}




int main() {

   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
   freopen("error.txt", "w", stderr);

  int number_of_values;
  scanf("%d", &number_of_values);

  int* values = (int*)calloc(number_of_values, sizeof(int));
  for(int i = 0; i < number_of_values; i++) {
    scanf("%d", &values[i]);
  }

  pair_set pairs;
  pair_t input;
  while(scanf("%d %d", &input.first, &input.second) != EOF) {
    add(&pairs, input);
  }

  relationship_t relationship = { number_of_values, values, pairs };

  pair_pair_vector r = get_antisymetric_present_pairs(&relationship);

  printf("%d", r.size);

  return 0;
}
