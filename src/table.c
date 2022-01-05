#include "image.h"
#include "table.h"
#include <assert.h>


/*The structure color_table defines a table of colors and for that this structure contains 
an integer color_num which represents the number of colors , a pointer of integers that 
represents the successive colors in the table.A boolean owner that indicates whether or not
the table has allocated a pointer.(Only the table that has allocated a pointer can be freed.
We added The integer dim that represents the dimension of the image.
*/
struct color_table{
  int color_num;
  int *colors;
  boolean owner;
  int dim;
};


/*This function creates a color table (see struct color_table above) from a unidimensional image
(It creates the color table from an image composed of one line) Owner is set as True.
*/
color_table create_color_table(image self){
  color_table tab;
  int Dim = image_give_dim(self);
  assert(Dim>0 && Dim<=3); //We check with the assert that the arguments given are coherent.
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



/*This function deletes the color table. The pointer will be freed only if owner == True
The structure however is freed no matter what.
*/
boolean destroy_color_table(color_table tab){
	free(tab->colors);
	if (tab->owner == true){
		free(tab);
	}
	return(tab->owner);
}


/*This function creates a color table from another table . The first element of the new color_table
is old_color_table[offset] and the number of elements it contains is len.
*/
color_table color_table_duplicate(color_table tab, int offset, int len){
	color_table dup_tab;
	assert(offset>-1); //We check with the assert that the arguments given are coherent.
	assert(len>0); //We check with the assert that the arguments given are coherent.
	dup_tab->owner = false;
  dup_tab->dim = tab->dim;
	dup_tab->color_num = len;
	dup_tab->colors = tab->colors + dup_tab->dim*offset; //The offset depends on the dimension
	return(dup_tab);
}


/*This function fills the pointer given as 3rd argument color_i with the i_th color in the 
color table given as first argument 
*/
void color_table_get_color(color_table tab, int i, color* color_i){
  int Dim = tab->dim;
  assert(i<tab->color_num); //We check with the assert that the arguments given are coherent.
  for (int k=0; k<Dim; k++)
    color_i[k] = tab->colors[i*Dim+k];
  }
  
  
int color_table_get_color_num(color_table tab){
  return tab->color_num;
}


/*This function sorts the elements of a color table given as first argument depending on 
the 2nd argument i (0 for the red axis , 1 for the green axis and 2 for the blue axis)
In this version we use a bubble sort with a complexity of n^2.

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
*/  

/*This time we're gonna do a quicksort with a n*log(n) complexity 
which is way better than the n^2 complexity of the bubble sort
*/
// function to swap elements
void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// function to find the partition position
int partition(int *tab, int low, int high) {

  // select the rightmost element as pivot
  int pivot = tab[high];

  // pointer for greater element
  int i = (low - 3);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j=j+3) {
    if (tab[j] <= pivot) {

      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i=i+3;

      // swap element at i with element at j
      swap(&tab[i], &tab[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&tab[i + 3], &tab[high]);

  // return the partition point
  return (i +3);
}


void quickSort(int *tab, int low, int high) {
  if (low < high) {

    // find the pivot element such that elements smaller than the pivot are on the left of the pivot and the elements greater than the pivot are on right of the pivot
    int pi = partition(tab, low, high);

    // recursive call on the left of pivot
    quickSort(tab, low, pi - 3);

    // recursive call on the right of pivot
    quickSort(tab, pi + 3, high);
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
  quickSort(tab->colors,ax,dim*(tab->color_num) - 3 + ax);
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
//function to calculate the distance inspired from the module image, arranged here
