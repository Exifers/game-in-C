#ifndef VECTOR_H
#define VECTOR_H

struct vector {
  float x;
  float y;
};


struct vector vector_create(float x, float y);
void vector_add(struct vector *this, struct vector *other);
void vector_sub(struct vector *this, struct vector *other);
void vector_divf(struct vector *this, float coef);
void vector_cpy(struct vector *this, struct vector *other);
void vector_mulf(struct vector *this, float coef);
void vector_print(struct vector *this);

#endif /* VECTOR_H */
