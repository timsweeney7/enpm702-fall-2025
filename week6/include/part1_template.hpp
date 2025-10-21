/**
 * @brief Returns the greater of two values.
 * 
 * @tparam T A totally ordered type (requires operator>).
 * @param a First value. 
 * @param b Second value.
 * @return The larger of \p a and \p b.
 * @note Use explicit template arguments if deduction is ambiguous.
 * @code
 * auto m{max_value<int>(3, 4)};
 * @endcode
 */
template<typename T>
T max_value(T a, T b)
{
    return (a > b) ? a : b;
}