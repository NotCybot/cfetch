#include <iostream>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>

int main() {
    int nm[2];
    size_t len = 4;
    uint32_t count;

    // Anzahl der CPU-Kerne
    nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);

    if(count < 1) {
        nm[1] = HW_NCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);
        if(count < 1) { count = 1; }
    }
    std::cout << "Anzahl der CPU-Kerne: " << count << std::endl;

    // Größe des physischen Speichers
    int64_t memorySize;
    len = sizeof(memorySize);
    sysctlbyname("hw.memsize", &memorySize, &len, NULL, 0);
    std::cout << "Größe des physischen Speichers: " << memorySize / (1024 * 1024) << " MB" << std::endl;

    return 0;
}