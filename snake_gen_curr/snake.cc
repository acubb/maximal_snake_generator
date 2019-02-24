#include <iostream>
#include "snake.h"
using namespace std;

// Constructors

// Default Constructor
/* PRE:
   POST: This Snake object is defined.
*/
Snake::Snake () {
  max_length = 1;
  num_dimensions = 0;
  curr_length = 0;
  snake_str = new char[max_length];
  snake_str[0] = '\0';
}

// Secondary Constructor
/* PRE:  Takes dim, the number of dimensions this snake
         will be on, max, the maximum length of the snake,
	 and the character array the_str, the string rep. of
	 this snake.
   POST: This Snake object is defined with num_dimensions = dim,
         max_length = max, snake_str = the_str
*/
Snake::Snake (int dim, int max, char * the_str) {
  max_length = max;
  num_dimensions = dim;
  curr_length = 0;
  snake_str = the_str;
}


// Copy Constructor
/* PRE:  This Snake object is defined. S is another defined
         Snake object to be copied.
   POST: This Snake object is a deep copy of S.
*/
Snake::Snake (const Snake & S) {
  max_length = S.max_length;
  num_dimensions = S.num_dimensions;
  curr_length = S.curr_length;
  snake_str = S.snake_str;
}

// Destructor
/* PRE:  This Snake object is defined. 
   POST: This Snake object is destroyed with
         max_length = 0, num_dimensions = 0,
         curr_length = 0, and snake_str = NULL.
*/
Snake::~Snake () {
  max_length = 0;
  num_dimensions = 0;
  curr_length = 0;
  snake_str = NULL;
  delete[] snake_str;
}

// Accessors

/* PRE:  This Snake object is defined.
   POST: RV = curr_length.
*/
int Snake::getLength () {
  return (curr_length);
}

/* PRE:  This Snakes object is defined.
   POST: RV = snake_str.
*/
char * Snake::getStr () {
  return (snake_str);
}

// Modifiers

/* PRE:  This Snake object is defined.
         new_str is an array of characters to set
	 snake_str to.
   POST: Sets the snake_str to new_str.
 */
void Snake::setStr (char * new_str) {
  snake_str = new_str;
}

// Member functions

/* PRE:  This Snake object is defined. Takes
         the character to be added onto the snake.
   POST: Adds a character to the snake_str,
         and updates the length.
*/
void Snake::add_char (char ch) {
  snake_str[curr_length] = ch;
  curr_length ++;
  snake_str[curr_length] = '\0';
}

/*  PRE:  This Snake object is defined.
    POST: Updates curr_length to match the
          length of the_str.
*/
void Snake::update_length () {
  for (int i = 0; i < max_length; i ++) {
    char curr_ch = snake_str[i];
    if (curr_ch != '\0') {
      curr_length ++;
    }
  }
}
