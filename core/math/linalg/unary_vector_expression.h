#pragma once

#include <core/boost.h>
#include <boost/iterator/iterator_facade.hpp>

namespace core {
    template <typename E, typename F>
    class unary_vector_expression :
        public ublas::vector_expression<unary_vector_expression<E, F>>
    {
    private:
        typedef unary_vector_expression<E, F> self_type;
    public:
        typedef typename E::size_type size_type;
        typedef typename E::difference_type difference_type;
        typedef double value_type; //TODO fix this.
        typedef value_type const_reference;
        //typedef typename F::result_type value_type;
        //typedef value_type const_reference;
        typedef const self_type const_closure_type;
        typedef self_type closure_type;
        //typedef unknown_storage_tag storage_category;
    public:
        class const_iterator : public boost::iterator_facade<
            const_iterator,
            const value_type,
            boost::forward_traversal_tag>
        {};

    public:
        unary_vector_expression(const E& v, const F& f)
            : v_(v), f_(f)
        {
        }
        size_type size() const {
            return v_.size();
        }
        const_reference operator () (size_type i) const 
        {
            return f_(v_[i]);
        }
        const_reference operator [] (size_type i) const
        {
            return operator()(i);
        }

    private:
        typename E::const_closure_type v_;
        const F f_;
    };

    template <typename E, typename F>
    inline unary_vector_expression<E, F&>
    make_unary_vector_expression(
        const ublas::vector_expression<E>& v, const F& f)
    {
        return unary_vector_expression<E, F&>{v(), f};
    }

    template <typename E, typename F>
    inline unary_vector_expression<E, F>
    make_unary_vector_expression(
        const ublas::vector_expression<E>& v, const F&& f)
    {
        return unary_vector_expression<E, F>{v(), f};
    }
}