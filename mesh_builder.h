#if 0
/**
	Functions for creating simple until complex meshes.
*/
#endif

#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include <stdlib.h>
#include <stdint.h>
#include <complex.h>
#include "dl_list.h"
#include "utils_math.h"
#include "geometry.h"
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
		This function triangulates polygon from vec3 point array.
	*/
#endif
mesh_t * create_polygon3(const vec3_t *vecs, size_t cnt_vecs);
#if 0
	/**
		This function triangulates polygon from polygon shape. All shapes with more than 3 vertices were handled
	*/
#endif
mesh_t * create_polygon_shape(const shape_t * polyshape);

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

#if 0
	//create heighmap from array of floats
#endif
mesh_t * create_hmap_from_array(float *_array, uint32_t _rows, uint32_t _cols);

mesh_t * create_center();

#endif
