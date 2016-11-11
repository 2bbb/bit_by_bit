/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/container/iterator/delegation.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <iterator>

#include <bbb/core.hpp>
#include <bbb/container/iterator/providers.hpp>
#include <bbb/container/iterator/value_type_provider.hpp>
#include <bbb/container/iterator/inserter_provider.hpp>

namespace bbb {
    namespace container {
        namespace iterator {
            template <typename container>
            struct iterator_delegation
                : iterator_providers<container>::forward_iterator_provider
                    , iterator_providers<container>::reverse_iterator_provider
                    , inserter_provider<container>
                    , front_inserter_provider<container>
                    , back_inserter_provider<container>
                    , value_type_provider<container> {
                using delegation = iterator_delegation<container>;
            protected:
                iterator_delegation() = delete;
                iterator_delegation(container &body)
                    : iterator_providers<container>::forward_iterator_provider(body)
                    , iterator_providers<container>::reverse_iterator_provider(body)
                    , inserter_provider<container>(body)
                    , front_inserter_provider<container>(body)
                    , back_inserter_provider<container>(body) {}
            };
        };
    };
};
