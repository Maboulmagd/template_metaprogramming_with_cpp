#include <print>
#include <memory>

template<typename T, typename... Args>
[[nodiscard]] std::unique_ptr<T> make_unique(Args&&... args)
{
    // Call T's constructor but T is allocated on heap using new...
    T* res = new T(std::forward<Args>(args)...);
    return std::unique_ptr<T>(res);
}

struct Point
{
    int x;
    int y;
    int z;

    Point(const int x, const int y, const int z) : x{x}, y{y}, z{z}
    {

    }
};

int main(int argc, char** argv)
{
    std::unique_ptr<Point> point = make_unique<Point>(2, 3, 4);
    std::print("{}, {}, {}", point->x, point->y, point->z);

    return 0;
}