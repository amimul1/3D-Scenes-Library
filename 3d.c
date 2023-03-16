
/** Author: Amimul Ehsan Zoha
 *  Description: This is a c file which is a library which provides an interface for creating 
 *  a 3D scene and saves the scene to .stl files which makes it portable to view across
 *  a varity of 3d model viewing software. It uses a linkedlist ish data structure and different 
 *  3D objects are made of using triangles in 3d coordinates. Memory allocation and free has been done.
 */
#include <stdio.h>
#include <stdlib.h>
#include "3d.h"
#include<string.h>
#include<stdint.h>
#include <math.h>

Scene3D* Scene3D_create(){
    Scene3D* scene = malloc(sizeof(Scene3D));
    scene->count = 0;
    scene->root = NULL;
    return scene;
}

void Scene3D_destroy(Scene3D* scene){
    Triangle3DNode * node = scene->root;
    while (node!=NULL){
        Triangle3DNode * tempNode = node->next;
        free(node);
        node = tempNode;
    }
    free(scene);
}

void Scene3D_write_stl_text(Scene3D* scene, char* file_name){
    FILE * filePointer = fopen(file_name,"w");
    fprintf(filePointer,"solid scene\n");
    Triangle3DNode * node = scene->root;
    while (node!=NULL){
        Triangle3D curTriangle = node->triangle;
        fprintf(filePointer,"  facet normal 0.0 0.0 0.0\n");
        fprintf(filePointer,"    outer loop\n");
        fprintf(filePointer,"      vertex %0.5lf %0.5lf %0.5lf\n",curTriangle.a.x,curTriangle.a.y,curTriangle.a.z);
        fprintf(filePointer,"      vertex %0.5lf %0.5lf %0.5lf\n",curTriangle.b.x,curTriangle.b.y,curTriangle.b.z);
        fprintf(filePointer,"      vertex %0.5lf %0.5lf %0.5lf\n",curTriangle.c.x,curTriangle.c.y,curTriangle.c.z);
        fprintf(filePointer,"    endloop\n");
        fprintf(filePointer,"  endfacet\n");
        node = node->next;
    }
    fprintf(filePointer,"endsolid scene\n");
    fclose(filePointer);
    
}

void Scene3D_write_stl_binary(Scene3D* scene, char* file_name){
    FILE * filePointer = fopen(file_name,"wb");
    const __int32_t ZERO_INT32 = 0;
    for(int i = 0; i < 20; ++i) {
    fwrite(&ZERO_INT32, sizeof(__int32_t), 1, filePointer);
    }
    uint32_t triangleCount =  (uint32_t) scene->count;
    fwrite(&triangleCount, sizeof(uint32_t), 1, filePointer);
    Triangle3DNode * node = scene->root;
    while (node!=NULL){
        // first 12 bytes
        float normall = 0.0;
        fwrite(&normall, 4, 1, filePointer);
        fwrite(&normall, 4, 1, filePointer);
        fwrite(&normall, 4, 1, filePointer);
        Triangle3D curTriangle = node->triangle;
        //next 36 bytes 
        float cord = 0.0;
        cord = (float) curTriangle.a.x;
        fwrite(&cord, 4, 1, filePointer);
        cord = (float) curTriangle.a.y;
        fwrite(&cord, 4, 1, filePointer);
        cord = (float) curTriangle.a.z;
        fwrite(&cord, 4, 1, filePointer);
        cord = (float) curTriangle.b.x;
        fwrite(&cord, 4, 1, filePointer);
        cord = (float) curTriangle.b.y;
        fwrite(&cord, 4, 1, filePointer);
        cord = (float) curTriangle.b.z;
        fwrite(&cord, 4, 1, filePointer);
        cord = (float) curTriangle.c.x;
        fwrite(&cord, 4, 1, filePointer);
        cord = (float) curTriangle.c.y;
        fwrite(&cord, 4, 1, filePointer);
        cord = (float) curTriangle.c.z;
        fwrite(&cord, 4, 1, filePointer);
        uint16_t end = (uint16_t)0;
        fwrite(&end, 2, 1, filePointer);
        node = node->next;
    }
    fclose(filePointer);
}




void Scene3D_add_triangle(Scene3D* scene, Triangle3D triangleToAdd){
    //does this in O(1) time to be more efficient
    Triangle3DNode* new_node = malloc(sizeof(Triangle3DNode));
    new_node->triangle = triangleToAdd;
     new_node->next = scene->root;
     scene->root = new_node;
}

