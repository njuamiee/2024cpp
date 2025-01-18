#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <vector>

struct Review {
    int version;
    double foodRating;
    double serviceRating;
    double environmentRating;
    std::string timestamp;

    Review(int v, double f, double s, double e, const std::string& t)
        : version(v), foodRating(f), serviceRating(s), environmentRating(e), timestamp(t) {}
};

struct Customer {
    int id;
    std::list<Review> reviews; // Review history (versions)

    Customer() = default; // 默认构造函数
    Customer(int id) : id(id) {}

    void insertReview(double food, double service, double environment, const std::string& timestamp) {
        int version = reviews.empty() ? 1 : reviews.back().version + 1;
        reviews.emplace_back(version, food, service, environment, timestamp);
    }

    void modifyReview(const std::string& dimension, double newRating, const std::string& timestamp) {
        if (reviews.empty()) return;

        Review latest = reviews.back();
        if (dimension == "food") latest.foodRating = newRating;
        else if (dimension == "service") latest.serviceRating = newRating;
        else if (dimension == "environment") latest.environmentRating = newRating;

        latest.version = reviews.back().version + 1;
        latest.timestamp = timestamp;
        reviews.push_back(latest);
    }
};

class ReviewSystem {
private:
    std::unordered_map<int, Customer> customers;

public:
    void insert(int customerId, double food, double service, double environment, const std::string& timestamp) {
        if (customers.find(customerId) == customers.end()) {
            customers.emplace(customerId, Customer(customerId));
        }
        customers[customerId].insertReview(food, service, environment, timestamp);
        std::cout << "Review inserted successfully" << std::endl;
    }

    void modify(int customerId, const std::string& dimension, double newRating, const std::string& timestamp) {
        auto it = customers.find(customerId);
        if (it == customers.end()) {
            std::cout << "Customer ID not found, modification failed" << std::endl;
            return;
        }
        it->second.modifyReview(dimension, newRating, timestamp);
        std::cout << "Modification successful" << std::endl;
    }

    void remove(int customerId) {
        if (customers.erase(customerId)) {
            std::cout << "Deletion successful" << std::endl;
        } else {
            std::cout << "Customer ID not found, deletion failed" << std::endl;
        }
    }

    void displayHistory(int customerId, const std::string& dimension = "") const {
        auto it = customers.find(customerId);
        if (it == customers.end()) return;

        const Customer& customer = it->second;
        if (customer.reviews.empty()) return;

        std::cout << "History:" << std::endl;
        for (auto rit = customer.reviews.rbegin(); rit != customer.reviews.rend(); ++rit) {
            const Review& review = *rit;
            if (dimension.empty()) {
                std::cout << "Version " << review.version
                          << ": Food Rating " << review.foodRating
                          << " Service Rating " << review.serviceRating
                          << " Environment Rating " << review.environmentRating
                          << " Timestamp " << review.timestamp << std::endl;
            } else if (dimension == "food") {
                std::cout << "Version " << review.version
                          << ": Food Rating " << review.foodRating
                          << " Timestamp " << review.timestamp << std::endl;
            } else if (dimension == "service") {
                std::cout << "Version " << review.version
                          << ": Service Rating " << review.serviceRating
                          << " Timestamp " << review.timestamp << std::endl;
            } else if (dimension == "environment") {
                std::cout << "Version " << review.version
                          << ": Environment Rating " << review.environmentRating
                          << " Timestamp " << review.timestamp << std::endl;
            }
        }
    }

    void display(const std::string& dimension = "") const {
        std::vector<std::tuple<int, Review>> latestReviews;
        
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            const int& id = it->first;                 // 获取键
            const Customer& customer = it->second;    // 获取值
            if (customer.reviews.empty()) continue;
            latestReviews.emplace_back(id, customer.reviews.back());
        }

        std::sort(latestReviews.begin(), latestReviews.end(), [](const auto& a, const auto& b) {
            return std::get<1>(a).timestamp > std::get<1>(b).timestamp;
        });

