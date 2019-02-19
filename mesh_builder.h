#if 0
/**
	Functions for creating simple until complex meshes.
*/
#endif

#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include <stdlib.h>
#include <complex.h>
#include "utils_math.h"
#include "mesh.h"


#if 0
	/**
		This function creates a point mesh
	*/
#endif
mesh_t * create_point3(const vec3_t *p);

#if 0
	/**
		This function creates a line mesh
	*/
#endif
mesh_t * create_line3(const vec3_t *p1, const vec3_t *p2);

#if 0
	/**
		This function creates a line mesh
	*/
#endif
mesh_t * create_triangle3(const vec3_t *p1, const vec3_t *p2, const vec3_t *p3);

#if 0
	/**
		This function creates a quad mesh by given left bottom(LB) and up right(UR) vectors. You must free the memory by yourself.
	*/
#endif
mesh_t * create_quad3(const vec3_t *lb, const vec3_t *rb, const vec3_t *lt, const vec3_t *rt);

#if 0
	/**
		This function creates a cube mesh by given center vector. It will be created with side len.
		You must free the memory by yourself.
	*/
#endif
mesh_t * create_cube3_center(const vec3_t *center, const float sidelen);

#if 0
	/**
		This function creates a square block of given width height and depth. This
		segments are splitted into different segments.
	*/
#endif
mesh_t * create_square_block(const vec3_t *center, const float width, const float height, const float depth,
							const unsigned int cntx, const unsigned int cnty, const unsigned int cntz);

#if 0
	/**
		Create a Raster with lines in metric distance delta 1.0
	*/
#endif
mesh_t * create_raster(const float linelen);

#if 0
	/**
		Create a Raster from points
	*/
#endif
mesh_t * create_point_raster();

#if 0
	/**
		creates a Sphere.
	*/
#endif
mesh_t * createsphere(const float radius, const unsigned int longs, const unsigned int lats);

#if 0
	/**
		creates a Cylinder.
	*/
#endif
mesh_t * createcylinder(const float radius, const float height, const unsigned int longs, const unsigned int lats, 
						const bool showtop, const bool showbottom);

#if 0
	/**
		creates a cone.
	*/
#endif
mesh_t * createcone(const float radius, const float height, const unsigned int lats, const bool showbottom);

#if 0
	//creates a path with various angle ranges.
#endif
mesh_t * createpath(const float radius, const int cntelements, const float height, const int longs, const float scaleend);

#endif
