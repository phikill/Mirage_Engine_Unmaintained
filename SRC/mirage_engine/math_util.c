#include<linmath\linmath.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#include<stdbool.h>

#include<math.h>

#include"math_utils.h"

int random(int min, int max)
{
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}


vec3 *matrix_multiplay(vec3 vector, float matrix[3][3])
{
    vec3  result_vector;
    int i, j; // i = row; j = column;
    printf("\nProduct Matrix of [x]*[y]\n");
    // Load up A[n][n]
    for(i = 0; i<3; i++)
    {
        for (j = 0; j<3; j++)
        {
            result_vector[j] += matrix[j][i] * vector[i];

        }
    }
  return result_vector;

}

float* create_matrix3x3(vec3 x,vec3 y,vec3 z)
{
    float matriz[3][3]; 
    int i, j;

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            matriz[ i ][ j ] = x[i],  y[i], z[i];
        }
    }
    return matriz;
}

vec3* cross_product_vec3(vec3 vect_A, vec3 vect_B)
{
    vec3 cross_P;
    vec3 *cross_proxy_;

    cross_P[0] = (vect_A[1]) * (vect_B[2]) - (vect_A[2]) * (vect_B[1]);
    cross_P[1] = (vect_A[2]) * (vect_B[0]) - (vect_A[0]) * (vect_B[2]);
    cross_P[2] = (vect_A[0]) * (vect_B[1]) - (vect_A[1]) * (vect_B[0]);

    cross_proxy_ = &cross_P;
    return cross_proxy_;
}

void normalize(vec3 p)
{
    float x = p[0];
    float y = p[1];
    float z = p[2];
    vec3 P;
    float w = sqrt( x * x + y * y + z * z );
    P[0] = x /= w;
    P[1] = y /= w;
    P[2] = z /= w;;
    *p = *P;
}

float dot_product_vec3(vec3 vect_A, vec3 vect_B)
{
    int i;
    float product = 0.f;

    // Loop for calculate dot product
    // Loop for calculate dot product
    for(i = 0; i <= 2; ++i)
    {
        product = product + vect_A[i] * vect_B[i];
    }
    return product;
}

int vector3_lenght(vec3 vector)
{
    int len = sizeof(vector)/sizeof(vector[0]);
    return len;
}


int normalize_int(int d) 
{
    int max = 1;
    int min = 0;
    const int t = d < min ? min : d;
    return t > max ? max : t;
}

vec3 *calculate_basis(vec3  vec)
{
    float x = (float)vec[0];
    float y = (float)vec[1];
    float z = (float)vec[2];

    bool b0 = (abs(x) <  abs(y)) && (abs(x) <  abs(z));
    bool b1 = (abs(y) <= abs(x)) && (abs(y) <  abs(z));
    bool b2 = (abs(z) <= abs(x)) && (abs(z) <= abs(y));
    vec3 parallel_basis;
    //normalize(&vec);
    parallel_basis[0] = (float)b0;
    parallel_basis[1] = (float)b1;
    parallel_basis[2] = (float)b2;
    normalize(vec);
    return cross_product_vec3(vec, parallel_basis);
}

vec3 *paralel_basis(vec3  vec)
{
    float x = (float)vec[0];
    float y = (float)vec[1];
    float z = (float)vec[2];

    bool b0 = (abs(x) <  abs(y)) && (abs(x) <  abs(z));
    bool b1 = (abs(y) <= abs(x)) && (abs(y) <  abs(z));
    bool b2 = (abs(z) <= abs(x)) && (abs(z) <= abs(y));
    vec3 *parallel_basis = (vec3 *)malloc(sizeof(vec3));
    if(parallel_basis == NULL) 
    {
        return NULL;
    }
    //normalize(&vec);
    (*parallel_basis)[0] = (float)b0;
    (*parallel_basis)[1] = (float)b1;
    (*parallel_basis)[2] = (float)b2;
    return parallel_basis;
}

void softmax(double *input, size_t size) 
{
    int i;
    double m, sum, constant;

	assert(0 <= size <= sizeof(input) / sizeof(double));

	m = -INFINITY;
	for(i = 0; i < size; ++i) 
    {
		if(m < input[i]) 
        {
			m = input[i];
		}
	}

	sum = 0.0;
	for(i = 0; i < size; ++i) 
    {
		sum += exp(input[i] - m);
	}

	constant = m + log(sum);
	for(i = 0; i < size; ++i) 
    {
		input[i] = exp(input[i] - constant);
	}
}

int numbers_after_decimal(float no)
{

   int i = 0;
   int startCounting = 0;
   int count = 0;

   char c[500];
   sprintf(c, "%g", no);

   for(i = 0; i < strlen(c); i++)
   {
       if(startCounting == 1)
       {
           count ++;
       }
       if(c[i] == '.')
       {
           startCounting = 1;
       }
   }
   return count;
}

double clamp_double(double d, double min, double max) 
{

  const double t = d < min ? min : d;

  return t > max ? max : t;
}

int clamp_int(int d, int min, int max) 
{
  const int t = d < min ? min : d;

  return t > max ? max : t;
}
