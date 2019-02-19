#include "mesh_builder.h"
/**
shape_t * create_shape_point3(vec3_t *p1);
shape_t * create_shape_line3(vec3_t *p1, vec3_t *p2);
shape_t * create_shape_triangle3(vec3_t *p1, vec3_t *p2, vec3_t *p3);
*/
mesh_t *
create_point3(const vec3_t *p){
	mesh_t * point = alloc_mesh(1);
	point->shapes[0] = create_shape_point3(p);
	return point;
}

mesh_t * 
create_line3(const vec3_t *p1, const vec3_t *p2){
	mesh_t * line = alloc_mesh(1);
	line->shapes[0] = create_shape_line3(p1, p2);
	return line;
}

mesh_t * 
create_triangle3(const vec3_t *p1, const vec3_t *p2, const vec3_t *p3){
	mesh_t * triangle = alloc_mesh(1);
	triangle->shapes[0] = create_shape_triangle3(p1, p2, p3);
	return triangle;
}

mesh_t * 
create_quad3(const vec3_t *lb, const vec3_t *rb, const vec3_t *lt, const vec3_t *rt){
	mesh_t * quad = alloc_mesh(2);
	
	quad->shapes[0] = create_shape_triangle3(lb, rb, lt);
	quad->shapes[1] = create_shape_triangle3(lt, rb, rt);
	crgb_crgb_copy(&quad->shapes[1]->vertices[0]->color, &quad->shapes[0]->vertices[2]->color);
	quad->shapes[1]->vertices[2]->color.r = 1.0f;
	quad->shapes[1]->vertices[2]->color.g = 1.0f;
	quad->shapes[1]->vertices[2]->color.b = 1.0f;
	
	return quad;
}

mesh_t * 
create_cube3_center(const vec3_t *center, const float sidelen){
	return create_square_block(center, sidelen, sidelen, sidelen, 1, 1, 1);
}

