#include <stdlib.h>

// reserve memory for 10 points
Point *points = (Point*) malloc(10 * sizeof(Point)); 
// ...
free(points);
