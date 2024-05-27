#include "mesh.h"
#include <stdio.h>

const size_t mesh_size = sizeof(Mesh);
const size_t mesh_ptr_size = sizeof(Mesh*);

Mesh * 
alloc_mesh(const unsigned int meshcount){
	Mesh * newmesh = malloc(mesh_size);
	newmesh->shapes = malloc(meshcount * shape_ptr_size);
	newmesh->cntShapes = meshcount;
	for(unsigned int shape = 0; shape < newmesh->cntShapes; ++shape){
		newmesh->shapes[shape] = NULL;
	}
	mesh_unset_bbox(newmesh);
	return newmesh;
}

void 
free_mesh(Mesh *mesh){
	for(unsigned int shape = 0; shape < mesh->cntShapes; ++shape){
		Shape * curshape = mesh->shapes[shape]; 
		if (curshape != NULL){
			free_shape(curshape);
			free(curshape);
		}
	}
	free(mesh->shapes);
	free(mesh);
}

void 
mat_mul_mesh(Mesh * mesh, const Mat3 * matrix){
	Mesh * cmesh = mesh;
	Shape ** shapes = cmesh->shapes;
	for(unsigned int shape = cmesh->cntShapes; shape-- ;){
		mat_mul_shape(shapes[shape], matrix); 
	}
}

void 
scale_mesh(Mesh * mesh, const float scalex, const float scaley, const float scalez ){
	Mesh * cmesh = mesh;
	Shape ** shapes = cmesh->shapes;
	for(unsigned int shape = cmesh->cntShapes; shape-- ;){
		scale_shape(shapes[shape], scalex, scaley, scalez); 
	}
}

void 
translate_mesh(Mesh * mesh, const float tx, const float ty, const float tz ){
	Mesh * cmesh = mesh;
	Shape ** shapes = cmesh->shapes;
	for(unsigned int shape = cmesh->cntShapes; shape-- ;){
		translate_shape(shapes[shape], tx, ty, tz); 
	}
}

void 
debug_mesh(const Mesh * mesh){
	printf("cnt shapes: %i\n shape informations:\n", mesh->cntShapes);
	for(unsigned int shape = 0; shape < mesh->cntShapes; ++shape){
		debug_shape(mesh->shapes[shape]);
	}
	printf("bbox:\n");
	vec3_print(&mesh->bbox.min);
	vec3_print(&mesh->bbox.max);
}

void 
mesh_unset_bbox(Mesh *mesh){
	vec3_set_values(&mesh->bbox.min, FLT_MAX, FLT_MAX, FLT_MAX);
	vec3_set_values(&mesh->bbox.max, FLT_MIN, FLT_MIN, FLT_MIN);
	mesh->bbox.created = false;
}

void mesh_set_bbox(Mesh *mesh, const float minx, const float miny, 
								 const float minz, const float maxx, 
								 const float maxy, const float maxz){
	vec3_set_values(&mesh->bbox.min, minx, miny, minz);
	vec3_set_values(&mesh->bbox.max, maxx, maxy, maxz);
	mesh->bbox.created = false;
}

void 
mesh_create_bbox(Mesh * mesh){
	Vec3 * bbox_min = &mesh->bbox.min;
	Vec3 * bbox_max = &mesh->bbox.max;
	Vec3 * curvec;
	for(unsigned int shape = mesh->cntShapes; shape-- ;){
		Shape * curshape = mesh->shapes[shape];
		Vertex ** vertices = curshape->vertices;
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
mesh_set_color (Mesh * _mesh, ColorRGB * _color){
	ColorRGB * color = _color;
	Mesh * mesh = _mesh;

	for(unsigned int shape = 0; shape < mesh->cntShapes; ++shape){
		Shape * curshape = mesh->shapes[shape];
		set_shape_color(curshape, color);
	}
}

void 
mesh_color_by_bbox(Mesh * mesh){
	Vec3 * bbox_min = &mesh->bbox.min;
	Vec3 * bbox_max = &mesh->bbox.max;
	Vec3 * curvec;
	ColorRGB * color;
	Vertex * vertex;
	for(unsigned int shape = 0; shape < mesh->cntShapes; ++shape){
		Shape * curshape = mesh->shapes[shape];
		Vertex ** vertices = curshape->vertices;
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

void 
mesh_color_by_bbox2(Mesh * mesh){
	Vec3 * bbox_min = &mesh->bbox.min;
	Vec3 * bbox_max = &mesh->bbox.max;
	Vec3 * curvec;
	ColorRGB * color;
	Vertex * vertex;

	float d_y = ((bbox_max->y - bbox_min->y) * 0.5f);

	for(unsigned int shape = 0; shape < mesh->cntShapes; ++shape){
		Shape * curshape = mesh->shapes[shape];
		Vertex ** vertices = curshape->vertices;
		switch(curshape->cntVertex) {
			case 3:
				vertex = vertices[2];
				curvec = &vertex->vec;
				color = &vertex->color;
				color->b = 0.f;
				if ((curvec->y >= bbox_min->y ) && (curvec->y <= d_y )) {
					color->r = 1.f;
					color->g = interpolate_lin(curvec->y, bbox_min->y, 0.f, d_y, 1.f);
				} else {
					color->g = 1.f;
					color->r = interpolate_lin(curvec->y, d_y, 1.f, bbox_max->y, 0.f);
				}
				//color->r = interpolate_lin(curvec->y, bbox_min->y, 0.2f, bbox_max->y, 1.f);
				//color->g = interpolate_lin(curvec->y, bbox_min->y, 0.2f, bbox_max->y, 1.f);
				//color->b = interpolate_lin(curvec->y, bbox_min->y, 0.2f, bbox_max->y, 1.f);
			case 2:
				vertex = vertices[1];
				curvec = &vertex->vec;
				color = &vertex->color;
				color->b = 0.f;
				if ((curvec->y >= bbox_min->y ) && (curvec->y <= d_y )) {
					color->r = 1.f;
					color->g = interpolate_lin(curvec->y, bbox_min->y, 0.f, d_y, 1.f);
				} else {
					color->g = 1.f;
					color->r = interpolate_lin(curvec->y, d_y, 1.f, bbox_max->y, 0.f);
				}
				//color->r = interpolate_lin(curvec->y, bbox_min->y, 0.2f, bbox_max->y, 1.f);
				//color->g = interpolate_lin(curvec->y, bbox_min->y, 0.2f, bbox_max->y, 1.f);
				//color->b = interpolate_lin(curvec->y, bbox_min->y, 0.2f, bbox_max->y, 1.f);
			case 1:
				vertex = vertices[0];
				curvec = &vertex->vec;
				color = &vertex->color;
				color->b = 0.f;
				if ((curvec->y >= bbox_min->y ) && (curvec->y <= d_y )) {
					color->r = 1.f;
					color->g = interpolate_lin(curvec->y, bbox_min->y, 0.f, d_y, 1.f);
				} else {
					color->g = 1.f;
					color->r = interpolate_lin(curvec->y, d_y, 1.f, bbox_max->y, 0.f);
				}
				//color->r = interpolate_lin(curvec->y, bbox_min->y, 0.2f, bbox_max->y, 1.f);
				//color->g = interpolate_lin(curvec->y, bbox_min->y, 0.2f, bbox_max->y, 1.f);
				//color->b = interpolate_lin(curvec->y, bbox_min->y, 0.2f, bbox_max->y, 1.f);
				break;
		}
	}
}
