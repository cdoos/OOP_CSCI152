
#ifndef RATIONAL
#define RATIONAL 1
   // This is an include guard. Its purpose to ensure that
   // this file is not included more than once.

#include <iostream>
#include "bigint.h" 

bigint gcd( bigint i1, bigint i2 );
   // Use Euclidean Algorithm. 
   // static means that the function can be called without
   // class object. The function has no access to the fields
   // num and denom. 

class rational
{
   bigint num;
   bigint denom;

      // Maintain the following class invariant: 
      // num and denom's only common divisors are 1 and -1, and 
      // denom > 0 

   // Default constructor constructs (0,1):

public:
   rational( int num = 0 )
      : num( bigint( num )), 
        denom( bigint(1) )
   { }

   rational( const bigint& num, const bigint& denom ) 
      : num( num ), denom( denom ) 
   {
      normalize( ); 
   }

   void normalize( );   // Establish our delicate invariant.
  
   double approximation( ) const;   // Floating point approximation. 

   rational operator - ( ) const; 

   rational operator + ( const rational& ) const;
   rational operator - ( const rational& ) const;
   rational operator * ( const rational& ) const;
   rational operator / ( const rational& ) const; 

   bool operator == ( const rational& ) const;
   bool operator != ( const rational& ) const;
   bool operator > ( const rational& ) const;
   bool operator < ( const rational& ) const;
   bool operator >= ( const rational& ) const;
   bool operator <= ( const rational& ) const;

   void print( std::ostream& ) const; 
};

inline std::ostream& operator << ( std::ostream& out, const rational& r )
{
   r. print( out );
   return out;
}

#endif


