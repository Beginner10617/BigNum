#ifndef ARENA
#define ARENA

typedef struct {
  void* memory;
  size_t offset, cap;
} Arena;

Arena* createArena(size_t cap);
void* allocate(Arena* arena, size_t size);
void freeArena(Arena** arena);
#endif
