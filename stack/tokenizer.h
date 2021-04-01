
#ifndef TOKENIZER_INCLUDED 
#define TOKENIZER_INCLUDED    1

#include <iostream>
#include <deque>
#include <map> 

// This is the tokenizer for assignment 2.
// You are very welcome to study this code, but you don't have to.

enum inputtype { inp_plus, inp_minus, inp_times, inp_div, inp_mod, inp_pow, 
       inp_sin, inp_cos, inp_exp, inp_log, 
       inp_sqrt, inp_abs, inp_e, inp_pi,
       inp_num, inp_ident, inp_err, inp_comment, inp_space, 
       inp_end };

const char* cstring( inputtype inp );
   // Return a C-string representing inp, so that it can be printed.

inline std::ostream& operator << ( std::ostream& out, inputtype inp )
   { return out << cstring( inp ); } 


////////////////////////////

struct input
{
   std::istream* in;
   std::string name; 
   long unsigned int line;     // We count like computer scientists, 
   long unsigned int column;   // because that's what we are. 

   std::deque< char > buffer;

   input( ) = delete;

   input( std::istream* in, const std::string& name )
      : in( in ),
        name( name ),
        line(0), 
        column(0) 
   { }

   input( const input& ) = delete;
   input& operator = ( const input& ) = delete;

   char peek( size_t i ) const;
      // See i-th character in the buffer. It must be in the buffer
      // already, because we won't try to extend the buffer. 
      // This means that has(i') with i' > i must have succeeded before. 

   bool has( size_t i );
      // True if we have least i characters. If we have less, 
      // we try to read from the file. Therefore we are not const.  
      // After successful has(i), it is guaranteed that we 
      // we have all characters get(i') with i' < i.

   void commit( size_t i ); 
      // Irreversibly move forward. We must have at least i characters,
      // which means that has(i) must have succeeded before. 

   bool good( ) const { return in -> good( ); } 
   bool bad( ) const { return in -> bad( ); } 
   bool eof( ) const { return in -> eof( ); }
};

std::ostream& operator << ( std::ostream& , const input& );


////////////////////////////////////////////////////////////
// These tries should be generalized to full DFA.
// I think it is not hard at all.
////////////////////////////////////////////////////////////

template< typename D > 
struct trie
{
   D val; 
   std::map< char, trie > cont; 

   // We must have a value of the empty string. It can be error. 

   trie( D epsval ) 
      : val( epsval ) 
   { } 

   // default value is inserted whenever we create a subtrie:

   void insert( const char* c, D def, D val ) 
      { insert( this, c, def, val ); }

   static void insert( trie* tr, const char* c, D err, D val )
   {
      while( *c != '\0' )
      {
         auto p = tr -> cont. insert( 
            std::pair<char, trie<D>> ( *c, trie( err )));
         c ++;
         tr = & ( p. first -> second ); 
      }
      tr -> val = val;
   } 

   void print( std::ostream& out, std::string& indent ) const
   {
      out << indent << "val: " << val << "\n";
      for( const auto& p : cont )
      {
        out << indent << p. first << ":\n";
        indent += "   ";
        p.second. print( out, indent );  
        indent. pop_back( ); indent. pop_back( ); indent. pop_back( );
     }
  }

};

template< typename D > 
std::ostream& operator << ( std::ostream& out, const trie<D> & tr )
{
   std::string indent;
   tr. print( out, indent );
   return out;
}

//////////////////////////////


trie< inputtype > reservedwords( ); 

std::pair< inputtype, size_t > read( const trie<inputtype> * tr, input& inp );
   // Read longest possible input from trie.

std::pair< inputtype, size_t > read( input& inp ); 

double getdouble( input& inp, size_t len );

#endif

