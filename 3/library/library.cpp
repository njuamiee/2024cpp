#include <iostream>
#include <memory>
#include <string>
#include <cassert>
#include <unordered_map>
#include <functional>
class BorrowStrategy {
    public:
    virtual ~BorrowStrategy() = default;
    virtual double calculate(int days) const = 0;
};
class DailyBorrowStrategy : public BorrowStrategy {
    public:
    DailyBorrowStrategy() {
    }
    double calculate(int days) const override {
    return days * 1.0;
    }
};
// todo: complete MemberBorrowStrategy
class MemberBorrowStrategy : public BorrowStrategy {
    public:
    MemberBorrowStrategy(std::string level)
    : memberLevel(level) {
    }
    double calculate(int days) const override {
    int weeks = days / 7;
    weeks += (days % 7) > 0 ? 1 : 0;
    if (memberLevel == "REGULAR") {
    return weeks * 5 * 0.95;
    } else if (memberLevel == "GOLD") {
    return weeks * 5 * 0.85;
    } else if (memberLevel == "PLATINUM") {
    return weeks * 5 * 0.75;
    }
    }
    private:
    std::string memberLevel;
};
class Book {
    public:
    Book(int id) : id(id) {
    }
    double calculate_fee(int days) const {
        if(borrow_strategy) {
            return borrow_strategy->calculate(days);
        }
    }
    int get_id() const { return id; }
    void setBorrowStrategy(std::shared_ptr<BorrowStrategy> strategy) {
    borrow_strategy = strategy;
    }
    private:
    int id;
    std::shared_ptr<BorrowStrategy> borrow_strategy;
};
class Library {
    public:
    using BookPtr = std::shared_ptr<Book>;
    void add_book(const BookPtr &book) {
    books[book->get_id()] = book;
    }
    void borrow_book(int id, const std::shared_ptr<BorrowStrategy> &strategy) {
        auto it = books.find(id);
        if (it != books.end()) {
        it->second->setBorrowStrategy(strategy);
        }
    }
    double return_books(int days) {
        double total_fee = 0.0;
        for (const auto &book : books) {
            if(book.second->calculate_fee(days) > 0) {
                total_fee += book.second->calculate_fee(days);
            }
        }
        for(auto &book : books) {
            book.second->setBorrowStrategy(nullptr);
        }
        return total_fee;
    }
    private:
    std::unordered_map<int, BookPtr> books;
};
// === TEST_CASES ===
void TEST_1();
void TEST_2();
void TEST_3();
void TEST_4();
void TEST_5();
void TEST_6();
void TEST_7();
#define REGISTER_TEST_CASE(name) {#name, name}
int main() {
std::unordered_map<std::string, std::function<void()> >
test_functions_by_name = {
REGISTER_TEST_CASE(TEST_1), REGISTER_TEST_CASE(TEST_2),
REGISTER_TEST_CASE(TEST_3), REGISTER_TEST_CASE(TEST_4),
REGISTER_TEST_CASE(TEST_5), REGISTER_TEST_CASE(TEST_6),
REGISTER_TEST_CASE(TEST_7),
};
std::string test_case_name;
std::cin >> test_case_name;
auto it = test_functions_by_name.find(test_case_name);
assert(it != test_functions_by_name.end());
auto fn = it->second;
fn();
return 0;
}
void TEST_1() {
Library library;
library.add_book(std::make_shared<Book>(1));
library.add_book(std::make_shared<Book>(2));
library.borrow_book(1, std::make_shared<DailyBorrowStrategy>());
assert(library.return_books(5) == 5.0);
}
void TEST_2() {
Library library;
library.add_book(std::make_shared<Book>(1));
library.add_book(std::make_shared<Book>(2));
library.borrow_book(2, std::make_shared<MemberBorrowStrategy>("GOLD"));
assert(library.return_books(8) == 8.5);
}
void TEST_3() {
Library library;
library.add_book(std::make_shared<Book>(1));
assert(library.return_books(0) == 0.0);
}
void TEST_4() {
Library library;
library.add_book(std::make_shared<Book>(1));
library.add_book(std::make_shared<Book>(2));
library.borrow_book(1, std::make_shared<DailyBorrowStrategy>());
library.borrow_book(2, std::make_shared<MemberBorrowStrategy>("PLATINUM"));
assert(library.return_books(10) == 17.5);
}
void TEST_5() {
Library library;
library.add_book(std::make_shared<Book>(1));
library.add_book(std::make_shared<Book>(2));
library.borrow_book(1, std::make_shared<DailyBorrowStrategy>());
assert(library.return_books(5) == 5.0);
library.borrow_book(2, std::make_shared<MemberBorrowStrategy>("REGULAR"));
assert(library.return_books(7) == 4.75);
}
void TEST_6() {
Library library;
library.add_book(std::make_shared<Book>(1));
library.add_book(std::make_shared<Book>(2));
library.borrow_book(2, std::make_shared<MemberBorrowStrategy>("PLATINUM"));
assert(library.return_books(14) == 7.5);
}
void TEST_7() {
Library library;
library.add_book(std::make_shared<Book>(1));
library.add_book(std::make_shared<Book>(2));
library.borrow_book(1, std::make_shared<DailyBorrowStrategy>());
assert(library.return_books(5) == 5.0);
assert(library.return_books(10000) == 0.0);
}