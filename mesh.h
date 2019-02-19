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
	vec3_t min;
	vec3_t max;
	bool created;
} bbox_t;

typedef struct {
	unsigned int cntShapes;
	bbox_t bbox;
	shape_t ** shapes;
} mesh_t;

extern const size_t mesh_size;
extern const size_t mesh_ptr_size;

#if 0
	/**
		This function allocates and init mesh instance with given shapecount.
	*/
#endif
mesh_t * alloc_mesh( const unsigned int meshcount);

#if 0
	/**
		This function frees all memory from using shape.
	*/
#endif
void free_mesh(mesh_t *mesh);

#if 0
	/**
		multiplies every shape of mesh coords with given matrix like transform or roation one
	*/
#endif
void mat_mul_mesh(mesh_t * mesh, const mat3_t * matrix);
#if 0
	/**
		scales mesh
	*/
#endif
void scale_mesh(mesh_t * mesh, const float scalex, const float scaley, const float scalez );
#if 0
	/**
		translate mesh
	*/
#endif
void translate_mesh(mesh_t * mesh, const float tx, const float ty, const float tz );
#if 0
	/**
		shows detailed mesh info
	 */
#endif
void debug_mesh(const mesh_t * mesh);

#if 0	
	//clears bbox
#endif
void mesh_unset_bbox(mesh_t *mesh);

#if 0
	// Sets precalcualted bbox
#endif
void mesh_set_bbox(mesh_t *mesh, const float minx, const float miny, 
								 const float minz, const float maxx, 
								 const float maxy, const float maxz);

#if 0
	/**
		calculates bounding box on the fly. Could be slowly. You should set bbox during mesh creation.
	 */
#endif
void mesh_create_bbox(mesh_t * mesh);

#if 0
	/**
		calculates color by bbox for whole mesh segments.
	 */
#endif
void mesh_color_by_bbox(mesh_t * mesh);

#endif