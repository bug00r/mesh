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
	
	float waterfall_data[240] = { 
		0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.010309f,0.041237f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.989691f,0.773196f,0.000000f,0.000000f,0.350515f,0.030928f,0.515464f,0.000000f,0.979381f,0.876289f,0.000000f,0.000000f,0.412371f,0.020619f,0.659794f,0.000000f,0.989583f,0.906250f,0.000000f,0.000000f,0.354167f,0.197917f,0.697917f,0.000000f,0.989691f,0.948454f,0.000000f,0.010309f,0.783505f,0.360825f,0.773196f,0.000000f,0.979381f,0.958763f,0.000000f,0.010309f,0.721649f,0.268041f,0.804124f,0.000000f,0.989691f,0.969072f,0.000000f,0.000000f,0.742268f,0.412371f,0.762887f,0.000000f,1.000000f,0.938144f,0.000000f,0.092784f,0.989691f,0.608247f,0.927835f,0.000000f,0.989362f,1.000000f,0.000000f,0.095745f,0.914894f,0.531915f,0.904255f,0.000000f,1.000000f,0.989796f,0.000000f,0.040816f,0.938776f,0.693878f,0.948980f,0.000000f,1.000000f,1.000000f,0.000000f,0.247423f,0.989691f,0.762887f,0.969072f,0.000000f,1.000000f,1.000000f,0.000000f,0.312500f,0.989583f,0.750000f,0.968750f,0.000000f,1.000000f,1.000000f,0.000000f,0.239583f,1.000000f,0.843750f,0.958333f,0.000000f,1.000000f,1.000000f,0.000000f,0.479167f,1.000000f,0.885417f,1.000000f,0.000000f,1.000000f,1.000000f,0.000000f,0.391753f,1.000000f,0.793814f,0.989691f,0.000000f,1.000000f,1.000000f,0.000000f,0.593750f,1.000000f,0.927083f,1.000000f,0.000000f,1.000000f,1.000000f,0.000000f,0.625000f,1.000000f,0.989583f,1.000000f,0.000000f,1.000000f,1.000000f,0.000000f,0.731959f,0.979381f,0.989691f,1.000000f,0.000000f,1.000000f,1.000000f,0.010417f,0.802083f,0.989583f,1.000000f,0.989583f,0.000000f,1.000000f,1.000000f,0.000000f,0.865979f,1.000000f,1.000000f,1.000000f,0.000000f,1.000000f,1.000000f,0.000000f,0.750000f,1.000000f,0.979167f,1.000000f,0.000000f,1.000000f,1.000000f,0.000000f,0.865979f,1.000000f,1.000000f,1.000000f
	};

	mesh_t * map = create_hmap_from_array(&waterfall_data[0], 30, 8);

	mesh_create_bbox(map);
	mesh_color_by_bbox(map);

	#ifdef debug
		//debug_mesh(map);
	#endif
	
	free_mesh(map);

	//points forming the letter T
	vec3_t points[8] = { {5.f, .0f, .0f} , { 5.f, 10.f, .0f}, { .0f, 10.f, .0f}  , { .0f, 14.f, .0f}, 
						  {14.f, 14.f, .0f}, { 14.f, 10.f, .0f}, { 9.f, 10.f, .0f}, { 9.f, .0f, .0f}};


	shape_t *polygon_shape = create_shape_polygon3(points, 8);

	mesh_t *polygon = create_polygon3(points, 8);
	mesh_t *polygon2 = create_polygon_shape(polygon_shape);

	assert(polygon != NULL);
	assert(polygon2 != NULL);

	#ifdef debug
		printf("POLYGON 1 shapes: %i\n", polygon->cntShapes);
		printf("POLYGON 2 shapes: %i\n", polygon2->cntShapes);
	#endif

	assert(polygon->cntShapes == 6);
	assert(polygon2->cntShapes == 6);


	#ifdef debug
		printf("POLYGON 1\n\n");
		debug_mesh(polygon);
		printf("POLYGON 2\n\n");
		debug_mesh(polygon2);
	#endif

	free_shape(polygon_shape);
	free(polygon_shape);

	free_mesh(polygon);
	free_mesh(polygon2);

	#ifdef debug
		printf("End test mesh\n");
	#endif	
	return 0;
}