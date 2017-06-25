#define def_unary_op(op, name)\
                constexpr auto operator op() const\
                -> direct_function<op_type::name, direct_function>\
                { return {*this}; }

                def_unary_op(!, unary_not);
                def_unary_op(~, unary_bit_not);
                def_unary_op(+, unary_plus);
                def_unary_op(-, unary_minus);
                def_unary_op(&, address);
                def_unary_op(*, dereference);
#undef def_unary_op

                template <typename index_t>
                constexpr auto operator[](const index_t &index) const
                -> direct_function<op_type::subscript, direct_function, index_t>
                { return {std::tuple<direct_function, index_t>(*this, index)}; }

                // TODO implement member pointer
                template <typename obj, typename result, typename ... arguments>
                constexpr auto operator->*(result(obj::*meth)(arguments ...) const) const
                -> direct_function<op_type::member_pointer, direct_function, result(obj::*)(arguments ...) const>
                { return {std::tuple<direct_function, result(obj::*)(arguments ...) const>(*this, meth)}; }
