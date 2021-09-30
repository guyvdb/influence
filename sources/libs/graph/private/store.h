#ifndef STORE_H
#define STORE_H



#include "global.h"
#include <stdio.h>



// a callback function for scanning the tables
typedef void(*recycle_id_func)(obj_type_t, GRAPHID);


// the values are layed out in a fixed order
struct  idinfo {
  GRAPHID vertex;
  GRAPHID vertextype;
  GRAPHID edge;
  GRAPHID edgetype;
};
typedef struct idinfo idinfo_t;

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */

struct store {
  openstate_t state;

  char *vertex_table_filename;
  char *vertex_property_table_filename;
  char *vertex_type_table_filename;
  char *edge_table_filename;
  char *edge_property_table_filename;
  char *edge_type_table_filename;

  FILE *vertex_table;
  FILE *vertex_property_table;
  FILE *vertex_type_table;
  FILE *edge_table;
  FILE *edge_property_table;
  FILE *edge_type_table;
};
typedef struct store store_t;




/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */

store_t *store_create(const char *directory);
int store_open(store_t *s);
void store_close(store_t *s);
void store_free(store_t *s);
int store_scan(store_t *s, recycle_id_func fn, size_t pagesize, idinfo_t *idinfo);




#endif //STORE_H
