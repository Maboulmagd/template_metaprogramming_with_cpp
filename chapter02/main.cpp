#include "Printer.h"

#include <iostream>
#include <vector>

#include "SmartArray.h"

// template<typename Input, typename Predicate>
// int count_if(Input start, Input end, Predicate p)
// {
//     int total = 0;
//     for (Input i = start; i != end; ++i)
//     {
//         if (p(*i))
//         {
//             ++total;
//         }
//     }
//
//     return total;
// }
//

int main(int argc, char** argv)
{
    // int arr[]{1,1,2,3,5,8,11};
    // const int odds = count_if(std::begin(arr), std::end(arr), [](int const n)
    // {
    //     return n % 2 == 1;
    // });
    //
    // std::cout << odds << std::endl;

    std::println("");

    chapter02::Printer<std::string> printer;
    printer << std::string{"Hello World"};

    chapter02::Printer<bool> printer2;
    printer2 << true;

    chapter02::Printer<std::vector<int>> printer3;
    printer3 << std::vector<int>{1,2,3};

    chapter02::Printer<int> printer4;
    printer4 << 1;

    chapter02::Printer<int*> printer5;
    int* x = new int{1};
    printer5 << x;
    delete x;

    std::println("");

    chapter02::smart_array::SmartArray<int, 10> stackAllocatedArray;
    stackAllocatedArray.print();

    chapter02::smart_array::SmartArray<int> heapAllocatedArray(10);
    heapAllocatedArray.print();

    chapter02::smart_array::SmartArray<int*> heapAllocatedArray2({1,2,3,4,5});
    heapAllocatedArray2.print();

    std::println("");





    return 0;
}