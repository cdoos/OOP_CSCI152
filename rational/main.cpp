
#include "rational.h"

int main( int argc, char* argv [ ] )
{
   rational abc = rational(1,2);
     std::cout << abc << "\n";
    abc = abc*2;
    std::cout << abc << "\n";
 
    rational r = rational(5878273187318, -671273183873198);
    rational a = rational (-7123718731897318, 872818378634261001);
    rational b = rational(-784781748178317, -34618091834746);

    r = (r * a - b * a) / b / b * a + b + r * r * a / b;


    std::cout << r.approximation() << "\n";
    // TEST DEFAULT DECLARATION
    std::cout << "TEST DEFAULT DECLARATION" << "\n";
    rational def;
    rational def1(5);
    std::cout << def << "\n";
    std::cout << def1 << "\n";

    // TEST DIFFERENT DECLARATIONS
    std::cout << "TEST DIFFERENT DECLARATIONS" << "\n";
   // rational a(0, 0); // should terminate
  //  rational b(0, 10);
  //  rational c(10, 0); // should terminate
    rational d(10, 10);
    rational e(-100, 100);
    rational f(100, -100);
    rational g(-10, -10);
    rational h(0, -120);
    std::cout << gcd(0,-10) << "\n";
    bigint J = 1;
    for (int i = 1; i <= 100; i++) J *= 10;
    std::cout << J << "\n";
    std::cout << gcd(J,100) << "\n";
     //  std::cout << a << "\n";
     std::cout << gcd(10,10) << "\n";
        std::cout << gcd(10,-10) << "\n";
    std::cout << gcd(-10,-10) << "\n";
     std::cout << rational(-10,-10) << "\n";
    //std::cout << gcd(0,0) << "\n";
 //   std::cout << b << "\n";
    //    std::cout << c << "\n";
    std::cout << d << "\n";
    std::cout << e << "\n";
    std::cout << f << "\n";
    std::cout << g << "\n";
    std::cout << h << "\n";
    
    
    //std::cout << gcd(0, 0) << std::endl;
    std::cout << gcd(0, 2) << std::endl;
    std::cout << gcd(-2, -4) << std::endl;
    std::cout << gcd(30, 50) << std::endl;
    std::cout << gcd(-30, 50) << std::endl;
    std::cout << gcd(30, -50) << std::endl;
    std::cout << gcd(-30, -50) << std::endl;
    std::cout << gcd(0, -120) << std::endl;

    // TEST +-*/
    std::cout << "TEST +-*/" << "\n";

    rational r1 = rational(2, 1);
    rational r2 = rational(4, 1);
    rational r3 = rational(2, 3);
    rational r4 = rational(4, 5);

    std::cout << r1 + r2 << "\n";
    std::cout << r1 - r2 << "\n";
    std::cout << r1 * r2 << "\n";
    std::cout << r1 / r2 << "\n";

    std::cout << r3 + r4 << "\n";
    std::cout << r3 - r4 << "\n";
    std::cout << r3 * r4 << "\n";
    std::cout << r3 / r4 << "\n";

    std::cout << r2 + r4 << "\n";
    std::cout << r2 - r4 << "\n";
    std::cout << r2 * r4 << "\n";
    std::cout << r2 / r4 << "\n";

    // TEST BOOLEAN v1
    std::cout << "TEST BOOLEAN v1" << "\n";
    bool k1, k2, k3;
    k1 = r1 == r2;
    k2 = r1 != r2;
    
   // k3= gcd(1,20) !=gcd(0,0);
  //   std::cout << k3 << "\n";
    std::cout << k1 << "\n";
    std::cout << k2 << "\n";

    // TEST BOOLEAN v2
    std::cout << "TEST BOOLEAN v2" << "\n";
 
       rational x = rational(-1,2);
       rational y = rational(3,-33);
       rational z = rational(-33, -231);
       bool lol = (x*y)*z == x*(y*z);
       std::cout<<lol<<"\n";
       lol= x+(y-z) == -z +y +x;
       std::cout<<lol<<"\n";
       lol = x*(y+z)==y*x + x*z;
       std::cout<<lol<<"\n";
       rational c = rational(0, 2);
       std::cout<<c<<"\n";
      // rational b = rational(8, 0);
     // std::cout<<b<<"\n";
       rational l = rational(0,3);
       std::cout<<l<<"\n";
    //  rational q = rational(0, 0);
  //  std::cout<<q<<"\n";


    // TEST GIVEN BY SST
    std::cout << "TEST +-*/" << "\n";
    rational t = rational(1, 2);
    t = t * 2;
    std::cout << t << "\n";    // prints 1.
    t = t - rational(1,3);
    std::cout << t << "\n";    // Prints 2/3.
    std::cout<<gcd(32493478234924,489203482939)<<std::endl;
    
    std::cout<<gcd(-120,40)<<std::endl;
    std::cout<<gcd(20,120)<<std::endl;
    std::cout<<gcd(-20,-60)<<std::endl;
    std::cout<<gcd(-60,-10)<<std::endl;

    std::cout<<gcd(0,1)<<std::endl;

    std::cout<<gcd(-1,1)<<std::endl;

     std::cout<<gcd(-1,-1)<<std::endl;


    rational r7 = rational(20,5);
        std::cout<<r7<<std::endl;
    rational r8 = rational(-30e9,120e9);
        std::cout<<r8<<std::endl;
    rational r9 = rational(-20,-60);
        std::cout<<r9<<std::endl;
   return 0;
}


