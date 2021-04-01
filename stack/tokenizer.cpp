
#include "tokenizer.h"

const char* cstring( inputtype inp )
{
   switch( inp )
   {
   case inp_plus:     return "plus";  
   case inp_minus:    return "minus"; 
   case inp_times:    return "times"; 
   case inp_div:      return "div"; 
   case inp_mod:      return "mod"; 
   case inp_pow:      return "pow";

   case inp_sin:      return "sin"; 
   case inp_cos:      return "cos";
   
   case inp_exp:      return "exp"; 
   case inp_log:      return "log";

   case inp_sqrt:     return "sqrt"; 
   case inp_abs:      return "abs"; 

   case inp_e:        return "e";
   case inp_pi:       return "pi";

   case inp_num:      return "num"; 
   case inp_ident:    return "ident"; 

   case inp_err:      return "error"; 
   case inp_comment:  return "comment"; 
   case inp_space:    return "space"; 
   case inp_end:      return "end"; 
   }

   return "???"; 
}


////////////////////////////////////////////////////
// class input


char input::peek( size_t i ) const 
{
   if( i >= buffer. size( ))
      throw std::runtime_error( "input: peek beyond buffer" );
   return buffer[i];
}

bool input::has( size_t i )
{
   if( i > buffer. size( ))
   {
      if( !good( )) 
         return false; 

      while( i > buffer. size( ))
      {
         int c = in -> get( );
         if( !good( ))
            return false;
         buffer. push_back(c);
      }
   }
   return true;  
}

// In a real application, this operation would be unprotected:

void input::commit( size_t i ) 
{
   if( i > buffer. size( ))
      throw std::runtime_error( "input: commit beyond buffer" ); 

   while(i) 
   {
      if( buffer. front( ) == '\n' )
      {
         ++ line;
         column = 0; 
      }
      else
         ++ column;

      -- i; 
      buffer. pop_front( );  
   }
} 

namespace
{
   char hex( char c ) 
   {
      if( c >= 10 )
         return 'A' + ( c - 10 );
      else
         return '0' + c;
   }
}

std::ostream& operator << ( std::ostream& out, const input& inp )
{
   out << "input( " << inp. name << ", " << inp. line << ", " << 
          inp. column << " ) : ";

   for( char c : inp. buffer )
   {
      if( isprint(c)) 
         out << c; 
      else 
         out << "{" << hex( c >> 4 ) << hex( c & 0X0F ) << "}";
   }
   if( inp. eof( ) ) 
      out << " (end of file)";
   else
   {
      if( !inp. good( ))  
         out << "(file is not good)"; 
   }
   out << "\n";
   return out; 
}




// Put the reserved words in the trie. 

trie< inputtype > reservedwords( )
{
   trie< inputtype > res( inp_err );

   for( char c = '0'; c <= '9'; ++ c )
   {
      char inp[3];
      inp[0] = c; inp[1] = 0;
      res. insert( inp, inp_err, inp_num );
      inp[0] = '-'; inp[1] = c; inp[2] = 0;
      res. insert( inp, inp_err, inp_num );
   }

   for( char c = 'a'; c <= 'z'; ++ c )
   {
      char inp[2];
      inp[0] = c; inp[1] = 0;
      res. insert( inp, inp_err, inp_ident );
   }

   for( char c = 'A'; c <= 'Z'; ++ c )
   {
      char inp[2];
      inp[0] = c; inp[1] = 0;
      res. insert( inp, inp_err, inp_ident );
   }

   res. insert( "+", inp_err, inp_plus );
   res. insert( "-", inp_err, inp_minus );
   res. insert( "*", inp_err, inp_times );
   res. insert( "/", inp_err, inp_div );
   res. insert( "%", inp_err, inp_mod );
   res. insert( "^", inp_err, inp_pow );
  
   res. insert( "sin", inp_err, inp_sin );
   res. insert( "cos", inp_err, inp_cos );   

   res. insert( "exp", inp_err, inp_exp );
   res. insert( "log", inp_err, inp_log );

   res. insert( "sqrt", inp_err, inp_sqrt );
   res. insert( "abs", inp_err, inp_abs );

   res. insert( "e", inp_err, inp_e );
   res. insert( "pi", inp_err, inp_pi );

   res. insert( "=", inp_err, inp_end );

   res. insert( "//", inp_err, inp_comment );
   res. insert( "/*", inp_err, inp_comment );

   return res;
}


