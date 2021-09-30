

#include "id.h"


// To compute a GRAPHID from a pageno & slotno
// GRAPHID = (pageno * pageslots) + slotno + 1

// To compute a pageno & slotno from a GRAPHID
// pageno = (GRAPHID-1)/pageslots
// slotno = (GRAPHID-1)-(pageslots * pageno)


/*

 // compute counts / sizes
 int pageslots = (int)pagesize / (int)objsize;
 int pagepadding = pagesize - (pageslots * objsize);
 int pagecount = filesize / pagesize;

 */


void compute_object_id(size_t objsize, size_t pagesize, int pageno, int slotno, objinfo_t *result) {
  int pageslots = (int)pagesize / (int)objsize;
  result->id = (pageno * pageslots) + slotno + 1;
}

void compute_page_slot_no(size_t objsize, size_t pagesize, GRAPHID id, objinfo_t *result) {
  int pageslots = (int)pagesize / (int)objsize;
  result->pageno = (id-1)/pageslots;
  result->slotno = (id-1)-(pageslots*result->pageno);
}
