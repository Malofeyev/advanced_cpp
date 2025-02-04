#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class big_integer {
public:
    friend std::ostream& operator<<(std::ostream& os, const big_integer& big_int);


    big_integer(const std::string& num) {
        sign_ = (num[0] != '-');
        auto digits_rend = (num[0] == '-' || num[0] == '+'?std::prev(num.crend()):num.crend());
         
        for (auto it = num.crbegin(); it != digits_rend; it++) {
            digits_.push_back(*it - '0');
        }
    }

    big_integer(const big_integer&) = default;
    big_integer& operator=(const big_integer&) = default;

    big_integer(big_integer&& other) noexcept 
        : sign_(other.sign_)
        , digits_(std::move(other.digits_)) {}

    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            sign_ = other.sign_;
            digits_ = std::move(other.digits_);
        }
        return *this;
    }

    big_integer operator+(const big_integer& other) const {
        bool sign;
        std::vector<int> digits;

        auto res_compare = this->compare_abs(other);
        bool this_is_lt = (res_compare == ComparatorResult::lt);
        
        const std::vector<int>& lt_digits = (this_is_lt?this->digits_:other.digits_); 
        const std::vector<int>& gt_digits = (this_is_lt?other.digits_:this->digits_); 

        if (sign_ == other.sign_) {
            sign = sign_;
            int shift = 0;
            auto gt_it = gt_digits.cbegin();
            for (auto lt_it = lt_digits.cbegin(); 
                    lt_it != lt_digits.cend(); lt_it++, gt_it++) {
                shift += *lt_it + *gt_it;
                digits.push_back(shift % 10);
                shift /= 10;
            }
            for (; gt_it != gt_digits.cend(); gt_it++) {
                shift += *gt_it;
                digits.push_back(shift % 10);
                shift /= 10;
            }
            if (shift > 0) {
                digits.push_back(shift);
            }

        } else {
            if (res_compare == ComparatorResult::eq) {
               return big_integer{true, std::vector<int>(1)}; 
            }
            int delta = 0;
            auto gt_it = gt_digits.cbegin();
            for (auto lt_it = lt_digits.cbegin(); lt_it != lt_digits.cend(); lt_it++, gt_it++) {
                delta += *gt_it - *lt_it;
                if (delta < 0) {
                    digits.push_back(10 + delta);
                    delta = -1;
                } else {
                    digits.push_back(delta);
                    delta = 0;
                }
            }
            for (; gt_it != gt_digits.cend(); gt_it++) {
                delta += *gt_it;
                if (delta < 0) {
                    digits.push_back(10 + delta);
                    delta = -1;
                } else {
                    digits.push_back(delta);
                    delta = 0;
                }

            }
            auto firts_non_zero_it = std::find_if(digits.crbegin(), digits.crend(), 
                    [](int val) { return val != 0; } );
            auto count_digits = std::distance(firts_non_zero_it, digits.crend());
            digits.resize(count_digits?count_digits:1);

            sign = (this_is_lt?!sign_:sign_);
        }

        return big_integer(sign, std::move(digits));
    }

    big_integer operator*(const big_integer& other) const {
        if (other.digits_.back() == 0 || digits_.back() == 0) {
            return big_integer{true, std::vector<int>(1)};
        }
        bool sign = (sign_ ==  other.sign_);
        std::vector<int> digits;
        
        int i = 0;
        for (auto this_it = digits_.cbegin(); this_it != digits_.cend(); this_it++, i++) {
            int shift = 0;
            auto other_it = other.digits_.cbegin();
            for (int j = 0; digits.cbegin() + j + i != digits.cend(); other_it++, j++) {
                digits[i + j] += shift + *this_it * *other_it;
                shift = digits[i + j] / 10;
                digits[i + j] %= 10;
            }
            for (; other_it != other.digits_.cend(); other_it++) {
                digits.push_back(shift + *this_it * *other_it);
                shift = digits.back() / 10;
                digits.back() %= 10;
            }
            if (shift > 0) {
                digits.push_back(shift);
            }
        }
        return big_integer(sign, std::move(digits));
        
    }

private:

    big_integer(bool sign, std::vector<int>&& digits) 
        : sign_(sign), digits_(std::move(digits)) {}

    enum class ComparatorResult {
        lt,
        eq,
        gt
    };
    ComparatorResult compare_abs(const big_integer& other) const {
        if (digits_.size() < other.digits_.size()) {
            return ComparatorResult::lt;
        } if (digits_.size() > other.digits_.size()) {
            return ComparatorResult::gt;
        } else {
            auto mismatched_its = std::mismatch(digits_.crbegin(), digits_.crend(), 
                    other.digits_.crbegin(), other.digits_.crend());

            if (mismatched_its.first == digits_.crend()) {
                return ComparatorResult::eq;
            } else if (*(mismatched_its.first) < *(mismatched_its.second)) {
                return ComparatorResult::lt;
            } else {
                return ComparatorResult::gt;
            }
        }
    }

private:
    bool sign_;
    std::vector<int> digits_;
};

std::ostream& operator<<(std::ostream& os, const big_integer& big_int) {
    if (!big_int.sign_) {
        os << '-';
    }
    std::for_each(big_int.digits_.crbegin(), big_int.digits_.crend(), [&os](int e) { os << e; });
    return os;
}


int main(int argc, char *argv[]) {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result; // 193099
    return 0;
}
