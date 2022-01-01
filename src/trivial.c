#include "image.h"
#include "table.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

struct color_table{
  int color_num;
  int *colors;
  boolean owner;
  int dim;
};

int main(int argc, char* argv[]){
  assert(argc = 3);

  image self = FAIRE_image();
  image new_self = FAIRE_image();
  image tab_image=FAIRE_image();
  /* self = image initiale | new_self = image en sortie | tab_image = image du tableau de couleurs*/
  
  if ( image_charger(self, argv[1]) == 0 && image_charger(tab_image, argv[2]) == 0)
    fprintf(stderr, "Chargement des images réussi.\n");
  else
    return(-1);
  
  image_initialize(new_self, image_give_dim(self), image_give_largeur(self), image_give_hauteur(self));
  /*initialisation de la nouvelle image (mêmes dimensions que l'image initiale)*/  
  
  color_table table;
  table= create_color_table(tab_image);
  /*création de la table de couleurs*/
  
  int Dim = image_give_dim(self);
  color *pixel;
  color pixeltab[3];
  color pixel_proche[3];
  int distance;
  int minimum;
  /* pixel = pixel de l'image initiale | pixeltab = pixel de la table de couleurs | pixel_proche = pixel de la table de couleurs qui sera le plus proche du pixel initial*/
  
  
  image_debut(new_self);
  image_debut(self);
  do {
    pixel = image_lire_pixel(self); /* on lit le pixel courant*/
    color_table_get_color(table,0,pixeltab);
    minimum = calcul_distance(pixel,pixeltab,Dim); 
    /* on initialise le minimum pour pouvoir comparer dans la boucle ci-dessous*/
    
    for (int k = 1; k < table->color_num; k++) {
      color_table_get_color(table,k,pixeltab);
      distance = calcul_distance(pixel,pixeltab,Dim);
      
      if (distance < minimum){
        minimum = distance; 
        for (int l = 0; l < Dim; l++){
					pixel_proche[l] = pixeltab[l];		// On met la valeur de la table de couleur dans la val finale
				}  
        } 
        /*on cherche le minimum*/
      }
    image_ecrire_pixel(new_self, pixel_proche);
    image_pixel_suivant(new_self); /* on remplace l'ancien pixel par le nouveau*/
    } while (image_pixel_suivant(self));
    
    
    
    image_to_stream(new_self,stdout);
    
    
    
    DEFAIRE_image(self);
    DEFAIRE_image(tab_image);
    DEFAIRE_image(new_self);
    
    fprintf(stderr, "L'image finale a été générée avec succès. \n");
    
    return(0);
    /*on défait toutes les images, n'en ayant plus besoin*/
    }

    

//exemple d'exécution: ./bin/trivial.bin ./IMAGES/house.ppm ./IMAGES/TABLES/table_house_128.ppm > ./output/zelda3.ppm


