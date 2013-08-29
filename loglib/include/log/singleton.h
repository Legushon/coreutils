#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

#include <pthread.h> 

template <class T>
class cSingleton
{
	static T* self_;
	static int refcount_;
	static pthread_mutex_t instAccess;

protected:
	cSingleton() {
	}
	virtual ~cSingleton(){
		self_ = 0;
	}

public:
	static T* Instance();
	void FreeInst();
};

template <class T>
T* cSingleton<T>::self_ = 0;

template <class T>
int cSingleton<T>::refcount_ = 0;

template <class T>
pthread_mutex_t cSingleton<T>::instAccess = PTHREAD_MUTEX_INITIALIZER;

template <class T>
T* cSingleton<T>::Instance()
{
	pthread_mutex_lock( &instAccess );

	if ( !self_ )
		self_ = new T;

    refcount_++;
	pthread_mutex_unlock (&instAccess);
	return self_;
}

template <class T>
void cSingleton<T>::FreeInst()
{
	pthread_mutex_lock( &instAccess );

	if ( --refcount_ == 0 )
    {
		self_ = 0;
		delete this;
	}
	pthread_mutex_unlock (&instAccess);
}


//-----------------------
// Класс для быстрого доступа к сущности синглтона без создания промежуточного объекта (но можно)
template< class T > 
class SingletonWrapper
{
    public:
      typedef T singleton_type;

    protected:
      singleton_type *inst_;

    private:
      SingletonWrapper( const SingletonWrapper& ) {};


    public:
      SingletonWrapper() : inst_( singleton_type::Instance() ) {
      };

      ~SingletonWrapper() {
          inst_->FreeInst();
      };

      singleton_type* operator -> () {
          return inst_;
      };
};
#endif
