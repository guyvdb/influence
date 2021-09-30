#ifndef OBJ_H
#define OBJ_H

#include <stdint.h>

// Obj defines the header that is present on all stored objects as the first element of the struct


static const uint8_t OBJ_UNUSED = 0;
static const uint8_t OBJ_USED = 1;


struct objheader {
  // flags[0] -- 0 = unused, 1 = in use 
  char flags[2];
};

typedef struct objheader objheader_t;

#endif // OBJ_H
