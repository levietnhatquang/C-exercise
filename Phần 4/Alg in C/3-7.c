/*
 * Write a client program that uses the data type in Programs 3.3 and 3.4
 * for the following task: Read a sequence of points (pairs of floating-point
 * numbers) from standard input, and and the one that is closest to the first.
 */
    
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef struct
{
  int x;
  int y;
} point;

int distance(point, point);

int main(){
  point first, n, closest;
  bool is_first_number = true;
  int shortest_dist;

  while (!feof(stdin))
    {
      printf("Enter the number: ");
      scanf ("%d %d", &n.x, &n.y);
      if (is_first_number)
	{
	  first = n;
	  shortest_dist = INT_MAX;
	  is_first_number = false;
	  continue;
	}
      if (distance(first, n) < shortest_dist)
	{
	  closest = n;
	  shortest_dist = distance(first, n);
	}
    }
  printf("Closest point: %d, %d\n", closest.x, closest.y);
  return 0;
}

int distance (point a, point b)
{
  int x = b.x - a.x;
  int y = b.y - a.y;
  
  return sqrt(x*x + y*y);
}