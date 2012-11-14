#ifndef STX_BIND_HPP
#define STX_BIND_HPP

namespace stx {

//  Regular function wrappers.

template<class Func>
class callable_0
{
public:
    
    callable_0(Func func):
        func_(func)
    {
    }
    
    void operator()()
    {
        (*func_)();
    }
    
private:
    
    Func func_;
};

template<class Func, class A1>
class callable_1
{
public:
    
    callable_1(Func func, A1 a1):
        func_(func), a1_(a1)
    {
    }
    
    void operator()()
    {
        (*func_)(a1_);
    }
    
private:
    
    Func func_;
    A1 a1_;
};

template<class Func, class A1, class A2>
class callable_2
{
public:
    
    callable_2(Func func, A1 a1, A2 a2):
        func_(func), a1_(a1), a2_(a2)
    {
    }
    
    void operator()()
    {
        (func_)(a1_, a2_);
    }
    
private:
    
    Func func_;
    A1 a1_;
    A2 a2_;
};

template<class Func, class A1, class A2, class A3>
class callable_3
{
public:
    
    callable_3(Func func, A1 a1, A2 a2, A3 a3):
        func_(func), a1_(a1), a2_(a2), a3_(a3)
    {
    }
    
    void operator()()
    {
        (*func_)(a1_, a2_, a3_);
    }
    
private:
    
    Func func_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
};

template<class Func, class A1, class A2, class A3, class A4>
class callable_4
{
public:
    
    callable_4(Func func, A1 a1, A2 a2, A3 a3, A4 a4):
        func_(func), a1_(a1), a2_(a2), a3_(a3), a4_(a4)
    {
    }
    
    void operator()()
    {
        (*func_)(a1_, a2_, a3_, a4_);
    }
    
private:
    
    Func func_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
};

template<class Func, class A1, class A2, class A3, class A4, class A5>
class callable_5
{
public:
    
    callable_5(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5):
        func_(func), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5)
    {
    }
    
    void operator()()
    {
        (*func_)(a1_, a2_, a3_, a4_, a5_);
    }
    
private:
    
    Func func_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
};

template<class Func, class A1, class A2, class A3, class A4, class A5, class A6>
class callable_6
{
public:
    
    callable_6(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6):
        func_(func), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5), a6_(a6)
    {
    }
    
    void operator()()
    {
        (*func_)(a1_, a2_, a3_, a4_, a5_, a6_);
    }
    
private:
    
    Func func_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
    A6 a6_;
};

template<class Func, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
class callable_7
{
public:
    
    callable_7(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7):
        func_(func), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5), a6_(a6), a7_(a7)
    {
    }
    
    void operator()()
    {
        (*func_)(a1_, a2_, a3_, a4_, a5_, a6_, a7_);
    }
    
private:
    
    Func func_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
    A6 a6_;
    A7 a7_;
};

template<class Func, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
class callable_8
{
public:
    
    callable_8(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8):
        func_(func), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5), a6_(a6), a7_(a7), a8_(a8)
    {
    }
    
    void operator()()
    {
        (*func_)(a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_);
    }
    
private:
    
    Func func_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
    A6 a6_;
    A7 a7_;
    A8 a8_;
};

template<class Func>
inline callable_0<Func>
bind(Func func)
{
    return callable_0<Func>
        (func);
}

template<class Func, class A1>
inline callable_1<Func, A1>
bind(Func func, A1 a1)
{
    return callable_1<Func, A1>
        (func, a1);
}

template<class Func, class A1, class A2>
inline callable_2<Func, A1, A2>
bind(Func func, A1 a1, A2 a2)
{
    return callable_2<Func, A1, A2>
        (func, a1, a2);
}

template<class Func, class A1, class A2, class A3>
inline callable_3<Func, A1, A2, A3>
bind(Func func, A1 a1, A2 a2, A3 a3)
{
    return callable_3<Func, A1, A2, A3>
        (func, a1, a2, a3);
}

template<class Func, class A1, class A2, class A3, class A4>
inline callable_4<Func, A1, A2, A3, A4>
bind(Func func, A1 a1, A2 a2, A3 a3, A4 a4)
{
    return callable_4<Func, A1, A2, A3, A4>
        (func, a1, a2, a3, a4);
}

