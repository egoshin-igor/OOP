#pragma once
#include <memory>
#include <algorithm>

template <typename T>
class CMyArray
{
public:

	template < typename T>
	class MyIterator
	{
		friend class CMyArray;
	public:
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		bool operator ==(const MyIterator& other) const
		{
			return m_p = other.m_p;
		}

		bool operator !=(const MyIterator& other) const
		{
			return m_p != other.m_p;
		}

		MyIterator const operator +(int i)
		{
			return MyIterator(m_p + i);
		}

		MyIterator const operator -(int i)
		{
			return MyIterator(m_p - i);
		}

		reference operator*() const
		{
			return *m_p;
		}

		reference operator[](size_t i) const
		{
			return m_p[i];
		}

		MyIterator& operator++()
		{
			++m_p;
			return *this;
		}

		MyIterator& operator--()
		{
			--m_p;
			return *this;
		}

		MyIterator operator++(int)
		{
			auto tempIt(*this);
			++*this;
			return tempIt;
		}

		MyIterator operator--(int)
		{
			auto tempIt(*this);
			--*this;
			return tempIt;
		}
	private:
		pointer m_p = nullptr;
		MyIterator(pointer p)
		{
			m_p = p;
		}
	};
	typedef MyIterator<T> it;
	typedef std::reverse_iterator<MyIterator<T>> reverseIt;

	it begin();
	it end();
	reverseIt rbegin();
	reverseIt rend();

	CMyArray(std::initializer_list<T> arr);
	CMyArray(const CMyArray& arr);
	CMyArray(CMyArray&& arr);
	CMyArray() = default;
	~CMyArray();
	const T& operator[](size_t i) const;
	T& operator[](size_t i);
	size_t Size() const;
	CMyArray operator=(const CMyArray& other);
	CMyArray operator=(CMyArray&& other);
	void PushBack(T const& elem);
	bool operator ==(const CMyArray& other) const;
	bool operator !=(const CMyArray& other) const;
	void Resize(size_t size);
	void Clear();
private:
	void Copy(T* from, T* to, size_t size);
	void Copy(std::initializer_list<T> from, T* to, size_t size);
	size_t m_size = 0;
	T* m_data = nullptr;
};

template <typename T>
bool CMyArray<T>::operator ==(const CMyArray& other) const
{
	if (other.m_size != m_size)
	{
		return false;
	}

	for (size_t i = 0; i < m_size; ++i)
	{
		if (other.m_data[i] != m_data[i])
		{
			return false;
		}
	}
	return true;
}

template <typename T>
CMyArray<T>::CMyArray(std::initializer_list<T> arr)
	:m_size(arr.size()),
	m_data(new T[m_size])
{
	Copy(arr, m_data, m_size);
}

template <typename T>
CMyArray<T>::CMyArray(CMyArray&& arr)
	:CMyArray(arr)
{
	arr.Clear();
}

template <typename T>
CMyArray<T>::~CMyArray()
{
	delete[] m_data;
}

template <typename T>
void CMyArray<T>::Copy(std::initializer_list<T> from, T* to, size_t size)
{
	size_t i = 0;
	for (auto elem : from)
	{
		to[i] = elem;
		++i;
	}
}


template <typename T>
void CMyArray<T>::Copy(T* from, T* to, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		to[i] = from[i];
	}
}

template <typename T>
bool CMyArray<T>::operator !=(const CMyArray& other) const
{
	return !(*this == other);
}

template < typename T>
void CMyArray<T>::Resize(size_t size)
{
	T* newData = new T[size];
	if (size > m_size)
	{
		Copy(m_data, newData, m_size);
		for (size_t i = m_size; i < size; ++i)
		{
			newData[i] = T();
		}
	}
	else
	{
		Copy(m_data, newData, size);
	}
	delete[] m_data;
	m_data = newData;
	m_size = size;
}

template < typename T>
void CMyArray<T>::Clear()
{
	delete[] m_data;
	m_data = nullptr;
	m_size = 0;
}

template <typename T>
CMyArray<T>::CMyArray(const CMyArray& arr)
	:m_size(arr.Size()),
	m_data(new T[m_size])
{
	for (size_t i = 0; i < m_size; ++i)
	{
		m_data[i] = arr.m_data[i];
	}
}

template <typename T>
CMyArray<T> CMyArray<T>::operator=(const CMyArray& other)
{
	if (std::addressof(other) != this)
	{
		CMyArray tempCopy(other);
		std::swap(m_data, tempCopy.m_data);
		std::swap(m_size, tempCopy.m_size);
	}
	return *this;
}

template <typename T>
CMyArray<T> CMyArray<T>::operator=(CMyArray&& other)
{
	*this = other;
	other.Clear();
	return *this;
}

template <typename T>
const T& CMyArray<T>::operator[](size_t i) const
{
	if (i >= m_size || i < 0)
	{
		throw std::invalid_argument("index is out of range");
	}
	return m_data[i];
}

template <typename T>
T& CMyArray<T>::operator[](size_t i)
{
	if (i >= m_size || i < 0)
	{
		throw std::invalid_argument("index is out of range");
	}
	return m_data[i];
}


template < typename T>
size_t CMyArray<T>::Size() const
{
	return m_size;
}

template < typename T>
void CMyArray<T>::PushBack(T const& elem)
{
	T* newData = new T[m_size + 1];
	Copy(m_data, newData, m_size);
	newData[m_size] = elem;
	delete[] m_data;
	m_data = newData;
	m_size = m_size + 1;
}

template < typename T>
typename CMyArray<T>::it CMyArray<T>::begin()
{
	return it(m_data);
}

template < typename T>
typename CMyArray<T>::it CMyArray<T>::end()
{
	return it(m_data + m_size);
}

template <typename T>
typename CMyArray<T>::reverseIt CMyArray<T>::rbegin()
{
	return reverseIt(m_data + m_size);
}

template < typename T>
typename CMyArray<T>::reverseIt CMyArray<T>::rend()
{
	return reverseIt(m_data);
}

