#define UNICODE
#include <iostream>
#include "Windows.h"
#include "stdio.h"
using namespace std;
void C_char() {
	const char* text = "你好世界";
	cout << text << endl;
}
void W_char() {
	const wchar_t * pwText = L"你好世界";
	//cout << pwText << endl;
	wcout << pwText << endl;
	int len = wcslen(pwText);
	wprintf(L"%s %d\n", pwText, len);
}
void T_char() {
	const TCHAR* text = __TEXT("hello");
#ifdef UNICODE
	wcout <<"宽字节:"<< text << endl;
#else
	cout <<"单字节:"<< text << endl;
#endif
}
VOID printUnicode() {
	const wchar_t* text =L"发生发生法发噶广发";
	HANDLE  handle =GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(handle, text,wcslen(text),NULL,NULL);
}
int main() {
	printUnicode();

}