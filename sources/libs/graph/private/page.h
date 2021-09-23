#ifndef PAGE_H
#define PAGE_H


// All objects are stored on pages. Pages are swapped in and out of the page cache as needed.
// All pages are the same size. Each page maps to a particular file, depending on object type.


typedef enum {
  page_type_unknown = 0,
  page_type_vertex_header,
  page_type_vertex,
  page_type_edge_header,
  page_type_edge,
  page_type_property_header,
  page_type_property
} page_type_t;


// the page structure
struct page {
  page_type_t type;  // the type of page
  int no;            // the no of the page which is an offset into the file
                     // no's are unique across a type but different types can have
                     // the same no

};

typedef struct page page_t;


// a cache page is a header and a set of bytes.

// the cache
struct cache {
  int pagesize;
  int pagecount;
  void *bytes;
};

typedef struct cache cache_t;


// Construct a new cache. The cache will allocate enough memory to
// store pagecount pages of pagesize bytes
cache_t * cache_create(int pagesize, int pagecount);

// free a cache previously created by graph_create_cache. 
void cache_free(cache_t *c);


// flush the entire cache to disk. return -1 on error 0 on success
int cache_flush_cache(cache_t *c);

// flush a single cache page to disk
int cache_flush_page(page_t *p);

// return the location of a page in the cache. if the page does not exist in
// the cache return -1
int cache_page_location(page_type_t type, int no);

// return a page at a given offset. if the offset does not exist NULL will
// be returned.
page_t *cache_get_page(int offset);

// return a void pointer to where pagesize bytes can be written which will represent
// a page loaded from disk. The returned pointer can be used as the locaton for an fread(); 
void *cache_get_next_page_write_location();





// set len bytes as a new page in the cache
//int cache_put_page(void* bytes, int len);






#endif //PAGE_H
