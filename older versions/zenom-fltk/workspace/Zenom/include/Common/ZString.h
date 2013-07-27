#ifndef ZSTRING_H
#define ZSTRING_H

class ZString
{
public:
	ZString(void);
	ZString(const int pInt);
	ZString(const double pDouble, const int pPrecision = 2);
	ZString(const char *pStr);
	ZString(const ZString &pStr);
	~ZString(void);

	int length() const;
	const char* c_str() const;
	ZString operator=(const ZString& pLeft) ;
	bool operator==(const ZString& pLeft) const;
	bool operator!=(const ZString& pLeft) const;
	ZString operator+(const ZString& pLeft) const;
	ZString& operator<<(const ZString& pLeft);
	int find(const char pChar, const int pCount = 1 ) const ;
	int findReverse(const char pChar, const int pCount = 1 ) const ;
	ZString removeFromBack(const char pChar); // verilen karakterin sag kismini siler, karakteri aramaya sagdan baslar
	ZString right(const int pCount) const;
	ZString left(const int pCount) const;

private:
	void reserveStr(int pSize);
	void createNullStr();
	char *mStrPtr;
	int mLength;
};

#endif
