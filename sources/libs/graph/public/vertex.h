#ifndef VERTEX_H
#define VERTEX_H


#include <obj.h>
#include "../private/global.h"


// TODO do we need this
// vertex header is only stored in memory. 
struct vertex_header {
  GRAPHID id;
};
typedef struct vertex_header vertex_header_t;


// A vertex is constituted as an implicid ID, a type ID, first in & out edge IDs and first property ID

// vertex data comes from perminant storage 
struct vertex_data {
  objheader_t              header; // must be first 
  GRAPHID                  edgeout; // first outward bound edge 
  GRAPHID                  edgein; // first inward bound edge 
  GRAPHID                  property; // first property
};
typedef struct vertex_data vertex_data_t;


// TODO do we need this 
// in memory representation of a vertex 
struct vertex {
  vertex_header_t header;       // stored in mem 
  vertex_data_t   data;         // disk storeable 
};
typedef struct vertex vertex_t;

#endif //VERTEX_H