        for (auto it = latestReviews.begin(); it != latestReviews.end(); ++it) {
            const int& id = std::get<0>(*it);
            const Review& latest = std::get<1>(*it);
            if (dimension.empty()) {
                std::cout << "Customer ID " << id
                          << " Food Rating " << latest.foodRating
                          << " Service Rating " << latest.serviceRating
                          << " Environment Rating " << latest.environmentRating
                          << " Timestamp " << latest.timestamp << std::endl;
            } else if (dimension == "food") {
                std::cout << "Customer ID " << id
                          << " Food Rating " << latest.foodRating
                          << " Timestamp " << latest.timestamp << std::endl;
            } else if (dimension == "service") {
                std::cout << "Customer ID " << id
                          << " Service Rating " << latest.serviceRating
                          << " Timestamp " << latest.timestamp << std::endl;
            } else if (dimension == "environment") {
                std::cout << "Customer ID " << id
                          << " Environment Rating " << latest.environmentRating
                          << " Timestamp " << latest.timestamp << std::endl;
            }
        }
    }

    void rangeQuery(double foodLower, double foodUpper, double serviceLower, double serviceUpper, double envLower, double envUpper) const {
        std::vector<int> result;

        for (auto it = customers.begin(); it != customers.end(); ++it) {
            const Customer& customer = it->second;
            if (customer.reviews.empty()) continue;

            const Review& latest = customer.reviews.back();
            if (latest.foodRating >= foodLower && latest.foodRating <= foodUpper &&
                latest.serviceRating >= serviceLower && latest.serviceRating <= serviceUpper &&
                latest.environmentRating >= envLower && latest.environmentRating <= envUpper) {
                result.push_back(it->first);
            }
        }
        
        // 顾客id降序排列
        std::sort(result.begin(), result.end(), std::greater<int>());

        for (int id : result) {
            const Customer& customer = customers.at(id);
            const Review& latest = customer.reviews.back();
            std::cout << "Customer ID " << id
                      << " Food Rating " << latest.foodRating
                      << " Service Rating " << latest.serviceRating
                      << " Environment Rating " << latest.environmentRating
                      << " Timestamp " << latest.timestamp << std::endl;
        }
    }
};

int main() {
    ReviewSystem system;

    int n; // 操作命令的总数
    std::cin >> n;
    std::cin.ignore(); // 忽略换行符

    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(std::cin, line);

        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "insert") {
            int customer_id;
            double food_rating, service_rating, environment_rating;
            std::string timestamp;
            iss >> customer_id >> food_rating >> service_rating >> environment_rating;
            std::getline(iss, timestamp);
            timestamp = timestamp.substr(1); // 去除前导空格
            system.insert(customer_id, food_rating, service_rating, environment_rating, timestamp);
        } 
        else if (command == "modify") {
            int customer_id;
            std::string dimension;
            double new_rating;
            std::string timestamp;
            iss >> customer_id >> dimension >> new_rating;
            std::getline(iss, timestamp);
            timestamp = timestamp.substr(1); // 去除前导空格
            system.modify(customer_id, dimension, new_rating, timestamp);
        } 
        else if (command == "delete") {
            int customer_id;
            iss >> customer_id;
            system.remove(customer_id);
        } 
        else if (command == "history") {
            int customer_id;
            std::string dimension;
            if (iss >> customer_id) {
                if (iss >> dimension) {
                    system.displayHistory(customer_id, dimension);
                } else {
                    system.displayHistory(customer_id);
                }
            }
        } 
        else if (command == "display") {
            std::string dimension;
            if (iss >> dimension) {
                system.display(dimension);
            } else {
                system.display();
            }
        } 
        else if (command == "range_query") {
            double food_lower, food_upper, service_lower, service_upper, env_lower, env_upper;
            iss >> food_lower >> food_upper >> service_lower >> service_upper >> env_lower >> env_upper;
            system.rangeQuery(food_lower, food_upper, service_lower, service_upper, env_lower, env_upper);
        } 
        else {
            std::cout << "Invalid command!" << std::endl;
        }
    }
    return 0;
}
