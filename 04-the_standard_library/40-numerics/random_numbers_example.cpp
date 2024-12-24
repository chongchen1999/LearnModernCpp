#include <iostream>
#include <random>
#include <functional>
#include <map>
#include <algorithm>
#include <iterator>
#include <cstdlib>

// Avoid using 'using namespace std;'


// Custom Rand_int class
class Rand_int {
public:
    Rand_int(int lo, int hi) 
        : p(lo, hi), 
          engine(std::random_device{}()), 
          dist(p), 
          r(std::bind(dist, engine)) 
    {}
    
    int operator()() { return r(); }
    
private:
    std::uniform_int_distribution<int>::param_type p;
    std::default_random_engine engine;
    std::uniform_int_distribution<int> dist;
    std::function<int()> r;
};

// Custom Rand_double class
class Rand_double {
public:
    Rand_double(double low, double high) 
        : engine(std::random_device{}()), 
          dist(low, high) 
    {}
    
    double operator()() { return dist(engine); }
    
private:
    std::default_random_engine engine;
    std::uniform_real_distribution<double> dist;
};

// Sampling algorithm
template<typename Iter, typename Size, typename Out, typename Gen>
Out random_sample(Iter first, Iter last, Out result, Size n, Gen&& gen) {
    using Dist = std::uniform_int_distribution<Size>;
    using Param = typename Dist::param_type;
    std::copy_n(first, n, result);
    std::advance(first, n);
    Dist dist;
    for (Size k = n; first != last; ++first, ++k) {
        Size r = dist(gen, Param{0, k});
        if (r < n)
            *(result + r) = *first;
    }
    return result;
}

int main() {
    // Using custom Rand_int and Rand_double
    Rand_int ri{10, 20};
    Rand_double rdouble{0, 0.5};
    
    for (int i = 0; i < 100; ++i)
        std::cout << ri() << " ";
    std::cout << std::endl;
    
    for (int i = 0; i < 100; ++i)
        std::cout << rdouble() << " ";
    std::cout << std::endl;

    // Using standard random number engine and distribution
    auto gen = std::bind(std::normal_distribution<double>{15, 4.0}, std::default_random_engine{});
    for (int i = 0; i < 500; ++i) std::cout << gen() << " ";
    std::cout << std::endl;

    // Demonstrating linear_congruential_engine
    std::map<int, int> m;
    std::linear_congruential_engine<unsigned int, 17, 5, 0> linc_eng;
    for (int i = 0; i < 1000000; ++i)
        if (1 < ++m[linc_eng()]) std::cout << i << std::endl;

    // Demonstrating independent_bits_engine
    std::independent_bits_engine<std::default_random_engine, 4, unsigned int> ibe;
    for (int i = 0; i < 100; ++i)
        std::cout << '0' + ibe() << " ";
    std::cout << std::endl;

    // Demonstrating random_device
    std::random_device rd_device;  // Renamed from rd to rd_device
    double entropy = rd_device.entropy();
    std::cout << "Entropy: " << entropy << std::endl;

    // Demonstrating uniform_int_distribution
    std::uniform_int_distribution<int> uid1{1, 100};
    std::default_random_engine e(std::random_device{}());
    for (int i = 0; i < 20; ++i)
        std::cout << uid1(e) << " ";
    std::cout << std::endl;

    // Demonstrating C - style random numbers
    srand(123);
    int num = rand();
    std::cout << "C - style random number: " << num << std::endl;

    return 0;
}
