#ifndef CACHE_H
#define CACHE_H

#include "global.h"
#include "store.h"


// All objects are stored on pages. Pages are swapped in and out of the page cache as needed.
// All pages are the same size. Each page maps to a particular file, depending on object type.


// TODO deprecate 
struct page_header {
  int no;              // the no of the page which is an offset into the file
                       // no's are unique across a type but different types can have
                       // the same no
  obj_type_t type;    // the type of page
  TIMESTAMP timestamp;
  writestate_t writestate;
};
typedef struct page_header page_header_t;


// TODO deprecate 
// the page structure
struct page {
  page_header_t header;
  void *data;
};
typedef struct page page_t;


// a cache page is a header and a set of bytes.

struct cache_stats {
  
};
typedef struct cache_stats cache_stats_t;


struct cache_index {
  int no;
  obj_type_t type;
  TIMESTAMP timestamp;
  writestate_t writestate;  
};
typedef struct cache_index cache_index_t;


// the cache
struct cache {
  store_t *store;
  int pagesize;
  int pagecount;
  cache_stats_t stats;
  void *index;
  void *bytes;
};

typedef struct cache cache_t;


// Construct a new cache. The cache will allocate enough memory to
// store pagecount pages of pagesize bytes
cache_t * cache_create(store_t *store, int pagesize, int pagecount);

// free a cache previously created by graph_create_cache. 
void cache_free(cache_t *c);

// flush the entire cache to disk. return -1 on error 0 on success
int cache_flush_cache(cache_t *c);

// flush a single cache page to disk
int cache_flush_page(page_t *p);

size_t cache_page_header_size();
size_t cache_page_max_data_size(cache_t *c);


/* 
// how many of a particular object will fit on a cache page 
int cache_objects_per_page(cache_t *c, size_t objsize);

// how much padding is placed at the end of the cache page 
int cache_page_padding(cache_t *c, size_t objsize);
*/


GRAPHID cache_page_next_graphid(page_t *p, size_t objsize);

// return the location of a page in the cache. if the page does not exist in
// the cache return -1
int cache_page_location(obj_type_t type, int no);

// return a page at a given offset. if the offset does not exist NULL will
// be returned.
page_t *cache_get_page(int offset);

void cache_print_page_header(page_t *p);
void cache_print_page_data(page_t *p);




// return a void pointer to where pagesize bytes can be written which will represent
// a page loaded from disk. The returned pointer can be used as the locaton for an fread(); 
void *cache_get_next_page_write_location();





// set len bytes as a new page in the cache
//int cache_put_page(void* bytes, int len);






#endif //CACHE_H
