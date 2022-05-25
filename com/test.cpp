#include <iostream>
#include <cstring>
using namespace std;

int main() {

    // 想要测试一下\0字符在char类型中的表现
    // 一个疑问，strcpy()函数不会copy '\0'字符吗？
    char s1 = '\0';
    char* s2 = new char[6]{'h', 'e', 'l', 'l', 'o', '\0'};
    char* s3 = new char[6];
    strcpy(s3, s2);
    cout << "s1:" << s1 << " s2:" << s2 << " s3:" << s3 << "end" << endl;
    // 输出：s1: s2:hello s3:helloend
    // 可以看出"s1:"与"s2..."之间仅有一个空格，是我自己写的空格，另外s3与end之间也并未输出空格
    // 结论：strcpy函数并不会复制'\0'字符

    return 0;
}