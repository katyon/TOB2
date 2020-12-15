#pragma once
template<typename T>
class Singleton
{
public:
    static inline T& getInstance()
    {
        static T instance;
        return instance;
    }

private:
    void operator=(const Singleton& obj) {} // 代入演算子禁止
    Singleton(const Singleton& obj) {} // コピーコンストラクタ禁止

protected:
    Singleton() {}
    virtual ~Singleton() {}

};