#include <exception>
#include <future>
#include <iostream>
#include <thread>

void threadFunction() {
  try {
    // Code that might throw an exception
    throw std::runtime_error("Error in thread");
  } catch (...) {
    // Catch all exceptions and report them
    std::cout << "Caught an exception in the thread\n";
  }
}

void threadFunctionWithPromise(std::promise<void> &prom) {
  try {
    // Code that might throw an exception
    throw std::runtime_error("Error in thread");
  } catch (...) {
    // Capture the exception and pass it to the promise
    prom.set_exception(std::current_exception());
  }
}

int main() {
  // Example 1: Catching exceptions in a thread
  std::thread t1(threadFunction);
  t1.join(); // Wait for the thread to finish

  // Example 2: Propagating exceptions between threads
  std::promise<void> prom;
  std::future<void> fut = prom.get_future();

  std::thread t2(threadFunctionWithPromise, std::ref(prom));

  try {
    fut.get(); // Wait for the result from the thread
  } catch (const std::exception &e) {
    std::cout << "Exception caught in main thread: " << e.what() << '\n';
  }

  t2.join(); // Wait for the thread to finish

  return 0;
}
