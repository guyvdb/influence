#ifndef ID_H
#define ID_H

#include "global.h"
#include <stddef.h>

// utilities for dealing with graph ids, page and slot numbers

//int store_scan_table(const char *filename, obj_type_t type, size_t objsize, size_t pagesize, recycle_id_func fn, GRAPHID* maxval)// {


struct objinfo {
  GRAPHID id;
  int pageno;
  int slotno;
};

typedef struct objinfo objinfo_t;


void compute_object_id(size_t objsize, size_t pagesize, int pageno, int slotno, objinfo_t *result);
void compute_page_slot_no(size_t objsize, size_t pagesize, GRAPHID id, objinfo_t *result);




#endif // ID_H
