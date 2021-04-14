#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;

int wmain(int argc, wchar_t* argv[])
{
    init_apartment();
    Uri uri(L"http://aka.ms/cppwinrt");
    wprintf(L"Hello, %ls!\n", uri.AbsoluteUri().c_str());
    wprintf(L"arg count: %d\n", argc);
    for (int i = 0; i < argc; i++)
        wprintf(L"arg[%d]: %s\n", i, argv[i]);
    system("pause");
    return 0;
}
