#ifndef NANO_FUNCTION_HPP
#define NANO_FUNCTION_HPP

#include <cstdint>
#include <array>

namespace Nano
{

typedef std::array<std::uintptr_t, 2> delegate_key_t;

template <typename T_rv> class Function;
template <typename T_rv, typename... Args> class Function<T_rv(Args...)>
{
    typedef T_rv (*sig_t)(void*, Args...);

    void* m_this_ptr;
    sig_t m_stub_ptr;

    template <typename I, typename F>
    Function (I&& this_ptr, F&& stub_ptr):
        m_this_ptr { std::forward<I>(this_ptr) },
        m_stub_ptr { std::forward<F>(stub_ptr) } {}

    template <typename T> friend class Signal;

    Function (delegate_key_t const& _key):
        m_this_ptr { reinterpret_cast<void*>(std::get<0>(_key)) },
        m_stub_ptr { reinterpret_cast<sig_t>(std::get<1>(_key)) } {}

    public:

//------------------------------------------------------------------------------

    template <T_rv (*fun_ptr)(Args...)>
    static inline Function bind()
    {
        return { nullptr, [](void* , Args... args) {
        return (*fun_ptr)(std::forward<Args>(args)...); }};
    }
    template <typename T, T_rv (T::*mem_ptr)(Args...)>
    static inline Function bind(T* pointer)
    {
        return { pointer, [](void* this_ptr, Args... args) {
        return (static_cast<T*>(this_ptr)->*mem_ptr)
            (std::forward<Args>(args)...); }};
    }
    template <typename T, T_rv (T::*mem_ptr)(Args...) const>
    static inline Function bind(T* pointer)
    {
        return { pointer, [](void* this_ptr, Args... args) {
        return (static_cast<T*>(this_ptr)->*mem_ptr)
            (std::forward<Args>(args)...); }};
    }

//------------------------------------------------------------------------------

    T_rv operator()(Args&&... args) const
    {
        return (*m_stub_ptr)(m_this_ptr, std::forward<Args>(args)...);
    }
    bool operator== (delegate_key_t const& other) const
    {
        return other == this->operator delegate_key_t();
    }
    bool operator!= (delegate_key_t const& other) const
    {
        return other != this->operator delegate_key_t();
    }
    operator delegate_key_t() const
    {
        return { reinterpret_cast<std::uintptr_t>(m_this_ptr),
                 reinterpret_cast<std::uintptr_t>(m_stub_ptr) };
    }
};

} // namespace Nano ------------------------------------------------------------

namespace std // std specialization
{

template <> struct less<Nano::delegate_key_t>
{
    inline bool operator()(Nano::delegate_key_t const& lhs,
                           Nano::delegate_key_t const& rhs) const
    {
        std::size_t x = lhs[0] ^ rhs[0];
        std::size_t y = lhs[1] ^ rhs[1];

        if ((x < y) && (x < (x ^ y)))
        {
            return lhs[1] < rhs[1];
        }
        return lhs[0] < rhs[0];
    }
};

} // namespace std -------------------------------------------------------------

#endif // NANO_FUNCTION_HPP_2_514
