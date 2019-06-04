/*
 * Denne a data type for triangles in the unit square, including a function
 * that computes the area of a triangle. Then write a client program that generates
 * random triples of pairs of floats between 0 and 1 and computes empirically
 * the average area of the triangles generated
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define N 20

typedef struct
{
  float x;
  float y;
} point;

typedef struct
{
  point a;
  point b;
  point c;
} triangle;

  
float area(triangle);
float distance(point, point);
int slope(point, point);
bool collinear(point, point, point);
float rand_float(void);

int main(void){
  point a, b, c;
  triangle t;
  int i;
  float sum=0.0;

  srand(time(NULL));
  for (i = 0; i < N; i++) 
    {
      a.x = rand_float();
      a.y = rand_float();
      b.x = rand_float();
      b.y = rand_float();
      c.x = rand_float();
      c.y = rand_float();
      if (!collinear(a, b, c))
	{
	  t.a = a;
	  t.b = b;
	  t.c = c;
	  sum += area(t);
	}
    }
  printf("Average area: %f\n", sum/N);
  return 0;
}

float rand_float()
{
  int r = rand() % 1000;

  return r * 0.001;
}

float distance(point a, point b)
{
  float dx = a.x - b.x, dy = a.y - b.y;
  return sqrt(dx*dx + dy*dy);
}

int slope(point a, point b)
{
  int x = (b.x - a.x) * pow (10, 4);
  int y = (b.y - a.y) * pow (10, 4);

  return x/y;
}
bool collinear(point a, point b, point c)
{
  return (slope(a, b) == slope(b, c));
}

float area(triangle t)
{
  float a, b, c;

  a = distance(t.a, t.b);
  b = distance(t.b, t.c);
  c = distance(t.a, t.c);

  return sqrt((a+b-c)*(a-b+c)*(b+c-a)*(a+b+c))/4;
}