std::pair< inputtype, size_t > 
read( const trie< inputtype > * tr, input& inp ) 
{
   size_t i = 0;
   while( true )
   {
      if( !inp. has(i+1)) 
         return { tr -> val, i }; 
      auto p = tr -> cont. find( inp. peek(i)); 
      if( p == tr -> cont. end( ))
         return { tr -> val, i };

      ++ i;
      tr = &( p -> second );
   }
}


std::pair< inputtype, size_t > 
read( input& inp )
{
   static trie< inputtype > res = reservedwords( );

   if( !inp. has(1)) 
      return { inp_end, 0 };

   if( inp. has(1) && isspace( inp. peek(0)) ) 
   {
      size_t i = 1;
      while( inp. has(i+1) && isspace( inp. peek(i)) )
         ++ i;
      return { inp_space, i }; 
   }

   auto p = read( &res, inp );

   // Some inputs need special attention

   if( p. first == inp_comment )   
   {
      if( inp. peek(0) == '/' && inp. peek(1) == '*' ) 
      {
         size_t i = p. second; 
         while( inp. has(i+2) && 
                   ( inp. peek(i) != '*' || inp. peek(i+1) != '/' ))
         {
            ++ i;  
         }
         if( !inp. has( i + 1 ))
            return { inp_err, i };  
         if( !inp. has( i + 2 ))
            return { inp_err, i + 1 }; 
         return { inp_comment, i + 2 }; 
      }    

      if( inp. peek(0) == '/' && inp. peek(1) == '/' ) 
      {
         size_t i = p. second; 
         while( inp. has(i+1) && inp. peek(i) != '\n' )
            ++ i;
         if( !inp. has( i + 1 )) return { inp_err, i };
         return { inp_comment, i + 1 };
      }
      throw std::logic_error( "you reached the unreachable, congratulations" ); 
   }

   if( p. first == inp_num ) 
   {
      size_t i = p. second;
      while( inp. has(i+1) && isdigit( inp. peek(i)))
         ++ i;

      // fraction? 

      if( inp. has(i+1) && inp.peek(i) == '.' )
      {
         ++ i;
         while( inp. has(i+1) && isdigit( inp.peek(i)) )
            ++ i;
      }

      // Exponent, no more than 3 digits: 

      if( inp. has(i+1) && 
            ( inp. peek(i) == 'e' || inp. peek(i) == 'E' ))
      {
         ++ i;
         if( inp. has(i+1) && ( inp. peek(i) == '+' || inp. peek(i) == '-' ))
            ++ i;
          
         if( !inp. has(i+1) || !isdigit( inp. peek(i)) )
            return { inp_err, i }; 
         ++ i;  
         if( inp. has(i+1) && isdigit( inp. peek(i)) )
            ++ i;
         if( inp. has(i+1) && isdigit( inp. peek(i)) )
            ++ i;
      }
      return { inp_num, i }; 
   }     
 
   if( p. first == inp_ident )
   {
      size_t i = p. second;
      while( inp. has(i+1) && 
             ( isdigit( inp.peek(i)) || isalpha( inp.peek(i)) || 
               inp.peek(i) == '_' ))
      {
         ++ i;
      }
      return { inp_ident, i };
   }
 
   return p;  
}

double getdouble( input& inp, size_t len )
{
   std::string s;
   for( size_t i = 0; i != len; ++ i )
      s. push_back( inp. peek(i));
   return std::stod(s);  
}


