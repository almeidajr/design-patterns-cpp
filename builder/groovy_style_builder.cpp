#include <vector>
#include <iostream>

namespace html {
    class Tag {
    public:
        std::string name;
        std::string text;
        std::vector<Tag> children;
        std::vector<std::pair<std::string, std::string>> attributes;

        friend std::ostream &operator<<(std::ostream &os, const Tag &tag) {
            os << "<" << tag.name;
            for (const auto &attr: tag.attributes) {
                os << " " << attr.first << "=\"" << attr.second << "\"";
            }
            if (tag.children.empty()) {
                os << "/>" << std::endl;
            } else {
                os << ">" << std::endl;
                if (tag.text.length() > 0) {
                    os << tag.text << std::endl;
                }
                for (const auto &child: tag.children) {
                    os << child;
                }
                os << "</" << tag.name << ">" << std::endl;
            }
            return os;
        }

    protected:
        Tag(std::string name, std::string text) : name(std::move(name)), text(std::move(text)) {}

        Tag(std::string name, std::vector<Tag> children) : name(std::move(name)), children(std::move(children)) {}
    };

    class P : public Tag {
    public:
        explicit P(const std::string &text) : Tag("p", text) {}

        P(std::initializer_list<Tag> children) : Tag("p", children) {}
    };

    class Img : public Tag {
    public:
        explicit Img(const std::string &src) : Tag("img", "") {
            attributes.emplace_back(make_pair("src", src));
        }
    };

}

int main() {
    std::cout <<
              html::P{
                      html::Img{"cat.jpg"},
                      html::Img{"dog.jpg"}
              }
              << std::endl;

    return 0;
}
