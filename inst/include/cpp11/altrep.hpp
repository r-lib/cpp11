#pragma once

// It would be nice to remove this since all supported versions of R have ALTREP, but
// some groups rely on both this `#define` and `altrep.hpp` itself existing, like arrow:
// https://github.com/apache/arrow/blob/50f2d6e04e8323119d4dd31506827ee398d6b8e4/r/src/altrep.cpp#L27-L29
#define HAS_ALTREP
