#include <map>
#include <utility>
#include <string>
#include <iostream>
#include <string>

using namespace std;

#define enter() \
    {   \
        cout << __func__ << " :: enter" << endl;    \
    }

#define leave() \
    {   \
        cout << __func__ << " :: leave" << endl;    \
    }

#define TestClassHelper(num)  \
    extern "C" \
    { \
        void register_test() \
        {   \
            TestClass::foo<num>(); \
        } \
    }


class TestClass
{
    public:
        static bool add(const char *ch1, const char *ch2);
        static bool verify(const char *ch1, const char *ch2);
        static bool loadPlugin(void);
        static void dbg(void);
        template<int num> static void foo();
    
    protected:
        TestClass();
        ~TestClass();

        static TestClass *get(void);

    private:
        typedef std::map<std::pair<std::string, std::string>, std::string> TestClassMap;
        typedef TestClassMap::iterator TestClassMapIter;

        TestClassMap classes_;
};


bool
TestClass::add(const char *ch1, const char *ch2)
{
    enter();
    TestClass *tc = get();
    cout << __func__<< " tc: " << tc << endl;
    
    std::pair<string, string> p = std::make_pair<string, string>(ch1, ch2);
    TestClassMapIter it = tc->classes_.find(p);
    if (it != tc->classes_.end())
    {
        //
    }
    else 
    {
        std::string str = "test";
        tc->classes_.insert(std::make_pair(p, str));
    }
    leave();
    return true;
}

template<int num> 
void TestClass::foo() {
    enter();
    static int i;
    i++;
    cout << "i: " << i << endl;
    TestClass *tc = get();
    cout << __func__<< " tc: " << tc << endl;
    leave();
}

inline TestClass *TestClass::get(void)
{
    static TestClass tc;
    return &tc;
}

template<int num>
void bar()
{
    enter();
    const char *ch3 = "test3";
    const char *ch4 = "test4";

    TestClass::add(ch3, ch4);
    static int baz;
    printf("bar<%i>::baz = %i\n", num, baz++);
    leave();
}

