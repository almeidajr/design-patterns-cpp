#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <memory>

using namespace std;

struct HtmlElement {
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 4;

    HtmlElement() = default;

    HtmlElement(string name, string text) : name(std::move(name)), text(std::move(text)) {}

    string str(size_t indent = 0) const {
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (!text.empty()) {
            oss << string(indent_size * (indent + 1), ' ') << text << endl;
        }
        for (const auto &e: elements) {
            oss << e.str(indent + 1);
        }
        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }
};

struct HtmlBuilder {
    HtmlElement root;

    explicit HtmlBuilder(const string &root_name) {
        root.name = root_name;
    }

    HtmlBuilder &add_child(const string &child_name, const string &child_text) {
        HtmlElement e(child_name, child_text);
        root.elements.emplace_back(std::move(e));
        return *this;
    }

    string str() const {
        return root.str();
    }
};


int main() {
    HtmlBuilder builder{"body"};
    builder.add_child("h1", "hello, world").add_child("p", "this is a test").add_child("p", "another test");
    cout << builder.str() << endl;

    return 0;
}
