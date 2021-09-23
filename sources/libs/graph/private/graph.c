#include <graph.h>

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
graph_t * graph_open(graph_options_t *options) {
  graph_t *g = (graph_t*)malloc(sizeof(graph_t));
  g->options = options;
  g->pagecache = cache_create(options->pagesize, options->cachepages);
  return g;
}

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
void graph_close(graph_t* g) {
  cache_flush_cache(g->pagecache);
  cache_free(g->pagecache);
  free(g);
}
