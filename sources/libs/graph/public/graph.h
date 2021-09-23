#ifndef GRAPH_H
#define GRAPH_H



#include "../private/page.h"


struct graph_options {
  const char* directory;
  int pagesize;
  int cachepages;
};

typedef struct graph_options graph_options_t;


struct graph {
  graph_options_t *options;
  cache_t *pagecache;
};

typedef struct graph graph_t;




// open a graph
graph_t * graph_open(graph_options_t *options);

// close a graph
void graph_close(graph_t* g);


#endif //GRAPH_H
