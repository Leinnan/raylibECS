#include "utils/Arkona.hpp"

#include <math.h>
#include <cmath>

float ar::getDistance(Vector2 first,Vector2 second)
{
    float one_part = 0;
    float second_part = 0;
    float result = 0;

    one_part = second.x - first.x;
    one_part *= one_part;
    second_part = second.y - first.y;
    second_part *= second_part;

    result = sqrt(one_part + second_part);

    return result;
}


float ar::cubicEaseInOut(float t)
{
    if(t <= 0.5f)
        return 2.0f * pow(t,2.0f);
    t -= 0.5f;
    return 2.0f * t * (1.0f - t) + 0.5;
}

float ar::easeInOutBounce( float t )
{
    if( t < 0.5 ) {
        return 8 * pow( 2, 8 * (t - 1) ) * abs( sin( t * PI * 7 ) );
    } else {
        return 1 - 8 * pow( 2, -8 * t ) * abs( sin( t * PI * 7 ) );
    }
}
