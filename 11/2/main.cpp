#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class big_integer {
public:
    friend std::ostream& operator<<(std::ostream& os, const big_integer& big_int);


    big_integer(const std::string& num) {
        sign_ = (num[0] != '-');
        int first_digit_idx = (num[0] == '-' || num[0] == '+'?1:0);
        
        for (int j = num.length() - 1; j >= first_digit_idx; j--) {
            digits_.push_back(num[j] - '0');
        }
    }

    big_integer(const big_integer&) = default;
    big_integer& operator=(const big_integer&) = default;

    big_integer(big_integer&& other) 
        : sign_(other.sign_)
        , digits_(std::move(other.digits_)) {}

    big_integer& operator=(big_integer&& other) {
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
            for (int i = 0; i < lt_digits.size(); i++) {
                shift += lt_digits[i] + gt_digits[i];
                digits.push_back(shift % 10);
                shift /= 10;
            }
            for (int i = lt_digits.size(); i < gt_digits.size(); i++) {
                shift += gt_digits[i];
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
            for (int i = 0 ; i < lt_digits.size(); i++) {
                delta += gt_digits[i] - lt_digits[i];
                if (delta < 0) {
                    digits.push_back(10 + delta);
                    delta = -1;
                } else {
                    digits.push_back(delta);
                    delta = 0;
                }
            }
            for (int i = lt_digits.size(); i < gt_digits.size(); i++) {
                delta += gt_digits[i];
                if (delta < 0) {
                    digits.push_back(10 + delta);
                    delta = -1;
                } else {
                    digits.push_back(delta);
                    delta = 0;
                }

            }
            int i = digits.size() - 1;
            while (i >= 0 && digits[i] == 0) {
                i--;
            }
            digits.resize(std::max(1, i + 1));

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

        for (int i = 0; i < digits_.size(); i++) {
            int shift = 0;
            int j = 0;
            for (; j + i < digits.size(); j++) {
                digits[i + j] += shift + digits_[i] * other.digits_[j];
                shift = digits[i + j] / 10;
                digits[i + j] %= 10;
            }
            for (; j < other.digits_.size(); j++) {
                digits.push_back(shift + digits_[i] * other.digits_[j]);
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
            int i = digits_.size() - 1;
            while (i >= 0 && digits_[i] == other.digits_[i]) {
                i--;
            }

            if (i < 0) {
                return ComparatorResult::eq;
            } else if (digits_[i] < other.digits_[i]) {
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
    std::for_each(big_int.digits_.rbegin(), big_int.digits_.rend(), [&os](int e) { os << e; });
    return os;
}


int main(int argc, char *argv[]) {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result; // 193099
    return 0;
}
