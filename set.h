#ifndef SET_H
#define SET_H

#include <stdio.h>
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

int pair_comparer(const void* a, const void* b) {
  pair_t* pair1 = (pair_t*)a;
  pair_t* pair2 = (pair_t*)b;

  if(pair1->first < pair2->first) {
    return -1;
  }

  if(pair1->first > pair2->first) {
    return 1;
  }

  if(pair1->second < pair2->second) {
    return -1;
  }

  if(pair1->second > pair2->second) {
    return 1;
  }

  return 0;
}

int pair_pair_comparer(const void* a, const void* b) {
  pair_pair_t* pair_pair1 = (pair_pair_t*)a;
  pair_pair_t* pair_pair2 = (pair_pair_t*)b;

  pair_t* pair1 = &pair_pair1->first;
  pair_t* pair2 = &pair_pair2->first;

  if(pair1->first < pair2->first) {
    return -1;
  }

  if(pair1->first > pair2->first) {
    return 1;
  }

  if(pair1->second < pair2->second) {
    return -1;
  }

  if(pair1->second > pair2->second) {
    return 1;
  }

  return 0;
}

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
  set->size++;
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
  pair_vector vector = new_pair_vector();
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

void print(pair_vector* vector) {
  for(int i = 0; i < vector->size - 1; i++) {
    printf("(%d, %d), ", vector->array[i].first, vector->array[i].second);
  }

  printf("(%d, %d)\n", vector->array[vector->size - 1].first, vector->array[vector->size - 1].second);
}

void print_pair_pair_vector(pair_pair_vector* vector) {
  for(int i = 0; i < vector->size - 1; i++) {
    printf("((%d, %d), (%d, %d)), ", vector->array[i].first.first, vector->array[i].first.second, vector->array[i].second.first, vector->array[i].second.second);
  }

  printf("((%d, %d), (%d, %d))\n", vector->array[vector->size - 1].first.first, vector->array[vector->size - 1].first.second, vector->array[vector->size - 1].second.first, vector->array[vector->size - 1].second.second);
}

#endif
