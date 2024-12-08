#include <iostream>

namespace Graph_lib {
    class Shape { /* Graphical Shape */ };
    class Line : public Shape { /* Graphical Line */ };
    class Poly_line : public Shape { /* Sequence of Lines */ };
    class Text : public Shape { /* Text as a graphical object */ };
    
    Shape operator+(const Shape&, const Shape&) { return Shape(); }
    struct Graph_reader { /* Reader for graphical shapes */ };
    Graph_reader open(const char* filename) {
        std::cout << "Opening graphical shapes file: " << filename << "\n";
        return Graph_reader();
    }
}

namespace Text_lib {
    class Glyph { /* Text glyph */ };
    class Word { /* Sequence of glyphs */ };
    class Line { /* Sequence of words */ };
    class Text { /* Sequence of lines */ };
    
    Word operator+(const Line&, const Line&) { return Word(); }
    struct File { /* File for text data */ };
    File* open(const char* filename) {
        std::cout << "Opening text file: " << filename << "\n";
        return new File();
    }
}

int main() {
    Graph_lib::Line graphLine;
    Text_lib::Line textLine;
    
    auto graphFile = Graph_lib::open("shapes.dat");
    auto textFile = Text_lib::open("document.txt");
    
    delete textFile; // Clean up dynamically allocated memory
    return 0;
}
