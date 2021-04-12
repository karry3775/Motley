#pragma once

#include <visualizer.h>

namespace pendulum {

class SimplePendulum {
   public:
    SimplePendulum();
    SimplePendulum(const double length, const double radius,
                   const double ini_theta);
    void show();

   private:
    void update(const int interval);

    double length_;
    double radius_;
    double theta_;
    double time_;
    Visualizer viz_;

};  // class SimplePendulum

}  // namespace pendulum