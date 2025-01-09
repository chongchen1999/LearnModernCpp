#include <bit>
#include <cstdint>
#include <cstring>
#include <iostream>

void binaryToHttpEndian(const void* input, void* output, std::size_t size) {
    if (std::endian::native == std::endian::big) {
        // 如果当前机器是大端序，直接拷贝数据
        std::memcpy(output, input, size);
    } else if (std::endian::native == std::endian::little) {
        // 如果当前机器是小端序，需要将数据转换为大端序
        const uint8_t* src = static_cast<const uint8_t*>(input);
        uint8_t* dest = static_cast<uint8_t*>(output);
        for (std::size_t i = 0; i < size; ++i) {
            dest[i] = src[size - 1 - i];
        }
    } else {
        // 如果当前机器不是大端也不是小端
        std::cerr << "Warning: Unsupported endian type detected.\n";
    }
}

// 测试用例
int main() {
    uint32_t value = 0x12345678;  // 测试数据
    uint32_t convertedValue = 0;

    binaryToHttpEndian(&value, &convertedValue, sizeof(value));

    std::cout << "Original value: 0x" << std::hex << value << "\n";
    std::cout << "Converted value: 0x" << std::hex << convertedValue << "\n";

    return 0;
}
