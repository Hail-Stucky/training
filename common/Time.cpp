#include "common/Time.h"

namespace aria {
  std::chrono::steady_clock::time_point Time::startTime = std::chrono::steady_clock::now();
}