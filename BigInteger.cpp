#include <iostream>
#include <string>

class big_integer
{
private:
    std::string number;
public:
    big_integer() =  default;
    explicit big_integer(const std::string& number) : number(number)
    {}
    big_integer(big_integer&& other) noexcept
    {
        number = std::move(other.number);
    }
    big_integer& operator= (big_integer&& other) noexcept
    {
        if (this == &other)
            return *this;
        number = std::move(other.number);
    
        return *this;
    }
    big_integer operator+ (const big_integer& other)
    {
        big_integer result;
        int maxSize = (number.size() >= other.number.size()) ? number.size() : other.number.size();
        result.number.resize(maxSize + 1, '0');
        int a = number.size() - 1, b = other.number.size() - 1, c = result.number.size() - 1;
        while (a >= 0 && b >= 0)
        {
            result.number[c] += (number[a] - '0' + other.number[b] - '0');
            --a; --b; --c;
        }
        while (c)
        {
            if (a < 0)
            {
                result.number[c] += other.number[b] - '0';
                --b; --c;
            }
            if (b < 0)
            {
                result.number[c] += number[a] - '0';
                --a; --c;
            }
        }
        for (int i = result.number.size() - 1; i > 0; --i)
        {
            if (result.number[i] > '9')
            {
                result.number[i] -= 10;
                result.number[i - 1]++;
            }
        }
        if (result.number[0] == '0')
            result.number.erase(0, 1);

        return result;
    }
    big_integer& operator*= (int coeff)
    {
        if (!coeff)
        {
            number.clear();
            return *this;
        }
        std::string result;
        std::string coeffStr = std::to_string(coeff);
        result.resize(number.size() + coeffStr.size(), 0);
        int shift = 0;
        for (int b = coeffStr.size() - 1, shift = 0; b >= 0; --b, ++shift)
        {
            for (int a = number.size() - 1, c = result.size() - 1- shift; a >= 0; --a, --c)
            {
                int mult = (number[a] - '0') * (coeffStr[b] - '0');
                int sum = mult + result[c];

                result[c] = sum % 10;
                result[c - 1] += (sum / 10);
            }
        }
        for (int i = 0; i < result.size(); ++i)
            result[i] += '0';
        if (result[0] == '0')
            result.erase(0, 1);
        number = result;

        return *this;
    }
    big_integer operator* (int coeff)
    {
        big_integer result(this->number);
        result *= coeff;

        return result;
    }
    friend std::ostream& operator<< (std::ostream& os, const big_integer& ex);
};

std::ostream& operator<< (std::ostream& os, const big_integer& ex)
{
    if (ex.number.empty())
        os << '0';
    else
        os << ex.number;
    
    return os;
}

int main()
{
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << std::endl;

    auto number3 = big_integer("114575");
    auto result2 = number3 * 78524;
    std::cout << result2 << std::endl;

    number1 *= 78524;
    std::cout << number1 << std::endl;
    
    return EXIT_SUCCESS;
}
