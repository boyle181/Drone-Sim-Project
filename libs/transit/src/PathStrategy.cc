#include "PathStrategy.h"

PathStrategy::PathStrategy(std::vector<std::vector<float>> p)
  : path(p), index(0) {}

void PathStrategy::Move(IEntity* entity, double dt) {
  if (IsCompleted())
    return;

  Vector3 vi(path[index][0], path[index][1], path[index][2]);
  Vector3 dir = (vi - entity->GetPosition()).Unit();

  entity->SetPosition(entity->GetPosition() + dir*entity->GetSpeed()*dt);
  entity->SetDirection(dir);

  if (entity->GetPosition().Distance(vi) < 4)
    index++;
}

float PathStrategy::getTotalDistance() {
    float totalDistance = 0;
    if(path.size() > 0) {
      for (int i = 0; i < path.size() - 1 ; ++i) {
        totalDistance += sqrt(pow(path[i][0] - path[i+1][0], 2) + pow(path[i][1] - path[i+1][1], 2) + pow(path[i][2] - path[i+1][2], 2));
      }
    } else {
      return 0;
    }
    return totalDistance;
}

bool PathStrategy::IsCompleted() {
  return index >= path.size();
}
