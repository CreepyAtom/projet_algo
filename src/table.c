#include "image.h"
#include "table.h"
#include <assert.h>

struct color_table{
  int color_num;
  int *colors;
  boolean owner;
  int dim;
};


color_table create_color_table(image self){
  color_table tab;
  int Dim = image_give_dim(self);
  assert(Dim>0 && Dim<=3);
  tab = (color_table)malloc(sizeof(struct color_table));
  tab->owner = true;  
  tab->dim = Dim;
  tab->color_num = image_give_largeur(self);
  tab->colors = malloc(tab->color_num*Dim*sizeof(color));
 
 
  int *array;
  image_debut(self);
  for (int i = 0; i < tab->color_num; i++) {
        array = image_lire_pixel(self);
        image_pixel_suivant(self);
        for (int k = 0; k < Dim; k++) {
            tab->colors[i*Dim + k] = array[k];
        }
    } 
    return tab;
}




boolean destroy_color_table(color_table tab){
	free(tab->colors);
	if (tab->owner == true){
		free(tab);
	}
	return(tab->owner);
}




color_table color_table_duplicate(color_table tab, int offset, int len){
	color_table dup_tab;
	assert(offset>-1);
	assert(len>0);
	dup_tab->owner = false;
  dup_tab->dim = tab->dim;
	dup_tab->color_num = len;
	dup_tab->colors = tab->colors + dup_tab->dim*offset; /*l'offset d�pendra de la dimension*/
	return(dup_tab);
}





void color_table_get_color(color_table tab, int i, color* color_i){
  int Dim = tab->dim;
  assert(i<tab->color_num);
  for (int k=0; k<Dim; k++)
    color_i[k] = tab->colors[i*Dim+k];
  }
  
  
int color_table_get_color_num(color_table tab){
  return tab->color_num;
}
  
void swap_tab(color_table tab, int i){
  int temp_tab[tab->dim];
  if (tab->dim == 1){
    *temp_tab = *(tab->colors+i);
    *(tab->colors+i) = *(tab->colors+i+1);
    *(tab->colors+i+1) = *temp_tab;
    }
  else{
    *temp_tab = *(tab->colors+i);
    *(temp_tab+1) = *(tab->colors+i+1);
    *(temp_tab+2) = *(tab->colors+i+2);
    *(tab->colors+i) = *(tab->colors+i+3);
    *(tab->colors+i+1) = *(tab->colors+i+4);
    *(tab->colors+i+2) = *(tab->colors+i+5);
    *(tab->colors+i+3) = *temp_tab;
    *(tab->colors+i+4) = *(temp_tab+1);
    *(tab->colors+i+5) = *(temp_tab+2);
    }
  }
  

void color_table_sort(color_table tab, axis x){
  int dim = tab->dim;
  int ax;
  int swap = 1;
  int i;
  if (x == (axis)red)
    ax = 0;
  if (x == (axis)green)
    ax = 1;
  if (x == (axis)blue)
    ax = 2;
  while (1){
    swap = 0; 
    for (i=0;i<tab->color_num-1;i++){
      if (tab->colors[ax+dim*i] > tab->colors[ax+dim*(i+1)]){
        swap_tab(tab,dim*i);
        swap++;}
        }
        if (swap == 0)
          break;
      }
    }
  
  
  
void permute(int* a,int* b){
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

void quickSort(int tab[], int first, int last,int ax) {
    int pivot, i, j;
    if(first < last) {
        pivot = first + ax;
        i = first + ax;
        j = last + ax;
        while (i < j) {
            while(tab[i] <= tab[pivot] && i < last)
                i++;
            while(tab[j] > tab[pivot])
                j--;
            if(i < j) {
                permute(&tab[i], &tab[j]);
            }
        }
        permute(&tab[pivot], &tab[j]);
        quickSort(tab, first, j - 1,ax);
        quickSort(tab, j + 1, last,ax);
    }
}
 
void color_table_sort2(color_table tab, axis x){
  int dim = tab->dim;
  int ax;
  int i;
  if (x == red)
    ax = 0;
  if (x == green)
    ax = 1;
  if (x == blue)
    ax = 2;
  quickSort(tab->colors,0,tab->color_num-1,ax);
}
  
  
  
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void print_color_table(color_table tab){
  for (int i=0; i<tab->color_num;i++){
    printf("%d, %d, %d\n", tab->colors[tab->dim * i], tab->colors[tab->dim * i+1], tab->colors[tab->dim * i+2]);}
    }
  
  
  int calcul_distance(color* pix1,color*
					    pix2, int Dim)
{
  int ret=0;
  int i;

      for(i=0;i<Dim;i++)
	{
	  ret += ( (*pix1)-(*pix2) )*( (*pix1)-(*pix2) );
	  pix1++;
	  pix2++;
	}
  return ret;
}
/*fonction de calcul de distance inspir�e du module image, arrang�e ici*/