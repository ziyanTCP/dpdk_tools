//
// Created by Ziyan Wu on 11/11/19.
//

#ifndef AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_MEMORY_MGT_H_
#define AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_MEMORY_MGT_H_

#include <rte_common.h>
#include <rte_mempool.h>
/* for rte_versions retrieval */
#include <rte_version.h>


struct rte_mempool* MPCreate(char *name, int chunk_size, size_t total_size);
/* allocate one chunk */
void * MPAllocateChunk(struct rte_mempool* mp);

/* free one chunk */
void MPFreeChunk(struct rte_mempool*  mp, void *p);

/* destroy the memory pool */
void
MPDestroy(struct rte_mempool*  mp);

/* retrun the number of free chunks */
int
MPGetFreeChunks(struct rte_mempool *  mp); //TODO: What is a chunk?


#endif //AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_MEMORY_MGT_H_
