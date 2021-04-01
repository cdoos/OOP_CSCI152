
#include "rational.h"

bigint gcd( bigint n1, bigint n2 ) 
{
   if (n1 == bigint(0) && n2 == bigint(0))
      throw std::runtime_error( "GCD: both arguments are zero" );
   else if (n2 == bigint(0)) 
      return n1;
   
   return gcd(n2, n1 % n2);
}

void rational::normalize( ) 
{
   if (denom == bigint(0)) 
      throw std::runtime_error( "rational: denom == 0" );

   bigint d = gcd(num, denom);
   if (d < bigint(0)) 
      d = -d;

   num /= d;
   denom /= d;
   if (denom < bigint(0)) denom = -denom, num = -num;
}

double rational::approximation( ) const
{
   return num. approximation( ) / denom. approximation( ); 
}

rational rational::operator - ( ) const 
{ 
   rational t;
   if (denom < bigint(0)) t.denom = -denom, t.num = num;
   else t.denom = denom, t.num = -num;
   return t; 
}

rational rational::operator + ( const rational& r2 ) const 
{ 
   return rational(num * r2.denom + r2.num * denom, denom * r2.denom);
}

rational rational::operator - ( const rational& r2 ) const 
{ 
   return rational(num * r2.denom - r2.num * denom, denom * r2.denom);
}

rational rational::operator * ( const rational& r2 ) const 
{ 
   return rational(num * r2.num, denom * r2.denom);
}

rational rational::operator / ( const rational& r2 ) const 
{ 
   return rational(num * r2.denom, denom * r2.num);
}


// Putting full trust in our normalization:

bool rational::operator == ( const rational& r2 ) const
{
   return (num == r2.num && denom == r2.denom);
}

bool rational::operator != ( const rational& r2 ) const
{
   return !(num == r2.num && denom == r2.denom);
}

void rational::print( std::ostream& stream ) const 
{ 
   if (denom == 1) 
      stream << num;
   else 
      stream << num << "/" << denom; 
}

