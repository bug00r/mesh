#include <stdio.h>
#include <assert.h>
#include <float.h>
#include "mesh.h"
#include "mesh_builder.h"

int 
main() 
{
	#ifdef debug
		printf("Start test mesh\n");
	#endif	
	
	#if 0
		// test mesh allocation and free
	#endif
	
	mesh_t * mesh = alloc_mesh(3);
	
	assert(mesh->shapes[0] == NULL);
	assert(mesh->shapes[1] == NULL);
	assert(mesh->shapes[2] == NULL);
	
	assert(mesh->bbox.min.x == FLT_MAX);
	assert(mesh->bbox.min.y == FLT_MAX);
	assert(mesh->bbox.min.z == FLT_MAX);
	assert(mesh->bbox.max.x == FLT_MIN);
	assert(mesh->bbox.max.y == FLT_MIN);
	assert(mesh->bbox.max.z == FLT_MIN);
	
	assert(!mesh->bbox.created);
	
	free_mesh(mesh);

	#if 0
		//test quad mesh
	#endif
	
	vec3_t lb = {0.f, 0.f, 0.5f};
	vec3_t rt = {1.f, 1.f, 0.f};
	vec3_t lt = {0.f, 1.f, 0.5f};
	vec3_t rb = {1.f, 0.f, 0.0f};
	
	mesh_t * quad = create_quad3(&lb, &rb, &lt, &rt);
	
	assert(vec3_equals(&quad->shapes[0]->vertices[0]->vec, &lb));
	assert(vec3_equals(&quad->shapes[0]->vertices[1]->vec, &rb));
	assert(vec3_equals(&quad->shapes[0]->vertices[2]->vec, &lt));
	assert(vec3_equals(&quad->shapes[1]->vertices[0]->vec, &lt));
	assert(vec3_equals(&quad->shapes[1]->vertices[1]->vec, &rb));
	assert(vec3_equals(&quad->shapes[1]->vertices[2]->vec, &rt));
	
	mesh_create_bbox(quad);
	assert(quad->bbox.min.x == 0.f);
	assert(quad->bbox.min.y == 0.f);
	assert(quad->bbox.min.z == 0.f);
	assert(quad->bbox.max.x == 1.f);
	assert(quad->bbox.max.y == 1.f);
	assert(quad->bbox.max.z == 0.5f);
	
	assert(quad->bbox.created);
	
	mesh_unset_bbox(quad);
	
	assert(quad->bbox.min.x == FLT_MAX);
	assert(quad->bbox.min.y == FLT_MAX);
	assert(quad->bbox.min.z == FLT_MAX);
	assert(quad->bbox.max.x == FLT_MIN);
	assert(quad->bbox.max.y == FLT_MIN);
	assert(quad->bbox.max.z == FLT_MIN);
	
	assert(!quad->bbox.created);
	
	free_mesh(quad);
	
	#if 0
		//test quad top
	#endif
	
	lb = (vec3_t){0.f, 1.f, 0.f};
	rt = (vec3_t){1.f, 1.f, 1.f};
	lt = (vec3_t){0.f, 1.f, 1.f};
	rb = (vec3_t){1.f, 1.f, 0.0f};
	
	quad = create_quad3(&lb, &rb, &lt, &rt);
	
	assert(vec3_equals(&quad->shapes[0]->vertices[0]->vec, &lb));
	assert(vec3_equals(&quad->shapes[0]->vertices[1]->vec, &rb));
	assert(vec3_equals(&quad->shapes[0]->vertices[2]->vec, &lt));
	assert(vec3_equals(&quad->shapes[1]->vertices[0]->vec, &lt));
	assert(vec3_equals(&quad->shapes[1]->vertices[1]->vec, &rb));
	assert(vec3_equals(&quad->shapes[1]->vertices[2]->vec, &rt));
	
	free_mesh(quad);
	
	
	#if 0
		// test create cube
	#endif
	
	vec3_t center = { .5f, .5f, .5f };
	float sidelen = 1.f;
	
	mesh_t * cube = create_cube3_center(&center, sidelen);
	
	//for ( int cntshape = 0; cntshape < cube->cntShapes ; ++cntshape)
	//{
	//	printf("shape [%i]:\n",cntshape);
	//	shape_t * shape = cube->shapes[cntshape];
	//	if (shape == NULL) {
	//		printf("shape is null :(\n");
	//	} else {
	//		printf("%f %f %f\n", shape->vertices[0]->vec.x, shape->vertices[0]->vec.y, shape->vertices[0]->vec.z);
	//		printf("%f %f %f\n", shape->vertices[1]->vec.x, shape->vertices[1]->vec.y, shape->vertices[1]->vec.z);
	//		printf("%f %f %f\n", shape->vertices[2]->vec.x, shape->vertices[2]->vec.y, shape->vertices[2]->vec.z);
	//	}
	//	
	//}
	
	free_mesh(cube);
	
	#ifdef debug
		printf("End test mesh\n");
	#endif	
	return 0;
}