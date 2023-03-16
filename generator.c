
/** Author: Amimul Ehsan Zoha
 *  Description: This is a c file which is uses the 3d.c library I created to draw 3d objects into a stl
 *  file. Using the library, I implement a message which has 3d words and letters and also the new
 * shapes, fractal and spheres. this makes look nicer. I also have uploaded a screenshot of what the created
 *  stl file produces.
 */

#include <stdio.h>
#include <stdlib.h>
#include "3d.h"
#include<string.h>

/**
* This function draws the 3d message using the shapes and it says :CS IS COOL
* @param Scene3D* scene the scene in which we are drawing
* @return void
*/
void draw_message(Scene3D* scene){
    Coordinate3D cord = (Coordinate3D){0,0,0};
    cord = (Coordinate3D){0,0,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
    cord = (Coordinate3D){-3,-3,0};
    Scene3D_add_cuboid(scene,cord, 2,8,3);
    cord = (Coordinate3D){0,-8,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
    cord = (Coordinate3D){10,0,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
    cord = (Coordinate3D){10,-4,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
    cord = (Coordinate3D){10,-8,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
    cord = (Coordinate3D){7,-3,0};
    Scene3D_add_cuboid(scene,cord, 2,4,3);
    cord = (Coordinate3D){7+6,-3-3,0};
    Scene3D_add_cuboid(scene,cord, 2,4,3);
    cord = (Coordinate3D){20,0,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
    cord = (Coordinate3D){-3+20,-3,0};
    Scene3D_add_cuboid(scene,cord, 2,8,3);
    cord = (Coordinate3D){0+20,-8,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
    cord = (Coordinate3D){33,-4,0};
    Scene3D_add_cuboid(scene,cord, 2,10,3);
    cord = (Coordinate3D){10+30,0,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
    cord = (Coordinate3D){10+30,-4,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
    cord = (Coordinate3D){10+30,-8,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
    cord = (Coordinate3D){7+30,-3,0};
    Scene3D_add_cuboid(scene,cord, 2,4,3);
    cord = (Coordinate3D){7+6+30,-3-3,0};
    Scene3D_add_cuboid(scene,cord, 2,4,3);
    cord = (Coordinate3D){0+55,0,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
    cord = (Coordinate3D){-3+55,-3,0};
    Scene3D_add_cuboid(scene,cord, 2,8,3);
    cord = (Coordinate3D){0+55,-8,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
    cord = (Coordinate3D){0+65,-5,0};
     Scene3D_add_sphere(scene,cord,4, 1);
    cord = (Coordinate3D){0+65+10,-5,0};
    //drawing a sphere
    Scene3D_add_sphere(scene,cord,4, 1);
    cord = (Coordinate3D){-3+65,-3,0};
    cord = (Coordinate3D){0+65,-8,0};
    cord = (Coordinate3D){-3+65+6,-4,0};
    cord = (Coordinate3D){0+65+10,0,0};
    cord = (Coordinate3D){-3+65+10,-3,0};
    cord = (Coordinate3D){0+65+10,-8,0};
    cord = (Coordinate3D){-3+65+6+10,-4,0};
    cord = (Coordinate3D){-3+55+30,-3,0};
    Scene3D_add_cuboid(scene,cord, 2,8,3);
    cord = (Coordinate3D){0+55+30,-8,0};
    Scene3D_add_cuboid(scene,cord, 8,2,3);
}
/**
* This function draws the some shape effects to make it look nicer.
* @param Scene3D* scene the scene in which we are drawing
* @return void
*/
void draw_shapeEffects(Scene3D* scene){
    char* directions[] = {"up", "down", "left", "right", "forward", "backward"}; 
    Coordinate3D origin = (Coordinate3D){5, 25, 3};
    for (int i = 0; i <= 5; i ++) { 
        Scene3D_add_pyramid(scene, origin, 6, 9, directions[i]); 
    } 
    origin = (Coordinate3D){80, 25, 3};
    for (int i = 0; i <= 5; i ++) { 
        Scene3D_add_pyramid(scene, origin, 6, 9, directions[i]); 
    } 
    origin = (Coordinate3D){80, -25, 3};
    for (int i = 0; i <= 5; i ++) { 
        Scene3D_add_pyramid(scene, origin, 6, 9, directions[i]); 
    }
    origin = (Coordinate3D){5, -25, 3};
      for (int i = 0; i <= 5; i ++) { 
          Scene3D_add_pyramid(scene, origin, 6, 9, directions[i]); 
    } 
    // drawing fractal
    origin = (Coordinate3D){45, 25, 3}; 
    Scene3D_add_fractal(scene,origin, 9, 3);
    origin = (Coordinate3D){45, 15, 3}; 
    Scene3D_add_pyramid(scene,origin,8, 9, "backward");  
    origin = (Coordinate3D){45, -30, 3}; 
    Scene3D_add_fractal(scene,origin, 9, 3);
}
int main(int argc, char** argv){
    Scene3D* scene = Scene3D_create();
    draw_message(scene);
    draw_shapeEffects(scene);
    Scene3D_write_stl_text(scene, "star.stl");
    Scene3D_destroy(scene);
    return 0;
}

