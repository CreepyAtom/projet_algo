#include "image.h"
#include "table.h"
#include <assert.h>

struct color_table{
  int color_num;
  int *colors;
  boolean owner;
};

color_table create_color_table(image self){
	color_table tab;
	int Dim = image_give_dim(self);
	assert(Dim>0 && Dim<=3);
  tab = malloc(sizeof(color_table));

 	tab->color_num = image_give_largeur(self)*image_give_hauteur(self);
	tab->colors = malloc(tab->color_num*image_give_dim(self)*sizeof(int));
	tab->colors = image_lire_pixel(self);
	tab->owner = true;
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
	assert(offset>-1);
	assert(len>0);
	color_table dup_tab;
	dup_tab->owner = false;
	dup_tab->color_num = len;
	dup_tab->colors = tab->colors + offset;
	return(dup_tab);
}


