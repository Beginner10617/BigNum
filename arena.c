#include "arena.h"
#include "stdlib.h"
#include "stdio.h"
#include "assert.h"
// Display colors for errors and warnings
#define ERROR "\x1b[31m"
#define WARNING "\033[33m"
#define COLOR_RESET "\x1b[0m"

Arena* createArena(size_t cap){
  Arena* arena = malloc(
    sizeof(Arena));
  if(arena == NULL){
    printf(ERROR 
    "Unable to create Arena allocator\n"
    COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  arena->offset=0;
  arena->cap=cap;
  arena->memory = malloc(cap);
  if(arena == NULL){
    printf(ERROR 
    "Unable to allocate memory to arena\n"
    COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  return arena;
}

void* allocate(Arena* arena, size_t size){
  assert(arena);
  if(arena->offset + size > arena->cap){
    printf(WARNING 
    "Arena allocator capacity exceeded\n"
    COLOR_RESET);
    while(arena->offset + size > arena->cap)
    {
      arena->cap *= 2;
    }
    arena->memory = realloc(
      arena->memory, 
      arena->cap);
    if(arena->memory == NULL){
      printf(ERROR
      "Unable to reallocate memory to arena\n"
      COLOR_RESET);
      exit(EXIT_FAILURE);
    }
  }
  void* out = arena->memory
    + arena->offset;
  arena->offset += size;
  return out;
}

void freeArena(Arena** arena){
  if(arena && *arena){
    if((*arena)->memory)
      free( (*arena)->memory );
    free(*arena);
  }
}
