#ifndef COUNTER_H
#define COUNTER_H

#include <stdio.h>
#include "global.h"
#include "store.h"


// the value of a recycled id stored in the linked list or on disk
struct ident_recycled_value {
  obj_type_t type;
  GRAPHID id;
};

typedef struct ident_recycled_value ident_recycled_value_t;

// A linked list item of recycled ids 
struct ident_recycled_rec {
  struct ident_recycled_rec *next;
  struct ident_recycled_rec *prev;
  ident_recycled_value_t value;
};
typedef struct ident_recycled_rec ident_recycled_rec_t;

// the ident 
struct ident {
  openstate_t state;
  char *filename;
  store_t *store;
  idinfo_t next;

  ident_recycled_rec_t *vertex_recycled;
  ident_recycled_rec_t *vertex_type_recycled;
  ident_recycled_rec_t *edge_recycled;
  ident_recycled_rec_t *edge_type_recycled;
};
typedef struct ident ident_t;



ident_t *ident_create(const char *directory, store_t *store);
int ident_open(ident_t *ident);
void ident_close(ident_t *ident);
void ident_free(ident_t *ident);


#endif // IDENT_H
