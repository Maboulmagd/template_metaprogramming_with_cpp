#ifndef TEMPLATE_METAPROGRAMMING_WITH_CPP_PRINTER_H
#define TEMPLATE_METAPROGRAMMING_WITH_CPP_PRINTER_H

#include <iostream>

namespace printer
{
    template <typename T>
    class Printer
    {
    public:
        void operator<<(const T& obj) const
        {
            std::cout << obj << std::endl;
        }
    };

    template<>
    class Printer<bool>
    {
    public:
        void operator<<(const bool& obj) const
        {
            auto flags = std::cout.flags();
            std::cout << std::boolalpha << obj << std::endl;
            std::cout.flags(flags);
        }
    };

    template<typename T>
    class Printer<std::vector<T>>
    {
    public:
        void operator<<(const std::vector<T>& obj) const
        {
            for (auto it = obj.cbegin(); it != obj.cend(); ++it)
            {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
    };

    template<typename T>
    class Printer<T*>
    {
    public:
        void operator<<(const T* obj) const
        {
            std::cout << "address: " << obj << " value: " << *obj << std::endl;
        }
    };
}

#endif //TEMPLATE_METAPROGRAMMING_WITH_CPP_PRINTER_H