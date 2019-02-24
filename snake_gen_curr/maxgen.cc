#include <iostream>
#include <fstream>
#include "maxgen.h"
#include "snake.h"
using namespace std;

#define ASCII_DIGIT_LOWER 48 // Lower bound for 0 - 9
                             // ascii values.
#define END_ARRAY -1 // Index for end of the array.

// Constructors

// Default Constructor
/* PRE:  
   POST: This MaxGen object is defined.
*/
MaxGen::MaxGen () {
  num_dimensions = 3; // Default generate for 3-snake of
  length = 4;         // length 4.
  curr_num_snakes = 0;
  max_num_snakes = 1;
  snakes = new Snake[max_num_snakes];
  curr_num_points = 0;
  max_num_points = 1;
  points = new char *[max_num_points];
}

// Secondary Constructor
/* PRE:  Takes two ints: dim, the number of dimensions
         the snakes will be generated on, and len, the
	 maximum length of the snakes to be generated.
   POST: This MaxGen object is defined with
         num_dimensions = dim and length = len.
*/
MaxGen::MaxGen (int dim, int len) {
  num_dimensions = dim;
  length = len;
  curr_num_snakes = 0;
  max_num_snakes = 1;
  snakes = new Snake[max_num_snakes];
  curr_num_points = 0;
  max_num_points = 1;
  points = new char *[max_num_points];
}

// Copy Constructor
/* PRE:  This MaxGen object is defined. G is another
         defined MaxGen object to be copied.
   POST: This MaxGen object is a deep copy of G.
*/
MaxGen::MaxGen (const MaxGen & G) {
  // Copy over values
  num_dimensions = G.num_dimensions;
  length = G.length;

  curr_num_snakes = G.curr_num_snakes;
  max_num_snakes = G.max_num_snakes;
  // Copy over snakes array.
  snakes = new Snake[max_num_snakes];
  for (int i = 0; i < curr_num_snakes; i ++) {
    snakes[i] = G.snakes[i];
  }
  curr_num_points = G.curr_num_points;
  max_num_points = G.max_num_points;
  // Copy over points array of points.
  points = new char*[length];
  for (int i = 0; i < curr_num_points; i ++) {
    points[i] = G.points[i];
  }
}

// Destructor
/* PRE:  This MaxGen object is defined.
   POST: This MaxGen object is destroyed, with
         num_dimensions = 0, length = 0,
	 curr_num_snakes = 0, max_num_snakes = 0,
	 snakes = NULL, and points = NULL.
*/
MaxGen::~MaxGen () {
  // Set values to 0.
  num_dimensions = 0;
  length = 0;
  curr_num_snakes = 0;
  max_num_snakes = 0;

  // Set snakes to null and delete it.
  snakes = NULL;
  delete[] snakes;

  // Delete each point in the points array.
  for (int i = 0; i < length; i ++) {
    delete[] points[i];
  }
  // Set points to null and delete it.
  points = NULL;
  delete[] points;
}

// Member functions

/* PRE:  This MaxGen object is defined.
   POST: Generates maximal snakes of given
         length in the given number of dimensions,
	 populating the snakes array.
 */
void MaxGen::generate_max_snakes () {
  // Allocate memory for the start point,
  // which is num_dimensions in length.
  // Then fill it with num_dimensions number of '0's
  char * start_point = new char[num_dimensions];
  for (int i = 0; i < num_dimensions; i++) {
    start_point[i] = '0';
  }
  // Start generation beginning at start point.
  help_gen_max_snakes(start_point);
}

/* PRE:  This MaxGen object is defined.
         curr_point is a defined array of
	 characters that represents the 
	 current point in the hypercube.
   POST: Generates maximal snakes of given
         length and in the given number of dimensions,
	 starting at the specified point.
*/
void MaxGen::help_gen_max_snakes (char * curr_point) {
  // Start by adding the current point to the array of points.
  add_point(curr_point);
  // Debugging output.
  //cerr << "NUM_POINTS: " << curr_num_points << endl;
  //for (int i = 0; i < curr_num_points; i++) {
  //  cerr << "Point " << i << ": " << points[i] << endl;
  //}
  //cerr << endl;
  // If the current snake on the points array is maximal,
  // finished. Only add the snake to the array of snakes if
  // it is of the specified length. Length of the snake is
  // found by subtracting 1 from the number of points on the
  // snake.
  if (currently_maximal(curr_point, 1) && currently_maximal(points[0], 0)) {
    if (curr_num_points - 1 == length) {
      // Convert the points array into the
      // character representation of the snake.
      char * snake_str = convert_to_snake();   
      // Make new snake and add it.
      Snake new_snake(num_dimensions, length, snake_str);
      new_snake.update_length(); // Length is default 0. Adjustment.
      add_snake(new_snake);      
    }
  }
  else {
    // Else, the current snake can be extended. The next
    // point is found by comparing each possible
    // point (the neighbors of the current point) with
    // every other point in the points array.
    // Next point is every point with distance <= 1
    // from current point, and distance > 1 from every
    // other point.
    int num_points = curr_num_points; // Save starting point for backtrack.
    // Checking each dimension for next point.
    for (int i = 0; i < num_dimensions; i ++) {
      num_points = curr_num_points;   // Save starting point.
      // Check that the ith dimension satisfies new point
      // criteria. If it does, next point is found. Start
      // generating from that point. 
      if (check_dim(curr_point, i)) {
	char * new_point = copy_point(curr_point); // Copy point.
	change_dimension(new_point, i); // Make the dimension change.
	help_gen_max_snakes(new_point); // Move on to next point.
	curr_num_points = num_points;   // After we've come back from
	                                // a maximal snake, reset the start point.
   	delete new_point;
      }
    }
  }
}

