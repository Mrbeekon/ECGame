#ifndef SEVENT_H
#define SEVENT_H

#include "ECStd.hpp"

template <typename _ArgT>
class SEvent
{
    typedef std::function<void(_ArgT&)> _func_t;
    typedef std::vector<_func_t> _funcv_t;

    _funcv_t _funcs;

    inline void _caller(_func_t f, _ArgT& e)
    {
        f(e);
    }

public:
    SEvent& operator+=(const _func_t& f)
    {
        _funcs.push_back(f);
        return *this;
    }

    SEvent& operator()(_ArgT& e)
    {
        for(typename _funcv_t::iterator it = _funcs.begin();
            it != _funcs.end(); ++it) {
            _caller(*it, e);
        }
        return *this;
    }
};

#endif
