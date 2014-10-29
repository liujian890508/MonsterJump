#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template<typename T> 
class Singleton
{
public:
	Singleton()
	{

	}
	~Singleton()
	{

	}

	static T* getInstance()
	{
		return &m_sInstance;
	}

protected:

private:
	static T m_sInstance;
};

template<typename T> T Singleton<T>::m_sInstance;

#endif