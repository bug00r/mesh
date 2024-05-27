#if 0
/**
	This is a simple shape class. 
*/
#endif

#ifndef MESH_H
#define MESH_H

#include <stddef.h>
#include <stdlib.h>
#include <float.h>

#include "shape.h"

typedef struct {
	Vec3 min;
	Vec3 max;
	bool created;
} BBox;

typedef struct {
	unsigned int cntShapes;
	BBox bbox;
	Shape ** shapes;
} Mesh;

extern const size_t mesh_size;
extern const size_t mesh_ptr_size;

#if 0
	/**
		This function allocates and init mesh instance with given shapecount.
	*/
#endif
Mesh * alloc_mesh( const unsigned int meshcount);

#if 0
	/**
		This function frees all memory from using shape.
	*/
#endif
void free_mesh(Mesh *mesh);

#if 0
	/**
		multiplies every shape of mesh coords with given matrix like transform or roation one
	*/
#endif
void mat_mul_mesh(Mesh * mesh, const Mat3 * matrix);
#if 0
	/**
		scales mesh
	*/
#endif
void scale_mesh(Mesh * mesh, const float scalex, const float scaley, const float scalez );
#if 0
	/**
		translate mesh
	*/
#endif
void translate_mesh(Mesh * mesh, const float tx, const float ty, const float tz );
#if 0
	/**
		shows detailed mesh info
	 */
#endif
void debug_mesh(const Mesh * mesh);

#if 0	
	//clears bbox
#endif
void mesh_unset_bbox(Mesh *mesh);

#if 0
	// Sets precalcualted bbox
#endif
void mesh_set_bbox(Mesh *mesh, const float minx, const float miny, 
								 const float minz, const float maxx, 
								 const float maxy, const float maxz);

#if 0
	/**
		calculates bounding box on the fly. Could be slowly. You should set bbox during mesh creation.
	 */
#endif
void mesh_create_bbox(Mesh * mesh);

#if 0
	/**
		calculates color by bbox for whole mesh segments.
	 */
#endif
void mesh_color_by_bbox(Mesh * mesh);
void mesh_color_by_bbox2(Mesh * mesh);

void mesh_set_color (Mesh * _mesh, ColorRGB * _color);
#endif