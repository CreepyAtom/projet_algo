#include "image.h"
#include "table.h"
#include "kdarbre.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

struct color_table{
  int color_num;
  int *colors;
  boolean owner;
  int dim;
};

struct kdtree{
  color_table tab;
  struct kdtree *left_son;
  struct kdtree *right_son;
  axis ax;
  int pivot;
};
  
int min(int a, int b){
  if (a<b)
    return a;
  return b;
  }
  
int max(int a, int b){
  if (a<b)
    return b;
  return a;
  }
  
axis select_axis(color_table tab){
  int Dim = tab->dim;
  int min_tab[Dim], max_tab[Dim], spread_tab[Dim];
  color pixel[Dim];
  int color_num = tab->color_num;
  int i,j,k;
  for (i=0; i < Dim; i++){
    min_tab[i] = 255;
    max_tab[i] = 0;
    }
  
  for (i = 0; i < color_num; i++){
    color_table_get_color(tab,i,pixel);
    for (k = 0; k < Dim ; k++){
        min_tab[k] = min(pixel[k],min_tab[k]);
        max_tab[k] = max(pixel[k],max_tab[k]);
        }
      }
  for (i=0; i < Dim; i++){
   spread_tab[i] = max_tab[i]-min_tab[i];
   fprintf(stderr, "%d\n", spread_tab[i]);
   }
   if (spread_tab[0]>spread_tab[1] && spread_tab[0]>spread_tab[2])
     return red;
   if (spread_tab[1]>spread_tab[0] && spread_tab[1]>spread_tab[2])
     return green;
   if (spread_tab[2]>spread_tab[0] && spread_tab[2]>spread_tab[1])
     return blue;
  }


        
void main(int argc, char* argv[]){
  kdtree A= (kdtree)malloc(sizeof(struct kdtree));
  image test_image=FAIRE_image();
  image_charger(test_image, argv[1]);
  
  
  A->tab = create_color_table(test_image);
  A->ax = select_axis(A->tab);
  color_table_sort(A->tab,A->ax);
  //print_color_table(A->tab);
  printf("%d\n", 5/2);
  
  }
  
  
  
//Exemple d'exécution: ./bin/kdarbre.bin ./IMAGES/TABLES/table_fille_1024.ppm