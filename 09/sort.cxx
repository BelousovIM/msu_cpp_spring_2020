#include "sort.h"
#include <iostream>

class sorter
{
	std::mutex mutex_, qmutex_, mmutex_;
	std::condition_variable cv_;

	using type = uint64_t;
	size_t type_size = sizeof(uint64_t);
	size_t maxmem_ = 8000000;
	size_t tcounter_;
	size_t fcounter_;
	type* memory_;
	std::ifstream input_;
	std::ofstream output_;
	std::queue<std::string> fqueue_;
    
public:	

	sorter(const char* name1, const char* name2)
		: memory_(new type[maxmem_])
		, tcounter_(0)
		, fcounter_(0)
	{
		input_.open(name1, std::ios::binary);
		output_.open(name2, std::ios::binary);
		
		auto t1 = std::thread([this]
		{
			this->sortFile(this->memory_);
			while (this->merge(this->memory_)) {}
		});
		
		auto t2 = std::thread([this]
		{
			while (this->merge(this->memory_ + this->maxmem_/2)) {}

		});
		t1.join();
		t2.join();
	}
	
	std::string CreateName()
	{
		return std::to_string(++fcounter_) + ".txt";
	}
	
	void sortFile(type* mem)
	{
		++tcounter_;
		for(;;)
		{
			/*{
				std::unique_lock<std::mutex> lock(mutex_);
				std::cout << "sort\t" << std::this_thread::get_id() << std::endl;
			}*/
			size_t size;
			{
				std::unique_lock<std::mutex> lock(mutex_);
				input_.read(reinterpret_cast<char*>(mem), maxmem_/2);
				size = input_.gcount() / type_size;
			}

			if (size == 0)
				break;

			std::sort(mem, mem + size);

			std::string name = CreateName();
			std::ofstream out(name, std::ios::binary);
			out.write(reinterpret_cast<char*>(mem), type_size * size);
			out.close();

			{
				std::unique_lock<std::mutex> lock(qmutex_);
				fqueue_.push(name);
			}
			if (fqueue_.size() > 1) cv_.notify_one();
		}
		/*{
			std::unique_lock<std::mutex> lock(mutex_);
			std::cout << "sort\tend" << std::endl;
		}*/
		--tcounter_;
	}
	
	bool merge(type* mem)
	{
		/*{
			std::unique_lock<std::mutex> lock(mutex_);
			std::cout << "merge\t" << std::this_thread::get_id() << std::endl;
		}*/
		std::unique_lock<std::mutex> mlock(mmutex_);
		while (fqueue_.size() < 2)
		{
			if (tcounter_ > 0)
				cv_.wait(mlock);
			else
				return false;
		}
		++tcounter_;
		
		std::unique_lock<std::mutex> lock(qmutex_);
		std::ifstream firstF(fqueue_.front(), std::ios::binary);
		fqueue_.pop();
		std::ifstream secondF(fqueue_.front(), std::ios::binary);
		fqueue_.pop();

		lock.unlock();

		std::string name = CreateName();
		std::ofstream mergedFile(name, std::ios::binary);
		
		
		
		type first, second;
		
		if (!firstF.eof() && !secondF.eof())
		{
			firstF.read(reinterpret_cast<char*>(&first), type_size);
			secondF.read(reinterpret_cast<char*>(&second), type_size);
			
			while (true)
			{
				if (first <= second)
				{
					mergedFile.write(reinterpret_cast<char*>(&first), type_size);
					if (!firstF.eof())
						firstF.read(reinterpret_cast<char*>(&first), type_size);
					else
					{
						mergedFile.write(reinterpret_cast<char*>(&second), type_size);
						break;
					}
				}
				else
				{
					mergedFile.write(reinterpret_cast<char*>(&second), type_size);
					if (!secondF.eof())
						secondF.read(reinterpret_cast<char*>(&second), type_size);
					else
					{
						mergedFile.write(reinterpret_cast<char*>(&second), type_size);
						break;
					}
				}
			}
		}
		
		type val;
		while (!firstF.eof())
		{
			firstF.read(reinterpret_cast<char*>(mem), maxmem_/2);
			mergedFile.write(reinterpret_cast<char*>(mem), firstF.gcount());
		}
		while (!secondF.eof())
		{
			secondF.read(reinterpret_cast<char*>(mem), maxmem_/2);
			mergedFile.write(reinterpret_cast<char*>(mem), secondF.gcount());
		}

		firstF.close();
		secondF.close();
		mergedFile.close();

		{
			std::unique_lock<std::mutex> lock1(qmutex_);
			fqueue_.push(name);
		}
		--tcounter_;
		return true;
	}

	~sorter()
	{
		std::ifstream in(fqueue_.front(), std::ios::binary);

		while (!in.read(reinterpret_cast<char*>(memory_), maxmem_).eof())
			output_.write(reinterpret_cast<char*>(memory_), in.gcount());

		in.close();


		input_.close();
		output_.close();

		delete[] memory_;
	}
};

void sortFile()
{
	sorter A("input.txt", "output.txt");
}
