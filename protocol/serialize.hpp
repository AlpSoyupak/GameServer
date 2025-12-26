#pragma once

#include <vector>
#include <span>
#include <cstddef>
#include <cstring>
#include <type_traits>
#include "buffer.hpp"

template <typename T>
requires std::is_trivially_copyable_v<T>
void write(ByteBuffer& buf, const T& value) {
    const std::byte* p = reinterpret_cast<const std::byte*>(&value);
    buf.insert(buf.end(), p, p + sizeof(T));
}

template <typename T>
requires std::is_trivially_copyable_v<T>
T read(ReadBuffer& buf) {
    T value;
    std::memcpy(&value, buf.data(), sizeof(T));
    buf = buf.subspan(sizeof(T));
    return value;
}
