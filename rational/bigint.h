

#ifndef BIGINT
#define BIGINT   1

#include <iostream> 
#include <vector> 
#include <stdexcept>

class bigint
{
public:
   using word = unsigned short int;

private: 
   std::vector< word > repr;

   using iterator = std::vector< word > :: iterator;
   using const_iterator = std::vector< word > :: const_iterator;

   int sign;

public: 

   static int compare( const_iterator p1, const_iterator p2,
                       size_t len );

   static int compare( const std::vector< word > & v1,
                       const std::vector< word > & v2 );

   static int compare( const bigint& i1, const bigint& i2 ); 

   static void add( iterator p1, 
                    const_iterator q1, const_iterator q2,
                    word factor );

   static word subtract( iterator p1, word restword, 
                         const_iterator q1, const_iterator q2, word factor );

   static void add( const_iterator p1, const_iterator p2, 
                    const_iterator q1, const_iterator q2,
                    iterator r1, iterator r2 );

   static void subtract( const_iterator p1, const_iterator p2,
                         const_iterator q1, const_iterator q2,
                         iterator r1, iterator r2 );

   static void addorsub( const bigint& b1, const bigint& b2, int s2,
                         bigint& r ); 

   static void multiply( const std::vector< word > & v1,
                         const std::vector< word > & v2,
                         std::vector< word > & res );

   static unsigned int divide_fp( word x1, word x2, word x3,
                                  word y1, word y2 )
   {
      return static_cast< unsigned int > (
             ( 65536.0 * 65536.0 * x1 + 65536.0 * x2 + x3 ) /
             ( 65536.0 * y1 + y2 ));
   }


   static unsigned int divide( word x1, word x2, word x3,
                               word y1, word y2 );

   static std::vector< bigint::word >
          divide( const std::vector< word > & d, 
                  std::vector< word > & rest );

   void ensure( size_t s )
   {
      repr. reserve(s);
      while( repr. size( ) < s )
         repr. push_back(0);
   }

   void reduce( )
   {
      while( repr. size( ) && repr. back( ) == 0 )
         repr. pop_back( );
   }

   bigint( const std::vector< word > & v, int s )
      : repr(v),
        sign(s)
   { }

public: 
   bigint( ) 
      : sign(1)
   { }


   bigint( long int x );

   bigint( const bigint& ) = default;
   bigint( bigint&& ) = default;
   bigint& operator = ( const bigint& ) = default;
   bigint& operator = ( bigint&& ) = default;
   ~bigint( ) = default;

   static bool testmachine( ); 

   unsigned int checksum( unsigned int prime ) const;

   void operator += ( const bigint& b ) { addorsub( *this, b, 1, *this ); } 
   void operator -= ( const bigint& b ) { addorsub( *this, b, -1, *this ); }
   bigint operator + ( const bigint& b ) const
                                         { bigint res;
                                           addorsub( *this, b, 1, res );
                                           return res; }
   bigint operator - ( const bigint& b ) const  
                                         { bigint res;
                                           addorsub( *this, b, -1, res );
                                           return res; }

   void operator *= ( const bigint& b )
   {
      bigint res;
      res. ensure( repr. size( ) + b. repr. size( ));
      multiply( repr, b. repr, res. repr );
      res. reduce( );
      sign *= b. sign; 
      res. repr. swap( this -> repr );
   }

   bigint operator / ( const bigint& b ) const 
   {
      if( b. repr. size( ) == 0 )
         throw std::runtime_error( "cannot divide by zero" ); 

      bigint i = *this;
      bigint quot = bigint( divide( b. repr, i. repr ), sign * b. sign ); 
      quot. reduce( );
      return quot;
   } 

   void operator /= ( const bigint& b )
   {
      if( b. repr. size( ) == 0 )
         throw std::runtime_error( "cannot divide by zero" ); 

      bigint i = * this; 
      *this = bigint( divide( b. repr, i. repr ), sign * b. sign );
      reduce( ); 
   }

   bigint operator % ( const bigint& b ) const 
   {
      if( b. repr. size( ) == 0 )
         throw std::runtime_error( "cannot divide by zero" );

      bigint i = *this; 
      divide( b. repr, i. repr );
      i. reduce( );
      return bigint( i. repr, sign ); 
   }

   bigint operator - ( ) const
   {
      return bigint( repr, - sign );
   }

   int getsign( ) const
   {
      return sign;
   }

   unsigned int getunsigned( ) const
   {
      if( repr. size( ) >= 2 )
         throw std::runtime_error( "cannot make unsigned, number is too big" );

      if( repr. size( ) == 0 )
         return 0;
      else
         return repr. front( );
   }
 
   double approximation( ) const;
   
   size_t hash( ) const;
  
   friend std::ostream& operator << ( std::ostream& stream, bigint b );

   friend bigint operator * ( const bigint& , const bigint& );    
};


inline bigint operator * ( const bigint& b1, const bigint& b2 ) 
{
   bigint res;
   res. ensure( b1. repr. size( ) + b2. repr. size( ));
   bigint::multiply( b1. repr, b2. repr, res. repr );
   res. reduce( );
   res. sign = b1. sign * b2. sign;
   return res;
}


inline bool operator == ( const bigint& i1, const bigint& i2 )
{
   return bigint::compare(i1,i2) == 0;
}

inline bool operator != ( const bigint& i1, const bigint& i2 )
{
   return bigint::compare(i1,i2) != 0;
}

inline bool operator < ( const bigint& i1, const bigint& i2 )
{
   return bigint::compare(i1,i2) == -1;
}

inline bool operator > ( const bigint& i1, const bigint& i2 )
{
   return bigint::compare(i1,i2) == 1;
}

inline bool operator <= ( const bigint& i1, const bigint& i2 )
{
   return bigint::compare(i1,i2) != 1;
}

inline bool operator >= ( const bigint& i1, const bigint& i2 )
{
   return bigint::compare(i1,i2) != -1;
}


#endif

