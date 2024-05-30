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

  for(int i = 0; i < MAX_SIZE_SET; i++) {
    for(int j = 0; j < MAX_SIZE_SET; j++) {
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

pair_vector get_reflexive_clasp(relationship_t* relationship) {
  pair_vector vector = get_all_values(&relationship->pairs); 
  pair_vector ausent_pairs = get_reflexive_ausent_pairs(relationship);

  for(int i = 0; i < ausent_pairs.size; i++) {
    push_back(&vector, ausent_pairs.array[i]);
  }
  
  return vector;
}

pair_vector get_symetric_clasp(relationship_t* relationship) {
  pair_vector vector = get_all_values(&relationship->pairs); 
  pair_vector ausent_pairs = get_symetric_ausent_pairs(relationship);

  for(int i = 0; i < ausent_pairs.size; i++) {
    push_back(&vector, ausent_pairs.array[i]);
  }
  
  return vector;
}

pair_vector get_transitive_clasp(relationship_t relationship) {
  pair_vector vector;
  while(true) {
    pair_vector vector = get_transitive_ausent_pairs(&relationship);

    if(vector.size == 0) {
      vector = get_all_values(&relationship.pairs);
      return vector;
    }
    
    for(int i = 0; i < vector.size; i++) {
      dbg(vector.array[i].first, vector.array[i].second);
    }

    for(int i = 0; i < vector.size; i++) {
      add(&relationship.pairs, vector.array[i]);
    }
  }
}

bool is_a_equivalence_relationship(relationship_t* relationship) {
  pair_vector ausent_reflexive_pairs = get_reflexive_ausent_pairs(relationship);
  pair_vector ausent_symetric_pairs = get_symetric_ausent_pairs(relationship);
  pair_vector ausent_transitive_pairs = get_transitive_ausent_pairs(relationship);

  if(ausent_reflexive_pairs.size == 0 && ausent_symetric_pairs.size == 0 && ausent_transitive_pairs.size == 0) {
    return true;
  }

  return false;
}

bool is_partial_order_relationship(relationship_t* relationship) {
  pair_vector ausent_reflexive_pairs = get_reflexive_ausent_pairs(relationship);
  pair_pair_vector present_antisymetric_pairs = get_antisymetric_present_pairs(relationship);
  pair_vector ausent_transitive_pairs = get_transitive_ausent_pairs(relationship);

  if(ausent_reflexive_pairs.size == 0 && present_antisymetric_pairs.size == 0 && ausent_transitive_pairs.size == 0) {
    return true;
  }

  return false;
}

void output_pair_vector_property(pair_vector* vector) {
  if(vector->size == 0) {
    printf("V\n");
    return;
  }

  printf("F\n");
  print(vector);
}

void output_pair_pair_vector_property(pair_pair_vector* vector) {
  if(vector->size == 0) {
    printf("V\n");
    return;
  }

  printf("F\n");
  print_pair_pair_vector(vector);
}

void output_clasp(pair_vector* clasp, relationship_t* relationship) {
  if(clasp->size == relationship->pairs.size) {
    printf("R\n");
    return;
  } 

  print(clasp);
}

void output_bool(bool value) {
  if(value) {
    printf("V\n");
    return;
  }

  printf("F\n");
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

  printf("Propriedades\n");

  pair_vector ausent_reflexive_pairs = get_reflexive_ausent_pairs(&relationship);
  pair_vector present_ireflexive_pairs = get_ireflexive_present_pairs(&relationship);
  pair_vector ausent_symetric_pairs = get_symetric_ausent_pairs(&relationship);
  pair_pair_vector ausent_antisymetric_pairs = get_antisymetric_present_pairs(&relationship);
  pair_vector ausent_transitive_pairs = get_transitive_ausent_pairs(&relationship);

  pair_vector reflexive_clasp = get_reflexive_clasp(&relationship);
  pair_vector symetric_clasp = get_symetric_clasp(&relationship);
  pair_vector transitive_clasp = get_transitive_clasp(relationship);

  qsort(ausent_antisymetric_pairs.array, ausent_reflexive_pairs.size, sizeof(pair_t), pair_comparer);
  qsort(present_ireflexive_pairs.array, present_ireflexive_pairs.size, sizeof(pair_t), pair_comparer);
  qsort(ausent_symetric_pairs.array, ausent_symetric_pairs.size, sizeof(pair_t), pair_comparer);

  for(int i = 0; i < ausent_antisymetric_pairs.size; i++) {
    pair_t a = ausent_antisymetric_pairs.array[i].first, b = ausent_antisymetric_pairs.array[i].second;

    if(pair_comparer(&a, &b) > 0) {
      pair_t aux = a;
      ausent_antisymetric_pairs.array[i].first = b;
      ausent_antisymetric_pairs.array[i].second = b;
    }
  }

  qsort(ausent_antisymetric_pairs.array, ausent_antisymetric_pairs.size, sizeof(pair_pair_t), pair_pair_comparer);

  qsort(ausent_transitive_pairs.array, ausent_transitive_pairs.size, sizeof(pair_t), pair_comparer);
  qsort(reflexive_clasp.array, reflexive_clasp.size, sizeof(pair_t), pair_comparer);
  qsort(symetric_clasp.array, symetric_clasp.size, sizeof(pair_t), pair_comparer);
  qsort(transitive_clasp.array, transitive_clasp.size, sizeof(pair_t), pair_comparer);


  printf("1. Reflexiva: "); 
  output_pair_vector_property(&ausent_reflexive_pairs);

  printf("2. Irreflexiva: "); 
  output_pair_vector_property(&present_ireflexive_pairs);

  printf("3. Simetrica: "); 
  output_pair_vector_property(&ausent_symetric_pairs);


  printf("4. Anti-simetrica: "); 
  output_pair_pair_vector_property(&ausent_antisymetric_pairs);


  printf("5. Assimetrica: "); 
  output_bool(is_asymetric(&relationship));

  printf("6. Transitiva: ");
  output_pair_vector_property(&ausent_transitive_pairs);

  printf("Relacao de equivalencia: ");
  output_bool(is_a_equivalence_relationship(&relationship));


  printf("Relacao de ordem parcial: ");
  output_bool(is_partial_order_relationship(&relationship));

  printf("Fecho reflexivo da relacao: ");
  output_clasp(&reflexive_clasp, &relationship);


  printf("Fecho simetrico da relacao: ");
  output_clasp(&symetric_clasp, &relationship);


  printf("Fecho transitivo da relacao: ");
  output_clasp(&transitive_clasp, &relationship);

  return 0;
}