void Scene3D_add_quadrilateral( Scene3D* scene, Coordinate3D a, Coordinate3D b,
 Coordinate3D c, Coordinate3D d){
     Triangle3D triangle_1 = (Triangle3D) {a, b, c};
     Triangle3D triangle_2 = (Triangle3D) {b, c, d}; 
     Triangle3D triangle_3 = (Triangle3D) {a, c, d}; 
     Triangle3D triangle_4 = (Triangle3D) {a, b, d}; 
     Scene3D_add_triangle(scene, triangle_1); 
     Scene3D_add_triangle(scene, triangle_2);
     Scene3D_add_triangle(scene, triangle_3);
     Scene3D_add_triangle(scene, triangle_4); 
}

void Scene3D_add_cuboid(
    Scene3D* scene,
    Coordinate3D origin, 
    double width, double height, double depth){
         Coordinate3D a = (Coordinate3D){origin.x-width/2,origin.y+height/2, origin.z+depth/2};
         Coordinate3D b = (Coordinate3D){origin.x+width/2,origin.y+height/2, origin.z+depth/2};
         Coordinate3D c = (Coordinate3D){origin.x-width/2,origin.y-height/2, origin.z+depth/2};
         Coordinate3D d = (Coordinate3D){origin.x+width/2,origin.y-height/2, origin.z+depth/2};
         Coordinate3D e = (Coordinate3D){origin.x-width/2,origin.y+height/2, origin.z-depth/2};
         Coordinate3D f = (Coordinate3D){origin.x+width/2,origin.y+height/2, origin.z-depth/2};
         Coordinate3D g = (Coordinate3D){origin.x-width/2,origin.y-height/2, origin.z-depth/2};
         Coordinate3D h = (Coordinate3D){origin.x+width/2,origin.y-height/2, origin.z-depth/2};
         Scene3D_add_quadrilateral(scene,a,b,c,d);
         Scene3D_add_quadrilateral(scene,e,a,g,c);
         Scene3D_add_quadrilateral(scene,f,b,h,d);
         Scene3D_add_quadrilateral(scene,e,f,a,b);
         Scene3D_add_quadrilateral(scene,g,h,c,d);
         Scene3D_add_quadrilateral(scene,e,f,g,h);
    }


    

