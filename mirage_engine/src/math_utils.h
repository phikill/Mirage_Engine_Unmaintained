#pragma once

#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#include <linmath\linmath.h>

typedef struct
{
 float cos[360];        //Save sin cos in values 0-360 degrees
 float sin[360];
}math;

float dot_product_vec3(vec3 vect_A, vec3 vect_B);
// Function to find
// cross product of two vector array.
vec3* cross_product_vec3(vec3 vect_A, vec3 vect_B);

void normalize( vec3 p_ );

float* create_matrix3x3( vec3 x,vec3 y,vec3 z );
vec3 *paralel_basis( vec3  vec );

vec3 *matrix_multiplay( vec3 vector, float matrix[3][3]);
int vector3_lenght(vec3 vector);
int normalize_int(int val);
vec3 *calculate_basis( vec3  N_ );
void   softmax(double* input, size_t size);
int numbers_after_decimal(float no);
double clamp_double(double d, double min, double max);

int random(int min, int max);

int clamp_int(int d, int min, int max);

#endif

