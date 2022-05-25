#ifndef __MYSTRING__
#define __MYSTRING__

class String
{
public:                                 
   String(const char* cstr=0);                  // 一般构造函数                  
   String(const String& str);                   // 深拷贝构造函数
   String& operator=(const String& str);        // 拷贝赋值函数        
   ~String();                                   // 析构函数       
   char* get_c_str() const { return m_data; }   // 取值函数
private:
   char* m_data;  // 为了使得内部对象可动态分配内存，不选择使用数组对象，而是指针对象
};

#include <cstring>

inline
String::String(const char* cstr)
{
   if (cstr) { // 对于指定初值的构造
      m_data = new char[strlen(cstr)+1];  // +1 预留出字符'\0'的空间
      strcpy(m_data, cstr);
   }
   else { // 对于未指定初值的构造
      m_data = new char[1];
      *m_data = '\0';   // 字符串以标识\0结束
   }
}

inline
String::~String() // 析构函数，含指针对象的类必须要有
{
   delete[] m_data;  // 释放指针对象所指的所有内存空间，防止内存泄漏
}

inline
String& String::operator=(const String& str) // 深拷贝赋值函数 
{
   // 自赋值检测，这是非常重要的
   // 如果不进行自赋值检测，后面的步骤会出错，在delete自己后，再赋值时会找不到对象内容
   if (this == &str)
      return *this;

   delete[] m_data;  // 先delete被赋值对象
   m_data = new char[ strlen(str.m_data) + 1 ];    // 分配内存空间
   strcpy(m_data, str.m_data);   // 内容拷贝
   return *this;
}

inline
String::String(const String& str)   // 深拷贝构造函数
{
   m_data = new char[ strlen(str.m_data) + 1 ];
   strcpy(m_data, str.m_data);
}

#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, const String& str)
{
   os << str.get_c_str();
   return os;
}

#endif
