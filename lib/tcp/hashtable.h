//
// Created by Ziyan Wu on 11/9/19.
//

#ifndef AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_HASHTABLE_H_
#define AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_HASHTABLE_H_

#ifndef UNUSED //StreamHTSearch
#define UNUSED(x)	(void)x
#endif

#define NUM_BINS_FLOWS 		(131072)     /* 132 K entries per thread*/
#define NUM_BINS_LISTENERS	(1024)	     /* assuming that chaining won't happen excessively */
#define TCP_AR_CNT 		(3)

#define IS_FLOW_TABLE(x)	(x == HashFlow)
#define IS_LISTEN_TABLE(x)	(x == HashListener)


#include "tcp_stream.h"
#include "socket.h"
//#include "middleman/actors/tcp_conn/tcp_out.h"

//#include "shared.h"

typedef struct hash_bucket_head {
  struct tcp_stream *tqh_first;
  struct tcp_stream **tqh_last;
} hash_bucket_head;
typedef struct list_bucket_head {
  struct tcp_listener *tqh_first;
  struct tcp_listener **tqh_last;
} list_bucket_head;
/* hashtable structure */
struct hashtable {
  uint32_t bins;
  union {
    hash_bucket_head *ht_table;
    list_bucket_head *lt_table;
  };
  // functions
  unsigned int (*hashfn) (const void *);
  int (*eqfn) (const void *, const void *);
};

unsigned int HashFlow(const void *f);

int EqualFlow(const void *f1, const void *f2);
int EqualListener(const void *l1, const void *l2);

struct hashtable *CreateHashtable(unsigned int (*hashfn) (const void *), // key function
                                  int (*eqfn) (const void*, const void *),            // equality
                                  int bins); // no of bins
void * StreamHTSearch(struct hashtable *ht,  void *it);
void * ListenerHTSearch(struct hashtable *ht, const void *it);
unsigned int HashListener(const void *l);
int StreamHTInsert(struct hashtable *ht, void *);

void* StreamHTRemove(struct hashtable *ht, void *it);
#endif //AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_HASHTABLE_H_

