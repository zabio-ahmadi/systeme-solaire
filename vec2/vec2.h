#ifndef _VEC2_H_
#define _VEC2_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct _vec2
{
    double x, y;
} vec2;

typedef struct _coordinates
{
    uint32_t row, column;
} coordinates;

vec2 vec2_create(double x_, double y_);

vec2 vec2_create_zero();

vec2 vec2_add(vec2 lhs, vec2 rhs);

vec2 vec2_sub(vec2 lhs, vec2 rhs);

vec2 vec2_mul(double scalar, vec2 rhs);

double vec2_dot(vec2 lhs, vec2 rhs);

double vec2_norm_sqr(vec2 v);

double vec2_norm(vec2 v);

vec2 vec2_normalize(vec2 v);

bool vec2_is_approx_equal(vec2 lhs, vec2 rhs, double eps);

coordinates vec2_to_coordinates(vec2 v, uint32_t width, uint32_t height);

void vec2_print(vec2 v);

#endif
