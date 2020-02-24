//
// Created by Ziyan Wu on 11/11/19.
//

#include "middleman/actors/tcp_conn/memory_mgt.h"

typedef struct tag_mem_chunk
{
  int mc_free_chunks;
  struct tag_mem_chunk *mc_next;
} mem_chunk;

typedef mem_chunk *mem_chunk_t;

struct rte_mempool * MPCreate(char *name, int chunk_size, size_t total_size)
{
  struct rte_mempool *mp;
  size_t sz, items;

  items = total_size/chunk_size;
  sz = RTE_ALIGN_CEIL(chunk_size, RTE_CACHE_LINE_SIZE);
  mp = rte_mempool_create(name, items, sz, 0, 0, NULL,
                          0, NULL, 0, rte_socket_id(),
                          MEMPOOL_F_NO_SPREAD);

  if (mp == NULL) {
    // TRACE_ERROR("Can't allocate memory for mempool!\n"); // TODO: RTE_LOG
    exit(EXIT_FAILURE);
  }

  return mp;
}

void * MPAllocateChunk(struct rte_mempool *  mp)
{
  int rc;
  void *buf;

  rc = rte_mempool_get(mp, (void **)&buf);
  if (rc != 0)
    return NULL;

  return buf;
}

void MPDestroy(struct rte_mempool *  mp)
{
  rte_mempool_free(mp);

}

int MPGetFreeChunks(struct rte_mempool *  mp)
{
  return (int)rte_mempool_avail_count(mp);
}