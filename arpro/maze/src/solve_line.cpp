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

    // constructor for line solver
    int dist;
    Position(int _x, int _y, int _dist = 1) : Point(_x, _y), dist(_dist) {}

    int distToParent()
    {
        // in cell-based motion, the distance to the parent is always 1
        return dist;
    }

    std::vector<Pair> directions = {
        {1, 0},  // right
        {-1, 0}, // left
        {0, 1},  // down
        {0, -1}  // up
    };

    bool is_corridor(int x, int y)
    {
        int free_neighbours = 0;
        for(Pair &dir:directions)
            if(maze.isFree(x+dir.first), y+dir.second)
                ++free_neighbours;

        return free_neighbours==2;
    }

    std::vector<Position> children()
    {
        // this method should return  all positions reachable from this one
        std::vector<Position> generated;

        // TODO add free reachable positions from this point
        for(Pair &dir:directions)
        {
            int new_x = x+dir.first; int new_y = y+dir.second;
            dist = 1;

            // loop till end of corridor
            while(maze.isFree(new_x, new_y) and is_corridor(new_x, new_y))
            {
                new_x += dir.first; new_y += dir.second;
                ++dist;
            }

            if(maze.isFree(new_x, new_y))
                generated.emplace_back(new_x, new_y, dist);
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
    Position::maze.saveSolution("line");
    cv::waitKey(0);

}
