#include "pch.h"
#include <ppltasks.h>

using namespace winrt;
using namespace concurrency;
using namespace Windows::ApplicationModel::AppService;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

AppServiceConnection _connection{ nullptr };
IAsyncAction RequestReceived(AppServiceConnection const& connection, AppServiceRequestReceivedEventArgs const& args);
void ServiceClosed(AppServiceConnection const& connection, AppServiceClosedEventArgs const& args);

/// <summary>
/// Creates the app service connection
/// </summary>
IAsyncAction ConnectToAppServiceAsync()
{
    // Get the package family name
    Windows::ApplicationModel::Package package = Windows::ApplicationModel::Package::Current();
    hstring packageFamilyName = package.Id().FamilyName();

    // Create and set the connection
    auto connection = AppServiceConnection();
    connection.PackageFamilyName(packageFamilyName);
    connection.AppServiceName(L"CommunicationService");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));
    wprintf(L"Opening connection...\n");

    // Open the connection
    AppServiceConnectionStatus status = co_await connection.OpenAsync();
    if (status == AppServiceConnectionStatus::Success)
    {
        _connection = connection;
        wprintf(L"Successfully opened connection.\n");
        _connection.RequestReceived(TypedEventHandler<AppServiceConnection, AppServiceRequestReceivedEventArgs>(RequestReceived));
        _connection.ServiceClosed(TypedEventHandler<AppServiceConnection, AppServiceClosedEventArgs>(ServiceClosed));
    }
    else if (status == AppServiceConnectionStatus::AppUnavailable || status == AppServiceConnectionStatus::AppServiceUnavailable)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED));
        wprintf(L"AppService Unavailable\n");
    }
}

int wmain(int argc, wchar_t* argv[])
{
    init_apartment();
    Uri uri(L"http://aka.ms/cppwinrt");
    wprintf(L"Hello, %ls!\n", uri.AbsoluteUri().c_str());
    wprintf(L"arg count: %d\n", argc);
    for (int i = 0; i < argc; i++)
        wprintf(L"arg[%d]: %s\n", i, argv[i]);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_GREEN));
    wprintf(L"*********************************\n\n");
    wprintf(L"**** Classic desktop C++ app ****\n\n");
    wprintf(L"*********************************\n\n");
    wprintf(L"Creating app service connection\n\n");

    ConnectToAppServiceAsync();

    system("pause");
    return 0;
}

/// <summary>
/// Receives message from UWP app and sends a response back
/// </summary>
IAsyncAction RequestReceived(AppServiceConnection const& connection, AppServiceRequestReceivedEventArgs const& args)
{
    auto deferral = args.GetDeferral();
    auto message = args.Request().Message();
    auto method = message.Lookup(L"request").as<hstring>();
    PCWSTR data = method.data();

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_GREEN));
    wprintf(L"%s", data);
    wprintf(L" - request received\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN));

    //ShowToast(data);
    auto response = ValueSet();
    response.Insert(L"response", box_value(hstring(L"ack")));
    AppServiceResponseStatus status = co_await args.Request().SendResponseAsync(response);
    deferral.Complete();
}

/// <summary>
/// Occurs when the other endpoint closes the connection to the app service
/// </summary>
void ServiceClosed(AppServiceConnection const& connection, AppServiceClosedEventArgs const& args)
{
}
