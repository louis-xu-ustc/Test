#include "testMapOnQNX.h"
#include <iostream>

using namespace std;


TestClass::TestClass()
{
    
}

TestClass::~TestClass()
{

}

bool
TestClass::verify(const char *ch1, const char *ch2)
{
    TestClass *tc = get();

    pair<string, string> p = make_pair<string, string>(ch1, ch2);
    TestClassMapIter it = tc->classes_.find(p);

    dbg();
    return it != tc->classes_.end();
}

void
TestClass::dbg(void)
{
    TestClass *tc = get();
    
    for (TestClassMapIter it = tc->classes_.begin(); it != tc->classes_.end(); it++)
    {
        cout << __func__ << " - " << __LINE__ << " item: " << it->first.first.c_str() << " : " << it->first.second.c_str() << endl;
    }
}

int main(int argc, char**argv)
{
    const char *ch1 = "test1";
    const char *ch2 = "test2";

    TestClass::add(ch1, ch2);

    bool ret = TestClass::verify(ch1, ch2);
    cout << "ret: " << ret << endl;

    return 0;
}
