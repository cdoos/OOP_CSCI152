
#include "stack.h"

void stack::ensure_capacity( size_t c ) {
   if (c > current_capacity) {
      size_t new_capacity = 1;
      while (new_capacity < c) {
         new_capacity *= 2;
      }
      double* new_data = new double[new_capacity];
      std::copy(data, data + current_size, new_data);
      delete[] data;
      data = new_data;
      current_capacity = new_capacity;
   }
}

stack::stack( ) :
   data(new double[4]),
   current_size(0),
   current_capacity(4)
{

}

stack::stack( const stack& s ) :
   data(new double[s.current_capacity]),
   current_size(s.current_size),
   current_capacity(s.current_capacity)
{
   std::copy(s.data, s.data + s.current_size, data);
}

const stack& stack::operator = ( const stack& s ) {
   ensure_capacity(s.current_size);
   current_size = s.current_size;
   std::copy(s.data, s.data + s.current_size, data);
   return *this;
}

stack::~stack( ) {
   delete[] data;
}

void stack::push( double d ) {
   ensure_capacity(current_size + 1);
   data[current_size] = d;
   ++current_size;
}
  
stack::stack( std::initializer_list< double > init ) : 
   data(new double[init.size()]),
   current_capacity(init.size()),
   current_size(0)
{  
   for (int val : init) {
      push(val);
   }
}

  
void stack::pop( ) {
   if (current_size > 0) 
      --current_size;
   else 
      throw std::runtime_error( "pop: stack is empty" );
} 

void stack::clear( ) {
   current_size = 0;
} 

void stack::reset( size_t s ) {
   current_size = s;
}

double stack::peek( ) const {
   if (current_size > 0)
      return data[current_size - 1];
   else
      throw std::runtime_error( "peek: stack is empty" );
} 

size_t stack::size( ) const {
   return current_size;
}

bool stack::empty( ) const {
   return (current_size == 0);
}

void stack::print( std::ostream& out ) const {
    for (size_t i = 0; i < current_size; ++i) {
        if (i > 0) {
            out << ", ";
        }
        out << data[i];
    }
}

