#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP
#include  <functional>
#include <type_traits>

template<typename T>
struct ControlBlock{
    int Count;
    std::function<void(T*)> deleter;
};

template<typename T>
class shared_ptr{
public:
   shared_ptr(){
    m_ptr = nullptr;
    m_block = nullptr;
   }

   shared_ptr(T* rs) : m_ptr{rs} {
      m_block = new ControlBlock<T>();
      m_block->Count++;
   }

   shared_ptr(const shared_ptr& copy){
    this->m_block = copy.m_block;
    if(copy.m_block->Count == 0){
        this->m_ptr = nullptr;
    }else{
        this->m_ptr = copy.m_ptr;
        this->m_block->Count++;
    }
   }

    shared_ptr(T* rs, std::function<void(T*)> customDeleter) : m_ptr(rs) {
        m_block = new ControlBlock<T>();
        m_block->Count++;
        m_block->deleter = customDeleter;
    }


   ~shared_ptr(){
    m_block->Count--;
    if( m_block->Count == 0){
       delete m_ptr;
       delete m_block;
    }
   }

public:
  T& operator*(){
       return *m_ptr;
   }

  template <typename U = T, typename = typename std::enable_if<!std::is_fundamental<U>::value>::type>
  U* operator->() {
    return m_ptr;
  }

public:
  int use_count(){
    return m_block->Count;
  }

private:
   T* m_ptr;
   ControlBlock<T>* m_block;
};





#endif //SHAREDPTR_HPP