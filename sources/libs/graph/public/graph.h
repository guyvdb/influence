#ifndef GRAPH_H
#define GRAPH_H


#include "../private/global.h"
#include "../private/cache.h"
#include "../private/store.h"
#include "../private/ident.h"

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
struct graph_options {
  const char* directory;
  int pagesize;
  int cachepages;
};
typedef struct graph_options graph_options_t;


/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
struct graph {
  graph_options_t *options;
  openstate_t state;
  cache_t *pagecache;
  store_t *store;
  ident_t *ident;
};
typedef struct graph graph_t;




/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */


// allocate a graph 
graph_t *graph_create(graph_options_t *options);

// free the graphs resources
void graph_free(graph_t *g);

// open a graph
int graph_open(graph_t *g);

// close a graph
void graph_close(graph_t* g);


// a testbed function
void graph_test(graph_t *g);

#endif //GRAPH_H
