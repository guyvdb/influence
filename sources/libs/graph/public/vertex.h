#ifndef VERTEX_H
#define VERTEX_H


#include <graph_types.h>



struct vertex_header {

  
};
typedef struct vertex_header vertex_header_t;


// A vertex is constituted as an implicid ID, a type ID, first in & out edge IDs and first property ID

struct vertex {
  vertex_header_t header;
  GRAPHID id;
  GRAPHID out_edge_id;
  GRAPHID in_edge_id;
  GRAPHID property_id;
};

typedef struct vertex vertex_t;


#endif //VERTEX_H
