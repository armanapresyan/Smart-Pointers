#ifndef UNIQUEPTR_HPP
#define UNIQUEPTR_HPP
#include <type_traits>


template<typename T>
class unique_ptr{

public:
   unique_ptr(T* resource) : m_ptr{resource} {}
   unique_ptr(const unique_ptr& other) = delete;
   unique_ptr(unique_ptr&& other) noexcept : m_ptr(std::move(other.m_ptr)) {
        other.m_ptr = nullptr;
    }
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }
  
   ~unique_ptr() { delete m_ptr; }


public:
   T& operator*(){
       return *m_ptr;
   }

  template <typename U = T, typename = typename std::enable_if<!std::is_fundamental<U>::value>::type>
  U* operator->() {
    return m_ptr;
  }



private:
   T* m_ptr;
};



#endif //UNIQUEPTR_HPP