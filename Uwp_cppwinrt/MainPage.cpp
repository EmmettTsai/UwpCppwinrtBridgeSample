#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::UI::Xaml;

namespace winrt::Uwp_cppwinrt::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    void MainPage::ClickHandler(IInspectable const& sender, RoutedEventArgs const&)
    {
        //myButtonDefault().Content(box_value(L"Clicked"));
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
}
