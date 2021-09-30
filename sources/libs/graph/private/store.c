#include <store.h>
#include <string.h>
#include <stdlib.h>
#include <obj.h>
#include <vertex.h>

#include "id.h"



/* ---------------------------------------------------------------------------
 *  PRIVATE
 * --------------------------------------------------------------------------- */


void alloc_append_filename(char **dest, const char *directory, const char *filename);
FILE * store_file_open(const char *filename);




/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
FILE *store_file_open(const char *filename) {
  FILE *f = fopen(filename, "a+");
  if(!f) {
    f = fopen(filename, "r+");
  }

  if(!f) {
    printf("[STORE] Error - failed to open file %s\n", filename);
  }
  return f;
}


/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
void alloc_append_filename(char **dest, const char *directory, const char *filename) {
  size_t len = strlen(directory) + strlen(filename) + 1;
  if(directory[strlen(directory)-1] != '/') {
    len++;
  }

  *dest = (char*)malloc(len);


  if(directory[strlen(directory)-1] != '/') {
    sprintf(*dest,"%s/%s", directory, filename);
  } else {
    sprintf(*dest,"%s%s", directory, filename);
  }
}

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
int store_scan_table(const char *filename, obj_type_t type, size_t objsize, size_t pagesize, recycle_id_func fn, GRAPHID* maxgraphid) {
  unsigned char page[pagesize];
  void *slotptr;
  objheader_t *header;
  objinfo_t objinfo;

  int maxid = -1;

  // Open the file
  FILE *f = store_file_open(filename);
  if(!f) {
    printf("[STORE] Error. Failed to open file %s for scan.\n", filename);
    return 0;
  }

  // compute file size
  fseek(f, 0L, SEEK_END);
  int filesize = ftell(f);
  fseek(f, 0L, SEEK_SET);

  // compute counts / sizes
  int pageslots = (int)pagesize / (int)objsize;
  int pagepadding = pagesize - (pageslots * objsize);
  int pagecount = filesize / pagesize;

  // To compute a GRAPHID from a pageno & slotno
  // GRAPHID = (pageno * pageslots) + slotno + 1

  // To compute a pageno & slotno from a GRAPHID
  // pageno = (GRAPHID-1)/pageslots
  // slotno = (GRAPHID-1)-(pageslots * pageno)

  // loop through all the pages backwards
  for(int pageno = pagecount-1; pageno >= 0; pageno--) {
    // seek to start of page
    long pos = ((long)pageno) * ((long)pagesize);
    if(fseek(f,pos,SEEK_SET) != 0) {
      printf("[STORE] Error. Failed to seek to page %d - offset %d.\n", pageno, pos);
      return -1;
    }

    // read page size bytes
    if(fread((void*)page, pagesize, 1, f) != 1) {
      printf("[STORE] Error. Failed to read page %d from file.\n", pageno);
      return -1;
    }

    // callbacks only happen after we have a maxid.
    if(maxid != -1) {
      // already have found max id
      slotptr = (void*)page;
      for(int slot = 0; slot < pageslots; slot++) {
        // read off slot header
        header = (objheader_t*)slotptr;

        if((uint8_t)header->flags[0] == OBJ_UNUSED) {
          // we have max id and this is unused slot so we should
          // recycle the id..
          compute_object_id(objsize, pagesize, pageno, slot, &objinfo);

          // trigger the callback
          fn(type, objinfo.id);

          // increment the slotptr by one record
          slotptr += objsize;
        }

      }
    } else {
      // do not have a max id if this is the first OBJ_USED record from max slot to min slot
      // then we can potentially set the first object id. We potentially have to loop slots twice.
      // First find the max id and then loop again if max id was found to fire the callback.

      slotptr = (void*)page;

      for(int slot = pageslots - 1; slot >= 0; slot--) {
        header - (objheader_t*)slotptr;
        if((uint8_t)header->flags[0] == OBJ_USED) {
          // hit our first used object from the back of the file forward.
          compute_object_id(objsize, pagesize, pageno, slot, &objinfo);
          maxid = objinfo.id;
          break;
        }
        // increment the slotptr by one record
        slotptr += objsize;
      }

      // loop through second time and do callbacks if we have a max id
      if(maxid != -1) {
        slotptr = (void*)page;
        for(int slot = 0; slot < pageslots; slot++) {
          // read off slot header
          header = (objheader_t*)slotptr;

          if((uint8_t)header->flags[0] == OBJ_UNUSED) {
            // we have max id and this is unused slot so we should
            // recycle the id..
            compute_object_id(objsize, pagesize, pageno, slot, &objinfo);

            // trigger the callback
            fn(type, objinfo.id);

            // increment the slotptr by one record
            slotptr += objsize;
          }
        }
      }
    }
  }


  // if max value is still set to -1 there are no records in the table
  if(maxid == -1) {
    *maxgraphid = 0;
  } else {
    *maxgraphid = maxid;
  }


  fclose(f);
}


