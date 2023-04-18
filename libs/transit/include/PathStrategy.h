#ifndef PATH_STRATEGY_H_
#define PATH_STRATEGY_H_

#include "IStrategy.h"

/**
 * @brief this class inhertis from the IStrategy class and is represents
 * a movement strategy where the entity simply moves along the given path
 */
class PathStrategy : public IStrategy {
 protected:
  std::vector<std::vector<float>> path;
  int index;

 public:
  /**
   * @brief Construct a new PathStrategy Strategy object
   *
   * @param path the path to follow
   */
  PathStrategy(std::vector<std::vector<float>> path = {});

  /**
   * @brief Move toward next position in the path
   *
   * @param entity Entity to move
   * @param dt Delta Time
   */
  virtual void Move(IEntity* entity, double dt);

  /**
   * @brief Check if the trip is completed by seeing if index 
   *        has reached the end of the path
   *
   * @return True if complete, false if not complete
   */
  virtual bool IsCompleted();

 /**
   * @brief Calculate the total distance of the path
   *        
   *
   * @return float - the total distance
   */
  float getTotalDistance() {
    float totalDistance = 0;
    if(path.size() > 0) {
      for (int i = 0; i < path.size() - 1 ; ++i) {
        totalDistance += sqrt(pow(path[i][0] - path[i+1][0], 2) + pow(path[i][1] - path[i+1][1], 2) + pow(path[i][2] - path[i+1][2], 2));
      }
    } else {
      return 0;
    }
    return totalDistance;
  };
};

#endif  // PATH_STRATEGY_H_