void Scene3D_add_pyramid(Scene3D* scene,Coordinate3D origin, 
    double width, double height, char* orientation){
        if (strcmp(orientation,"right")==0){
            // x coor stays the same
            Coordinate3D a = (Coordinate3D){origin.x,(origin.y+width/2), (origin.z+width/2)};
            Coordinate3D b = (Coordinate3D){origin.x,(origin.y-width/2), (origin.z+width/2)};
            Coordinate3D c = (Coordinate3D){origin.x,(origin.y-width/2), (origin.z-width/2)};
            Coordinate3D d = (Coordinate3D){origin.x,(origin.y+width/2), (origin.z-width/2)};
            Coordinate3D e = (Coordinate3D){(origin.x+height),origin.y, origin.z};
            Triangle3D triangle_1 = (Triangle3D){a,b,e};
            Triangle3D triangle_2 = (Triangle3D){a,d,e};
            Triangle3D triangle_3 = (Triangle3D){d,e,c};
            Triangle3D triangle_4 = (Triangle3D){b,c,e};
            Scene3D_add_quadrilateral(scene,a,b,c,d);
            Scene3D_add_triangle(scene,triangle_1);
            Scene3D_add_triangle(scene,triangle_2);
            Scene3D_add_triangle(scene,triangle_3);
            Scene3D_add_triangle(scene,triangle_4);
        }
        else if (strcmp(orientation,"left")==0){
            Coordinate3D a = (Coordinate3D){origin.x,(origin.y+width/2), (origin.z+width/2)};
            Coordinate3D b = (Coordinate3D){origin.x,(origin.y-width/2), (origin.z+width/2)};
            Coordinate3D c = (Coordinate3D){origin.x,(origin.y-width/2), (origin.z-width/2)};
            Coordinate3D d = (Coordinate3D){origin.x,(origin.y+width/2), (origin.z-width/2)};
            Coordinate3D e = (Coordinate3D){(origin.x-height),origin.y, origin.z};
            Triangle3D triangle_1 = (Triangle3D){a,b,e};
            Triangle3D triangle_2 = (Triangle3D){a,d,e};
            Triangle3D triangle_3 = (Triangle3D){d,e,c};
            Triangle3D triangle_4 = (Triangle3D){b,c,e};
            Scene3D_add_quadrilateral(scene,a,b,c,d);
            Scene3D_add_triangle(scene,triangle_1);
            Scene3D_add_triangle(scene,triangle_2);
            Scene3D_add_triangle(scene,triangle_3);
            Scene3D_add_triangle(scene,triangle_4);
        }
        else if(strcmp(orientation,"up")==0){
            //z coor stays the same 
            Coordinate3D a = (Coordinate3D){(origin.x-width/2),(origin.y+width/2), origin.z};
            Coordinate3D b = (Coordinate3D){(origin.x+width/2),(origin.y+width/2), origin.z}; 
            Coordinate3D c = (Coordinate3D){(origin.x-width/2),(origin.y-width/2), origin.z};
            Coordinate3D d = (Coordinate3D){(origin.x+width/2),(origin.y-width/2), origin.z};
            Coordinate3D e = (Coordinate3D){origin.x,origin.y,(origin.z+height)};
            Triangle3D triangle_1 = (Triangle3D){b,d,e};
            Triangle3D triangle_2 = (Triangle3D){a,e,c};
            Triangle3D triangle_3 = (Triangle3D){d,e,c};
            Triangle3D triangle_4 = (Triangle3D){a,b,e};
            Scene3D_add_quadrilateral(scene,a,b,c,d);
            Scene3D_add_triangle(scene,triangle_1);
            Scene3D_add_triangle(scene,triangle_2);
            Scene3D_add_triangle(scene,triangle_3);
            Scene3D_add_triangle(scene,triangle_4);
        }

        else if(strcmp(orientation,"down")==0){
            //z coor stays the same 
            Coordinate3D a = (Coordinate3D){(origin.x-width/2),(origin.y+width/2), origin.z};
            Coordinate3D b = (Coordinate3D){(origin.x+width/2),(origin.y+width/2), origin.z};
            Coordinate3D c = (Coordinate3D){(origin.x-width/2),(origin.y-width/2), origin.z};
            Coordinate3D d = (Coordinate3D){(origin.x+width/2),(origin.y-width/2), origin.z};
            Coordinate3D e = (Coordinate3D){origin.x,origin.y,(origin.z-height)};
            Triangle3D triangle_1 = (Triangle3D){b,d,e};
            Triangle3D triangle_2 = (Triangle3D){a,e,c};
            Triangle3D triangle_3 = (Triangle3D){d,e,c};
            Triangle3D triangle_4 = (Triangle3D){a,b,e};
            Scene3D_add_quadrilateral(scene,a,b,c,d);
            Scene3D_add_triangle(scene,triangle_1);
            Scene3D_add_triangle(scene,triangle_2);
            Scene3D_add_triangle(scene,triangle_3);
            Scene3D_add_triangle(scene,triangle_4);
        }

        else if(strcmp(orientation,"forward")==0){
            // y coord remains the same
            Coordinate3D a = (Coordinate3D){(origin.x-width/2), origin.y, origin.z+width/2};
            Coordinate3D b = (Coordinate3D){(origin.x+width/2), origin.y, (origin.z+width/2)};
            Coordinate3D c = (Coordinate3D){(origin.x-width/2), origin.y, (origin.z-width/2)};
            Coordinate3D d = (Coordinate3D){(origin.x+width/2), origin.y, (origin.z-width/2)};
            Coordinate3D e = (Coordinate3D){origin.x,(origin.y+height),origin.z};
            Triangle3D triangle_1 = (Triangle3D){b,d,e};
            Triangle3D triangle_2 = (Triangle3D){a,c,e};
            Triangle3D triangle_3 = (Triangle3D){d,e,c};
            Triangle3D triangle_4 = (Triangle3D){a,b,e};
            Scene3D_add_quadrilateral(scene,a,b,c,d);
            Scene3D_add_triangle(scene,triangle_1);
            Scene3D_add_triangle(scene,triangle_2);
            Scene3D_add_triangle(scene,triangle_3);
            Scene3D_add_triangle(scene,triangle_4);
        }
        else if(strcmp(orientation,"backward")==0){
            // y coord remains the same
            Coordinate3D a = (Coordinate3D){(origin.x-width/2), origin.y, origin.z+width/2};
            Coordinate3D b = (Coordinate3D){(origin.x+width/2), origin.y, (origin.z+width/2)};
            Coordinate3D c = (Coordinate3D){(origin.x-width/2), origin.y, (origin.z-width/2)};
            Coordinate3D d = (Coordinate3D){(origin.x+width/2), origin.y, (origin.z-width/2)};
            Coordinate3D e = (Coordinate3D){origin.x,(origin.y-height),origin.z};
            Triangle3D triangle_1 = (Triangle3D){b,d,e};
            Triangle3D triangle_2 = (Triangle3D){a,c,e};
            Triangle3D triangle_3 = (Triangle3D){d,e,c};
            Triangle3D triangle_4 = (Triangle3D){a,b,e};
            Scene3D_add_quadrilateral(scene,a,b,c,d);
            Scene3D_add_triangle(scene,triangle_1);
            Scene3D_add_triangle(scene,triangle_2);
            Scene3D_add_triangle(scene,triangle_3);
            Scene3D_add_triangle(scene,triangle_4);
        }
    }
