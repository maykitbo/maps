#ifdef WKB_TEST
#include "wkb/wkb.h"
#endif

#ifdef TEMP_TEST
#include "temp_test/temp_test.h"
#endif

int main()
{
#ifdef WKB_TEST
    WKB::test();
#endif

#ifdef TEMP_TEST
    TEMP::test();
#endif
    return 0;
}