/* PRE:  This MaxGen object is defined.
         Takes my_snake, the snake string being added to the 
	 list of snakes to check.
   POST: Checks if the isomorphic snake relative
         to my_snake exists in the snakes array.
	 Returns true if it exists, false otherwise.
 */
bool MaxGen::iso_exists (char * my_snake) {
  bool return_val = false;
  for (int i = 0; i < curr_num_snakes) {
    char * curr_snake_str = snakes[i].getStr();
    //    for (int i = curr_num_dimensions
    int count = 0;
    while (curr_snake_str[0 + count] == my_snake[(length - 1) - count]
	   && (count < num_dimensions)) {
      count ++;
    }
    if (count == num_dimensions) {
      return_val = true;
    }
  }
  //cerr << "ISO " <<  << 
  return (return_val);
}

/* PRE:  This MaxGen object is defined.
         Takes the current point, an array of characters,
	 and dim, the index of the dimension to be checked.
   POST: Returns true if changing the dimension would result in
         a valid snake, false otherwise. 
*/
bool MaxGen::check_dim (char * curr_point, int dim) {
  bool return_val = false; // Return boolean. Default false.
  char * temp_point = copy_point(curr_point); // Temporary point.
  change_dimension(temp_point, dim); // Change the dimension given.
  // If the point after the dimension change is valid, return true.
  if (valid_new_point(temp_point, 1)) {
    return_val = true;
  }
  delete temp_point;
  return (return_val);
}

/* PRE:  This MaxGen object is defined.
         Takes an array of characters, the point, and the
         index of the dimension to be changed.
   POST: Flips the dimension. If the dimension is
         0, change to 1, and vice versa.
 */
void MaxGen::change_dimension (char * point, int dim) {
  // Simple dimension bit flip. If 0, 1. Else, 0.
  if (point[dim] == '0') {
    point[dim] = '1';
  }
  else {
    point[dim] = '0';
  }
}

/* PRE:  This MaxGen object is defined.
         Takes two arrays of characters, two points.
   POST: Returns an int, the distance between the two
         points.
*/
int MaxGen::get_distance (char * point1, char * point2) {
  int distance = 0;
  // Distance is obtained by counting the differing
  // dimensions between the two points.
  for (int i = 0; i < num_dimensions; i ++) {
    if (point1[i] != point2[i]) {
      distance ++;
    }
  }
  return (distance);
}

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
bool MaxGen::currently_maximal (char * curr_point, int dir) {
  bool return_val = true; // Return boolean.
  char * new_point = copy_point(curr_point); // Copy point.
  // Change every dimension, and check if the
  // resulting point is a valid point.
  // If it is, snake can be extended and return
  // false. Else, return true.
  for (int i = 0; i < num_dimensions; i ++) {
    change_dimension(new_point, i);
    if (valid_new_point(new_point, dir)) {
      return_val = false;
    }
    change_dimension(new_point, i);
  }
  delete new_point;
  return (return_val);
}

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
bool MaxGen::valid_new_point (char * point, int dir) {
  bool return_val = true; // Return boolean.
  // Check the given point against every other
  // point besides the most recent one for
  // distance <= 1.
  if (dir == 1) {
    for (int i = 0; i < curr_num_points - 1; i ++) {
      char * curr_point = points[i];
      if (get_distance(point, curr_point) <= 1) {
	return_val = false;
      }
    }
  }
  if (dir == 0) {
    for (int i = 1; i < curr_num_points; i ++) {
      char * curr_point = points[i];
      if (get_distance(point, curr_point) <= 1) {
	return_val = false;
      }
    }
  }
  return (return_val);
}

/* PRE:  This MaxGen object is defined.
         Takes an array of characters, the
	 point to be added to the points array.
   POST: Adds that point to the point array.
 */
