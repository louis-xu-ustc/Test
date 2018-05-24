#include <map>
#include <utility>
#include <string>

class TestClass
{
    public:
        static bool add(const char *ch1, const char *ch2);
        static bool verify(const char *ch1, const char *ch2);
        static void dbg(void);

    protected:
        TestClass();
        ~TestClass();

        static TestClass *get(void);

    private:
        typedef std::map<std::pair<std::string, std::string>, std::string> TestClassMap;
        typedef TestClassMap::iterator TestClassMapIter;

        TestClassMap classes_;
};

inline TestClass *TestClass::get(void)
{
    static TestClass tc;
    return &tc;
}

bool
TestClass::add(const char *ch1, const char *ch2)
{
    TestClass *tc = get();
    
    pair<string, string> p = make_pair<string, string>(ch1, ch2);
    TestClassMapIter it = tc->classes_.find(p);
    if (it != tc->classes_.end())
    {
        //
    }
    else 
    {
        string str = "test";
        tc->classes_.insert(make_pair(p, str));
    }
    dbg();
    return true;
}