/* ---------------------------------------------------------------------------
 * PUBLIC
 * --------------------------------------------------------------------------- */


/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
store_t *store_create(const char *directory) {
  store_t *s = (store_t*)malloc(sizeof(store_t));
  s->state = closed;

  alloc_append_filename(&s->vertex_table_filename, directory, "vertex.data");
  alloc_append_filename(&s->vertex_property_table_filename, directory, "vertex.prop");
  alloc_append_filename(&s->vertex_type_table_filename, directory, "vertex.type");

  alloc_append_filename(&s->edge_table_filename, directory, "edge.data");
  alloc_append_filename(&s->edge_property_table_filename, directory, "edge.prop");
  alloc_append_filename(&s->edge_type_table_filename, directory, "edge.type");

  return s;
}

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
int store_open(store_t *s) {
  if(s->state == closed) {
    // TODO check the return values of store_file_open() and notify/exit on error

    // vertex
    s->vertex_table = store_file_open(s->vertex_table_filename);
    s->vertex_property_table = store_file_open(s->vertex_property_table_filename);
    s->vertex_type_table = store_file_open(s->vertex_type_table_filename);

    // edge
    s->edge_table = store_file_open(s->edge_table_filename);
    s->edge_property_table = store_file_open(s->edge_property_table_filename);
    s->edge_type_table = store_file_open(s->edge_type_table_filename);


    s->state = open;

    return  1;
  } else {
    printf("[STORE] Error. Store cannot open. It is not in closed state.\n");
    return 0;
  }
}


/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
void store_close(store_t *s) {
  if(s->state == open) {
    if(s->vertex_table) fclose(s->vertex_table);
    if(s->vertex_property_table) fclose(s->vertex_property_table);
    if(s->vertex_type_table) fclose(s->vertex_type_table);

    if(s->edge_table) fclose(s->edge_table);
    if(s->edge_property_table) fclose(s->edge_property_table);
    if(s->edge_type_table) fclose(s->edge_type_table);

    s->state = closed;
  } else {
    printf("[STORE] Error. Store cannot close. It is not in open state.\n");
  }
}

/* ---------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------------- */
void store_free(store_t *s) {
  if(s != 0x0) {
    if(s->state == open) {
      store_close(s);
    }
    free(s->vertex_table_filename);
    free(s->vertex_property_table_filename);
    free(s->vertex_type_table_filename);
    free(s->edge_table_filename);
    free(s->edge_property_table_filename);
    free(s->edge_type_table_filename);

    free(s);
  }
}

/* ---------------------------------------------------------------------------
 * Perform a full table scan on each table. Call the recyle_id_func for each
 * object id that is marked as deleted. Set the value of nextvals to the highest
 * object id + 1 for each object type.
 *
 * The store must be in closed state in order to scan.
 * --------------------------------------------------------------------------- */
int store_scan(store_t *s, recycle_id_func fn, size_t pagesize, idinfo_t *idinfo) {
  if(s->state != closed) {
    printf("[STORE] Error. Cannot scan a store. It is not in closed state.\n");
    return 0;
  }


  s->state = pending;


  // TODO this could be threaded with thread per obj_type.

  printf("[STORE] Start vertex scan on %s.\n", s->vertex_table_filename);
  store_scan_table(s->vertex_table_filename, obj_type_vertex, sizeof(vertex_data_t), pagesize, fn, &idinfo->vertex);


  //  int store_scan_table(const char *filename, obj_type_t type, size_t objsize, size_t pagesize, recycle_id_func fn, GRAPHID* maxgraphid) {


  s->state = closed;

}
