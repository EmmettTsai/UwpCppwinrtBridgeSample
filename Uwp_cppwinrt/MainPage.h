#pragma once

#include "MainPage.g.h"

namespace winrt::Uwp_cppwinrt::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        void Button3ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
        Windows::Foundation::IAsyncAction SendRequest();
    };
}

namespace winrt::Uwp_cppwinrt::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
