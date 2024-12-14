#pragma once

#include <limits>
#include <climits>
#include <cstdint>

// NOLINTBEGIN(CppInconsistentNaming)

// Data types

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

// Limits

constexpr i8 I8_MIN = std::numeric_limits<i8>::min();
constexpr i8 I8_MAX = std::numeric_limits<i8>::max();

constexpr i16 I16_MIN = std::numeric_limits<i16>::min();
constexpr i16 I16_MAX = std::numeric_limits<i16>::max();

constexpr i32 I32_MIN = std::numeric_limits<i32>::min();
constexpr i32 I32_MAX = std::numeric_limits<i32>::max();

constexpr i64 I64_MIN = std::numeric_limits<i64>::min();
constexpr i64 I64_MAX = std::numeric_limits<i64>::max();

constexpr u8 U8_MIN = std::numeric_limits<u8>::min();
constexpr u8 U8_MAX = std::numeric_limits<u8>::max();

constexpr u16 U16_MIN = std::numeric_limits<u16>::min();
constexpr u16 U16_MAX = std::numeric_limits<u16>::max();

constexpr u32 U32_MIN = std::numeric_limits<u32>::min();
constexpr u32 U32_MAX = std::numeric_limits<u32>::max();

constexpr u64 U64_MIN = std::numeric_limits<u64>::min();
constexpr u64 U64_MAX = std::numeric_limits<u64>::max();

constexpr f32 F32_MIN = std::numeric_limits<f32>::lowest();
constexpr f32 F32_MAX = std::numeric_limits<f32>::max();
constexpr f32 F32_SMALLEST = std::numeric_limits<f32>::min();

constexpr f64 F64_MIN = std::numeric_limits<f64>::lowest();
constexpr f64 F64_MAX = std::numeric_limits<f64>::max();
constexpr f64 F64_SMALLEST = std::numeric_limits<f64>::min();

// Ensure that the floating point types are using the correct sizes

static_assert(CHAR_BIT * sizeof(float) == 32, "The size of the float type is not 32 bits");
static_assert(CHAR_BIT * sizeof(double) == 64, "The size of the double type is not 64 bits");

// NOLINTEND(CppInconsistentNaming)
