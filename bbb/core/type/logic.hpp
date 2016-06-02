/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/type/logic.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

namespace bbb {
    namespace logic {
        namespace detail {
            template <template <typename> class pred, typename ... arguments>
            struct all;
            template <template <typename> class pred, typename argument, typename ... arguments>
            struct all<pred, argument, arguments ...> {
                using type = typename std::conditional<
                    pred<argument>::value,
                    typename all<pred, arguments ...>::type,
                    std::false_type
                >::type;
            };
            template <template <typename> class pred, typename argument>
            struct all<pred, argument> {
                using type = pred<argument>;
            };

            template <template <typename> class pred, typename ... arguments>
            struct any;
            template <template <typename> class pred, typename argument, typename ... arguments>
            struct any<pred, argument, arguments ...> {
                using type = typename std::conditional<
                    pred<argument>::value,
                    std::true_type,
                    typename any<pred, arguments ...>::type
                >::type;
            };
            template <template <typename> class pred, typename argument>
            struct any<pred, argument> {
                using type = pred<argument>;
            };
        };

        template <template <typename> class pred, typename ... arguments>
        using all_t = typename detail::all<pred, arguments ...>::type;

        template <template <typename> class pred, typename ... arguments>
        using any_t = typename detail::any<pred, arguments ...>::type;
    };

    using namespace logic;
};
