#include <a_star.h>
#include <maze.h>

using namespace std;
using namespace ecn;

// a node is a x-y position, we move from 1 each time
class Position : public Point
{
public:
    // constructor from coordinates
    Position(int _x, int _y) : Point(_x, _y) {}

    // constructor from base ecn::Point
    Position(ecn::Point p) : Point(p.x, p.y) {}

    int distToParent()
    {
        // in cell-based motion, the distance to the parent is always 1
        return 1;
    }

    std::vector<Position> children()
    {
        // this method should return  all positions reachable from this one
        std::vector<Position> generated;

        // TODO add free reachable positions from this point
        // step 1: scan its children/neighbors - one cell apart
        std::vector<Pair> directions = {
            {1, 0},  // right
            {-1, 0}, // left
            {0, 1},  // down
            {0, -1}  // up
        };

        // step 2: check if any of them are walls or out of bounds
        for(auto &dir : directions)
        {
            int new_x = x + dir.first;
            int new_y = y + dir.second;

            if(maze.isFree(new_x, new_y)) // isFree returns pixel value
            {
                // step 3: if the position is free, add it as a child
                generated.emplace_back(new_x, new_y); // better than push_back in this case, avoids temp. Position variable
            }
        }

        return generated;
    }
};



int main( int argc, char **argv )
{
    // load file
    std::string filename = Maze::mazeFile("maze.png");
    if(argc == 2)
        filename = std::string(argv[1]);

    // let Point know about this maze
    Position::maze.load(filename);

    // initial and goal positions as Position's
    Position start = Position::maze.start(),
            goal = Position::maze.end();

    // call A* algorithm
    ecn::Astar(start, goal);

    // save final image
    Position::maze.saveSolution("cell");
    cv::waitKey(0);

}
