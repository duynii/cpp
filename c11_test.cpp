#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

static const int SIZE=10;

class Q
{
private:
	char _buf[SIZE];
public:
	/*
	Q(const char* cstr)
	{
		if(cstr == NULL)
		{
			memset(_buf, 0, SIZE);
			return;
		} 

		size_t len =  strlen(cstr);
		strncpy(_buf, cstr, SIZE - 1);
		_buf[SIZE-1] = '\0';
	}
	*/

	Q(const char cstr[])
	{
		if(cstr == NULL)
		{
			memset(_buf, 0, SIZE);
			return;
		} 
		size_t len =  strlen(cstr);
		strncpy(_buf, cstr, SIZE - 1);
		_buf[SIZE-1] = '\0';
	}

	Q(const Q& rhs)
	{
		strncpy(_buf, rhs._buf, SIZE - 1);	
		_buf[SIZE-1] = '\0';
	}

	Q& operator=(const Q& rhs)
	{
		if(this == &rhs) return *this;

		strncpy(_buf, rhs._buf, SIZE-1);	
		_buf[SIZE-1] = '\0';

		return *this;
	}

	void print() const
	{
		printf("%s\n", _buf);
	}
};

int main()
{
    printf("Woot starting c11\n");

    Q q("this is a string");
    q.print();

    Q p(q);
    p.print();

    Q r("test");
    r.print();
    r = q;
    r.print();

    return 0;
}