template<class Func, class A1, class A2, class A3, class A4, class A5>
inline callable_5<Func, A1, A2, A3, A4, A5>
bind(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    return callable_5<Func, A1, A2, A3, A4, A5>
        (func, a1, a2, a3, a4, a5);
}

template<class Func, class A1, class A2, class A3, class A4, class A5, class A6>
inline callable_6<Func, A1, A2, A3, A4, A5, A6>
bind(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    return callable_6<Func, A1, A2, A3, A4, A5, A6>
        (func, a1, a2, a3, a4, a5, a6);
}

template<class Func, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline callable_7<Func, A1, A2, A3, A4, A5, A6, A7>
bind(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    return callable_7<Func, A1, A2, A3, A4, A5, A6, A7>
        (func, a1, a2, a3, a4, a5, a6, a7);
}

template<class Func, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline callable_8< Func,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8>
bind(Func func, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    return callable_8< Func,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8>
        (func, a1, a2, a3, a4, a5, a6, a7, a8);
}

// Member function wrappers.

template<class Func, class T>
class callable_mf_0
{
public:
    
    callable_mf_0(Func func, T p):
        func_(func), p_(p)
    {
    }
    
    void operator()()
    {
        (p_->*func_)();
    }
    
private:
    
    Func func_;
    T p_;
};

template<class Func, class T, class A1>
class callable_mf_1
{
public:
    
    callable_mf_1(Func func, T p, A1 a1):
        func_(func), p_(p), a1_(a1)
    {
    }
    
    void operator()()
    {
        (p_->*func_)(a1_);
    }
    
private:
    
    Func func_;
    T p_;
    A1 a1_;
};

template<class Func, class T, class A1, class A2>
class callable_mf_2
{
public:
    
    callable_mf_2(Func func, T p, A1 a1, A2 a2):
        func_(func), p_(p), a1_(a1), a2_(a2)
    {
    }
    
    void operator()()
    {
        (p_->*func_)(a1_, a2_);
    }
    
private:
    
    Func func_;
    T p_;
    A1 a1_;
    A2 a2_;
};

template<class Func, class T, class A1, class A2, class A3>
class callable_mf_3
{
public:
    
    callable_mf_3(Func func, T p, A1 a1, A2 a2, A3 a3):
        func_(func), p_(p), a1_(a1), a2_(a2), a3_(a3)
    {
    }
    
    void operator()()
    {
        (p_->*func_)(a1_, a2_, a3_);
    }
    
private:
    
    Func func_;
    T p_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
};

template<class Func, class T, class A1, class A2, class A3, class A4>
class callable_mf_4
{
public:
    
    callable_mf_4(Func func, T p, A1 a1, A2 a2, A3 a3, A4 a4):
        func_(func), p_(p), a1_(a1), a2_(a2), a3_(a3), a4_(a4)
    {
    }
    
    void operator()()
    {
        (p_->*func_)(a1_, a2_, a3_, a4_);
    }
    
private:
    
    Func func_;
    T p_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
};

template<class Func, class T, class A1, class A2, class A3, class A4, class A5>
class callable_mf_5
{
public:
    
    callable_mf_5(Func func, T p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5):
        func_(func), p_(p), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5)
    {
    }
    
    void operator()()
    {
        (p_->*func_)(a1_, a2_, a3_, a4_, a5_);
    }
    
private:
    
    Func func_;
    T p_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
};

template<class Func, class T, class A1, class A2, class A3, class A4, class A5, class A6>
class callable_mf_6
{
public:
    
    callable_mf_6(Func func, T p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6):
        func_(func), p_(p), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5), a6_(a6)
    {
    }
    
    void operator()()
    {
        (p_->*func_)(a1_, a2_, a3_, a4_, a5_, a6_);
    }
    
private:
    
    Func func_;
    T p_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
    A6 a6_;
};

template<class Func, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
class callable_mf_7
{
public:
    
    callable_mf_7(Func func, T p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7):
        func_(func), p_(p), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5), a6_(a6), a7_(a7)
    {
    }
    
    void operator()()
    {
        (p_->*func_)(a1_, a2_, a3_, a4_, a5_, a6_, a7_);
    }
    
private:
    
    Func func_;
    T p_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
    A6 a6_;
    A7 a7_;
};

template<class Func, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
class callable_mf_8
{
public:
    
