#include "vector3D.h"

Vector3D *vector3D_init(Vector3D v[static 1], float n1, float n2, float n3) {
  v->x = n1;
  v->y = n2;
  v->z = n3;
  return v;
}

Vector3D *vector3D_add(const Vector3D a[static 1], const Vector3D b[static 1], Vector3D v[static 1]) {
  v->x = a->x + b->x;
  v->y = a->y + b->y;
  v->z = a->z + b->z;
  return v;
}

Vector3D *vector3D_mut_add(Vector3D a[static 1], const Vector3D b[static 1]) {
  a->x += b->x;
  a->y += b->y;
  a->z += b->z;
  return a;
}

Vector3D *vector3D_sub(const Vector3D a[static 1], const Vector3D b[static 1], Vector3D v[static 1]) {
  v->x = a->x - b->x;
  v->y = a->y - b->y;
  v->z = a->z - b->z;
  return v;
}

Vector3D *vector3D_mut_sub(Vector3D a[static 1], const Vector3D b[static 1]) {
  a->x -= b->x;
  a->y -= b->y;
  a->z -= b->z;
  return a;
}

Vector3D *vector3D_mul(const Vector3D a[static 1], const Vector3D b[static 1], Vector3D v[static 1]) {
  v->x = a->x * b->x;
  v->y = a->y * b->y;
  v->z = a->z * b->z;
  return v;
}

Vector3D *vector3D_mut_mul(Vector3D a[static 1], const Vector3D b[static 1]) {
  a->x *= b->x;
  a->y *= b->y;
  a->z *= b->z;
  return a;
}

float vector3D_dot(const Vector3D a[static 1], const Vector3D b[static 1]) {
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

Vector3D *vector3D_scale(const Vector3D a[static 1], float s,Vector3D v[static 1]) {
  v->x = a->x*s;
  v->y = a->y*s;
  v->z = a->z*s;
  return v;
}

Vector3D *vector3D_mut_scale(Vector3D v[static 1], float s) {
  v->x *= s;
  v->y *= s;
  v->z *= s;
  return v;
}

Vector3D *vector3D_div(const Vector3D a[static 1], float s,Vector3D v[static 1]) {
  return vector3D_scale(a, s / 1.0, v);
}

Vector3D *vector3D_mut_div(Vector3D v[static 1], float s) {
  return vector3D_mut_scale(v, s / 1.0);
}

Vector3D *vector3D_normalize(Vector3D v[static 1]) {
  double mag = vector3D_magnitude(v);
  v->x /= mag;
  v->y /= mag;
  v->z /= mag;
  return v;
}

Vector3D *vector3D_mut_negate(Vector3D v[static 1]) {
  v->x = -v->x;
  v->y = -v->y;
  v->z = -v->z;
  return v;
}

float vector3D_magnitude(const Vector3D v[static 1]) {
  return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

Vector3D *vector3D_reflect(const Vector3D a[static 1], const Vector3D b[static 1], Vector3D v[static 1]) {
  Vector3D q = {.x = 0, .y = 0};
  vector3D_sub(a, b, &q);
  return vector3D_scale(&q, 2.0 * vector3D_dot(a, b), v);
}

Vector3D *vector3D_project(const Vector3D a[static 1], const Vector3D b[static 1], Vector3D v[static 1]) {
  return vector3D_scale(b, vector3D_dot(a, b) / vector3D_dot(b, b), v);
}

Vector3D *vector3D_reject(const Vector3D a[static 1], const Vector3D b[static 1], Vector3D v[static 1]) {
  Vector3D q = {.x = 0, .y = 0};
  vector3D_scale(b, vector3D_dot(a, b), &q);
  return vector3D_sub(b, vector3D_div(b, vector3D_dot(b, b), &q), v);
}

Vector3D *point3D_subP(const Point3D a[static 1], const Point3D b[static 1], Vector3D v[static 1]) {
  v->x = a->x - b->x;
  v->y = a->y - b->y;
  v->z = a->z - b->z;
  return v;
}

Point3D *point3D_addV(const Point3D a[static 1], const Vector3D b[static 1], Point3D p[static 1]) {
  p->x = a->x + b->x;
  p->y = a->y + b->y;
  p->z = a->z + b->z;
  return p;
}

Point3D *point3D_subV(const Point3D a[static 1], const Vector3D b[static 1], Point3D p[static 1]) {
  p->x = a->x - b->x;
  p->y = a->y - b->y;
  p->z = a->z - b->z;
  return p;
}

Point3D *point3D_addP(const Point3D a[static 1], const Point3D b[static 1], Point3D p[static 1]) {
  p->x = a->x + b->x;
  p->y = a->y + b->y;
  p->z = a->z + b->z;
  return p;
}

Point3D *point3D_mut_negate(Point3D p[static 1]) {
  p->x = -p->x;
  p->y = -p->y;
  p->z = -p->z;
  return p;
}
