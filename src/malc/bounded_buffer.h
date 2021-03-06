#ifndef __MALC_FIXED_BUFFER_H__
#define __MALC_FIXED_BUFFER_H__

#include <bl/base/dynarray.h>
#include <bl/nonblock/mpmc_bpm.h>

define_dynarray_types(cpuq, mpmc_bpm)

/*----------------------------------------------------------------------------*/
typedef struct boundedb {
  cpuq queues;
}
boundedb;
/*---------------------------------------------------------------------------*/
extern void boundedb_init (boundedb* b);
/*---------------------------------------------------------------------------*/
bl_err boundedb_reset(
  boundedb*        b,
  alloc_tbl const* alloc,
  u32              bytes,
  u32              slot_size,
  u32              max_slots,
  bool             per_cpu
  );
/*---------------------------------------------------------------------------*/
void boundedb_destroy (boundedb* b, alloc_tbl const* alloc);
/*---------------------------------------------------------------------------*/
bl_err boundedb_alloc (boundedb* b, u8** mem, u32 slots);
/*---------------------------------------------------------------------------*/
void boundedb_dealloc (boundedb* b, u8* mem, u32 slots);
/*---------------------------------------------------------------------------*/

#endif
