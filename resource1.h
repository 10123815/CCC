#ifndef _MULTI_THREAD_RESOURCE_H_
#define _MULTI_THREAD_RESOURCE_H_

#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>

class Resource
{
public:
	void Use (int user_id) 
	{
		std::unique_lock<std::mutex> lck(mtx_);
		DoUse(user_id);
	}
protected:
	virtual void DoUse (int user_id) = 0;
private:
	std::mutex mtx_;
};

class StringResource : public Resource
{
public:
	StringResource (const std::string& str) : str_(str) {}
protected:
	void DoUse (int user_id) override
	{
		for (auto& ch : str_)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::cout<<"    "<<user_id<<" use "<<ch<<std::endl;
		}
	}
private:
	std::string str_;
};

class FileResource : public Resource
{
public:
	FileResource (std::string file_name) : file_name_(file_name) {}
protected:
	void DoUse (int user_id)
	{
		std::ifstream file;
		file.open(file_name_, std::ios::in);
		std::string data;
		file>>data;
		file.close();
		for (auto& ch : data)
		{
			std::cout<<"   "<<user_id<<" use "<<ch<<std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
private:
	std::string file_name_;
};


#endif