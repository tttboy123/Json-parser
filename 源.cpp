import <iostream>;
using namespace std;
#include "Json.h"
using namespace Seazzz::json;
int main()
{
	const string& str = "1.23";
	Json v;
	v.parse(str);
}