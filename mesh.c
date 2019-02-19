#include "mesh.h"
#include <stdio.h>

const size_t mesh_size = sizeof(mesh_t);
const size_t mesh_ptr_size = sizeof(mesh_t*);

mesh_t * 
alloc_mesh(const unsigned int meshcount){
	mesh_t * newmesh = malloc(mesh_size);
	newmesh->shapes = malloc(meshcount * shape_ptr_size);
	newmesh->cntShapes = meshcount;
	for(unsigned int shape = 0; shape < newmesh->cntShapes; ++shape){
		newmesh->shapes[shape] = NULL;
	}
	mesh_unset_bbox(newmesh);
	return newmesh;
}

void 
free_mesh(mesh_t *mesh){
	for(unsigned int shape = 0; shape < mesh->cntShapes; ++shape){
		shape_t * curshape = mesh->shapes[shape]; 
		if (curshape != NULL){
			free_shape(curshape);
			free(curshape);
		}
	}
	free(mesh->shapes);
	free(mesh);
}

void 
mat_mul_mesh(mesh_t * mesh, const mat3_t * matrix){
	mesh_t * cmesh = mesh;
	shape_t ** shapes = cmesh->shapes;
	for(unsigned int shape = cmesh->cntShapes; shape-- ;){
		mat_mul_shape(shapes[shape], matrix); 
	}
}

void 
scale_mesh(mesh_t * mesh, const float scalex, const float scaley, const float scalez ){
	mesh_t * cmesh = mesh;
	shape_t ** shapes = cmesh->shapes;
	for(unsigned int shape = cmesh->cntShapes; shape-- ;){
		scale_shape(shapes[shape], scalex, scaley, scalez); 
	}
}

void 
translate_mesh(mesh_t * mesh, const float tx, const float ty, const float tz ){
	mesh_t * cmesh = mesh;
	shape_t ** shapes = cmesh->shapes;
	for(unsigned int shape = cmesh->cntShapes; shape-- ;){
		translate_shape(shapes[shape], tx, ty, tz); 
	}
}

void 
debug_mesh(const mesh_t * mesh){
	printf("cnt shapes: %i\n shape informations:\n", mesh->cntShapes);
	for(unsigned int shape = 0; shape < mesh->cntShapes; ++shape){
		debug_shape(mesh->shapes[shape]);
	}
	printf("bbox:\n");
	vec3_print(&mesh->bbox.min);
	vec3_print(&mesh->bbox.max);
}

void 
mesh_unset_bbox(mesh_t *mesh){
	vec3_set_values(&mesh->bbox.min, FLT_MAX, FLT_MAX, FLT_MAX);
	vec3_set_values(&mesh->bbox.max, FLT_MIN, FLT_MIN, FLT_MIN);
	mesh->bbox.created = false;
}

void mesh_set_bbox(mesh_t *mesh, const float minx, const float miny, 
								 const float minz, const float maxx, 
								 const float maxy, const float maxz){
	vec3_set_values(&mesh->bbox.min, minx, miny, minz);
	vec3_set_values(&mesh->bbox.max, maxx, maxy, maxz);
	mesh->bbox.created = false;
}

void 
mesh_create_bbox(mesh_t * mesh){
	vec3_t * bbox_min = &mesh->bbox.min;
	vec3_t * bbox_max = &mesh->bbox.max;
	vec3_t * curvec;
	for(unsigned int shape = mesh->cntShapes; shape-- ;){
		shape_t * curshape = mesh->shapes[shape];
		vertex_t ** vertices = curshape->vertices;
		switch(curshape->cntVertex) {
			case 3:
				curvec = &vertices[2]->vec;
				bbox_min->x = fminf(bbox_min->x, curvec->x); 
				bbox_min->y = fminf(bbox_min->y, curvec->y);
				bbox_min->z = fminf(bbox_min->z, curvec->z);
				bbox_max->x = fmaxf(bbox_max->x, curvec->x);
				bbox_max->y = fmaxf(bbox_max->y, curvec->y);
				bbox_max->z = fmaxf(bbox_max->z, curvec->z);
			case 2:
				curvec = &vertices[1]->vec;
				bbox_min->x = fminf(bbox_min->x, curvec->x); 
				bbox_min->y = fminf(bbox_min->y, curvec->y);
				bbox_min->z = fminf(bbox_min->z, curvec->z);
				bbox_max->x = fmaxf(bbox_max->x, curvec->x);
				bbox_max->y = fmaxf(bbox_max->y, curvec->y);
				bbox_max->z = fmaxf(bbox_max->z, curvec->z);
			case 1:
				curvec = &vertices[0]->vec;
				bbox_min->x = fminf(bbox_min->x, curvec->x); 
				bbox_min->y = fminf(bbox_min->y, curvec->y);
				bbox_min->z = fminf(bbox_min->z, curvec->z);
				bbox_max->x = fmaxf(bbox_max->x, curvec->x);
				bbox_max->y = fmaxf(bbox_max->y, curvec->y);
				bbox_max->z = fmaxf(bbox_max->z, curvec->z);
				break;
		}
	}
	mesh->bbox.created = true;
}

void 
mesh_color_by_bbox(mesh_t * mesh){
	vec3_t * bbox_min = &mesh->bbox.min;
	vec3_t * bbox_max = &mesh->bbox.max;
	vec3_t * curvec;
	cRGB_t * color;
	vertex_t * vertex;
	for(unsigned int shape = 0; shape < mesh->cntShapes; ++shape){
		shape_t * curshape = mesh->shapes[shape];
		vertex_t ** vertices = curshape->vertices;
		switch(curshape->cntVertex) {
			case 3:
				vertex = vertices[2];
				curvec = &vertex->vec;
				color = &vertex->color;
				color->r = interpolate_lin(curvec->x, bbox_min->x, 0.f, bbox_max->x, 1.f);
				color->g = interpolate_lin(curvec->y, bbox_min->y, 0.f, bbox_max->y, 1.f);
				color->b = interpolate_lin(curvec->z, bbox_min->z, 0.f, bbox_max->z, 1.f);
			case 2:
				vertex = vertices[1];
				curvec = &vertex->vec;
				color = &vertex->color;
				color->r = interpolate_lin(curvec->x, bbox_min->x, 0.f, bbox_max->x, 1.f);
				color->g = interpolate_lin(curvec->y, bbox_min->y, 0.f, bbox_max->y, 1.f);
				color->b = interpolate_lin(curvec->z, bbox_min->z, 0.f, bbox_max->z, 1.f);
			case 1:
				vertex = vertices[0];
				curvec = &vertex->vec;
				color = &vertex->color;
				color->r = interpolate_lin(curvec->x, bbox_min->x, 0.f, bbox_max->x, 1.f);
				color->g = interpolate_lin(curvec->y, bbox_min->y, 0.f, bbox_max->y, 1.f);
				color->b = interpolate_lin(curvec->z, bbox_min->z, 0.f, bbox_max->z, 1.f);
				break;
		}
	}
}
