#pragma once

#include "App.xaml.g.h"

namespace winrt::Uwp_cppwinrt::implementation
{
    extern Windows::ApplicationModel::AppService::AppServiceConnection _Connection;

    struct App : AppT<App>
    {
        App();
        ~App();
        static Windows::ApplicationModel::AppService::AppServiceConnection Connection();

        void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&);
        void OnSuspending(IInspectable const&, Windows::ApplicationModel::SuspendingEventArgs const&);
        void OnNavigationFailed(IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const&);
        void OnBackgroundActivated(Windows::ApplicationModel::Activation::BackgroundActivatedEventArgs const& args);

        static Windows::ApplicationModel::AppService::AppServiceConnection _Connection;

    private:
        Windows::ApplicationModel::Background::IBackgroundTaskInstance::Canceled_revoker m_appServiceDeferralCanceledEventRevoker;
        void OnTaskCanceled(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& sender, Windows::ApplicationModel::Background::BackgroundTaskCancellationReason const& reason);
        Windows::ApplicationModel::Background::BackgroundTaskDeferral appServiceDeferral{ nullptr };
    };
}
