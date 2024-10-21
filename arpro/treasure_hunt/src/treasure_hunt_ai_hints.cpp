#include <treasure_hunt_ai.h>
#include <duels/utils/grid_point.h>

#include <duels/algo/a_star.h>

constexpr int FREE{0};
constexpr int ROCK{1};
constexpr int UNKNOWN{2};

TreasureHuntAI::TreasureHuntAI()
    : map(20, 30, UNKNOWN) // fill the 20x30 map with 2's (unknown)
{
    // register this map for all grid points
    pose.setMap(map);

    // TODO the treasure may be at any position: update candidates
    candidates.reserve(map.width()*map.height());
}

Action TreasureHuntAI::computeFrom(const Feedback &feedback)
{
    // register where we are
    pose.set(feedback.pose);
    // if we are here then it is not a treasure position
    removeCandidate(pose);

    // TODO process feedback.scan to update map
    //  for(auto &[x,y,occupied]:feedback.scan)
    //      map.cell(x,y) = occupied ? ROCK:FREE;

    for(auto &[x,y,occupied]:feedback.scan)
    {
        if(occupied)
        {
            map.cell(x, y) = ROCK;
            removeCandidate(Vector2D(x, y));
        } else
        {
            map.cell(x, y) = FREE;
            updateCandidates(Vector2D(x, y));
        }
    }

    // TODO process feedback.treasure_distance to update candidates
    // as we compare floating points, a small threshold is useful to tell if two values are equal
    if(!candidates.empty()){
        pruneCandidates([this, feedback](Vector2D<int> cand){
            return std::abs(pose.distance(cand)-feedback.treasure_distance) > 0.5;
        });
    }

    // TODO use A* to find shortest path to first candidate, will assume unknown cells are free
    auto path = Astar(pose, candidates.front());

    Action action; // compute it from pose and next
    // TODO identify which move from pose to next
    if(path[1] != pose)
    {
        action = Action::MOVE;
    }else action = Action::TURN_LEFT;

    // TODO do not use Action::MOVE if the next cell is unknown
    if(!map.isFree(path[1]))
        action = Action::SONAR;

    return action;
}
