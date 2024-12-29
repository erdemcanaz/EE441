#include <iostream>
#include <stdexcept>
#include <cstdlib>

struct MemoryTableEntry
{
    void* address;
    bool isArray;
    const char* fileName;
    size_t lineNo;
};

constexpr MemoryTableEntry EMPTY_TABLE_ENTRY = { nullptr, false, nullptr, 0 };

#define LEAK_DETECTOR_TABLE_SIZE 10000

class LeakDetector
{
private:
    MemoryTableEntry m_table[LEAK_DETECTOR_TABLE_SIZE];

public:
    LeakDetector()
    {
        for (size_t i = 0 ; i < LEAK_DETECTOR_TABLE_SIZE ; ++i) {
            m_table[i] = EMPTY_TABLE_ENTRY;
        }
    }

    ~LeakDetector()
    {
        for (size_t i = 0 ; i < LEAK_DETECTOR_TABLE_SIZE ; ++i) {
            if (m_table[i].address == nullptr) continue;

            std::cout << "[Leak Detector] Address " << m_table[i].address << " is not deleted by \"operator new"
                << (m_table[i].isArray ? "[]\"" : "\"") << ".\n";
            std::cout << "[Leak Detector] \tAllocation happened at \"" << m_table[i].fileName << ":" << m_table[i].lineNo
                << "\"\n";
        }
    }

    void record_allocation(void* address, bool isArray, const char* fileName, size_t lineNo) noexcept
    {
        if (address == nullptr) return;

        for (size_t i = 0 ; i < LEAK_DETECTOR_TABLE_SIZE ; ++i) {
            if (m_table[i].address != nullptr) {
                if (m_table[i].address != address) continue;
                std::cout << "\n[Leak Detector] Same address is allocated without deleting.\n";
                std::cout << "[Leak Detector] \tFirst allocation happened at \"" << m_table[i].fileName << ":" << m_table[i].lineNo
                << "\"\n";
                std::cout << "[Leak Detector] \tSecond allocation happened at \"" << fileName << ":" << lineNo << "\"\n" << std::endl;
                exit(-1);
            }

            m_table[i] = { address, isArray, fileName, lineNo };
            return;
        }

        std::cout << "\n[Leak Detector] Leak Detector Table is full.\n" << std::endl;
        exit(-1);
    }

    void record_deletion(void* address, bool isArray) noexcept
    {
        if (address == nullptr) return;

        for (size_t i = 0 ; i < LEAK_DETECTOR_TABLE_SIZE ; ++i) {
            if (m_table[i].address != address) continue;

            if (m_table[i].isArray != isArray) {
                std::cout << "[Leak Detector] Address " << address << " is deleted with a wrong operator." << std::endl;
                std::cout << "[Leak Detector] \tAllocation happened at \"" << m_table[i].fileName << ":" << m_table[i].lineNo
                    << "\"\n";
                exit(-1);
            }

            m_table[i] = EMPTY_TABLE_ENTRY;
            return;
        }

        std::cout << "[Leak Detector] Address " << address << " is deleted without allocation." << std::endl;
        exit(-1);
    }
};

static LeakDetector leakDetector;

void* operator new(size_t count, const char* fileName, size_t lineNo) noexcept
{
    void* ptr = std::malloc(count);
    leakDetector.record_allocation(ptr, false, fileName, lineNo);
    return ptr;
}

void* operator new[](size_t count, const char* fileName, size_t lineNo) noexcept
{
    void* ptr = std::malloc(count);
    leakDetector.record_allocation(ptr, true, fileName, lineNo);
    return ptr;
}

void* operator new(size_t count) noexcept
{
    return operator new(count, "unknown", 0);
}

void* operator new[](size_t count) noexcept
{
    return operator new[](count, "unknown", 0);
}

void operator delete(void* ptr) noexcept
{
    leakDetector.record_deletion(ptr, false);
    std::free(ptr);
}

void operator delete[](void* ptr) noexcept
{
    leakDetector.record_deletion(ptr, true);
    std::free(ptr);
}

void operator delete(void* ptr, size_t count) noexcept
{
    operator delete(ptr);
}

void operator delete[](void* ptr, size_t count) noexcept
{
    operator delete(ptr);
}

void operator delete(void* ptr, const char* fileName, size_t lineNo) noexcept
{
    operator delete(ptr);
}

void operator delete[](void* ptr, const char* fileName, size_t lineNo) noexcept
{
    operator delete[](ptr);
}

void operator delete(void* ptr, size_t count, const char* fileName, size_t lineNo) noexcept
{
    operator delete(ptr);
}

void operator delete[](void* ptr, size_t count, const char* fileName, size_t lineNo) noexcept
{
    operator delete[](ptr);
}
