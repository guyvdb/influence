#include <graph.h>
#include <stdlib.h>
#include <stdio.h>





graph_t *graph_create(graph_options_t *options);
void graph_free(graph_t *g);
int graph_open(graph_t *g);
void graph_close(graph_t* g);





/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
graph_t * graph_create(graph_options_t *options) {

  printf("[GRAPH] options.directory is %s\n", options->directory);

  //  printf("openstate size is %d\n", sizeof(openstate_t));


  // create the graph 
  graph_t *g = (graph_t*)malloc(sizeof(graph_t));
  g->options = options;
  g->state = closed;



  // set up a store
  g->store = store_create(options->directory);

  // set up the ident
  g->ident = ident_create(options->directory, g->store);

  






  // set up the cache
  g->pagecache = cache_create(g->store, options->pagesize, options->cachepages);

  return g;
}

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
void graph_free(graph_t* g) {
  if(g != 0x0) {
    if(g->state == open) {
      graph_close(g);
    }
    ident_free(g->ident);
    store_free(g->store);
    cache_free(g->pagecache);
    free(g);
  }
}


/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
int graph_open(graph_t *g) {


  // open the ident
  if(!ident_open(g->ident)) {
    return 0;
  }


  // open the store 
  if(!store_open(g->store)) {
    return 0;
  }

  return 1;
}

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
void graph_close(graph_t *g) {
  if(g->state == open) {
    cache_flush_cache(g->pagecache);
  }

  if(g->ident->state == open) {
    ident_close(g->ident);
  }

  if(g->store->state == open) {
    store_close(g->store);
  }
}



void graph_test(graph_t *g) {
  // for the given cache page size how many 
}
