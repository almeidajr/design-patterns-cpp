#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <memory>

using namespace std;

struct HtmlBuilder;

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

    static unique_ptr<HtmlBuilder> build(const string &root_name) {
        return make_unique<HtmlBuilder>(root_name);
    }
};

struct HtmlBuilder {
    HtmlElement root;

    explicit HtmlBuilder(const string &root_name) {
        root.name = root_name;
    }

    HtmlBuilder *add_child(string child_name, string child_text) {
        HtmlElement e{std::move(child_name), std::move(child_text)};
        root.elements.emplace_back(e);
        return this;
    }

    string str() const {
        return root.str();
    }

    explicit operator HtmlElement() const { return root; }
};


int main() {
    auto builder = HtmlElement::build("body");
    builder
            ->add_child("h1", "hello, world")
            ->add_child("p", "this is a test")
            ->add_child("p", "another test");
    cout << builder->str() << endl;

    return 0;
}
