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
    void operator=(const Singleton& obj) {} // ������Z�q�֎~
    Singleton(const Singleton& obj) {} // �R�s�[�R���X�g���N�^�֎~

protected:
    Singleton() {}
    virtual ~Singleton() {}

};