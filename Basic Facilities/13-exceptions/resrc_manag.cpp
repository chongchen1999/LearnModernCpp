#include <cstdio>
#include <stdexcept>
#include <string>
#include <mutex>
#include <memory>
#include <iostream>

class File_ptr {
    FILE* p; // The managed resource (file pointer)
public:
    File_ptr(const char* n, const char* a) : p{fopen(n, a)} {
        if (!p) throw std::runtime_error{"File_ptr: Can't open file"};
    }

    File_ptr(const std::string& n, const char* a) : File_ptr{n.c_str(), a} {}

    ~File_ptr() {
        if (p) fclose(p);
    }

    operator FILE*() { return p; }
};

class Locked_file_handle {
    File_ptr file;
    std::unique_lock<std::mutex> lck;
public:
    Locked_file_handle(const char* file_name, std::mutex& m)
        : file{file_name, "rw"}, lck{m} {}
};

void use_file(const char* fn) {
    File_ptr f{fn, "r"};
    // ... use f ...
}

void use_locked_file(const char* file_name, std::mutex& m) {
    Locked_file_handle resource{file_name, m};
    // Resources are managed automatically
}

void use_smart_pointer() {
    std::unique_ptr<int[]> data{new int[10]};
    // ... use data ...
}

int main() {
    try {
        use_file("example.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    std::mutex m;
    try {
        use_locked_file("example.txt", m);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    use_smart_pointer();

    return 0;
}
