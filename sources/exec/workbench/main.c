#include <stdio.h>
#include <string.h>
#include <graph.h>




// graph_t *graph_create(graph_options_t *options);



void structest() {
  
}


void graphtest() {
  graph_options_t opts = {
    "/home/guyvdb/Projects/influence/data",4096,10
  };
  graph_t *g = graph_create(&opts);
  graph_open(g);
  graph_close(g);
  graph_free(g);
}

int main(int argc, char** argv) {

  graphtest();

  
}
 
