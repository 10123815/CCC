#include <string>

#include <unistd.h>
#include <pthread.h>

#include "resource2.h"

WRResource rsrc;

// void UseResource(Resource* rsrc, int id) {
// 	rsrc->Use(id);
// }

void printids(const char* s) {
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s %lu, %lu\n", s, (uint64_t)pid, (unsigned long)tid);
}

void* thr_fn(void* args) {
	// pthread_mutex_lock(&mutex);
	// printf("%d\n", data.a);
	// data.a++;
	// printf("%d\n", data.a);
	// pthread_mutex_unlock(&mutex);
	rsrc.Print();
	pthread_exit((void*)1);
}

int main(int argc, char const* argv[]) {

	// Resource* file_rsrc = new FileResource("a");
	// Resource* str_rsrc = new StringResource(data);
	// int cmd;
	// while (std::cin >> cmd) {
	// 	if (cmd % 2 == 0) {
	// 		std::thread thr(UseResource, file_rsrc, std::ref(cmd));
	// 		thr.detach();
	// 	} else {
	// 		std::thread thr(UseResource, str_rsrc, std::ref(cmd));
	// 		thr.detach();
	// 	}
	// }

	// pthread_mutex_init(&mutex, nullptr);

	pthread_t ntid1;
	int err = pthread_create(&ntid1, nullptr, thr_fn, (void*)"NULL");
	if (err != 0) {
		printf("fuck");
		exit(1);
	}

	pthread_t ntid2;
	err = pthread_create(&ntid2, nullptr, thr_fn, (void*)"NULL");
	if (err != 0) {
		printf("fuck");
		exit(1);
	}

	sleep(1);
	rsrc.Write(3, '9');
	rsrc.Print();

	// pthread_mutex_lock(&mutex);
	// printf("%d\n", data.a);
	// data.a++;
	// printf("%d\n", data.a);
	// pthread_mutex_unlock(&mutex);

	void* rval_ptr;
	pthread_join(ntid1, &rval_ptr);
	pthread_join(ntid2, &rval_ptr);

	// pthread_mutex_destroy(&mutex);
	exit(0);

}

