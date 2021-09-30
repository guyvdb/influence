#include <cache.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */


/* ---------------------------------------------------------------------------
 * create a cache
 * --------------------------------------------------------------------------- */
cache_t *cache_create(store_t* store, int pagesize, int pagecount) {

  // create cache
  cache_t* c = malloc(sizeof(cache_t));
  c->store = store;
  c->pagesize = pagesize;
  c->pagecount = pagecount;


  // create page byte buffer
  c->bytes = malloc(pagesize * pagecount);

  // zero the cache bytes
  memset(c->bytes, 0x0, pagesize * pagecount);

  // create the page index elements
  c->index = malloc(sizeof(cache_index_t)*pagecount);

  // zero the page index elements
  memset(c->index, 0x0, sizeof(cache_index_t) * pagecount);


  printf("[CACHE] allocated %d bytes\n", pagesize * pagecount);
  return c;
}

/* ---------------------------------------------------------------------------
 * free a cache
 * --------------------------------------------------------------------------- */
void cache_free(cache_t* c) {
  if(c != 0x0) {
    free(c->bytes);
    free(c->index);
    free(c);
  }
}

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
int cache_flush_cache(cache_t *c) {

}

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
size_t cache_page_header_size() {
  return sizeof(page_header_t);
}

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
size_t cache_page_max_data_size(cache_t *c) {
  return (size_t)(c->pagesize) - cache_page_header_size();
}


/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
//int cache_objects_per_page(cache_t *c, size_t objsize) {
//  return c->pagesize / (int)objsize;
//}

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
//int cache_page_padding(cache_t *c, size_t objsize) {

  /*
  double p = (double)c->pagesize % (double)objsize;

  // this is the percent of objsize remaining.
  double a = (double)objsize * p;

  // TODO need to round this value correctly???? we could have a rounding error here
  return (int)a;
*/
// return 0;

//}
