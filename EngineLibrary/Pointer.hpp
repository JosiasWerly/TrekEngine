#pragma once
#ifndef _Pointer
#define _Pointer
class DataCounter {
    unsigned int refsCount = 1;
public:
    inline unsigned int refs() {
        return refsCount;
    }
    inline void decrement() {
        if (refsCount > 0)
            refsCount--;
    }
    inline void increment() {
        refsCount++;
    }
};

struct Ptr {
    virtual ~Ptr() {}
};
template<class T>struct TPtr : public Ptr {
    T *tPtr = nullptr;

    TPtr(T *tPtr = nullptr) : tPtr(tPtr) {}
    virtual ~TPtr() { delete tPtr; }
};

struct DataHolder {
    DataCounter dtCounter;
    Ptr *ptr = nullptr;
    ~DataHolder() { delete ptr; }
};

template<class T> class TPointer;
class Pointer {
protected:
    DataHolder *dtHolder = new DataHolder;

    inline void unPoint() {
        dtHolder->dtCounter.decrement();
        if (!dtHolder->dtCounter.refs())
            delete dtHolder;
    }
    inline void rePoint(const Pointer &other) {
        unPoint();
        dtHolder = other.dtHolder;
        dtHolder->dtCounter.increment();
    }
    
public:
    virtual ~Pointer() {
        unPoint();
    }
    Pointer(){
    }
    Pointer(const Pointer &other) {
        *this = other;
    }
    Pointer &operator=(const Pointer &other) {
        rePoint(other);
        return *this;
    }

    inline bool operator==(const Pointer &other) const { return dtHolder == other.dtHolder; }
    inline unsigned int references() { return dtHolder->dtCounter.refs(); }
    inline bool isValid() { return dtHolder->ptr; }
    inline void free() { delete dtHolder->ptr; dtHolder->ptr = nullptr; }
};

template<class T>class TPointer : public Pointer {
protected:
    template<class T> friend class TPointer;

    inline void rePoint(const TPointer &other) {
        Pointer::rePoint(other);
        acessor = other.acessor;
    }
    T *acessor = nullptr;
public:
    using Pointer::operator=;
    using Pointer::Pointer;

    TPointer() {
    }
    TPointer(T *value) {
        *this = value;
    }
    TPointer(const Pointer &other) {
        *this = other;
    }
    TPointer(const TPointer &other) {
        *this = other;
    }

    TPointer &operator=(const TPointer &other) {
        rePoint(other);
        return *this;
    }
    T *operator=(T *value) {
        delete dtHolder->ptr;
        dtHolder->ptr = new TPtr<T>(value);
        acessor = value;
        return value;
    }
    T *getValue() { return acessor; }
    T *operator()() { return acessor; }

    //inline bool operator==(const T &other) const { return acessor == other; }
    
    template<class t> inline bool isType() {
        return dynamic_cast<t*>(acessor);
    }
    template<class t> TPointer<t> make() {
        TPointer<t> out;
        out.dtHolder = dtHolder;
        out.acessor = (T *)acessor;
        out.dtHolder->dtCounter.increment();
        return out;
    }
};
#endif // !_Pointer