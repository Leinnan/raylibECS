#ifndef ARKONA_HPP
#define ARKONA_HPP
#include "raylib.h"

#ifndef PI
#define PI 3.1415926545
#endif


namespace ar{
    float getDistance(Vector2 first, Vector2 second);

    template<typename T>T getAbs(const T& value){ return value > 0 ? value : -value; };
    
    //credits for http://stackoverflow.com/users/1842511/creak
    float cubicEaseInOut(float t);
    float easeInOutBounce(float t);
}

#endif // ARKONA_HPP
