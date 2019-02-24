#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "maxgen.h"
using namespace std;

#define VALID_ARGS 4
#define MAX_BITS 10
#define FILE_NAME_LEN 12 

/* PRE:  The program takes 3 command line arguments to be stored
         in argv: num_dimensions, length, and output mode.
	 If output mode is 0, output snakes to terminal.
	 If output mode is 1, output snakes to a file.
   POST: Program generates snakes in num_dimensions of the
         given length.
 */
int main (int argc, char * argv[]) {
  if (argc != VALID_ARGS) {
    cout << "Error, invalid args." << endl;
  }
  else {
    int num_dimensions = atoi(argv[1]);
    int length = atoi(argv[2]);
    int op_mode = atoi(argv[3]);
    
    if (num_dimensions > MAX_BITS || num_dimensions < 0) {
      cout << "Error, invalid number of dimensions" << endl;
    }
    else {
      // Make MaxGen object and generate snakes.
      MaxGen dsnakes(num_dimensions, length); 
      dsnakes.generate_max_snakes();
      // Output to terminal mode.
      if (op_mode == 0) {
	dsnakes.output_max_snakes();
      }
      // Output to file mode.
      else if (op_mode == 1) {
	char file_name[FILE_NAME_LEN] = {argv[1][0], 's', 'n', 'a', 'k', 'e', 's', '.', 't', 'x', 't', '\0'};
	ofstream outFile(file_name);
	dsnakes.output_to_file(outFile);
	outFile.close();
      }
      else {
	cout << "Error invalid output code." << endl;
      }
    }
  }
  return (0);
}