mesh_t * create_square_block(const vec3_t *center, const float width, const float height, const float depth,
							const unsigned int cntx, const unsigned int cnty, const unsigned int cntz){
	unsigned int needshapes = (cntx * cnty * 4);
	needshapes += ( cntz * cnty * 4 ); 
	needshapes += ( cntz * cntx * 4 );
	mesh_t * square_block = alloc_mesh(needshapes);
	const float hw = width  * 0.5f;
	const float hh = height * 0.5f;
	const float hd = depth  * 0.5f;
	const float wseg = width / cntx;
	const float hseg = height / cnty;
	const float dseg = depth / cntz;
	unsigned int curx = 0;
	unsigned int cury = 0;
	unsigned int curz = 0;
	vec3_t p1,p2,p3,p4,start;
	unsigned int curShape = 0;
	//every side segment could be mirrored front to back, left to right, top to bottom
	//front + back
	vec3_set_values(&start, center->x - hw, center->y - hh, center->z + hd); //TODO set startvector
	float temp2 = start.z - depth; //used for back z
	do {
		curx = 0;  
		do {
			//front
			vec3_set_values(&p1, (start.x +	(curx * wseg))   ,  start.y + (cury * hseg)    , start.z);
			vec3_set_values(&p2, (start.x + ((curx+1) * wseg)),  start.y + (cury * hseg)    , start.z);
			vec3_set_values(&p3, (start.x +  (curx * wseg)),  start.y + ((cury+1) * hseg), start.z);
			vec3_set_values(&p4, (start.x + ((curx+1) * wseg)),  start.y + ((cury+1) * hseg), start.z);
			
			square_block->shapes[curShape++] = create_shape_triangle3(&p1, &p2, &p3);
			square_block->shapes[curShape++] = create_shape_triangle3(&p3, &p2, &p4);
			 
			//back
			p1.z = temp2;
			p2.z = temp2;
			p3.z = temp2;
			p4.z = temp2;
			
			square_block->shapes[curShape++] = create_shape_triangle3(&p2, &p1, &p4);
			square_block->shapes[curShape++] = create_shape_triangle3(&p4, &p1, &p3);
			
			curx++;
		} while (curx < cntx);
		cury++;
	} while (cury < cnty);
	
	//left + right
	cury = 0;
	vec3_set_values(&start, center->x - hw, center->y - hh, center->z - hd); //TODO set startvector
	temp2 = start.x + width; //used for right x
	do {
		curz = 0;
		do {
			//left
			vec3_set_values(&p1, start.x ,  start.y + (cury * hseg)    , start.z + (curz * dseg));
			vec3_set_values(&p2, start.x ,  start.y + (cury * hseg)    , start.z + ((curz+1) * dseg));
			vec3_set_values(&p3, start.x ,  start.y + ((cury+1) * hseg), start.z + (curz * dseg));
			vec3_set_values(&p4, start.x ,  start.y + ((cury+1) * hseg), start.z + ((curz+1) * dseg));
			square_block->shapes[curShape++] = create_shape_triangle3(&p1, &p2, &p3);
			square_block->shapes[curShape++] = create_shape_triangle3(&p3, &p2, &p4);

			//right
			p1.x = temp2;
			p2.x = temp2;
			p3.x = temp2;
			p4.x = temp2;
			
			square_block->shapes[curShape++] = create_shape_triangle3(&p2, &p1, &p4);
			square_block->shapes[curShape++] = create_shape_triangle3(&p4, &p1, &p3);
			
			++curz;
		} while (curz < cntz);
		++cury;
	} while (cury < cnty);
	
	//top + bottom
	curz = 0;
	vec3_set_values(&start, center->x - hw, center->y + hh, center->z + hd);
	temp2 = start.y - height; //used bottom y
	do {
		curx = 0;
		do {
			//top
			vec3_set_values(&p1, start.x + (curx * wseg),  start.y, start.z - (curz * dseg));
			vec3_set_values(&p2, start.x + ((curx+1) * wseg),  start.y, start.z - (curz * dseg));
			vec3_set_values(&p3, start.x + (curx * wseg),  start.y, start.z - ((curz+1) * dseg));
			vec3_set_values(&p4, start.x + ((curx+1) * wseg),  start.y, start.z - ((curz+1) * dseg));
			square_block->shapes[curShape++] = create_shape_triangle3(&p1, &p2, &p3);
			square_block->shapes[curShape++] = create_shape_triangle3(&p3, &p2, &p4);

			//bottom
			p1.y = temp2;
			p2.y = temp2;
			p3.y = temp2;
			p4.y = temp2;
			square_block->shapes[curShape++] = create_shape_triangle3(&p2, &p1, &p4);
			square_block->shapes[curShape++] = create_shape_triangle3(&p4, &p1, &p3);
	
			++curx;
		} while (curx < cntx);
		++curz;
	} while (curz < cntz);

	return square_block;
}

mesh_t * 
create_raster(const float linelen){
	int lines = 5;
	const float linestep = 0.5f;
	mesh_t * raster = alloc_mesh(22);
	const cRGB_t linecolor = {.5f, 0.5f, 0.5f};
	vec3_t startvec, endvec;
	
	int curshape = 0;
	for(int x = -lines; x <= lines; ++x ) {
		startvec = (vec3_t){ linestep*x , 0.0f, -linelen };
		endvec = (vec3_t){ linestep*x , 0.0f, linelen };
		raster->shapes[curshape] = create_shape_line3(&startvec, &endvec);
		set_shape_color(raster->shapes[curshape], &linecolor);
		curshape++;
	}
	
	for(int z = -lines; z <= lines; ++z ) {
		startvec = (vec3_t){ -linelen  , 0.0f, linestep*z};
		endvec = (vec3_t){ linelen , 0.0f,  linestep*z};
		raster->shapes[curshape] = create_shape_line3(&startvec, &endvec);
		set_shape_color(raster->shapes[curshape], &linecolor);
		curshape++;
	}
	
	return raster;
}

