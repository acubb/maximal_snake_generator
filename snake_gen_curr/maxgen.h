#ifndef INCLUDE_MAXGEN
#define INCLUDE_MAXGEN
#include "snake.h"
#include <fstream>
using namespace std;

class MaxGen {
  
 private:

  int num_dimensions; // The maximum number of dimensions
                      // to include in the generation.
  int length;         // Length of the maximal snakes to
                      // be generated.
  
  int curr_num_snakes; // Length of the array of snakes.
  int max_num_snakes;  // Maximum number of snakes that can
                       // fit in the snakes array at any given time.

  Snake * snakes; // The array of maximal snakes that
                  // are generated for the given # of dimensions
                  // and of the given length.

  int curr_num_points; // The current number of points in the points array.
  int max_num_points;  // The maximum amount of points that can fit in the
                       // points array.
  char ** points;  // The array of points of the snake.
                   // Each point is composed of an array of
                   // characters, either "0" or "1"
                   // Points array is curr_num_points x num_dimensions.
  
 public:

  // Constructors
  
  // Default Constructor
  /* PRE:  
     POST: This MaxGen object is defined.
   */
  MaxGen ();

  // Secondary Constructor
  /* PRE:  Takes two ints: dim, the number of dimensions
           the snakes will be generated on, and len, the
	   maximum length of the snakes to be generated.
     POST: This MaxGen object is defined with
           num_dimensions = dim and length = len.
   */
  MaxGen (int dim, int len);

  // Copy Constructor
  /* PRE:  This MaxGen object is defined. G is another
           defined MaxGen object to be copied.
     POST: This MaxGen object is a deep copy of G.
   */
  MaxGen (const MaxGen & G);

  // Destructor
  /* PRE:  This MaxGen object is defined.
     POST: This MaxGen object is destroyed, with
           num_dimensions = 0, length = 0,
           curr_num_snakes = 0, max_num_snakes = 0,
           and snakes = NULL.
  */
  ~MaxGen ();

  // Member functions

  /* PRE:  This MaxGen object is defined.
     POST: Generates maximal snakes of given length
           in the given number of dimensions,
	   populating the snakes array.
   */
  void generate_max_snakes ();

  /* PRE:  This MaxGen object is defined.
           curr_point is a defined array of
           characters that represents the 
           current point in the hypercube.
     POST: Generates maximal snakes of given
           length and in the given number of dimensions,
	   starting at the specified point.
  */
  void help_gen_max_snakes (char * curr_point);

  /* PRE:  This MaxGen object is defined.
           Takes the current point, an array of characters,
           and dim, the index of the dimension to be checked.
     POST: Returns true if changing the dimension would result in
           a valid snake, false otherwise. 
  */
  bool check_dim (char * curr_point, int dim);

  /* PRE:  This MaxGen object is defined.
           Takes an array of characters, the point, and the
           index of the dimension to be changed.
     POST: Flips the dimension. If the dimension is
           0, change to 1, and vice versa.
  */
  void change_dimension (char * point, int dim);

  /* PRE:  This MaxGen object is defined.
           Takes two arrays of characters, two points.
     POST: Returns an int, the distance between the two
           points.
  */
  int get_distance (char * point1, char * point2);

  /* PRE:  This MaxGen object is defined.
           Takes the current point, the
 	   array of characters most recently
	   added to the points array.
	   Also takes an int, dir, the direction the current
	   check is in. If it's 1, checking
	   forward direction. If it's 0,
	   checking backwards direction.
     POST: Returns true if the current snake
           on the points array is unable to
	   be extended, else false.
  */
  bool currently_maximal (char * curr_point, int dir);

  /* PRE:  This MaxGen object is defined.
           point is an array of characters to
           be checked.
	   Also takes an int, dir, the direction the current
	   check is in. If it's 1, checking
	   forward direction. If it's 0,
	   checking backwards direction.
     POST: Checks this point against every point
           but the most recent one. If n points,
           checks point against n - 1 points.
	   If distance between any point and
	   parameter point <= 1, return false,
	   else true.
  */
  bool valid_new_point (char * point, int dir);

  /* PRE:  This MaxGen object is defined.
           Takes an array of characters, the
	   point to be added to the points array.
     POST: Adds that point to the point array.
  */
  void add_point (char * the_point);

  /* PRE:  This MaxGen object is defined.
     POST: Deletes the most recently added point.
           from the points array.
  */
  void del_point ();

  /* PRE:  This MaxGen object is defined.
           Takes the point to be copied,
           an array of characters.
     POST: Returns a new array of characters
           that is a copy of point.
  */
  char * copy_point (char * point);
  
  /* PRE:  This MaxGen object is defined.
           Takes the snake object to be added to the
           snakes array.
     POST: Adds the new snake to the snakes array.
  */
  void add_snake (Snake new_snake);

  /* PRE:  This MaxGen object is defined.
     POST: Returns a character array, the string representation
           of the points array.
   */
  char * convert_to_snake ();
  
  /* PRE:  This MaxGen object is defined.
     POST: Outputs the contents of the snakes
           array to the terminal in readable format.
   */
  void output_max_snakes ();

  /* PRE:  This MaxGen object is defined.
           Takes the output stream to ouput the maximal
	   snakes into.
     POST: Outputs the maximal snakes into a .txt
           file named "snakes.txt" in the current
	   directory.
  */
  void output_to_file (ofstream & outFile);
};
#endif
