#ifndef __SClass__
#define __SClass__

class String {
private:
	char* str;
	int len;
public:
	String();
	String(const char* cstr);
	String(const String& s);
	String operator=(const String& s);
	void SetString(const char* cstr);
	void SetString(const String& s);
	char* GetString() const;
	~String();
};

#endif