mesh_t * 
create_point_raster(){
	const float pdiff = 0.08f;
	const int start = 10;
	const int startx = 10;
	mesh_t * raster = alloc_mesh(((2*startx)+1)*((2*startx)+1)*((2*start)+1));
	int curshape = 0;
	vec3_t curvec;
	for( int x = -startx; x <= startx ;++x ){
		for( int y = -start; y <= start ;++y ){
			for( int z = -startx; z <= startx ;++z ){
				curvec = (vec3_t){x*pdiff, y*pdiff, z*pdiff};
				raster->shapes[curshape] = create_shape_point3(&curvec);
				++curshape;
			}
		}
	}
	return raster;
}

mesh_t * 
createsphere(const float radius, const unsigned int longs, const unsigned int lats){
	const float degreelong = 180.f / longs;
    const float degreelats = 360.f / lats;
	float curlongdeg = 90.f;
	float curlatdeg = 0.f;
	const vec3_t startvec = {radius, 0, 0};
    mesh_t * sphere = alloc_mesh(longs * lats * 2);
	int curShape = 0;
	
	vec3_t p1, p2, p3, p4;
	float nextlongdegree, nextlatdegree;
	const float longcolorstep = 1.f / longs;
	
	unsigned int curlong = 0;
	
	cRGB_t color = { 0.f, 0.f, 0.f };
	mat3_t z_rot_matrix;
	mat3_t z_rot_matrix_2;
	mat3_t y_rot_matrix;
	mat3_t y_rot_matrix_2;
	mat3_t rotmat;
	do {
		nextlongdegree = curlongdeg - degreelong;

		create_rot_z_mat_dest(&z_rot_matrix, curlongdeg);
		create_rot_z_mat_dest(&z_rot_matrix_2, nextlongdegree);
		curlatdeg = 0.f;
		unsigned int curlat = 0;
		do {
			nextlatdegree = curlatdeg + degreelats;

			create_rot_y_mat_dest(&y_rot_matrix, curlatdeg);
			create_rot_y_mat_dest(&y_rot_matrix_2, nextlatdegree);

			mat3_mul_dest(&rotmat, &y_rot_matrix, &z_rot_matrix_2);
			mat_vec_mul_3_dest(&p1, &rotmat, &startvec);
			
			mat3_mul_dest(&rotmat, &y_rot_matrix_2, &z_rot_matrix_2);
			mat_vec_mul_3_dest(&p2, &rotmat, &startvec);

			mat3_mul_dest(&rotmat, &y_rot_matrix, &z_rot_matrix);
			mat_vec_mul_3_dest(&p3, &rotmat, &startvec);
			
			mat3_mul_dest(&rotmat, &y_rot_matrix_2, &z_rot_matrix);
			mat_vec_mul_3_dest(&p4, &rotmat, &startvec);
			
			sphere->shapes[curShape] = create_shape_triangle3(&p3, &p2, &p4);
			set_shape_color(sphere->shapes[curShape], &color);
			++curShape;
			sphere->shapes[curShape] = create_shape_triangle3(&p1, &p2, &p3);
			set_shape_color(sphere->shapes[curShape], &color);
			++curShape;

			curlatdeg += degreelats;
			++curlat;
		} while (curlat < lats);
		curlongdeg -= degreelong;
		++curlong;
		color.r += longcolorstep;
		color.g += longcolorstep;
	} while (curlong < longs);
	return sphere;
}

