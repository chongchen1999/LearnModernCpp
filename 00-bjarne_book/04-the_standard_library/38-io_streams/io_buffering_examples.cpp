#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

// Output stream and buffer example
int outputStreamExample() {
    std::ofstream fout("example.txt");
    fout << "0123456789";
    fout.seekp(8);
    fout << '#';
    fout.seekp(-4, std::ios_base::cur);
    fout << '*';
    fout.close();
    return 0;
}

// Input stream and buffer example
int inputStreamExample() {
    std::ifstream fin("example.txt");
    char c;
    fin.get(c);
    fin.putback(c);
    char peeked = fin.peek();
    std::cout << "Peeked character: " << peeked << std::endl;
    fin.sync();
    char buffer[10];
    fin.readsome(buffer, 5);
    buffer[fin.gcount()] = '\0';
    std::cout << "Read characters: " << buffer << std::endl;
    fin.close();
    return 0;
}

// istreambuf_iterator example
int istreambufIteratorExample() {
    std::stringstream ss("Hello, World!");
    std::istreambuf_iterator<char> it(ss);
    std::istreambuf_iterator<char> end;
    while (it!= end) {
        std::cout << *it++;
    }
    return 0;
}

// ostreambuf_iterator example
int ostreambufIteratorExample() {
    std::stringstream ss;
    std::ostreambuf_iterator<char> it(ss);
    std::string str = "Hello, World!";
    for (char c : str) {
        *it++ = c;
    }
    std::cout << ss.str() << std::endl;
    return 0;
}

int main() {
    outputStreamExample();
    inputStreamExample();
    std::cout << "istreambuf_iterator example output:" << std::endl;
    istreambufIteratorExample();
    std::cout << std::endl << "ostreambuf_iterator example output:" << std::endl;
    ostreambufIteratorExample();
    return 0;
}