/**
 * This function changes a degree value into a radian value
 *   Parameters:
 *     degree: The degree value as double type
 *   Return: the value in radian
 */
double radian(double degree){
    double radian = (degree/180)* PI;
    return radian;
}
/**
 * This function rounds a number to the correct decimal places
 *   Parameters:
 *     number: the number to be rounded
 *   Return: double the rounded number 
 */
double round_number(double number){
    number = number * 10000;
    number = round(number);
    number = number/10000;
    return number; 
}
void Scene3D_add_sphere(Scene3D* scene,Coordinate3D origin,double radius, double increment){
    for (double phi = increment; phi<=180; phi+=increment){
        for (double theta = 0;theta<360; theta+=increment){
            //getting the coordinates
            double x1 = round_number(radius*sin(radian(phi))*cos(radian(theta)));
            double y1 = round_number(radius*sin(radian(phi))*sin(radian(theta)));
            double z1 = round_number(radius*cos(radian(phi)));

            double x2 = round_number(radius*sin(radian(phi-increment))*cos(radian(theta)));
            double y2 = round_number(radius*sin(radian(phi-increment))*sin(radian(theta)));
            double z2 = round_number(radius*cos(radian(phi-increment)));

            double x3 = round_number(radius*sin(radian(phi))*cos(radian(theta-increment)));
            double y3 = round_number(radius*sin(radian(phi))*sin(radian(theta-increment)));
            double z3 = round_number(radius*cos(radian(phi)));

            double x4 = round_number(radius*sin(radian(phi-increment))*cos(radian(theta-increment)));
            double y4 = round_number(radius*sin(radian(phi-increment))*sin(radian(theta-increment)));
            double z4 = round_number(radius*cos(radian(phi-increment)));
            // adding the offset 
            Coordinate3D a = (Coordinate3D){(origin.x+x1), (origin.y+y1), (origin.z+z1)};
            Coordinate3D b = (Coordinate3D){(origin.x+x2), (origin.y+y2), (origin.z+z2)};
            Coordinate3D c = (Coordinate3D){(origin.x+x3), (origin.y+y3), (origin.z+z3)};
            Coordinate3D d = (Coordinate3D){(origin.x+x4), (origin.y+y4), (origin.z+z4)};

            Scene3D_add_quadrilateral(scene,a,b,c,d);
        }
    }
}

void Scene3D_add_fractal(Scene3D* scene, Coordinate3D origin, double size, int levels){
    if (levels ==0){
        return;
    }
    Scene3D_add_cuboid(scene,origin, size, size,size);
    Scene3D_add_fractal(scene,(Coordinate3D){origin.x+size/2, origin.y, origin.z}, size/2, levels-1);
    Scene3D_add_fractal(scene,(Coordinate3D){origin.x-size/2, origin.y, origin.z}, size/2, levels-1);
    Scene3D_add_fractal(scene,(Coordinate3D){origin.x, origin.y+size/2, origin.z}, size/2, levels-1);
    Scene3D_add_fractal(scene,(Coordinate3D){origin.x, origin.y-size/2, origin.z}, size/2,  levels-1);
    Scene3D_add_fractal(scene,(Coordinate3D){origin.x, origin.y, origin.z+size/2}, size/2,  levels-1);
    Scene3D_add_fractal(scene,(Coordinate3D){origin.x, origin.y, origin.z-size/2}, size/2, levels-1);
}