mesh_t * 
createcylinder(const float radius, const float height, const unsigned int longs, const unsigned int lats, 
			   const bool showtop, const bool showbottom) {
	unsigned int needshapes = (longs * lats * 2);
	if (showtop) { needshapes+=lats; }
	if (showbottom) { needshapes+=lats; }
	mesh_t * cylinder = alloc_mesh(needshapes);
	const float degreelats = 360.f / lats;
	const float heightseg = height / longs;
	const vec3_t startvec = {radius, 0.f, 0.f};
	const vec3_t centerbottom = {0.f, 0.f, 0.f};
	const vec3_t centertop = {0.f, height, 0.f};
	unsigned int curlat = 0;
	unsigned int curShape = 0;
	float curdegreelats = 0.f;
	vec3_t p1, p2, p3, p4, curvec, curvecnext;
	
	mat3_t y_rot_matrix;
	mat3_t y_rot_matrix_2;
	do {
		unsigned int curlong = 0;
		float curheight = 0.f;
		
		do {
			
			vec3_copy_dest(&curvec, &startvec);
			curvec.y = curheight;
			
			vec3_copy_dest(&curvecnext, &startvec);
			curvecnext.y = (curheight + heightseg);;
	
			create_rot_y_mat_dest(&y_rot_matrix, curdegreelats);
			create_rot_y_mat_dest(&y_rot_matrix_2, curdegreelats + degreelats);
			
			mat_vec_mul_3_dest(&p1, &y_rot_matrix, &curvec);
			mat_vec_mul_3_dest(&p2, &y_rot_matrix_2, &curvec);
			mat_vec_mul_3_dest(&p3, &y_rot_matrix, &curvecnext);
			mat_vec_mul_3_dest(&p4, &y_rot_matrix_2, &curvecnext);
			
			cylinder->shapes[curShape] = create_shape_triangle3(&p1, &p2, &p3);
			++curShape;
			cylinder->shapes[curShape] = create_shape_triangle3(&p3, &p2, &p4);
			++curShape;
			
			//do bottom
			if ( showbottom && (curlong == 0) ) {
				cylinder->shapes[curShape] = create_shape_triangle3(&p2, &p1, &centerbottom);
				++curShape;
			}
			//EO bottom
			
			++curlong;
			curheight += heightseg;
			
			//do top
			if ( showtop && (curlong == longs) ){
				cylinder->shapes[curShape] = create_shape_triangle3(&p3, &p4, &centertop);
				++curShape;
			}
			//EO top
			
		} while ( curlong < longs );
		curdegreelats += degreelats;
		++curlat;
	} while ( curlat < lats );
	return cylinder;
}

mesh_t * 
createcone(const float radius, const float height, const unsigned int lats, const bool showbottom){
	unsigned int needshapes = lats;
	if (showbottom) { needshapes+=lats; }
	mesh_t * cone = alloc_mesh(needshapes);
	const float degreelats = 360.f / lats;
	const vec3_t startvec = {radius, 0.f, 0.f};
	const vec3_t centerbottom = {0.f, 0.f, 0.f};
	const vec3_t centertop = {0.f, height, 0.f};
	unsigned int curlat = 0;
	unsigned int curShape = 0;
	float curdegreelats = 0.f;
	vec3_t p1, p2, curvec;
	mat3_t rot_matrix;

	do {		
		//+++++++++++
		vec3_copy_dest(&curvec, &startvec);

		create_rot_y_mat_dest(&rot_matrix, curdegreelats);
		mat_vec_mul_3_dest(&p1, &rot_matrix, &curvec);

		create_rot_y_mat_dest(&rot_matrix, curdegreelats + degreelats);
		mat_vec_mul_3_dest(&p2, &rot_matrix, &curvec);
		
		cone->shapes[curShape] = create_shape_triangle3(&centertop, &p1, &p2);
		++curShape;
		
		//do bottom
		if ( showbottom ) {
			cone->shapes[curShape] = create_shape_triangle3(&p2, &p1, &centerbottom);
			++curShape;
		}
		//+++++++++++
			
		curdegreelats += degreelats;
		++curlat;
	} while ( curlat < lats );
	return cone;
}

