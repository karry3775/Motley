#pragma once

#include "core.h"

namespace bundle_adjustment {

class BalProblemReader;

struct SnavelyReprojectionError;

void solve(char** argv);

}  // namespace bundle_adjustment