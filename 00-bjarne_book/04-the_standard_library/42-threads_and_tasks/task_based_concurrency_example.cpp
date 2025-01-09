#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <exception>
#include <chrono>
#include <thread>
#include <cassert>

using namespace std;

// Assume Record is defined elsewhere
struct Record {
    int price;
    enum class Color { red, blue, green } color;
    
    // Add operator<< for printing Records
    friend std::ostream& operator<<(std::ostream& os, const Record& r) {
        os << "Price: " << r.price << ", Color: ";
        switch(r.color) {
            case Color::red: os << "red"; break;
            case Color::blue: os << "blue"; break;
            case Color::green: os << "green"; break;
        }
        return os;
    }
};

// Global data to be searched
vector<Record> goods;

// Number of records for a linear search
const int grain = 50000;

// Implement wait_for_all
template<typename T>
vector<T> wait_for_all(vector<future<T>>& vf) {
    vector<T> res;
    res.reserve(vf.size());  // Optimization: pre-allocate space
    for (auto& fu : vf) {
        if (fu.valid()) {  // Check if future is valid before getting
            res.push_back(fu.get());
        }
    }
    return res;
}

// Implement wait_for_any with timeout handling
template<typename T>
int wait_for_any(vector<future<T>>& vf, std::chrono::steady_clock::duration d) {
    const auto start_time = std::chrono::steady_clock::now();
    const auto timeout = std::chrono::seconds{1};  // Add overall timeout
    
    while (std::chrono::steady_clock::now() - start_time < timeout) {
        for (int i = 0; i < vf.size(); ++i) {  // Changed != to < for consistency
            if (!vf[i].valid()) continue;
            auto status = vf[i].wait_for(d);
            switch (status) {
                case std::future_status::ready:
                    return i;
                case std::future_status::timeout:
                    break;
                case std::future_status::deferred:
                    throw std::runtime_error("wait_for_any(): deferred future");
            }
        }
        std::this_thread::sleep_for(d);
    }
    throw std::runtime_error("wait_for_any(): timeout");
}

// Sequential find task
template<typename Pred>
Record* find_rec(vector<Record>& vr, int first, int last, Pred pr) {
    // Bounds checking
    if (first < 0 || last > static_cast<int>(vr.size()) || first >= last) {
        return nullptr;
    }
    
    auto it = std::find_if(vr.begin() + first, vr.begin() + last, pr);
    return (it != vr.begin() + last) ? &(*it) : nullptr;
}

// Parallel find (pfind)
template<typename Pred>
Record* pfind(vector<Record>& vr, Pred pr) {
    if (vr.empty()) return nullptr;
    
    const int chunk_size = std::min(grain, static_cast<int>(vr.size()));
    vector<future<Record*>> res;
    
    for (size_t i = 0; i < vr.size(); i += chunk_size) {
        int end = std::min(static_cast<int>(i + chunk_size), static_cast<int>(vr.size()));
        res.push_back(async(launch::async, find_rec<Pred>, ref(vr), i, end, pr));
    }
    
    for (auto& future : res) {
        if (auto p = future.get()) {
            return p;
        }
    }
    return nullptr;
}

// Find all records in a segment
template<typename Pred>
vector<Record*> find_all_rec(vector<Record>& vr, int first, int last, Pred pr) {
    if (first < 0 || last > static_cast<int>(vr.size()) || first >= last) {
        return {};
    }
    
    vector<Record*> res;
    for (int i = first; i < last; ++i) {
        if (pr(vr[i])) {
            res.push_back(&vr[i]);
        }
    }
    return res;
}

// pfind_all
template<typename Pred>
vector<Record*> pfind_all(vector<Record>& vr, Pred pr) {
    if (vr.empty()) return {};
    
    const int chunk_size = std::min(grain, static_cast<int>(vr.size()));
    vector<future<vector<Record*>>> res;
    
    for (size_t i = 0; i < vr.size(); i += chunk_size) {
        int end = std::min(static_cast<int>(i + chunk_size), static_cast<int>(vr.size()));
        res.push_back(async(launch::async, find_all_rec<Pred>, ref(vr), i, end, pr));
    }
    
    auto r2 = wait_for_all(res);
    vector<Record*> r;
    for (const auto& x : r2) {
        r.insert(r.end(), x.begin(), x.end());
    }
    return r;
}

// Sequential find for one match
void just_find_cheap_red() {
    auto p = find_if(goods.begin(), goods.end(),
                    [](const Record& r) { return r.price < 200 && r.color == Record::Color::red; });
    if (p != goods.end()) {
        std::cout << "record " << *p << '\n';
    } else {
        std::cout << "not found\n";
    }
}

// Sequential find for all matches
void just_find_all_cheap_red() {
    if (goods.empty()) {
        std::cout << "no records\n";
        return;
    }
    
    auto vp = find_all_rec(goods, 0, goods.size(),
                          [](const Record& r) { return r.price < 200 && r.color == Record::Color::red; });
    if (vp.empty()) {
        std::cout << "no matching records\n";
    } else {
        for (const auto* p : vp) {
            std::cout << "record " << *p << '\n';
        }
    }
}

// Parallel find for one match
void find_cheap_red() {
    if (goods.empty()) {
        std::cout << "no records\n";
        return;
    }
    
    Record* p = pfind(goods,
                     [](const Record& r) { return r.price < 200 && r.color == Record::Color::red; });
    if (p) {
        std::cout << "record " << *p << '\n';
    } else {
        std::cout << "not found\n";
    }
}

// Parallel find for all matches
void find_all_cheap_red() {
    if (goods.empty()) {
        std::cout << "no records\n";
        return;
    }
    
    auto vp = pfind_all(goods,
                       [](const Record& r) { return r.price < 200 && r.color == Record::Color::red; });
    if (vp.empty()) {
        std::cout << "no matching records\n";
    } else {
        for (const auto* p : vp) {
            std::cout << "record " << *p << '\n';
        }
    }
}

int main() {
    try {
        // Initialize goods with some test data
        goods = {
            {100, Record::Color::red},
            {300, Record::Color::blue},
            {150, Record::Color::red},
            {200, Record::Color::green}
        };

        std::cout << "Testing sequential search:\n";
        just_find_cheap_red();
        just_find_all_cheap_red();

        std::cout << "\nTesting parallel search:\n";
        find_cheap_red();
        find_all_cheap_red();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}