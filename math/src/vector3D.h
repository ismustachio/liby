#pragma once
#include <assert.h>
#include <math.h>
#include <stdlib.h>

// A three dimensional direction vector having float components x, y and z. Its
// w coordinate it's assumed to be 0.
typedef struct {
  float x;
  float y;
  float z;
} Vector3D;

// Initializes the vector v with the floating components x and y.
Vector3D *vector3D_init(Vector3D v[static 1], float n1, float n2, float n3);

// Returns the magnitude of the vector v.
float vector3D_magnitude(const Vector3D v[static 1]);

// Negates of the vector v and returns it.
Vector3D *vector3D_mut_negate(Vector3D v[static 1]);

// Multiplies the vector v by the inverse of it's magnitude, normalizing it to
// unit length.
Vector3D *vector3D_mut_normalize(Vector3D v[static 1]);

// Returns the dot product between vectors a and b.
float vector3D_dot(const Vector3D a[static 1], const Vector3D b[static 1]);

// Sets the sum of the two vectors a and b to the vector v and returns v.
Vector3D *vector3D_add(const Vector3D a[static 1], const Vector3D b[static 1],
                       Vector3D v[static 1]);

// Add the vector b to a and returns a.
Vector3D *vector3D_mut_add(Vector3D a[static 1], const Vector3D b[static 1]);

// Sets the difference of the two vectors a and b to the vector v and returns v.
Vector3D *vector3D_sub(const Vector3D a[static 1], const Vector3D b[static 1],
                       Vector3D v[static 1]);

// Subtracts the vector b from a and returns a.
Vector3D *vector3D_mut_sub(Vector3D a[static 1], const Vector3D b[static 1]);

// Sets the componentwise product of the vectors a and b to the vector v and
// returns v.
Vector3D *vector3D_mul(const Vector3D a[static 1], const Vector3D b[static 1],
                       Vector3D v[static 1]);

// Sets the vector a componentwise product with the vector b and returns
// a.
Vector3D *vector3D_mut_mul(Vector3D a[static 1], const Vector3D b[static 1]);

//
Vector3D *vector3D_scale(const Vector3D a[static 1], float s,
                         Vector3D v[static 1]);

//
Vector3D *vector3D_mut_scale(Vector3D v[static 1], float s);

// Sets the product of the vector a and the inverse of the scalar s to vector v
// returns v.
Vector3D *vector3D_div(const Vector3D a[static 1], float s,
                       Vector3D v[static 1]);

// Mutates the vector v to the product of the vector v and the inverse of the
// scalar s.
Vector3D *vector3D_mut_div(Vector3D v[static 1], float s);

Vector3D *vector3D_reflect(const Vector3D a[static 1],
                           const Vector3D b[static 1], Vector3D v[static 1]);

// Sets the vector v to the (a.b)b, which is the projection of a onto b under
// the assumption that the magnitude of b is 1.
Vector3D *vector3D_project(const Vector3D a[static 1],
                           const Vector3D b[static 1], Vector3D v[static 1]);

// Sets the vector v to the (a-a.b)b, which is the rejection of a from b under
// the assumption that the magnitude of b is 1.
Vector3D *vector3D_reject(const Vector3D a[static 1],
                          const Vector3D b[static 1], Vector3D v[static 1]);

// Sets vector v to the cross product between a and b.
Vector3D *vector3D_cross(const Vector3D a[static 1], const Vector3D b[static 1],
                         Vector3D v[static 1]);

// A three dimensional point having float components x, y and z. Its w
// coordinate it's assumed to be 1.
typedef struct {
  float x;
  float y;
  float z;
} Point3D;

Vector3D *point3D_subP(const Point3D a[static 1], const Point3D b[static 1],
                       Vector3D v[static 1]);

Point3D *point3D_addV(const Point3D a[static 1], const Vector3D b[static 1],
                      Point3D p[static 1]);
Point3D *point3D_subV(const Point3D a[static 1], const Vector3D b[static 1],
                      Point3D p[static 1]);

Point3D *point3D_addP(const Point3D a[static 1], const Point3D b[static 1],
                      Point3D p[static 1]);

// Negates the point p and returns it.
Point3D *point3D_negate(Point3D p[static 1]);
