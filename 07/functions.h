#pragma once
#include <iostream>
#include <memory>

template <class T>
class Allocator
{
public:
	using value_type = T;
	using pointer = T*;
	using size_type = size_t;

	pointer allocate(size_type count) 
	{
		pointer new_data = static_cast<pointer>(malloc(sizeof(value_type) * count));
		if (new_data == nullptr) 
		{
			throw std::bad_alloc();
		}
		return new_data;
	}

	void deallocate(pointer ptr, size_type count) noexcept 
	{
		free(ptr);
	}

	template<typename ... Args>
	void construct(pointer ptr, Args&&... args) 
	{
		new(ptr) T(std::forward<Args>(args)...);
	}

	void destroy(pointer ptr) noexcept 
	{
		ptr->~T();
	}

	size_t max_size() const noexcept
	{
		return std::numeric_limits<size_type>::max() / sizeof(value_type);
	}
};

template <class T>
class Iterator: public std::iterator<std::random_access_iterator_tag, T>
{
public:
	using size_type = size_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using iterator = Iterator<value_type>;

	Iterator(pointer ptr) : 
		ptr_{ptr}
	{ 
	}

	bool operator==(const iterator& other) 
	{
		return ptr_ == other.ptr_;
	}

	bool operator!=(const iterator& other) 
	{
		return !(*this == other);
	}

	bool operator<(const iterator& other) 
	{
		return ptr_ < other.ptr_;
	}

	bool operator<=(const iterator& other) 
	{
		return ptr_ <= other.ptr_;
	}

	bool operator>(const iterator& other) 
	{
		return !(ptr_ <= other);
	}

	bool operator>=(const iterator& other) 
	{
		return !(ptr_ < other);
	}

	iterator& operator++() 
	{
		++ptr_;
		return *this;
	}

	iterator& operator--()
	{
		--ptr_;
		return *this;
	}

	iterator operator+(int shift) const 
	{
		return {ptr_ + shift};
	}

	iterator operator-(int shift) const 
	{
		return {ptr_ - shift};
	}

	iterator& operator+=(int shift)
	{
		ptr_ += shift;
		return *this;
	}

	iterator& operator-=(int shift) 
	{
		ptr_ -= shift;
		return *this;
	}

	reference operator*() 
	{
		return *ptr_;
	}

	reference operator[](size_t pos) const
	{
		return ptr_[pos];
	}
private:
	pointer ptr_;
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
	using size_type = size_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;
	using iterator = Iterator<T>;
	using reverse_iterator = std::reverse_iterator<iterator>;



	Vector()
		: alloc_{}
		, ptr_{alloc_.allocate(4)}
		, capacity_{4}
		, size_{0}
	{
	}

	Vector(const Vector<T>& other)
		: alloc_{}
		, ptr_{alloc_.allocate(other.size_)}
		, size_{0}
		, capacity_{other.size_}
	{
		for (; size_ < other.size_; ++size_) 
		{
			alloc_.construct(ptr_ + size_, other.ptr_[size_]);
		}
	}

	Vector(Vector<T>&& other)
		: alloc_{}
		, ptr_{other.ptr_}
		, size_{other.size_}
		, capacity_{other.capacity_}
	{
		other.ptr_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	Vector(std::initializer_list<T> init)
		: alloc_{}
		, ptr_{alloc_.allocate(init.size())}
		, size_{0}
		, capacity_{init.size()}
	{
		for (const T& value : init) 
		{
	    		alloc_.construct(ptr_ + size_++, std::move(value));
		}
	}

	~Vector() 
	{
		for (; size_ > 0;) 
		{
			alloc_.destroy(ptr_ + --size_);
		}
		alloc_.deallocate(ptr_, capacity_);
	}

	T& operator[](size_type i) 
	{
		return ptr_[i];
	}

	const T& operator[](size_type i) const
	{
		return ptr_[i];
	}

	void push_back(const T& value) 
	{
		if (size_ >= capacity_) 
		{
			reserve(size_ * 2);
		}
		alloc_.construct(ptr_ + size_++, value);
	}

	void push_back(T&& value) 
	{
		if (size_ >= capacity_) 
		{
			reserve(size_ * 2);
		}
		alloc_.construct(ptr_ + size_++, std::move(value));
	}

	void pop_back() 
	{
		if (size_ == 0)
			throw(std::runtime_error("Empty vector"));
		alloc_.destroy(ptr_ + --size_);
	}

	bool empty() const noexcept 
	{
		return size_ == 0;
	}

	size_type size() const noexcept 
	{
		return size_;
	}

	void clear() noexcept 
	{
		for (; size_ > 0;)
		{
			alloc_.destroy(ptr_ + --size_);
		}
	}

	iterator begin() noexcept
	{
		return iterator(ptr_);
	}

	iterator end() noexcept
	{
		return iterator(ptr_ + size_);
	}

	reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend() noexcept
	{
		return reverse_iterator(begin());
	}


	void resize(size_type new_size)
	{
		if (new_size < size_)
		{
			for (size_t i = new_size; i < size_; ++i)
				alloc_.destroy(ptr_ + i);
		}
		else if (new_size > size_)
		{
			
			reserve(new_size);
			for (size_t i = size_; i < new_size; ++i)
				alloc_.construct(ptr_ + i);
		}
		size_ = new_size;
	}

	void reserve(size_type new_capacity)
	{
		if (new_capacity > capacity_)
		{
			increase_size(new_capacity);
			capacity_ = new_capacity;
		}
	}

	void increase_size(size_type new_size)
	{
		pointer tmp = alloc_.allocate(new_size);

		for (size_t i = 0; i < size_; ++i)
			alloc_.construct(tmp + i, ptr_[i]);

		for (size_t i = 0; i < size_; ++i)
			alloc_.destroy(ptr_ + i);

		alloc_.deallocate(ptr_, capacity_);
		ptr_ = tmp;
	}
private:
	Alloc alloc_;
	pointer ptr_;
	size_type capacity_;
	size_type size_;
};
