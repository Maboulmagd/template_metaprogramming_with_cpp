#ifndef TEMPLATE_METAPROGRAMMING_WITH_CPP_SERIALIZER_H
#define TEMPLATE_METAPROGRAMMING_WITH_CPP_SERIALIZER_H

#include <memory>
#include <string>

namespace chapter02
{
    template<typename T>
    concept IsContainer = requires(T t)
    {
        { std::begin(t) } -> std::input_iterator;
        { std::end(t) } -> std::input_iterator;
    };

    template<typename T>
    concept IsSmartPointer = requires { typename T::element_type; } &&
        (std::same_as<T, std::unique_ptr<typename T::element_type>> ||
         std::same_as<T, std::shared_ptr<typename T::element_type>> ||
         std::same_as<T, std::weak_ptr<typename T::element_type>>);

    template<typename SerializableT>
    class Serializer
    {
    public:
        Serializer() = default;
        ~Serializer() = default;

        Serializer(const Serializer&) = delete;
        Serializer& operator=(const Serializer&) = delete;

        Serializer(Serializer&&) = delete;
        Serializer& operator=(Serializer&&) = delete;

        std::string serialize(const SerializableT &obj)
        {
            if constexpr (std::is_same_v<SerializableT, std::string> || std::is_same_v<SerializableT, std::wstring>)
            {
                return obj;// TODO Handle string escaping...
            }
            else if constexpr (std::is_same_v<SerializableT, bool>)
            {
                if (obj) { return "true"; }
                return "false";
            }
            else if constexpr (std::is_same_v<SerializableT, char> || std::is_same_v<SerializableT, signed char> || std::is_same_v<SerializableT, unsigned char>)
            {
                return std::to_string(obj);
            }
            else if constexpr (std::is_arithmetic_v<SerializableT>)
            {
                return std::to_string(obj);
            }
            else if constexpr (IsSmartPointer<SerializableT>)
            {
                if (obj == nullptr)
                {
                    return "nullptr";
                }

                return serialize(*obj);
            }
            else if constexpr (std::is_pointer_v<SerializableT>)
            {
                if (obj == nullptr)
                {
                    return "nullptr";
                }

                using pointedToType = std::remove_pointer_t<SerializableT>;
                return serialize(*obj);// Recurse, should work for built-in types (i.e fundamental_v)

                // Try with concepts since we are using C++20 and above
                // return *obj.toString();// Assuming pointed-to type has toString() implemented I imagine..
            }
            else if constexpr (IsContainer<SerializableT>)// Works with std::array AND c-style raw buffers/arrays
            {
                std::string res = "[";

                for (auto it = obj.begin(); it != obj.end(); ++it)
                {
                    res += serialize(*it);// Recursive handles
                    res += ",";
                }

                if (!res.empty()) res.pop_back();// Remove last ","
                res += "]";
                return res;
            }
            else if constexpr (obj.has_value())
            {

            }
            else
            {
                static_assert(!sizeof(SerializableT), "SerializableT type not supported");
            }




            /*
             * if constexpr arithmetic type: DONE
             * i.e int 42 -> return "42"
             * i.e float 42.0f -> return "42.0f"
             * i.e double 42.0 -> return "42.0"
             *
             * if constexpr string -> return new string copy DONE
             *
             * if constexpr user-defined type -> recurse on all data fields and concat to string? HARDER without toString() member function for the UDT
             *
             * if constexpt pointer type -> recurse on type that pointer types to, and return that instead of address DONE for fundamental types
             *
             * if constexpr container -> could be vector<int, float, double, string, char, pointer types?> -> recurse on type and concat to string? DONE
             * if constexpr container of containers -> recurse on container - > recurse on type and concat to string? DONE
             */
        }

        SerializableT deserialize(const std::string& serializedString)
        {

        }

    private:

    };
}

#endif //TEMPLATE_METAPROGRAMMING_WITH_CPP_SERIALIZER_H