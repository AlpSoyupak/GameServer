#pragma once
#include <vector>
#include <span>
#include <cstddef>
#include <cstring>
#include <type_traits>

using ByteBuffer = std::vector<std::byte>;
using ReadBuffer = std::span<const std::byte>;

