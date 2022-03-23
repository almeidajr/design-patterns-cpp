#include <iostream>
#include <vector>

using namespace std;

struct Document;

struct IPrinter {
    virtual void print(Document &doc) = 0;
};

struct Printer : IPrinter {
    void print(Document &doc) override {
        cout << "Printing document" << endl;
    }
};

struct IScanner {
    virtual void scan(Document &doc) = 0;
};

struct Scanner : IScanner {
    void scan(Document &doc) override {
        cout << "Scanning document" << endl;
    }
};

struct IMachine : IPrinter, IScanner {
};

struct Machine : IMachine {
    IPrinter &printer;
    IScanner &scanner;

    Machine(IPrinter &printer, IScanner &scanner) : printer{printer}, scanner{scanner} {}

    void print(Document &doc) override {
        printer.print(doc);
    }

    void scan(Document &doc) override {
        scanner.scan(doc);
    }
};


int main() {
    Printer printer;
    Scanner scanner;
    Machine machine{printer, scanner};

    return 0;
}
