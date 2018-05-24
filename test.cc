#include <iostream>

using namespace std;


class Someclass {
    public:
        int x;
    public :
        Someclass(int xx) : x(xx) { 
            //cout << "Construction: " << x << endl;
        }

        Someclass(const Someclass& a) { 
            x = a.x; 
            x++; 
            //cout << "Copy Construction: " << x << endl;
        }
        
        void operator =(const Someclass& a1) {
            x = a1.x;
            x--;
            //cout << "Assignment Construction: " << x << endl;
        }
};

int main( )
{
    Someclass a(4);

    Someclass b = a;
    cout << b.x << endl;

    Someclass c(b);
    cout << c.x << endl;

    Someclass d(c);
    d = c;
    cout << d.x << endl;

    return 0;
}
