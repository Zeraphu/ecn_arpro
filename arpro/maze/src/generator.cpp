#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <maze.h>

using namespace ecn;
using namespace std;


// Define the Node structure
struct Node
{
    int x, y;  // Node position - slight waste of memory, but it allows faster generation
    Node *parent;  // Pointer to parent node
    char c;  // Character to be displayed
    char dirs;  // Directions that still haven't been explored
};

std::vector<Node> nodes;  // Used std::vector of Node instead of array
int width, height, random_dig;
std::vector<int> wall_indices;

// Initialize the maze
int init()
{
    nodes.resize(width * height);  // Used std::vector instead of calloc
    if (nodes.empty()) return 1;

    // Setup crucial nodes
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            Node &n = nodes[i + j * width];  // Access the node
            n.x = i;  // Set the x-coordinate
            n.y = j;  // Set the y-coordinate

            // Set walls or paths
            if (i * j % 2)
            {
                n.dirs = 15;  // All directions unexplored
                n.c = ' ';    // This is a path node
            }
            else
            {
                n.c = '#';    // This is a wall
                wall_indices.push_back(i+j*width);
            }
        }
    }

    return 0;
}

// Link nodes and return the next node to be visited
Node *link(Node *n)
{
    int x = 0, y = 0;
    char dir;
    Node *dest;

    // Return if null pointer is passed
    if (!n) return nullptr;

    // While there are unexplored directions
    while (n->dirs)
    {
        // Randomly pick one direction
        dir = (1 << (rand() % 4));

        // If it has already been explored, try again
        if (~n->dirs & dir) continue;

        // Mark direction as explored
        n->dirs &= ~dir;

        // Depending on the chosen direction
        switch (dir)
        {
        // Check if it's possible to go right
        case 1:
            if (n->x + 2 < width)
            {
                x = n->x + 2;
                y = n->y;
            }
            else continue;
            break;

            // Check if it's possible to go down
        case 2:
            if (n->y + 2 < height)
            {
                x = n->x;
                y = n->y + 2;
            }
            else continue;
            break;

            // Check if it's possible to go left
        case 4:
            if (n->x - 2 >= 0)
            {
                x = n->x - 2;
                y = n->y;
            }
            else continue;
            break;

            // Check if it's possible to go up
        case 8:
            if (n->y - 2 >= 0)
            {
                x = n->x;
                y = n->y - 2;
            }
            else continue;
            break;
        }

        // Get the destination node (makes things a bit faster)
        dest = &nodes[x + y * width];

        // Make sure the destination node is not a wall
        if (dest->c == ' ')
        {
            // If destination is a linked node already, abort
            if (dest->parent) continue;

            // Otherwise, adopt node
            dest->parent = n;

            // Remove the wall between nodes
            nodes[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = ' ';

            // Return the address of the child node
            return dest;
        }
    }

    // If nothing more can be done, return the parent's address (backtracking)
    return n->parent;
}

// Draw the maze to the console
void draw(Maze *maze, bool show = false)
{
    if(show)
    {
        // Output maze to the terminal - nothing special
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                cout << nodes[j + i * width].c;
            }
            std::cout << std::endl;
        }
    }

    // Generate image(.png) of maze using maze.h/dig and save
    for (const Node &n : nodes)
    {
        if (n.c == ' ')
        {
            maze->dig(n.x, n.y);
        }
    }
    maze->save();
}

void random_digger()
{
    random_shuffle(wall_indices.begin(), wall_indices.end());

    for(int i = 0; i < int(wall_indices.size()*random_dig/100); i++)
        nodes[wall_indices[i]].c = ' ';
}

int main(int argc, char **argv)
{
    Node *start, *last;
    width = 101;
    height = 101;
    random_dig = 20;

    // Slightly modified user input section to allow easy execution form qtcreator
    // Check argument count
    if(argc < 4)
    {
        std::cout << argv[0] << ": No random dig specified! Setting default value as: " << random_dig << "%" <<endl;
    } else
        sscanf( argv[3], "%d", &random_dig );


    if (argc < 3)
    {
        std::cout << argv[0] << ": No dimensions specified! Setting default values width = " << width
                             << ", height = "<< height << std::endl;
    } else
    {
        sscanf( argv[1], "%d", &width );
        sscanf( argv[2], "%d", &height );
    }


    // Read maze dimensions from command line arguments
    if (width +height < 2)
    {
        std::cerr << argv[0] << ": invalid maze size value!" << std::endl;
        return 1;
    }

    // Only allow odd dimensions
    if (!(width % 2) || !(height % 2))
    {
        std::cerr << argv[0] << ": dimensions must be odd!" << std::endl;
        return 1;
    }

    // Do not allow negative dimensions
    if (width <= 0 || height <= 0)
    {
        std::cerr << argv[0] << ": dimensions must be greater than 0!" << std::endl;
        return 1;
    }

    // Seed the random generator
    srand((time(nullptr)));

    // Initialize maze
    if (init())
    {
        std::cerr << argv[0] << ": out of memory!" << std::endl;
        return 1;
    }

    // Setup start node
    start = &nodes[1 + width];
    start->parent = start;
    last = start;

    // Connect nodes until the start node is reached and cannot be left
    while ((last = link(last)) != start);

    // Draw the generated maze in CLI or in .png format
    ecn::Maze maze(height, width);
    draw(&maze);

    return 0;
}
