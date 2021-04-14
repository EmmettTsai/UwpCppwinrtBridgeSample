#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include "App.h"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::AppService;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;

namespace winrt::Uwp_cppwinrt::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    void MainPage::ClickHandler(IInspectable const& sender, RoutedEventArgs const&)
    {
        if (sender == myButtonDefault())
        {
            FullTrustProcessLauncher::LaunchFullTrustProcessForCurrentAppAsync();
        }
        else if (sender == myButtonCase1())
        {
            FullTrustProcessLauncher::LaunchFullTrustProcessForCurrentAppAsync(L"Case1GroupId");
        }
        else if (sender == myButtonCase2())
        {
            FullTrustProcessLauncher::LaunchFullTrustProcessForCurrentAppAsync(L"Case2GroupId");
        }
    }

    void MainPage::Button3ClickHandler(IInspectable const& sender, RoutedEventArgs const&)
    {
        SendRequest();
    }

    IAsyncAction MainPage::SendRequest()
    {
        ValueSet valueSet = ValueSet();
        valueSet.Insert(L"request", box_value(L"value"));

        if (App::Connection() != nullptr)
        {
            AppServiceResponse response = co_await App::Connection().SendMessageAsync(valueSet);
            hstring result = L"Received response: " + response.Message().Lookup(L"response").as<hstring>();
            myTextBlock().Text(result);
        }
    }
}
