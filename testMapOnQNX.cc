#include "testMapOnQNX.h"
#include <dlfcn.h>
#include <cstdlib>

TestClass::TestClass()
{
    
}

TestClass::~TestClass()
{

}

bool
TestClass::verify(const char *ch1, const char *ch2)
{
    enter();
    TestClass *tc = get();
    cout << __func__<< " tc: " << tc << endl;

    pair<string, string> p = make_pair<string, string>(ch1, ch2);
    TestClassMapIter it = tc->classes_.find(p);

    loadPlugin();
    dbg();
    leave();
    return it != tc->classes_.end();
}

bool 
TestClass::loadPlugin(void)
{
    enter();
    bool ret = true;
    const char* dlerror_save = NULL;
    void (*register_test)(void);
    const char *uc_dir = getenv("OTTO_DIR");
    for (int i = 1; i <= 2; i++) {
        string implSoName = string(uc_dir) + '/' +"lib/qnx/libTest" + to_string(i) + ".so";

        void *handle = dlopen(implSoName.c_str(), RTLD_GLOBAL | RTLD_NOW);
        if (!handle)
        {
            cout << __func__ << "handle doesn't exist" << endl;
            ret = false;
            goto err;
        }

        dlerror();
        register_test = reinterpret_cast<void(*)(void)>(dlsym(handle, "register_test"));

        if ((dlerror_save = dlerror()) != NULL)
        {
            cout << __func__ << "dlerror" << endl;
            ret = false;
            goto err;
        }
        register_test();
    }

err:
    leave();
    return ret;
}

void
TestClass::dbg(void)
{
    TestClass *tc = get();
    cout << __func__<< " tc: " << tc << endl;
    
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

    TestClass::foo<1>();
    TestClass::foo<2>();
    TestClass::foo<1>();
    TestClass::foo<2>();

    bar<1>();
    bar<2>();
    bar<1>();
    bar<2>();

    return 0;
}
