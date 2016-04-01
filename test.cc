#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <mutex>

std::mutex mtx;

std::string data = "111111111111111";

class Resource
{
public:
	void Use (int user_id) 
	{
		std::unique_lock<std::mutex> lck(mtx_);
		DoUse(user_id);
	}
protected:
	virtual void DoUse(int user_id) = 0;
private:
	std::mutex mtx_;
};

class StringResource : public Resource
{
public:
	StringResource (const std::string& str) : str_(str) {}
protected:
	void DoUse(int user_id) override
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

void UseResource(Resource* rsrc, int id)
{
	rsrc->Use(id);
}

int main(int argc, char const *argv[])
{
	
	Resource* rsrc = new StringResource(data);
	int cmd;
	while (std::cin>>cmd)
	{
		std::thread thr1(UseResource, rsrc, std::ref(cmd));
		thr1.detach();
	}

}