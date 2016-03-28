#include <thread>
#include <iostream>
#include <mutex>

int main(int argc, char const *argv[])
{
	auto func_obj = [](int num, int& res)
	{
		res += num;
		std::cout<<num<<"  "<<res<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	};

	int res = 0;
	int cmd = 0;
	while (std::cin>>cmd)
	{
		std::thread t(func_obj, cmd, std::ref(res));
		t.detach();
	}

}