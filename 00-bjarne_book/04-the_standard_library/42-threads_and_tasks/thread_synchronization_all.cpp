#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <list>
#include <functional>
#include <system_error>
#include <condition_variable>

// Define the types
class Message {};
class Image {};
class Y {};

namespace ThreadSync {

    // Mutex examples
    std::mutex cout_mutex;

    void hello() {
        cout_mutex.lock();
        std::cout << "Hello, ";
        cout_mutex.unlock();
    }

    void world() {
        cout_mutex.lock();
        std::cout << "World!";
        cout_mutex.unlock();
    }

    std::recursive_mutex recursive_cout_mutex;

    // Correct the recursive_write function
    template<typename Arg, typename... Args>
    void recursive_write(Arg a, Args... tail) {
        recursive_cout_mutex.lock();
        std::cout << a;
        (void)std::initializer_list<int>{(std::cout << tail, 0)...};
        recursive_cout_mutex.unlock();
    }

    std::timed_mutex timed_imtx;
    Image timed_buf;

    void timed_next() {
        while (true) {
            Image next_image;
            //... compute...
            if (timed_imtx.try_lock_for(std::chrono::milliseconds{100})) {
                timed_buf = next_image;
                timed_imtx.unlock();
            }
        }
    }


    // Multiple locks example
    std::mutex mtx1;
    std::mutex mtx2;

    void multiple_locks_task(std::mutex& m1, std::mutex& m2) {
        std::unique_lock<std::mutex> lck1{m1, std::defer_lock};
        std::unique_lock<std::mutex> lck2{m2, std::defer_lock};
        std::lock(lck1, lck2);
        //... use resources...
    }


    // call_once example
    class X {
    public:
        X();
    private:
        static std::once_flag static_flag;
        static Y static_data_for_class_X;
        static void init();
    };

    std::once_flag X::static_flag;
    Y X::static_data_for_class_X;

    void X::init() {
        // Initialize static_data_for_class_X
    }

    X::X() {
        std::call_once(static_flag, init);
    }


    // Condition variable examples
    template<typename T>
    class Sync_queue {
    public:
        void put(const T& val);
        void put(T&& val);
        void get(T& val);
        void get(T& val, std::chrono::steady_clock::duration d);
        void put(T val, std::chrono::steady_clock::duration d, int n);
    private:
        std::mutex mtx;
        std::condition_variable cond;
        std::list<T> q;
    };

    template<typename T>
    void Sync_queue<T>::put(const T& val) {
        std::lock_guard<std::mutex> lck(mtx);
        q.push_back(val);
        cond.notify_one();
    }

    template<typename T>
    void Sync_queue<T>::get(T& val) {
        std::unique_lock<std::mutex> lck(mtx);
        cond.wait(lck, [this] { return!q.empty(); });
        val = q.front();
        q.pop_front();
    }

    template<typename T>
    void Sync_queue<T>::get(T& val, std::chrono::steady_clock::duration d) {
        std::unique_lock<std::mutex> lck(mtx);
        bool not_empty = cond.wait_for(lck, d, [this] { return!q.empty(); });
        if (not_empty) {
            val = q.front();
            q.pop_front();
        }
        else {
            std::error_code ec;
            throw std::system_error(ec, "Sync_queue: get() timeout");
        }
    }

    template<typename T>
    void Sync_queue<T>::put(T val, std::chrono::steady_clock::duration d, int n) {
        std::unique_lock<std::mutex> lck(mtx);
        bool not_full = cond.wait_for(lck, d, [this, n] { return q.size() < n; });
        if (not_full) {
            q.push_back(val);
            cond.notify_one();
        }
        else {
            std::error_code ec;
            throw std::system_error(ec, "Sync_queue: put() timeout");
        }
    }

    Sync_queue<Message> sync_mq;

    void producer() {
        while (true) {
            Message m;
            //... fill m...
            try {
                sync_mq.put(m, std::chrono::milliseconds{200}, 10);
            }
            catch (const std::system_error& e) {
                std::cerr << e.what() << '\n';
            }
        }
    }

    void consumer() {
        while (true) {
            Message m;
            try {
                sync_mq.get(m, std::chrono::milliseconds{200});
            }
            catch (const std::system_error& e) {
                std::cerr << e.what() << '\n';
            }
            //... use m...
        }
    }

}


int main() {
    // Mutex example calls
    std::thread t1{ThreadSync::hello};
    std::thread t2{ThreadSync::world};
    t1.join();
    t2.join();

    // Recursive mutex example call
    ThreadSync::recursive_write("Hello,", "World!");

    // Timed mutex example - creating a thread but not waiting for it to finish for simplicity
    std::thread timed_thread{ThreadSync::timed_next};

    // Multiple locks example calls
    std::thread t3{ThreadSync::multiple_locks_task, std::ref(ThreadSync::mtx1), std::ref(ThreadSync::mtx2)};
    std::thread t4{ThreadSync::multiple_locks_task, std::ref(ThreadSync::mtx2), std::ref(ThreadSync::mtx1)};
    t3.join();
    t4.join();

    // call_once example
    ThreadSync::X x;

    // Condition variable example calls
    std::thread producer_thread{ThreadSync::producer};
    std::thread consumer_thread{ThreadSync::consumer};
    producer_thread.join();
    consumer_thread.join();

    // Joining the timed thread at the end
    timed_thread.join();

    return 0;
}
