#ifndef SET_H
#define SET_H

#include <stdbool.h>

#define MAX_SIZE_SET (51)
#define MAX_SIZE_VECTOR (MAX_SIZE_SET * MAX_SIZE_SET) 


typedef struct {
  int first;
  int second;
} pair_t;

typedef struct {
  pair_t first;
  pair_t second;
} pair_pair_t;

typedef struct {
  int size;
  int matrix[MAX_SIZE_SET][MAX_SIZE_SET];  
} pair_set;

typedef struct {
  int size;
  pair_t array[MAX_SIZE_VECTOR];
} pair_vector;

typedef struct {
  int size;
  pair_pair_t array[MAX_SIZE_VECTOR];
} pair_pair_vector;

pair_set new_pair_set() {
  pair_set set;
  set.size = 0;
  for(int i = 0; i < MAX_SIZE_SET; i++) {
    for(int j = 0; j < MAX_SIZE_SET; j++) {
      set.matrix[i][j] = -1;
    }
  }

  return set;
}

pair_vector new_pair_vector() {
  pair_vector vector;
  vector.size = 0;

  return vector;
}

pair_pair_vector new_pair_pair_vector() {
  pair_pair_vector vector;
  vector.size = 0;

  return vector;
}

void add(pair_set* set, pair_t pair) {
  set->matrix[pair.first][pair.second] = 1;
}

bool has(pair_set* set, pair_t pair) {
  return set->matrix[pair.first][pair.second] == 1;
}

void push_back(pair_vector* vector, pair_t pair) {
  vector->array[vector->size] = pair;
  vector->size++;
}

void append(pair_pair_vector* vector, pair_pair_t pair) {
  vector->array[vector->size] = pair;
  vector->size++;
}

pair_vector get_all_values(pair_set* set) {
  pair_vector vector;
  for(int i = 0; i < MAX_SIZE_SET; i++) {
    for(int j = 0; j < MAX_SIZE_SET; j++) {
      pair_t pair = { i, j };
      if(has(set, pair)) {
        push_back(&vector, pair);
      }
    }
  }

  return vector;
}

#endif
