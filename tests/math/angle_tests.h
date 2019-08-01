#include <cxxtest/TestSuite.h>

#include <math.h>
#include "../../inc/math/angle.h"

class AngleTests : public CxxTest::TestSuite
{
public:
    void testDegreesToRadians(void)
    {
        int degrees = 180;
        float expected = M_PI;
        TS_TRACE("degreesToRadians");
        TS_ASSERT_EQUALS(degreesToRadians(degrees), expected);
    }

    void testRadiansToDegrees(void)
    {
        float radians = M_PI;
        int expected = 180;
        TS_TRACE("radiansToDegrees");
        TS_ASSERT_EQUALS(radiansToDegrees(radians), expected);
    }
};