mesh_t * 
createpath(const float radius, const int cntelements, const float height, const int longs, const float scaleend) {
	int ang_max_x = 32; 
	int ang_max_y = 31; 
	int ang_max_z = 30;
	
    vec3_t zerovec = {0.f, 0.f, 0.f};
    vec3_t startvec = zerovec;
    vec3_t startvecring = {radius, 0.f, 0.f};
    int curelement = 0;
    float heightseg = height/cntelements;
	
	
    float curscaling = 1.0;
	float scalestep = (curscaling - scaleend) / cntelements;
	
	mesh_t * path = alloc_mesh(cntelements * longs * 2);

	mat3_t * roty;
	mat3_t * rotz;
	mat3_t * rotmat;
	
	vec3_t *p1;
	vec3_t *p2;
	vec3_t *p3;
	vec3_t *p4;
	
	int curShape = 0;
	float degreelong = 360.f / longs;
	srand ( time(NULL) );
	while (curelement < cntelements ) {
        //create random rotation mat => rotmat = createrandomxyzmatrix(xangles, yangles, zangles)
		rotmat = create_rot_x_mat(rand_path_deg(ang_max_x));
		roty = create_rot_y_mat(rand_path_deg(ang_max_y));
		mat3_mul(rotmat, roty);
		rotz = create_rot_z_mat(rand_path_deg(ang_max_z));
		mat3_mul(rotmat, rotz);

		//rotate base vec
		vec3_t basevec = {0.f, heightseg, 0.f};
		mat_vec_mul_3(rotmat, &basevec);
		
		free(roty);
		free(rotz);
		free(rotmat);
		
        vec3_t endvec;
		vec3_add_dest(&endvec, &startvec, &basevec);

        startvec = endvec;

        //calc ring
		
        vec3_t curvec = startvecring;
        int curlong = 0;
        float curlongdeg = 0.f;

        vec3_t scalevec = {curscaling, 1.0, curscaling};

        while ((curlongdeg + degreelong) <= 360.f) {
            mat3_t * y_rot_matrix = create_rot_y_mat(curlongdeg);
            mat3_t * y_rot_matrix_2 = create_rot_y_mat(curlongdeg + degreelong);
			
			#if 0
				//P1 und P2 sind die p3 und p4 des vorgänger rings. wenn nich vorhanden dann neu berechnen(erster ring)
			#endif
            if (curelement == 0) {
                p1 = vec3_copy_new(&curvec);
				mat_vec_mul_3(y_rot_matrix, p1);
				p2 = vec3_copy_new(&curvec);
				mat_vec_mul_3(y_rot_matrix_2, p2);
			} else {
				int pasttriindx =  curShape - (longs*2) + 1;
				p1 = vec3_copy_new(&path->shapes[pasttriindx]->vertices[0]->vec);
				p2 = vec3_copy_new(&path->shapes[pasttriindx]->vertices[2]->vec);
			}
			
			#if 0
				//p3 und p4 sind multiplikation vom base vector und das addiert von p1 und p2 des letzten rings
			#endif
            p3 = vec3_add_new(p1, &basevec);
            p4 = vec3_add_new(p2, &basevec);

			#if 0
				//scaling current vector
			#endif
			vec3_scale_dest(p3, scalevec.x, 1.f, scalevec.z);
			vec3_scale_dest(p4, scalevec.x, 1.f, scalevec.z);
			
			path->shapes[curShape] = create_shape_triangle3(p1, p2, p3);
			++curShape;
			path->shapes[curShape] = create_shape_triangle3(p3, p2, p4);
			++curShape;
			
            curlongdeg += degreelong;
            ++curlong;
			free(y_rot_matrix);
			free(y_rot_matrix_2);
			free(p1);
			free(p2);
			free(p3);
			free(p4);
		}
		curscaling -= scalestep;
        ++curelement;
	}
	return path;
}