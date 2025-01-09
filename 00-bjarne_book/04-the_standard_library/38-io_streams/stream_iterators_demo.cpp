#include <iostream>
#include <iterator>
#include <algorithm>

int main() {
    std::cout << "Enter integers (end input with Ctrl+D on Unix or Ctrl+Z on Windows):\n";

    // Create input stream iterator for std::cin
    std::istream_iterator<int> input_start{std::cin};
    std::istream_iterator<int> input_end;

    // Create output stream iterator for std::cout
    std::ostream_iterator<int> output{std::cout, ", "};

    // Copy from input to output
    std::copy(input_start, input_end, output);

    std::cout << "\nDone.\n";
    return 0;
}
