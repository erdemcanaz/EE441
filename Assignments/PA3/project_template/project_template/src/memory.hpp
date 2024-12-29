#pragma once
#include <cstdlib>

void* operator new(size_t count) noexcept;
void* operator new[](size_t count) noexcept;
void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;
void operator delete(void* ptr, size_t count) noexcept;
void operator delete[](void* ptr, size_t count) noexcept;

void* operator new(size_t count, const char* fileName, size_t lineNo) noexcept;
void* operator new[](size_t count, const char* fileName, size_t lineNo) noexcept;
void operator delete(void* ptr, const char* fileName, size_t lineNo) noexcept;
void operator delete[](void* ptr, const char* fileName, size_t lineNo) noexcept;
void operator delete(void* ptr, size_t count, const char* fileName, size_t lineNo) noexcept;
void operator delete[](void* ptr, size_t count, const char* fileName, size_t lineNo) noexcept;

#define new new(__FILE__, __LINE__)
