/*
 * Add a function to the point data type (Programs 3.3 and 3.4) that
 * determines whether or not three points are collinear, to within a numerical
 * tolerance of 10-4  Assume that the points are all in the unit square.
 */
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct
{
  float x;
  float y;
} point;

float distance(point, point);
int slope(point, point);
bool collinear(point, point, point);


int main(void) {
  point p1, p2, p3;

  printf("1st point: ");
  scanf("%f %f", &p1.x, &p1.y);
  printf("2nd point: ");
  scanf("%f %f", &p2.x, &p2.y);
  printf("3rd point: ");
  scanf("%f %f", &p3.x, &p3.y);
  if (collinear(p1, p2, p3))
    printf("The points are collinear\n");
  else
    printf("The points are not collinear\n");
    
  return 0;
}

float distance(point p1, point p2)
{
  float dx = p1.x - p2.x, dy = p1.y - p2.y;
  return sqrt(dx*dx + dy*dy);
}

int slope(point p1, point p2)
{
  int x = (p2.x - p1.x) * pow (10, 4);
  int y = (p2.y - p1.y) * pow (10, 4);

  return x/y;
}
bool collinear(point p1, point p2, point p3)
{
  return (slope(p1, p2) == slope(p2, p3));
}


