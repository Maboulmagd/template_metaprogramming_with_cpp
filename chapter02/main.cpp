#include <iostream>

template<typename Input, typename Predicate>
int count_if(Input start, Input end, Predicate p)
{
    int total = 0;
    for (Input i = start; i != end; ++i)
    {
        if (p(*i))
        {
            ++total;
        }
    }

    return total;
}



int main(int argc, char** argv)
{
    int arr[]{1,1,2,3,5,8,11};
    const int odds = count_if(std::begin(arr), std::end(arr), [](int const n)
    {
        return n % 2 == 1;
    });

    std::cout << odds << std::endl;

    return 0;
}