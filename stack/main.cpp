
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <stdexcept>

#include "stack.h"
#include "tokenizer.h"

struct rpn_error
{
   std::string cause; 
   long unsigned int line;
   long unsigned int column;

   rpn_error( const std::string& cause, 
              long unsigned int line, long unsigned int column )
      : cause( cause ), 
        line( line ),  
        column( column )
   { }
};

inline std::ostream& operator << ( std::ostream& out, const rpn_error& e )
{
   out << e.cause << " at position " << e.line + 1 << "/" << e.column + 1;
      // We add 1 because counting of lines and column starts at 0. 
      // We need to translate CS language to civilian language. 
   return out;
}

// Apply an operator with no arguments (also kown as constants): 

double apply0( inputtype op )
{
   std::cout << "applying " << op << "\n";
   if (op == inp_pi) {
      return 3.141592653589793238462643383279502884;
   } else if (op == inp_e) {
      return 2.7182818284590452353602874713527;
   } else {
      throw std::logic_error( "unknown 0-ary operator" );
   }
}

// Apply an operator with one argument:

double apply1( inputtype op, double d1 )
{
   std::cout << "applying " << op << " on " << d1 << "\n";
   if (op == inp_exp) {
      return pow(M_E, d1);
   } else if (op == inp_log) {
      return log(d1);
   } else if (op == inp_sqrt) {
      return sqrt(d1);
   } else if (op == inp_sin) {
      return sin(d1);
   } else if (op == inp_cos) {
      return cos(d1);
   } else if (op == inp_abs) {
      return abs(d1);
   } else {
      throw std::logic_error( "unknown unary operator" ); 
   }
      // this is a message the implementer of rpn, so it can be rude. 
}

// Apply an operator with two arguments:
 
double apply2( inputtype op, double d1, double d2 )
{  
   std::cout << "applying " << op << " on " << d1 << " and " << d2 << "\n";
   if (op == inp_plus) {
      return d1 + d2;
   } else if (op == inp_minus) {
      return d1 - d2;
   } else if (op == inp_times) {
      return d1 * d2;
   } else if (op == inp_div) {
      return d1 / d2;
   } else if (op == inp_mod) {
      return d1 - static_cast<long int> (( d1 / d2 )) * d2;
   } else if (op == inp_pow) {
      return pow(d1, d2);
   } else {
      throw std::logic_error( "unknown binary operator" ); 
   }
      // this is a message the implementer of rpn, so it can be rude.
}


// Evaluate an expression in RPN:
//
// Remove #if 0 when you completed the implementation of stack.

double rpn( input& inp ) 
{
   stack st; 

   while( true ) 
   {
      std::pair< inputtype, size_t > p = read( inp );
      // Construct a pair containing the type of input with its length.
      // The characters are stored in a buffer inside inp. 
      // They can be obtained by calling inp. get(i).

      // std::cout << p. first << "/" << p. second << "\n";
      // If you want to see the input, you can remove the comment.

      switch( p. first )
      { 
      case inp_e:
      case inp_pi:
         st. push( apply0( p. first ));
         break;
 
      case inp_num:
         // Translate contents of buffer into double :

         st. push( getdouble( inp, p. second )); 
         break; 
        
      case inp_sin:
      case inp_cos:
      case inp_exp:
      case inp_log:
      case inp_sqrt:
      case inp_abs: 
         {
            if( st. size( ) < 1 )
            {
               throw rpn_error( 
                  std::string( "unary operator " ) +
                  cstring( p. first ) + ": no number on stack", 
                                 inp. line, inp. column );
            }

            double d1 = st. peek( ); st. pop( );
            st. push( apply1( p. first, d1 ));
         }
         break;

      case inp_plus:
      case inp_minus:
      case inp_times:
      case inp_div: 
      case inp_mod:
      case inp_pow: 
         {
            if( st. size( ) < 2 ) 
            {
               throw rpn_error( 
                  std::string( "binary operator " ) +
                  cstring( p. first ) + ": less than two numbers on stack",
                  inp. line, inp. column );
            }

            double d2 = st. peek( ); st. pop( );
            double d1 = st. peek( ); st. pop( );
 
            st. push( apply2( p. first, d1, d2 )); 
         }
         break;  

      case inp_space:
      case inp_comment: 
         break; 

      case inp_end:
         if( st. size( ) == 0 )
         {
            throw rpn_error( "no value to return",
                    inp. line, inp. column );
         }
         if( st. size( ) > 1 )
         {
            std::cout << 
               "(there was more than one value on the stack)\n";
         }

         return st. peek( );

      default:
         throw rpn_error( std::string( "unknown operator " ) + 
                          cstring( p. first ), inp. line, inp. column ); 
      }
      std::cout << st << "\n";
      inp. commit( p. second ); 
   }

   return st. peek( ); 
}


int main( int argc, char* argv [ ] )
{

#if 0
   // A bit of testing code. Add your own tests,
   // and use valgrind. 

   stack s1 = { 4, 2, 1 };
   stack s2 = { 8, 7, 4, 3, 0 };

   for( size_t i = 0; i < 1000; ++ i )
   {
      s1. push( i*i ); 
      s2 = s1;
 
   }
   double sum = 0;
   while( s2. size( ))
   {
      stack s3 = s2;
      sum += s3. peek( );
      s2. pop( );
   }

   std::cout << "the sum is " << sum << "\n"; 

   return 0;
#endif

#if 1
   // Replace by #if 1 if you want to evaluate RPN. 

   input inp( &std::cin, "stdin" );

   try
   {
      std::cout << "evaluating rpn:\n"; 
      double res = rpn( inp ); 
      std::cout << res << "\n"; 
   }
   catch( const std::logic_error& e )
   {
      std::cout << e. what( ) << "\n";
   }
   catch( const std::runtime_error& e )
   {
      std::cout << e. what( ) << "\n";
   }
   catch( const rpn_error& e )
   {
      std::cout << e << "\n";
   }
   return 0;
 
   std::cout << inp << "\n";
   return 0;
#endif 
}

