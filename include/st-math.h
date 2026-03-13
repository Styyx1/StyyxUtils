//
// Created by styyx on 12/03/2026.
//

#pragma once

namespace StyyxUtil
{
    struct MathUtil {

    /// @brief Template function to add to a value without ever risking overflowing the maximum value that type can have.
    /// @tparam T Has to be a number
    /// @param base The value to add to
    /// @param increment The value added to base
    /// @return The result of the addition
    /// @par Example
    /// @code
    /// const uint8_t result = MathUtil::SafelyAdd<uint8_t>(200, 100);
    /// // result will be 255 instead of overflowing
    /// @endcode
    /// @deprecated Use MathUtil::SafelyAddWithCap instead. You can use it without passing a cap to cap it to numeric limits
    template <typename T>
    requires std::is_arithmetic_v<T>
    [[deprecated("Use MathUtil::SafelyAddWithCap instead")]]
    static T SafelyAdd(T base, T increment)
    {
        using ForMath = std::conditional_t<std::is_integral_v<T> && sizeof(T) < sizeof(int), int, T>;

        const auto a = static_cast<ForMath>(base);
        const auto b = static_cast<ForMath>(increment);
        const auto max = static_cast<ForMath>(std::numeric_limits<T>::max());

        return static_cast<T>(a + b > max ? max : a + b);
    }

    /// @brief Add a value to another one and cap the result
    /// @tparam T Has to be a number
    /// @param base The value to add to
    /// @param increment The value added to base
    /// @param cap A cap for the result. If nothing is passed, the cap will be the numeric limit
    /// @return the result of the addition
    /// @note If cap is less than base, the result will be capped to cap regardless of increment
    template <typename T>
    requires std::is_arithmetic_v<T>
    static T SafelyAddWithCap(T base, T increment, T cap = std::numeric_limits<T>::max()) {

        using ForMath = std::conditional_t<std::is_integral_v<T> && sizeof(T) < sizeof(int), int, T>;

        const auto a = static_cast<ForMath>(base);
        const auto b = static_cast<ForMath>(increment);
        const auto max = std::min(static_cast<ForMath>(cap), static_cast<ForMath>(std::numeric_limits<T>::max()));

        return static_cast<T>(a + b > max ? max : a + b);
    }
};
}