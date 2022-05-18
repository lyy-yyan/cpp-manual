#include <iostream>
#include "complex.h"    // 引入头文件，复数类

using namespace std;

// 可以重载输出操作符 <<
// 对于类似 << 这类的操作符重载函数不能作为成员函数
ostream&
operator << (ostream& os, const complex& x)
{
  return os << '(' << real (x) << ',' << imag (x) << ')';
}

int main()
{
  // 声明两个复数对象c1，c2
  complex c1(2, 1);
  complex c2(4, 0);

  cout << c1 << endl;           // (2,1)
  cout << c2 << endl;           // (4,0)
  
  cout << c1+c2 << endl;        // (6,1)
  cout << c1-c2 << endl;        // (-2,1)
  cout << c1*c2 << endl;        // (8,4)
  cout << c1 / 2 << endl;       // (1,0.5)
  
  cout << conj(c1) << endl;     // (2,-1)
  cout << norm(c1) << endl;     // 5
  cout << polar(10,4) << endl;  // (-6.53644,-7.56802)
  
  cout << (c1 += c2) << endl;   // (6,1)
  
  cout << (c1 == c2) << endl;   // 0
  cout << (c1 != c2) << endl;   // 1
  cout << +c2 << endl;          // (4,0)
  cout << -c2 << endl;          // (-4,-0)
  
  cout << (c2 - 2) << endl;     // (2,0)
  cout << (5 + c2) << endl;     // (9,0)
  
  return 0;
}
