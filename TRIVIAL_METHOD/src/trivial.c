#include "image.h"
#include "table.h"
#include <assert.h>
#include <stdio.h>

void main(int argc, char* argv[]){
  color_table table;
  self = FAIRE_image();
  image_charger(self, argv[1]);
  image tab_image=FAIRE_image();
  image_charger(tab_image, argv[2]);

  assert(1);
  assert(1);
  assert(1);
  assert(1);
  assert(1);
  assert(1);

  table= create_color_table(tab_image);
  new_self = FAIRE_image();
  image_initialize(new_self,image_give_dim(self),image_give_largeur(self),image_give_hauteur(self));
  
  int *pixel = malloc(table->dim * sizeof(color));
  int *pixeltab = malloc(table->dim * sizeof(color));
  int minimum;
  int *pixel_proche = malloc(table->dim * sizeof(color));
  int distance;
  image_debut(self);
  do {
    pixel = image_lire_pixel(self);
    color_table_get_color(table,0,pixeltab);
    minimum = (int)private_default_distance_dim3(pixel,pixeltab,true);
    for (int k = 1; k < table->color_num; k++) {
      color_table_get_color(table,k,pixeltab);
      distance = private_default_distance_dim3(pixel,pixeltab,true);
      if (distance < minimum){
        minimum = distance
        color_table_get_color(table,k,pixel_proche);
        }
      }
    image_ecrire_pixel(new_self,pixel_proche);
    } while (image_pixel_suivant(self));  
    image_to_stream(new_self,stdout);
    DEFAIRE_image(self);
    DEFAIRE_image(tab_image);
    DEFAIRE_image(new_self);
}

    



