#ifndef SEVENT_H
#define SEVENT_H

#include "ECStd.hpp"

/* This allows for the creation of 'Special Events'
 * These are a special type which allow for the calling
 * of multiple methods at once. All special events bear
 * an 'EventArgs' type -- this is given to the called
 * methods, and can contain parameters for the event.
 *
 * An event can be specified like so:
 *
 * // Define the EventArgs
 * struct ErrorEventArgs
 * {
 *     std::string reasonString;
 *     ushort      errorCode;
 * }
 *
 * // Declare our error as a class member
 * SEvent<ErrorEventArgs> onError;
 * 
 * In the constructor, add some functions that will be called,
 * or even a lambda function:
 * 
 * onError += HandleError;
 * onError += [](ErrorEventArgs) {
 *     // Do Stuff
 * };
 *
 * To call the event, simply do:
 *
 * onError();
 *
 * when necessary.
 */

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
