#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include <math.h>

namespace GEngine {
class MathUtils {
   public:
    static double degToRad(double angleDeg) {
        return angleDeg / 180 * M_PI;
    }

    static double radToDeg(double angleRad) {
        return angleRad / M_PI * 180;
    }
};

}  // namespace GEngine

#endif
