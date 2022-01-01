#ifndef __TABLE_HH__
#define __TABLE_HH__

typedef enum {red,green,blue} axis;
typedef int color; /* ou char*/
typedef enum {false,true} boolean;

typedef struct color_table *color_table;

color_table create_color_table(image);
boolean destroy_color_table(color_table);
color_table color_table_duplicate(color_table,int,int);

void color_table_get_color(color_table,int,color*);
int color_table_get_nb_color(color_table);
void color_table_sort(color_table,axis);
void color_table_sort2(color_table,axis);

int calcul_distance(color*,color*, int);
void print_color_table(color_table);



#endif