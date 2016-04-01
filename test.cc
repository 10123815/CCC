#include <string>

#include "multi_thread_resource.h"

std::string data = "111111111111111";

void UseResource(Resource* rsrc, int id)
{
	rsrc->Use(id);
}

int main(int argc, char const *argv[])
{
	
	Resource* file_rsrc = new FileResource("a");
	Resource* str_rsrc = new StringResource(data);
	int cmd;
	while (std::cin>>cmd)
	{
		if (cmd % 2 == 0)
		{
			std::thread thr(UseResource, file_rsrc, std::ref(cmd));
			thr.detach();
		}
		else
		{
			std::thread thr(UseResource, str_rsrc, std::ref(cmd));
			thr.detach();
		}
	}

}