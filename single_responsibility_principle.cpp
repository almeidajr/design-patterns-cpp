#include <iostream>
#include <utility>
#include <vector>
#include <fstream>

using namespace std;

struct Journal {
    string title;
    vector<string> entries;

    explicit Journal(string title) : title{std::move(title)} {}

    void add_entry(const string &entry) {
        static int count = 1;
        entries.push_back(to_string(count++) + ": " + entry);
    }
};

struct PersistenceManager {
    static void save(const Journal &j, const string &filename) {
        ofstream ofs(filename);
        for (const auto &e: j.entries) {
            ofs << e << endl;
        }
    }
};

int main() {
    Journal journal{"Dear Diary"};
    journal.add_entry("I ate a bug");
    journal.add_entry("I cried today");

    PersistenceManager pm;
    pm.save(journal, "journal.txt");
    return 0;
}
