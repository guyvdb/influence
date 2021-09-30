#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdint.h>

typedef uint32_t  GRAPHID;
typedef uint32_t TIMESTAMP;

typedef enum {
  false,
  true
} bool;

typedef enum {
  closed,
  open,
  pending
} openstate_t; 

typedef enum {
  clean,
  dirty 
} writestate_t;

typedef enum {
  obj_type_unknown = 0,
  obj_type_vertex,
  obj_type_edge,
  obj_type_property
} obj_type_t;


// CONSTANTS
static const GRAPHID NULL_GRAPHID = 0;
static const GRAPHID INVALID_GRAPHID = UINT32_MAX - 1;

#endif // GLOBAL_H