void MaxGen::add_point (char * the_point) {
  // If necessary, allocate more space for
  // points array.
  if (curr_num_points >= max_num_points) {
    char ** temp_points = points;//new char *[max_num_points];
    int new_max = (2 * (max_num_points));
    points = new char*[new_max];
    for (int i = 0; i < curr_num_points; i ++) {
      points[i] = new char[num_dimensions];
      for (int j = 0; j < num_dimensions; j ++) {
	points[i][j] = temp_points[i][j];
      }
    }
    temp_points = NULL;
    delete[] temp_points;
    max_num_points = new_max;
  }
  // Add the point, increment number of points.
  points[curr_num_points] = the_point;
  curr_num_points ++;
}

/* PRE:  This MaxGen object is defined.
   POST: Deletes the most recently added point.
         from the points array.
 */
void MaxGen::del_point () {
  // Delete recent point, decrement number of points.
  points[curr_num_points - 1] = NULL;
  curr_num_points --;
}

/* PRE:  This MaxGen object is defined.
         Takes the point to be copied,
	 an array of characters.
   POST: Returns a new array of characters
         that is a copy of the point.
 */
char * MaxGen::copy_point (char * point) {
  // Allocate space for the copy.
  char * new_point = new char[num_dimensions];
  // Copy values over.
  for (int i = 0; i < num_dimensions; i ++) {
    new_point[i] = point[i];
  }
  // End the point with an end of string character.
  new_point[num_dimensions] = '\0';
  return (new_point);
}

/* PRE:  This MaxGen object is defined.
         Takes the snake object to be added to the
         snakes array.
   POST: Adds the new snake to the snakes array.
*/
void MaxGen::add_snake (Snake new_snake) {
  // Allocate more space if necessary.
  if (curr_num_snakes >= max_num_snakes) {
    Snake * temp_snakes = snakes;
    int new_max = 2 * max_num_snakes;
    snakes = new Snake[new_max];
    for (int i = 0; i < curr_num_snakes; i++) {
      snakes[i] = temp_snakes[i];    
    }
    max_num_snakes = new_max;
    temp_snakes = NULL;
    delete[] temp_snakes;
  }
  // Add the snake, increment the number of snakes.
  snakes[curr_num_snakes] = new_snake;
  curr_num_snakes ++;
}

/* PRE:  This MaxGen object is defined. 
   POST: Returns a character array, the string representation
         of the points array.
*/
char * MaxGen::convert_to_snake () {
  // Allocate space for the string.
  char * return_str = new char[curr_num_points + 1];
  // Compare each pair of points in the points array
  // and find the differing dimension. The index
  // of that dimension is then added to the string.
  for (int i = 0; i < curr_num_points - 1; i ++) {
    char * curr_point = points[i];
    char * next_point = points[i + 1];
    int change_dim_index = 0;
    for (int j = 0; j < num_dimensions; j ++) {
      if (curr_point[j] != next_point[j]) {
	change_dim_index = j;
      }
    }
    char new_ch = change_dim_index + ASCII_DIGIT_LOWER;
    return_str[i] = new_ch;
  }
  return_str[curr_num_points - 1] = '\0'; // End of string character added.
  return (return_str);
}

/* PRE:  This MaxGen object is defined.
   POST: Outputs the contents of the snakes
         array to the terminal in readable format.
*/
void MaxGen::output_max_snakes () {
  if (curr_num_snakes == 0) {
    cout << "No snakes were generated." << endl;
  }
  else {
    // Printing each snake with necessary information.
    for (int i = 0; i < curr_num_snakes; i ++) {
      Snake curr_snake = snakes[i];
      char * snake_str = curr_snake.getStr();
      int snake_len = curr_snake.getLength();
      cout << "Snake index: " << i << " Snake: " << snake_str << endl;
    }
  }
}

/* PRE:  This MaxGen object is defined.
         Takes the defined output stream to 
	 ouput the maximal snakes into.
   POST: Outputs the maximal snakes into a .txt
         file named "snakes.txt" in the current
	 directory.
*/
void MaxGen::output_to_file (ofstream & outFile) {
  if (curr_num_snakes == 0) {
    cout << "No snakes were generated." << endl;
  }
  else {
    outFile << "SNAKES IN: " << num_dimensions << " DIMENSIONS," <<
      " OF LENGTH: " << length << " # OF SNAKES: " << curr_num_snakes << endl;
    for (int i = 0; i < curr_num_snakes; i++) {
      Snake curr_snake = snakes[i];
      char * snake_str = curr_snake.getStr();
      int snake_len = curr_snake.getLength();
      outFile << "Snake index: " << i << " Snake: " << snake_str << endl;
    }
  }
}



  
