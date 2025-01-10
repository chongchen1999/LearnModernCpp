#include <iostream>
#include <type_traits>

// 定义scoped enumeration
enum class Permission : unsigned int {
    None = 0,
    Read = 1 << 0,
    Write = 1 << 1,
    Exec = 1 << 2
};

constexpr Permission operator|(Permission lhs, Permission rhs) {
    using T = std::underlying_type_t<Permission>;
    return static_cast<Permission>(static_cast<T>(lhs) | static_cast<T>(rhs));
}

constexpr Permission operator&(Permission lhs, Permission rhs) {
    using T = std::underlying_type_t<Permission>;
    return static_cast<Permission>(static_cast<T>(lhs) & static_cast<T>(rhs));
}

// 辅助函数用于检查Permission是否包含某个选项
constexpr bool hasPermission(Permission value, Permission flag) {
    return (value & flag) == flag;
}

int main() {
    Permission p1 = Permission::Read | Permission::Write;

    // 检查权限
    if (hasPermission(p1, Permission::Read)) {
        std::cout << "Has Read permission" << std::endl;
    }

    if (hasPermission(p1, Permission::Exec)) {
        std::cout << "Has Exec permission" << std::endl;
    } else {
        std::cout << "Does not have Exec permission" << std::endl;
    }

    return 0;
}
