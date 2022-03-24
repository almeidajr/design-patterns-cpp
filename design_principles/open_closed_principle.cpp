#include <iostream>
#include <vector>

using namespace std;

enum Color {
    kRed, kGreen, kBlue
};

enum Size {
    kSmall, kMedium, kLarge
};

struct Product {
    string name;
    Color color;
    Size size;
};

template<typename T>
struct AndSpecification;

template<typename T>
struct Specification {
    virtual ~Specification() = default;

    virtual bool is_satisfied(T *item) const = 0;

    AndSpecification<T> operator&&(Specification<T> &other) {
        return AndSpecification<T>(*this, other);
    }
};

struct ColorSpecification : Specification<Product> {
    Color color;

    explicit ColorSpecification(const Color color) : color{color} {}

    bool is_satisfied(Product *item) const override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product> {
    Size size;

    explicit SizeSpecification(const Size size) : size{size} {}

    bool is_satisfied(Product *item) const override {
        return item->size == size;
    }
};

template<typename T>
struct AndSpecification : Specification<T> {
    const Specification<T> &first;
    const Specification<T> &second;

    AndSpecification(const Specification<T> &first, const Specification<T> &second) : first(first), second(second) {}

    bool is_satisfied(T *item) const override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

template<typename T>
struct Filter {
    virtual vector<T *> filter(const vector<T *> &items, Specification<T> &spec) = 0;
};

struct ProductFilter : Filter<Product> {
    vector<Product *> filter(const vector<Product *> &items, Specification<Product> &spec) override {
        vector<Product *> result;
        for (auto &p: items) {
            if (spec.is_satisfied(p)) {
                result.push_back(p);
            }
        }
        return result;
    }
};

int main() {
    Product apple{"Apple", Color::kGreen, Size::kSmall};
    Product tree{"Tree", Color::kRed, Size::kLarge};
    Product house{"House", Color::kBlue, Size::kMedium};
    Product car{"Car", Color::kGreen, Size::kLarge};

    vector<Product *> products{&apple, &tree, &house, &car};
    ProductFilter pf;
    ColorSpecification green(Color::kGreen);
    for (auto &p: pf.filter(products, green)) {
        cout << p->name << endl;
    }
    SizeSpecification large(Size::kLarge);
    AndSpecification<Product> green_and_large(green, large);
    for (auto &p: pf.filter(products, green_and_large)) {
        cout << p->name << endl;
    }
    ColorSpecification red(Color::kRed);
    auto red_and_large = red && large;
    for (auto &p: pf.filter(products, red_and_large)) {
        cout << p->name << endl;
    }

    return 0;
}
