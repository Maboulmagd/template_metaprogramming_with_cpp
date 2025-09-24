#include <iostream>

/*
Goal: Start with simple templates; understand instantiation and specialization.
Challenges:

Implement a templated min / max / clamp function.

Write a templated swap function that works for any type.

Create a simple wrapper class Box<T> that holds a value of type T and implements get() and set().

Optional: implement template aliases like using IntBox = Box<int>;.
 */

namespace MTL
{
    template <typename T>
    [[nodiscard]] constexpr T max(const T& first, const T& second)
    {
        return first > second ? first : second;
    }

    template <typename T>
    [[nodiscard]] constexpr T min(const T& first, const T& second)
    {
        return first < second ? first : second;
    }

    template <typename T>
    [[nodiscard]] constexpr T clamp(const T& value, const T& lower_bound, const T& upper_bound)
    {
        if (value < lower_bound)
        {
            return lower_bound;
        }
        if (value > upper_bound)
        {
            return upper_bound;
        }
        return value;
    }

    template <typename T>
    void swap(T& first, T& second)
    {
        T temp = std::move(first);
        first = std::move(second);
        second = std::move(temp);
    }

    template <typename T>
    class Box
    {
    public:
        template<typename U>
        void set(U&& value)
        {
            this->value_ = std::forward<U>(value);
        }
        [[nodiscard]] const T& get() const
        {
            return this->value_;
        }
    private:
        T value_;
    };


}


int main(int argc, char** argv)
{
    std::println("{}", MTL::max(5, 10));
    std::cout << MTL::max(5, 10) << std::endl;

    std::println("{}", MTL::min(5, 10));
    std::cout << MTL::min(5, 10) << std::endl;

    std::println("{}", MTL::clamp(15, 0, 10));
    std::println("{}", MTL::clamp(-5, 0, 10));
    std::println("{}", MTL::clamp(5, 0, 10));

    int x = 5;
    int y = 10;

    std::println("Before swapping: x={}, y={}", x, y);
    MTL::swap(x, y);
    std::println("After swapping: x={}, y={}", x, y);

    std::string hello = "Hello";
    std::string world = "World";

    std::println("Before swapping: hello={}, world={}", hello, world);
    MTL::swap(hello, world);
    std::println("After swapping: hello={}, world={}", hello, world);

    MTL::Box<int> box;
    box.set(5);
    std::println("{}", box.get());

    MTL::Box<std::string> box_string;
    box_string.set("Hello World!");
    std::println("{}", box_string.get());

    using IntBox = MTL::Box<int>;
    using StringBox = MTL::Box<std::string>;

    IntBox int_box;
    int_box.set(50);
    std::println("{}", int_box.get());

    StringBox string_box;
    string_box.set("Hello World!");
    std::println("{}", string_box.get());

    return 0;
}