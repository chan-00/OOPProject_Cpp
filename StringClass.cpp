#include<iostream>
#include<cstring>
#include "StringClass.h"

using namespace std;

String::String() {
	str = NULL;
	len = 0;
}

String::String(const char* cstr) {
	len = strlen(cstr) + 1;
	str = new char[len];
	strcpy(str, cstr);
}

String::String(const String& s) {
	len = strlen(s.str) + 1;
	str = new char[len];
	strcpy(str, s.str);
}

String String::operator=(const String& s) {
	if (str != NULL)
		delete[]str;

	len = strlen(s.str) + 1;
	str = new char[len];
	strcpy(str, s.str);
	String newStr(str);

	return newStr;
}

void String::SetString(const char* cstr) {
	if (str != NULL)
		delete[]str;

	len = strlen(cstr) + 1;
	str = new char[len];
	strcpy(str, cstr);
}

void String::SetString(const String& s) {
	if (str != NULL)
		delete[]str;

	len = strlen(s.str) + 1;
	str = new char[len];
	strcpy(str, s.str);
}

char* String::GetString() const {
	return str;
}

String::~String() {
	if (str != NULL)
		delete[]str;
}