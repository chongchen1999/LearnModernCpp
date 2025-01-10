#include <iostream>
#include <stdexcept>

template <typename T>
class ThreeDimArray {
private:
    T* data;                        // 存储数据的一维数组
    size_t x_size, y_size, z_size;  // 三维数组的尺寸

    // 计算三维索引转换为一维数组的索引
    size_t getIndex(size_t x, size_t y, size_t z) const {
        if (x >= x_size || y >= y_size || z >= z_size) {
            throw std::out_of_range("Index out of range");
        }
        return x * y_size * z_size + y * z_size + z;
    }

public:
    // 构造函数
    ThreeDimArray(size_t x, size_t y, size_t z)
        : x_size(x), y_size(y), z_size(z) {
        data = new T[x_size * y_size * z_size];  // 分配内存
    }

    // 拷贝构造函数
    ThreeDimArray(const ThreeDimArray& other)
        : x_size(other.x_size), y_size(other.y_size), z_size(other.z_size) {
        data = new T[x_size * y_size * z_size];  // 分配新内存
        std::copy(other.data, other.data + (x_size * y_size * z_size),
                  data);  // 深拷贝数据
    }

    // 拷贝赋值运算符
    ThreeDimArray& operator=(const ThreeDimArray& other) {
        if (this == &other) {
            return *this;  // 自赋值检查
        }

        // 先释放原来的内存
        delete[] data;

        // 分配新内存并深拷贝数据
        x_size = other.x_size;
        y_size = other.y_size;
        z_size = other.z_size;
        data = new T[x_size * y_size * z_size];
        std::copy(other.data, other.data + (x_size * y_size * z_size), data);

        return *this;
    }

    // 析构函数
    ~ThreeDimArray() { delete[] data; }

    // 多维下标运算符重载
    T& operator()(size_t x, size_t y, size_t z) {
        return data[getIndex(x, y, z)];
    }

    const T& operator()(size_t x, size_t y, size_t z) const {
        return data[getIndex(x, y, z)];
    }

    // 获取三维数组的大小
    size_t getXSize() const { return x_size; }
    size_t getYSize() const { return y_size; }
    size_t getZSize() const { return z_size; }
};

int main() {
    // 创建一个 2x3x4 的三维数组，类型为 int
    ThreeDimArray<int> arr(2, 3, 4);

    // 使用下标运算符访问数据
    arr(0, 0, 0) = 1;
    arr(0, 0, 1) = 2;
    arr(1, 2, 3) = 10;

    // 输出一些元素
    std::cout << "arr(0, 0, 0): " << arr(0, 0, 0) << std::endl;
    std::cout << "arr(1, 2, 3): " << arr(1, 2, 3) << std::endl;

    // 测试拷贝构造函数
    ThreeDimArray<int> arr_copy = arr;
    std::cout << "arr_copy(1, 2, 3): " << arr_copy(1, 2, 3) << std::endl;

    // 测试拷贝赋值
    ThreeDimArray<int> arr_assigned(2, 3, 4);
    arr_assigned = arr;
    std::cout << "arr_assigned(1, 2, 3): " << arr_assigned(1, 2, 3)
              << std::endl;

    return 0;
}