    callable_mf_8(Func func, T p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8):
        func_(func), p_(p), a1_(a1), a2_(a2), a3_(a3), a4_(a4), a5_(a5), a6_(a6), a7_(a7), a8_(a8)
    {
    }
    
    void operator()()
    {
        (p_->*func_)(a1_, a2_, a3_, a4_, a5_, a6_, a7_, a8_);
    }
    
private:
    
    Func func_;
    T p_;
    A1 a1_;
    A2 a2_;
    A3 a3_;
    A4 a4_;
    A5 a5_;
    A6 a6_;
    A7 a7_;
    A8 a8_;
};

template<class T, class R>
inline callable_mf_0<R (T::*)(), T*>
bind(R (T::* func)(), T* p)
{
    return callable_mf_0<R (T::*)(), T*>
        (func, p);
}

template<class T, class R, class A1>
inline callable_mf_1<R (T::*)(A1), T*, A1>
bind(R (T::* func)(A1), T* p, A1 a1)
{
    return callable_mf_1<R (T::*)(A1), T*, A1>
        (func, p, a1);
}

template<class T, class R, class A1, class A2>
inline callable_mf_2<R (T::*)(A1, A2), T*, A1, A2>
bind(R (T::* func)(A1, A2), T* p, A1 a1, A2 a2)
{
    return callable_mf_2<R (T::*)(A1, A2), T*, A1, A2>
        (func, p, a1, a2);
}

template<class T, class R, class A1, class A2, class A3>
inline callable_mf_3<R (T::*)(A1, A2, A3), T*, A1, A2, A3>
bind(R (T::* func)(A1, A2, A3), T* p, A1 a1, A2 a2, A3 a3)
{
    return callable_mf_3<R (T::*)(A1, A2, A3), T*, A1, A2, A3>
        (func, p, a1, a2, a3);
}

template<class T, class R, class A1, class A2, class A3, class A4>
inline callable_mf_4<R (T::*)(A1, A2, A3, A4), T*, A1, A2, A3, A4>
bind(R (T::* func)(A1, A2, A3, A4), T* p, A1 a1, A2 a2, A3 a3, A4 a4)
{
    return callable_mf_4<R (T::*)(A1, A2, A3, A4), T*, A1, A2, A3, A4>
        (func, p, a1, a2, a3, a4);
}

template<class T, class R, class A1, class A2, class A3, class A4, class A5>
inline callable_mf_5<R (T::*)(A1, A2, A3, A4, A5), T*, A1, A2, A3, A4, A5>
bind(R (T::* func)(A1, A2, A3, A4, A5), T* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    return callable_mf_5<R (T::*)(A1, A2, A3, A4, A5), T*, A1, A2, A3, A4, A5>
        (func, p, a1, a2, a3, a4, a5);
}

template<class T, class R, class A1, class A2, class A3, class A4, class A5, class A6>
inline callable_mf_6<R (T::*)(A1, A2, A3, A4, A5, A6), T*, A1, A2, A3, A4, A5, A6>
bind(R (T::* func)(A1, A2, A3, A4, A5, A6), T* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    return callable_mf_6<R (T::*)(A1, A2, A3, A4, A5, A6), T*, A1, A2, A3, A4, A5, A6>
        (func, p, a1, a2, a3, a4, a5, a6);
}

template<class T, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline callable_mf_7<R (T::*)(A1, A2, A3, A4, A5, A6, A7), T*, A1, A2, A3, A4, A5, A6, A7>
bind(R (T::* func)(A1, A2, A3, A4, A5, A6, A7), T* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    return callable_mf_7<R (T::*)(A1, A2, A3, A4, A5, A6, A7), T*, A1, A2, A3, A4, A5, A6, A7>
        (func, p, a1, a2, a3, a4, a5, a6, a7);
}

template<class T, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline callable_mf_8<R (T::*)(A1, A2, A3, A4, A5, A6, A7, A8), T*, A1, A2, A3, A4, A5, A6, A7, A8>
bind(R (T::* func)(A1, A2, A3, A4, A5, A6, A7, A8), T* p, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    return callable_mf_8<R (T::*)(A1, A2, A3, A4, A5, A6, A7, A8), T*, A1, A2, A3, A4, A5, A6, A7, A8>
        (func, p, a1, a2, a3, a4, a5, a6, a7, a8);
}

} // namespace stx

#endif // STX_BIND_HPP
