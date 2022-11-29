#include "vector2D.h"

Vector2D *vector2D_init(Vector2D v[static 1], float n1, float n2) {
  v->x = n1;
  v->y = n2;
  return v;
}

Vector2D *vector2D_add(const Vector2D a[static 1], const Vector2D b[static 1], Vector2D v[static 1]) {
  v->x = a->x + b->x;
  v->y = a->y + b->y;
  return v;
}

Vector2D *vector2D_mut_add(Vector2D a[static 1], const Vector2D b[static 1]) {
  a->x += b->x;
  a->y += b->y;
  return a;
}

Vector2D *vector2D_sub(const Vector2D a[static 1], const Vector2D b[static 1], Vector2D v[static 1]) {
  v->x = a->x - b->x;
  v->y = a->y - b->y;
  return v;
}

Vector2D *vector2D_mut_sub(Vector2D a[static 1], const Vector2D b[static 1]) {
  a->x -= b->x;
  a->y -= b->y;
  return a;
}

Vector2D *vector2D_mul(const Vector2D a[static 1], const Vector2D b[static 1], Vector2D v[static 1]) {
  v->x = a->x * b->x;
  v->y = a->y * b->y;
  return v;
}

Vector2D *vector2D_mut_mul(Vector2D a[static 1], const Vector2D b[static 1]) {
  a->x *= b->x;
  a->y *= b->y;
  return a;
}

float vector2D_dot(const Vector2D a[static 1], const Vector2D b[static 1]) {
  return a->x * b->x + a->y * b->y;
}

Vector2D *vector2D_scale(const Vector2D a[static 1], float s,Vector2D v[static 1]) {
  v->x = a->x*s;
  v->y = a->y*s;
  return v;
}

Vector2D *vector2D_mut_scale(Vector2D v[static 1], float s) {
  v->x *= s;
  v->y *= s;
  return v;
}

Vector2D *vector2D_div(const Vector2D a[static 1], float s,Vector2D v[static 1]) {
  return vector2D_scale(a, s / 1.0, v);
}

Vector2D *vector2D_mut_div(Vector2D v[static 1], float s) {
  return vector2D_mut_scale(v, s / 1.0);
}

Vector2D *vector2D_normalize(Vector2D v[static 1]) {
  double mag = vector2D_magnitude(v);
  v->x /= mag;
  v->y /= mag;
  return v;
}

Vector2D *vector2D_mut_negate(Vector2D v[static 1]) {
  v->x = -v->x;
  v->y = -v->y;
  return v;
}

float vector2D_magnitude(const Vector2D v[static 1]) {
  return sqrt(v->x*v->x + v->y*v->y);
}

Vector2D *vector2D_reflect(const Vector2D a[static 1], const Vector2D b[static 1], Vector2D v[static 1]) {
  Vector2D q = {.x = 0, .y = 0};
  vector2D_sub(a, b, &q);
  return vector2D_scale(&q, 2.0 * vector2D_dot(a, b), v);
}

Vector2D *vector2D_project(const Vector2D a[static 1], const Vector2D b[static 1], Vector2D v[static 1]) {
  return vector2D_scale(b, vector2D_dot(a, b) / vector2D_dot(b, b), v);
}

Vector2D *vector2D_reject(const Vector2D a[static 1], const Vector2D b[static 1], Vector2D v[static 1]) {
  Vector2D q = {.x = 0, .y = 0};
  vector2D_scale(b, vector2D_dot(a, b), &q);
  return vector2D_sub(b, vector2D_div(b, vector2D_dot(b, b), &q), v);
}

Vector2D *point2D_subP(const Point2D a[static 1], const Point2D b[static 1], Vector2D v[static 1]) {
  v->x = a->x - b->x;
  v->y = a->y - b->y;
  return v;
}

Point2D *point2D_addV(const Point2D a[static 1], const Vector2D b[static 1], Point2D p[static 1]) {
  p->x = a->x + b->x;
  p->y = a->y + b->y;
  return p;
}

Point2D *point2D_subV(const Point2D a[static 1], const Vector2D b[static 1], Point2D p[static 1]) {
  p->x = a->x - b->x;
  p->y = a->y - b->y;
  return p;
}

Point2D *point2D_addP(const Point2D a[static 1], const Point2D b[static 1], Point2D p[static 1]) {
  p->x = a->x + b->x;
  p->y = a->y + b->y;
  return p;
}

Point2D *point2D_mut_negate(Point2D p[static 1]) {
  p->x = -p->x;
  p->y = -p->y;
  return p;
}
