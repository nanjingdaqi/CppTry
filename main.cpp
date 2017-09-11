#include <iostream>
#include "foo.h"
#include "lib_foo.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    cout << "VAR: " << MY_VAR <<endl;

    cout << "my_lib: " << foo() << endl;

    return 0;
}