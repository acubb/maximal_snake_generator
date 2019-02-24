#ifndef INCLUDE_SNAKE
#define INCLUDE_SNAKE

class Snake {

 private:
  
  int max_length;     // The maximum length of this snake object.
  int num_dimensions; // Number of dimensions this snake object
                      // goes up to.
  int curr_length;    // The current length of this snake object
  char * snake_str;   // The string representation of this snake object.
  
 public:
  
  // Constructors
  
  // Default Constructor
  /* PRE:
     POST: This Snake object is defined.
   */
  Snake ();

  // Secondary Constructor
  /* PRE:  Takes dim, the number of dimensions this snake
           will be on, max, the maximum length of the snake,
           and the character array the_str, the string rep. of
	   this snake.
     POST: This Snake object is defined with num_dimensions = dim,
           max_length = max, snake_str = the_str
  */
  Snake (int dim, int max, char * the_str);

  // Copy Constructor
  /* PRE:  This Snake object is defined. S is another defined
           Snake object to be copied.
     POST: This Snake object is a deep copy of S.
   */
  Snake (const Snake & S);

  // Destructor
  /* PRE:  This Snake object is defined. 
     POST: This Snake object is destroyed with
           max_length = 0, num_dimensions = 0,
	   curr_length = 0, and snake_str = NULL.
   */
  ~Snake ();

  // Accessors

  /* PRE:  This Snake object is defined.
     POST: RV = curr_length.
   */
  int getLength ();

  /* PRE:  This Snakes object is defined.
     POST: RV = snake_str.
   */
  char * getStr ();

  // Modifiers

  /* PRE:  This Snake object is defined.
           new_str is an array of characters to set
	   snake_str to.
     POST: Sets the snake_str to new_str.
  */
  void setStr (char * new_str);

  // Member functions

  /* PRE:  This Snake object is defined. Takes
           the character to be added onto the snake.
     POST: Adds a character to the snake_str,
           and updates the length.
  */
  void add_char (char ch); 

  /*  PRE:  This Snake object is defined.
      POST: Updates curr_length to match the
            length of the_str.
   */
  void update_length ();
  
};
#endif
