# ArenaAllocator

A lightweight header-only C++ arena allocator implementation using a Meyers Singleton pattern (would be faster with global).

This allocator preallocates a contiguous block of memory at startup and performs fast bump-style allocations for objects of a fixed type.

## Features

- Header-only
- Thread-safe allocations via `std::mutex`
- Constant-time allocations
- Minimal overhead
- Singleton-backed arena
- Supports single object and array allocations

---

# Usage

## 1. Include the Header

```cpp
#include "ArenaAllocation.hh"
