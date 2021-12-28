#include "image.h"
#include "table.h"
#include <assert.h>
#include <stdio.h>

struct color_table{
  int color_num;
  int *colors;
  boolean owner;
  int dim;
};

  
void main(int argc, char* argv[]){
  color_table tab;
  image test_image=FAIRE_image();
  image_charger(test_image, argv[1]);
  
  
  printf("Test creation\n--------------------\n");
  tab= create_color_table(test_image);
  DEFAIRE_image(test_image);
  printf("Color num : %d\n",tab->color_num);
  for (int i=0; i<tab->color_num;i++){
    printf("%d, %d, %d\n", tab->colors[tab->dim * i], tab->colors[tab->dim * i+1], tab->colors[tab->dim * i+2]);}
	
	
  printf("Test destruction\n--------------------\n");
  printf("Color num : %d\n",tab->color_num);
  
  printf("Test duplication\n--------------------\n");
  color_table dup_tab;
  dup_tab=color_table_duplicate(tab,2,3);
  for (int i=0; i<dup_tab->color_num;i++){
  printf("%d, %d, %d\n", dup_tab->colors[dup_tab->dim * i], dup_tab->colors[dup_tab->dim * i+1], dup_tab->colors[dup_tab->dim * i+2]);
  };
  
  printf("Test getcolor\n --------------------\n");
  color* color_i;
  color_table_get_color(tab,2,color_i);
  printf("%d, %d, %d\n", *color_i, *(color_i+1), *(color_i+2));
  }
  printf("Test sort\n--------------------\n");
  }
  
    

