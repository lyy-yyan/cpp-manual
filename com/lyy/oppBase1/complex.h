#ifndef __MYCOMPLEX__   // 防卫式声明：如果没有声明过，则继续（可防止重复声明），使用#endif结束
#define __MYCOMPLEX__   // 声明

// 前置声明
class complex; 
complex&
  __doapl (complex* ths, const complex& r);
complex&
  __doami (complex* ths, const complex& r);
complex&
  __doaml (complex* ths, const complex& r);

// 类的声明
class complex
{
public:
  // 初始化行为，若将re = r; im = i;写入{}中，则时赋值行为，效率比初始化行为低
  // 这种写法仅限构造函数 ~: re (r), im (i)
  // 下面构造函数的参数传递为值传递，如果可以使用引用传递，请尽量使用，效率更高
  complex (double r = 0, double i = 0): re (r), im (i) { }
  
  // 定义在class内的函数为成员函数，在其外的为全局函数
  complex& operator += (const complex&);      // 参数为引用传递
  complex& operator -= (const complex&);      // 操作符重载
  complex& operator *= (const complex&);
  complex& operator /= (const complex&);
  // 即使是写在body内部的函数也不一定被编译为inline函数，太复杂的函数就不会
  // 常量成员函数：该函数不会改变数据内容
  // 对于一个变量或者是一个函数，如果确保它的值不会改变，尽量添加const关键字修饰
  double real () const { return re; }
  double imag () const { return im; }
private:
    double re, im;
    // 可以使用模板声明就可在创建对象时灵活使用数据类型 T re, im; complex<int> c2(1, 6);

  // friend关键字修饰友元函数，表示该函数可以自由直接地获取private成员
  friend complex& __doapl (complex *, const complex&);
  friend complex& __doami (complex *, const complex&);
  friend complex& __doaml (complex *, const complex&);
};


// 类的定义
// inline指内敛函数，要求编译器尽量将该函数编译为内敛函数，仅是尽量
inline complex&                             // 返回值以引用形式接收
__doapl (complex* ths, const complex& r)
{
  ths->re += r.re;
  ths->im += r.im;
  return *ths;                              // 传递者以指针形式传递，传递者无需知道接收者是以引用形式接收的
}
 
inline complex&
complex::operator += (const complex& r)     // ::即成员函数未在类内部声明定义，在类外部定义
{
  return __doapl (this, r);                 // 哪个对象调用这个函数，this就是那个对象
}

inline complex&
__doami (complex* ths, const complex& r)
{
  ths->re -= r.re;
  ths->im -= r.im;
  return *ths;
}
 
inline complex&
complex::operator -= (const complex& r)
{
  return __doami (this, r);
}
 
inline complex&
__doaml (complex* ths, const complex& r)
{
  double f = ths->re * r.re - ths->im * r.im;
  ths->im = ths->re * r.im + ths->im * r.re;
  ths->re = f;
  return *ths;
}

inline complex&
complex::operator *= (const complex& r)
{
  return __doaml (this, r);
}
 
inline double
imag (const complex& x)
{
  return x.imag ();
}

inline double
real (const complex& x)
{
  return x.real ();
}

inline complex                                                // 这里无法返回引用类型，因为函数返回的是一个局部变量
operator + (const complex& x, const complex& y)
{
  return complex (real (x) + real (y), imag (x) + imag (y));  // 创建一个临时对象complex
}

inline complex
operator + (const complex& x, double y)
{
  return complex (real (x) + y, imag (x));
}

inline complex
operator + (double x, const complex& y)
{
  return complex (x + real (y), imag (y));
}

inline complex
operator - (const complex& x, const complex& y)
{
  return complex (real (x) - real (y), imag (x) - imag (y));
}

inline complex
operator - (const complex& x, double y)
{
  return complex (real (x) - y, imag (x));
}

inline complex
operator - (double x, const complex& y)
{
  return complex (x - real (y), - imag (y));
}

inline complex
operator * (const complex& x, const complex& y)
{
  return complex (real (x) * real (y) - imag (x) * imag (y),
			   real (x) * imag (y) + imag (x) * real (y));
}

inline complex
operator * (const complex& x, double y)
{
  return complex (real (x) * y, imag (x) * y);
}

inline complex
operator * (double x, const complex& y)
{
  return complex (x * real (y), x * imag (y));
}

complex
operator / (const complex& x, double y)
{
  return complex (real (x) / y, imag (x) / y);
}

inline complex      // 此行可以修改为inline complex&，效率更高，此处的x并非局部变量，可用引用返回
operator + (const complex& x)
{
  return x;
}

inline complex
operator - (const complex& x)
{
  return complex (-real (x), -imag (x));
}

inline bool
operator == (const complex& x, const complex& y)
{
  return real (x) == real (y) && imag (x) == imag (y);
}

inline bool
operator == (const complex& x, double y)
{
  return real (x) == y && imag (x) == 0;
}

inline bool
operator == (double x, const complex& y)
{
  return x == real (y) && imag (y) == 0;
}

inline bool
operator != (const complex& x, const complex& y)
{
  return real (x) != real (y) || imag (x) != imag (y);
}

inline bool
operator != (const complex& x, double y)
{
  return real (x) != y || imag (x) != 0;
}

inline bool
operator != (double x, const complex& y)
{
  return x != real (y) || imag (y) != 0;
}

// new add 可以重载输出操作符 <<
// 对于类似 << 这类的操作符重载函数不能作为成员函数
# include <iostream>
ostream& 
operator << (ostream& os, const complex& x)
{
  return os << '(' << real(x) << ', ' << imag(x) << ')';
}

#include <cmath>

inline complex
polar (double r, double t)
{
  return complex (r * cos (t), r * sin (t));
}

inline complex
conj (const complex& x) 
{
  return complex (real (x), -imag (x));
}

inline double
norm (const complex& x)
{
  return real (x) * real (x) + imag (x) * imag (x);
}

#endif   //__MYCOMPLEX__




