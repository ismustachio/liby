#pragma once
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define VECTOR2D_ZERO                                                          \
  { 0, 0 }

// A two dimensional direction vector having float components x and y. Its w
// coordinate it's assumed to be 0.
typedef struct {
  float x;
  float y;
} Vector2D;

// Initializes the vector v with the floating components x and y.
Vector2D *vector2D_init(Vector2D v[static 1], float n1, float n2);

// Returns the magnitude of the vector v.
float vector2D_magnitude(const Vector2D v[static 1]);

// Negates of the vector v and returns it.
Vector2D *vector2D_mut_negate(Vector2D v[static 1]);

// Multiplies the vector v by the inverse of it's magnitude, normalizing it to
// unit length.
Vector2D *vector2D_mut_normalize(Vector2D v[static 1]);

// Returns the dot product between vectors a and b.
float vector2D_dot(const Vector2D a[static 1], const Vector2D b[static 1]);

// Sets the sum of the two vectors a and b to the vector v and returns v.
Vector2D *vector2D_add(const Vector2D a[static 1], const Vector2D b[static 1],
                       Vector2D v[static 1]);

// Add the vector b to a and returns a.
Vector2D *vector2D_mut_add(Vector2D a[static 1], const Vector2D b[static 1]);

// Sets the difference of the two vectors a and b to the vector v and returns v.
Vector2D *vector2D_sub(const Vector2D a[static 1], const Vector2D b[static 1],
                       Vector2D v[static 1]);

// Subtracts the vector b from a and returns a.
Vector2D *vector2D_mut_sub(Vector2D a[static 1], const Vector2D b[static 1]);

// Sets the componentwise product of the vectors a and b to the vector v and
// returns v.
Vector2D *vector2D_mul(const Vector2D a[static 1], const Vector2D b[static 1],
                       Vector2D v[static 1]);

// Sets the vector a componentwise product with the vector b and returns
// a.
Vector2D *vector2D_mut_mul(Vector2D a[static 1], const Vector2D b[static 1]);

//
Vector2D *vector2D_scale(const Vector2D a[static 1], float s,
                         Vector2D v[static 1]);

//
Vector2D *vector2D_mut_scale(Vector2D v[static 1], float s);

// Sets the product of the vector a and the inverse of the scalar s to vector v
// returns v.
Vector2D *vector2D_div(const Vector2D a[static 1], float s,
                       Vector2D v[static 1]);

// Mutates the vector v to the product of the vector v and the inverse of the
// scalar s.
Vector2D *vector2D_mut_div(Vector2D v[static 1], float s);

Vector2D *vector2D_reflect(const Vector2D a[static 1],
                           const Vector2D b[static 1], Vector2D v[static 1]);

Vector2D *vector2D_project(const Vector2D a[static 1],
                           const Vector2D b[static 1], Vector2D v[static 1]);

Vector2D *vector2D_reject(const Vector2D a[static 1],
                          const Vector2D b[static 1], Vector2D v[static 1]);

// A two dimensional point having float components x and y. Its w
// coordinate it's assumed to be 1.
typedef struct {
  float x;
  float y;
} Point2D;

Vector2D *point2D_subP(const Point2D a[static 1], const Point2D b[static 1],
                       Vector2D v[static 1]);

Point2D *point2D_addV(const Point2D a[static 1], const Vector2D b[static 1],
                      Point2D p[static 1]);
Point2D *point2D_subV(const Point2D a[static 1], const Vector2D b[static 1],
                      Point2D p[static 1]);

Point2D *point2D_addP(const Point2D a[static 1], const Point2D b[static 1],
                      Point2D p[static 1]);

// Negates the point p and returns it.
Point2D *point2D_negate(Point2D p[static 1]);
