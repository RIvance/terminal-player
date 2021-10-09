#ifndef COMMON_H
#define COMMON_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

using String = std::string;

#define use(content) template <typename Tp> using content <Tp>

template <typename Tp, typename Alloc = std::allocator<Tp>>
using List = std::vector<Tp, Alloc>;

use(Ref = std::shared_ptr);
use(WeakRef = std::weak_ptr);
use(Allocator = std::allocator);

using Exception = std::exception;
using std::to_string;

#define  str  to_string

struct Pos { int x, y; };

typedef int8_t    int8;
typedef uint8_t   uint8;
typedef int16_t   int16;
typedef uint16_t  uint16;
typedef int32_t   int32;
typedef uint32_t  uint32;
typedef int64_t   int64;
typedef uint64_t  uint64;

typedef uint8_t byte;

#endif // COMMON_H