// first pointer returned is 8-byte aligned
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "p3Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   
   exit(0);
}

