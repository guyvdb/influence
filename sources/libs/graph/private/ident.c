#include "ident.h"
#include <string.h>
#include <stdlib.h>


/* ---------------------------------------------------------------------------
 * PRIVATE
 * --------------------------------------------------------------------------- */



/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
/* void printidentvalues(ident_next_values_t *values) { */
/*   unsigned char *ptr = (unsigned char*)values; */


/*   printf("values ["); */

/*   for(size_t i=0; i<sizeof(ident_next_values_t); i++) { */
/*     char v = *ptr; */
/*     printf("0x%X ", v); */
/*   } */

/*   printf("\b]\n"); */
/* } */






/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
void perform_table_scan(ident_t *ident) {
  printf("[IDENT] Performing table scan.\n");
  ident->next.vertex = 1;
  ident ->next.vertextype = 1;
  ident ->next.edge = 1;
  ident ->next.edgetype = 1;


  //  int store_scan(store_t *s, recycle_id_func fn, size_t pagesize, ident_next_values_t *nextvals);

  store_scan(ident->store, )
    //int store_scan(store_t *s, recycle_id_func fn, size_t pagesize, idinfo_t *idinfo);

    // TODO we need the callback function to somehow have acces to the ident_t in order to make the linked list


}

/* ---------------------------------------------------------------------------
 * PUBLIC
 * --------------------------------------------------------------------------- */


/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
ident_t *ident_create(const char *directory, store_t *store) {

  // create ident and initialize
  ident_t *ident = (ident_t*)malloc(sizeof(ident_t));
  ident->state = closed;

  ident ->next.vertex = NULL_GRAPHID;
  ident ->next.vertextype = NULL_GRAPHID;
  ident ->next.edge = NULL_GRAPHID;
  ident ->next.edgetype = NULL_GRAPHID;

  ident->vertex_recycled = 0x0;
  ident->vertex_type_recycled = 0x0;
  ident->edge_recycled = 0x0;
  ident->edge_type_recycled = 0x0;

  ident->store = store;


  // calculate file name 
  size_t len = strlen(directory) + strlen("ident.data") + 1;
  if(directory[strlen(directory)-1] != '/') {
    len++;
  }

  ident ->filename = (char*)malloc(len);
  if(directory[strlen(directory)-1] != '/') {
    sprintf(ident ->filename,"%s/ident.data", directory);
  } else {
    sprintf(ident ->filename,"%sident.data", directory);    
  }

  return ident ;
}


/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
int ident_open(ident_t *ident ) {
  size_t count;
  int tablescan = 0;

  // open the file
  printf("[IDENT] Reading %s\n", ident->filename);
  FILE *f = fopen(ident->filename, "a+");
  if(!f) {
    f = fopen(ident->filename, "r+");
  }


  // read in the next id values 
  count = fread( (void*)&ident->next, sizeof(idinfo_t), 1, f);
  if(count != 1) {
    // need to do full table scan the ident file was too few bytes.
    printf("[IDENT] Full table scan required. Ident file does not contain enough data.\n");
    tablescan = 1;
  }
  
  // if the idents are invalid full table scan
  if(ident->next.vertex == INVALID_GRAPHID ||
     ident->next.vertextype == INVALID_GRAPHID ||
     ident->next.edge == INVALID_GRAPHID ||
     ident->next.edgetype == INVALID_GRAPHID) {
    printf("[IDENT] Full table scan required. Ident was not written out on last shutdown.\n");
    tablescan = 1;
  }



  // read in the recycled ids from the rest of the file 


  // invalidate the ident file header
  idinfo_t invalid =  {INVALID_GRAPHID, INVALID_GRAPHID, INVALID_GRAPHID, INVALID_GRAPHID};
  if(fseek(f, 0, SEEK_SET) != 0) {
    // failed to seek to beginning of file
    printf("[IDENT] Error. Failed to seek to beginning of file.\n");
  }

  count = fwrite((void*)&invalid, sizeof(idinfo_t), 1, f);
  if (count != 1) {
    printf("[IDENT] Error. Failed to write ident values to file.\n");
  }


  // close file 
  fclose(f);


  // do a tablescan if needed
  if(tablescan) {
    perform_table_scan(ident);
  }

  
}

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
void ident_close(ident_t *ident ) {
  printf("[IDENT] Saving ident values.\n");
  // open the file

  // write the idents

  // close the file 
}

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
void ident_free(ident_t *ident ) {
  if(ident  != 0x0) {

    if(ident ->state == open) {
      ident_close(ident);
    }

    free(ident ->filename);
    free(ident );
  }
}
