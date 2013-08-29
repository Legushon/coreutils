#ifndef VALUE_INITIALIZED_HPP
#define VALUE_INITIALIZED_HPP

template < class T >
class value_initialized
{
public:
	value_initialized(): value_()
	{
	}
	value_initialized(const T & src): value_(src){}
	template < typename T2 >
	T & operator +=( const T2 & src)
	{
		value_ += src;
		return value_;
	}
	T & operator ++()
	{
		return ++value_;
	}
	T operator ++(int inc)
	{	
		T temp = value_;
		value_++;
		return temp;
	}
	T & operator --()
	{
		return --value_;
	}
	T operator --(int inc)
	{	
		T temp = value_;
		value_--;
		return temp;
	}
	T * operator &()
	{
		return &value_;
	}
	operator T &() 
	{
		return value_;
	}
	
	operator const T &() const
	{
		return value_;
	}
	
	T & get()
	{
		return value_;
	}
	
	const T & get() const
	{
		return value_;
	}
private:
	T value_;
};

template< class T, class VI>
T operator - (T & left, const value_initialized<VI> & right)
{
	return left - right.get();
}

#endif
