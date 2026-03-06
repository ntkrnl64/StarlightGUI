#pragma once

#include <pch.h>
#include <coroutine>
#include <exception>

namespace slg {
    // 更加安全的协程，智能捕获异常而不是直接崩溃退出
    struct coroutine {
        coroutine() = default;

        struct promise_type {
            coroutine get_return_object() const noexcept { return {}; }

            void return_void() const noexcept {}

            std::suspend_never initial_suspend() const noexcept { return {}; }

            std::suspend_never final_suspend() const noexcept { return {}; }

            void unhandled_exception() const noexcept
            {
                try {
                    std::rethrow_exception(std::current_exception());
                }
                catch (const winrt::hresult_error& e) {
                    LOG_ERROR(L"App", L"===== Unhandled exception detected! =====");
                    LOG_ERROR(L"App", L"Type: 'winrt::hresult_error'");
                    LOG_ERROR(L"App", L"Code: %d", e.code().value);
                    LOG_ERROR(L"App", L"Message: %s", e.message().c_str());
                    LOG_ERROR(L"App", L"=========================================");
                }
                catch (const std::exception& e) {
                    LOG_ERROR(L"App", L"===== Unhandled exception detected! =====");
                    LOG_ERROR(L"App", L"Type: 'std::exception'");
                    LOG_ERROR(L"App", L"Message: %hs", e.what());
                    LOG_ERROR(L"App", L"=========================================");
                }
                catch (...) {
                    LOG_ERROR(L"App", L"===== Unhandled exception detected! =====");
                    LOG_ERROR(L"App", L"Type: OTHER/UNKNOWN");
                    LOG_ERROR(L"App", L"This should not happen!");
                    LOG_ERROR(L"App", L"=========================================");
                }
            }
        };
    };
}