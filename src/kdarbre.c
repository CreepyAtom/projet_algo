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
  
axis kd_tree_select_axis(color_table tab){
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
   }
   if (spread_tab[0]>spread_tab[1] && spread_tab[0]>spread_tab[2])
     return red;
   if (spread_tab[1]>spread_tab[0] && spread_tab[1]>spread_tab[2])
     return green;
   if (spread_tab[2]>spread_tab[0] && spread_tab[2]>spread_tab[1])
     return blue;
  }

int kd_tree_cut_axis(color_table tab, axis ax){
  int color_num = tab->color_num;
  int pivot;
  color pixel[3];
  color_table_get_color(tab,color_num/2,pixel);
  pivot = pixel[ax];
  return pivot; 
  }
  //choix de programmation: l'indice du pixel sera toujours inférieur ou égal à color_num/2 (division flottante)
 
 
 
kdtree create_kdtree(color_table tab, int threshold){
  kdtree A= (kdtree)malloc(sizeof(struct kdtree));
  color_table tab_left, tab_right;
  A->tab = tab;
  int color_num = tab->color_num;
  if (color_num <= threshold){
    A->left_son = NULL;
    A->right_son = NULL;
    A->pivot = -1;
    A->ax = -1;
    return A;
  }
  
  A->ax = kd_tree_select_axis(tab);
  color_table_sort(A->tab,A->ax);
 
  A->pivot = kd_tree_cut_axis(A->tab, A->ax);
  tab_left = color_table_duplicate(A->tab, 0, color_num/2);
  tab_right = color_table_duplicate(A->tab, color_num/2, color_num-color_num/2);

  A->left_son = create_kdtree(tab_left, threshold);
  A->right_son = create_kdtree(tab_right, threshold);
  return A;
  }
  
void destroy_kdtree(kdtree A){
  if (A == NULL){} //cas de base, lorsque l'on atteint une feuille
  else{
    destroy_kdtree(A->left_son); //libération du fils gauche

    destroy_kdtree(A->right_son); //libération du fils droit

    destroy_color_table(A->tab); //libération de la table

    free(A); // libération de l'arbre lui-même
  }
}
  
void kdtree_get_nearest_color(kdtree A, color* pixel, color* new_pixel){
  axis ax = A->ax;
  color pixeltab[3];
  color new_pixel_temp[3];
  int distance;
  int minimum = 100000;
  int Dim = A->tab->dim;
  if (A->left_son ==NULL  && A->right_son == NULL){ //on atteint la feuille
    for (int k = 0; k < A->tab->color_num; k++) {
      color_table_get_color(A->tab,k,pixeltab);
      distance = calcul_distance(pixel,pixeltab,Dim);
      
      if (distance < minimum){
        minimum = distance; 
        for (int l = 0; l < Dim; l++){
					new_pixel[l] = pixeltab[l];		// On met la valeur de la table de couleur dans la val finale
				}  
      } 
    }
  }
  else{ //on n'a pas encore atteint la feuille
    if (pixel[ax] <= A->pivot){ // cas fils gauche
      kdtree_get_nearest_color(A->left_son, pixel, new_pixel);
      distance = calcul_distance(pixel,new_pixel,Dim);
      if (distance >= ( new_pixel[ax]-A->pivot )*( new_pixel[ax]-A->pivot)){ //cas intersection
        kdtree_get_nearest_color(A->right_son, pixel, new_pixel_temp); // on teste l'autre fils
        if (calcul_distance(pixel,new_pixel_temp,Dim)<distance){ // si l'autre fils est meilleur, on le choisit
          new_pixel[0] = new_pixel_temp[0];
          new_pixel[1] = new_pixel_temp[1];
          new_pixel[2] = new_pixel_temp[2];
          }
        }
      }
    else{
      kdtree_get_nearest_color(A->right_son, pixel, new_pixel);
      distance = calcul_distance(pixel,new_pixel,Dim);
      if (distance >= ( new_pixel[ax]-A->pivot )*( new_pixel[ax]-A->pivot)){ //cas intersection
        kdtree_get_nearest_color(A->left_son, pixel, new_pixel_temp); // on teste l'autre fils
        if (calcul_distance(pixel,new_pixel_temp,Dim)<distance){ // si l'autre fils est meilleur, on le choisit
          new_pixel[0] = new_pixel_temp[0];
          new_pixel[1] = new_pixel_temp[1];
          new_pixel[2] = new_pixel_temp[2];
          }
        }
      }
    }
  }
    
//Exemple d'exécution: ./bin/kdarbre.bin ./IMAGES/TABLES/table_fille_1024.ppm
