#ifndef __KDTREE_HH__
#define __KDTREE_HH__

#include "table.h"

typedef struct kdtree *kdtree;
kdtree create_kdtree(color_table,int);
void destroy_kdtree(kdtree);

#endif

