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
#include "utilsmath.h"
#include "geometry.h"
#include "mesh.h"

#if 0
	/**
		This function creates a point mesh
	*/
#endif
Mesh * create_point3(const Vec3 *p);

#if 0
	/**
		This function creates a line mesh
	*/
#endif
Mesh * create_line3(const Vec3 *p1, const Vec3 *p2);

#if 0
	/**
		This function creates a line mesh
	*/
#endif
Mesh * create_triangle3(const Vec3 *p1, const Vec3 *p2, const Vec3 *p3);

#if 0
	/**
		This function creates a quad mesh by given left bottom(LB) and up right(UR) vectors. You must free the memory by yourself.
	*/
#endif
Mesh * create_quad3(const Vec3 *lb, const Vec3 *rb, const Vec3 *lt, const Vec3 *rt);
Mesh * create_quad3_textured(const Vec3 *lb, const Vec3 *rb, const Vec3 *lt, const Vec3 *rt, unsigned int texId);
Mesh * create_quad3_textured_coords(const Vec3 *lb, const Vec3 *rb, const Vec3 *lt, const Vec3 *rt,
							   unsigned int texId, const Vec2* lbTex, const Vec2* rbTex, const Vec2* ltTex, const Vec2* rtTex);

#if 0
	/**
		This function triangulates polygon from vec3 point array.
	*/
#endif
Mesh * create_polygon3(const Vec3 *vecs, size_t cnt_vecs);
#if 0
	/**
		This function triangulates polygon from polygon shape. All shapes with more than 3 vertices were handled
	*/
#endif
Mesh * create_polygon_shape(const Shape * polyshape);

#if 0
	/**
		This function creates a cube mesh by given center vector. It will be created with side len.
		You must free the memory by yourself.
	*/
#endif
Mesh * create_cube3_center(const Vec3 *center, const float sidelen);

#if 0
	/**
		This function creates a square block of given width height and depth. This
		segments are splitted into different segments.
	*/
#endif
Mesh * create_square_block(const Vec3 *center, const float width, const float height, const float depth,
							const unsigned int cntx, const unsigned int cnty, const unsigned int cntz);

#if 0
	/**
		Create a Raster with lines in metric distance delta 1.0
	*/
#endif
Mesh * create_raster(const float linelen);

#if 0
	/**
		Create a Raster from points
	*/
#endif
Mesh * create_point_raster();

#if 0
	/**
		creates a Sphere.
	*/
#endif
Mesh * createsphere(const float radius, const unsigned int longs, const unsigned int lats);

#if 0
	/**
		creates a Cylinder.
	*/
#endif
Mesh * createcylinder(const float radius, const float height, const unsigned int longs, const unsigned int lats, 
						const bool showtop, const bool showbottom);

#if 0
	/**
		creates a cone.
	*/
#endif
Mesh * createcone(const float radius, const float height, const unsigned int lats, const bool showbottom);

#if 0
	//creates a path with various angle ranges.
#endif
Mesh * createpath(const float radius, const int cntelements, const float height, const int longs, const float scaleend);

#if 0
	//create heighmap from array of floats
#endif
Mesh * create_hmap_from_array(float *_array, uint32_t _rows, uint32_t _cols);

Mesh * create_center();

#endif
