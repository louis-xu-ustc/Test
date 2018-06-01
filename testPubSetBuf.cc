#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

inline std::string uchar2hex(unsigned char inchar)
{
    std::ostringstream oss (std::ostringstream::out);
    oss << std::setw(2) << std::setfill('0') << std::hex << (int)(inchar);
    return oss.str();
}

int main(int argc, char** argv)
{

    string str = "Hello World.";
    const void *blob = str.data();
    const unsigned int size = str.length();

    istringstream buf;

    buf.rdbuf()->pubsetbuf((char *)(const_cast<void *>(blob)), size);
    cout << "buf content: " << endl;
    while (buf) 
    {
        cout << uchar2hex(char(buf.get())) << endl;
    }
}
