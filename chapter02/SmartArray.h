#ifndef TEMPLATE_METAPROGRAMMING_WITH_CPP_SMARTARRAY_H
#define TEMPLATE_METAPROGRAMMING_WITH_CPP_SMARTARRAY_H

#include <cassert>

namespace smart_array
{
    template<typename Derived>
    class Printer
    {
    public:
        void print() const
        {
            const auto& derived {static_cast<const Derived&>(*this)};
            for (std::size_t i = 0zu; i < derived.size(); ++i)
            {
                std::cout << derived.operator[](i) << " ";
            }
            std::cout << std::endl;
        }
    };

    template<typename T, std::size_t Size = 0>
    class SmartArray : public Printer<SmartArray<T, Size>>
    {
    public:
        SmartArray() = default;
        ~SmartArray() = default;

        SmartArray(const SmartArray&) = delete;
        SmartArray& operator=(const SmartArray&) = delete;

        SmartArray(SmartArray&&) = delete;
        SmartArray& operator=(SmartArray&&) = delete;

        [[nodiscard]] static constexpr std::size_t size()
        {
            return Size;
        }

        T& operator[](const std::size_t& index)
        {
            assert(index < Size);
            return this->pArr_[index];
        }

        const T& operator[](const std::size_t& index) const
        {
            assert(index < Size);
            return this->pArr_[index];
        }

    private:
        T pArr_[Size] = {0};
    };

    template<typename T>
    class SmartArray<T, 0> : public Printer<SmartArray<T, 0>>
    {
    public:
        SmartArray() = delete;
        explicit SmartArray(const std::size_t& size) : size_(size)
        {
            this->pArr_ = new T[this->size_];

            for (std::size_t i = 0uz; i < this->size_; ++i)
            {
                this->pArr_[i] = i;
            }

            assert(this->pArr_ != nullptr);
        }

        ~SmartArray()
        {
            if (this->pArr_ != nullptr)
            {
                delete[] pArr_;
                this->pArr_ = nullptr;
            }
            this->size_ = 0;
        }

        SmartArray(const SmartArray&) = delete;
        SmartArray& operator=(const SmartArray&) = delete;

        SmartArray(SmartArray&&) = delete;
        SmartArray& operator=(SmartArray&&) = delete;

        [[nodiscard]] constexpr std::size_t size() const
        {
            return this->size_;
        }

        T& operator[](const std::size_t& index)
        {
            assert(index < this->size_);
            return this->pArr_[index];
        }

        const T& operator[](const std::size_t& index) const
        {
            assert(index < this->size_);
            return this->pArr_[index];
        }

    private:
        T* pArr_ = nullptr;
        std::size_t size_ = 0;
    };

    template<typename T>
    class SmartArray<T*, 0> : public Printer<SmartArray<T*, 0>>
    {
    public:
        SmartArray() = delete;
        explicit SmartArray(const std::size_t& size, const T& init_value) : size_(size)
        {
            this->pArr_ = new T*[this->size_];

            for (std::size_t i = 0uz; i < this->size_; ++i)
            {
                this->pArr_[i] = new T{init_value};
            }

            assert(this->pArr_ != nullptr);
        }

        SmartArray(const std::initializer_list<T>& initializer_list) : size_(initializer_list.size())
        {
            this->pArr_ = new T*[this->size_];

            std::size_t i = 0;
            for (const auto& value : initializer_list)
            {
                this->pArr_[i++] = new T{value};
            }
        }

        ~SmartArray()
        {
            if (this->pArr_ != nullptr)
            {
                for (std::size_t i = 0uz; i < this->size_; ++i)
                {
                    delete this->pArr_[i];
                }

                delete[] pArr_;
                this->pArr_ = nullptr;
            }
            this->size_ = 0;
        }

        SmartArray(const SmartArray&) = delete;
        SmartArray& operator=(const SmartArray&) = delete;

        SmartArray(SmartArray&&) = delete;
        SmartArray& operator=(SmartArray&&) = delete;

        [[nodiscard]] constexpr std::size_t size() const
        {
            return this->size_;
        }

        T& operator[](const std::size_t& index)
        {
            assert(index < this->size_);
            return *this->pArr_[index];
        }

        const T& operator[](const std::size_t& index) const
        {
            assert(index < this->size_);
            return *this->pArr_[index];
        }

    private:
        T** pArr_ = nullptr;
        std::size_t size_ = 0;
    };

    template<typename T, std::size_t Size>
    std::ostream& operator<<(std::ostream& os, const SmartArray<T, Size>& arr)
    {
        arr.print();
        return os;
    }
}

#endif //TEMPLATE_METAPROGRAMMING_WITH_CPP_SMARTARRAY_H