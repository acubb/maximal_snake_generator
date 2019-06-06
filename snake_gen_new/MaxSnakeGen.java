
import java.util.ArrayList;

public class MaxSnakeGen {
    int num_dims;
    int length;
    static int num_bits_in_int = 32;
    ArrayList snakes = new ArrayList();
    ArrayList nodes = new ArrayList();

    public MaxSnakeGen () {
	this.num_dims = 3;
	this.length = 4;	
    }

    public MaxSnakeGen (int num_dims, int length) {
	this.num_dims = num_dims;
	this.length = length;
    }

    public void generate_max_snakes () {
	int start_node = 0;
	help_gen_max_snakes(start_node);
    }

    public void help_gen_max_snakes (int curr_node) {
	nodes.add(curr_node);
	
	//terminal_output_nodes();
	//System.err.println();
	if (is_maximal() && ((nodes.size() - 1) == length)) {
	    //System.err.println("MADE INTO IF");
	    add_snake_from_nodes();

	    Snake new_snake = (Snake) snakes.get(snakes.size() - 1);
	    System.out.println("snake " + (snakes.size() - 1) + ": " +
			       new_snake.get_snake_str());
	}
	else {
	    for (int i = 0; i < num_dims; i ++ ) {
		int new_node = flip_dimension (i, curr_node);
		if (valid_new_node(new_node))
		    help_gen_max_snakes(new_node);
	    }
	}
	//Object node_object = (Object) curr_node;
	//nodes.remove(node_object);
	nodes.remove(nodes.size() - 1);
    }

    public int flip_dimension (int dim, int node) {
	int new_node = node;
	int mask = 1 << dim;
	if ((mask & new_node) == 0)
	    new_node += mask;
	else
	    new_node -= mask;
	return (new_node);
    }

    public int get_distance (int node1, int node2) {
	int distance = 0;
	int XOR = node1 ^ node2;
	while (XOR > 0) {
	    XOR &= (XOR - 1);
	    distance ++;
	}
	return (distance);
    }

    public int get_differing_dim (int node1, int node2) {
	int XOR = node1 ^ node2;
	return (num_bits_in_int - Integer.numberOfLeadingZeros(XOR) - 1);
    }

    public void add_snake_from_nodes () {
	Snake new_snake = new Snake();
	for (int i = 0; i < nodes.size() - 1; i ++ ) {
	    int node1 = (int) nodes.get(i);
	    int node2 = (int) nodes.get(i + 1);
	    int new_digit = get_differing_dim(node1, node2);
	    char new_char = 0;
	    if (new_digit < 10)
		new_char = (char) (new_digit + 48);
	    else
		new_char = (char) (new_digit + 55); // ASCII Decimal for "A" is 65		
	    new_snake.add_char(new_char);
	}
	snakes.add(new_snake);
    }

    public boolean valid_new_node (int new_node) {
	int index = 0;
	boolean valid = true;
	while (index < nodes.size() - 1 && valid) {
	    int comparison_node = (int) nodes.get(index);
	    if ((get_distance(new_node, comparison_node) <= 1) ||
		comparison_node == new_node)
		valid = false;
	    index ++;
	}
	return (valid);
    }

    public boolean is_maximal () {
	boolean maximal = true;
	int accum = 0;

	int tail = (int) nodes.get(nodes.size() - 1);
	// Forward direction (from tail of snake)
	while (maximal && (accum < num_dims)) {
	    int new_node = flip_dimension(accum, tail);
	    if (valid_new_node(new_node))
		maximal = false;
	    accum ++;
	}

	int head = (int) nodes.get(0);
	accum = 0;
	// Backward direction (from head of snake)
	while (maximal && (accum < num_dims)) {
	    int new_node = flip_dimension(accum, head);
	    if (valid_new_node(new_node))
		maximal = false;
	    accum ++;
	}
	return (maximal);
    }

    public void terminal_output_nodes () {
	for (int i = 0; i < nodes.size(); i ++ ) {
	    int curr_node = (int) nodes.get(i);
	    System.out.println(i + ": " +
			       String.format("%3s", Integer.toBinaryString(curr_node)).replace(" ", "0"));
	}
    }

    public void terminal_output_snakes () {
	for (int i = 0; i < snakes.size(); i ++ ) {
	    Snake curr_snake = (Snake) snakes.get(i);
	    System.out.println(i + ": " + curr_snake.get_snake_str());
	}
    }

    public void file_output_snakes () {
	return;
    }
}
