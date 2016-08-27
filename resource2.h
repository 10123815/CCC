#include <pthread.h>
#include <string>
#include <unistd.h>

template <typename M>
class Locker {
  public:
	Locker(M& mtx) : mutex_(mtx) {
		Lock(mutex_);
	}
	~Locker() {
		Unlock(mutex_);
	}
	Locker(const Locker&) = delete;
	void operator=(const Locker&) = delete;
  protected:
	// Template meta programming.
	// A group of overloaded Lock/Unlock function to handler different type of mutex.
	void Lock(pthread_mutex_t& mtx) {
		pthread_mutex_lock(&mtx);
	}
	void Unlock(pthread_mutex_t& mtx) {
		pthread_mutex_unlock(&mtx);
	}
  private:
	M& mutex_;
};

template <>
class Locker <pthread_rwlock_t> {
  public:
	Locker(pthread_rwlock_t& mtx) : mutex_(mtx) {

	}
	~Locker() {
		pthread_rwlock_unlock(&mutex_);
	}
	Locker(const Locker&) = delete;
	void operator=(const Locker&) = delete;
	int Wlock() {
		return pthread_rwlock_wrlock(&mutex_);
	}
	int Rlock() {
		return pthread_rwlock_rdlock(&mutex_);
	}
  private:
	pthread_rwlock_t& mutex_;
};

class Resource {
  public:
	Resource() {
		pthread_mutex_init(&mutex_, nullptr);
	}
	Resource(const Resource&) = delete;
	virtual ~Resource() {
		pthread_mutex_destroy(&mutex_);
	}

	void Print() {
		Locker<pthread_mutex_t> lck(mutex_);
		for (auto ch : data_) {
			printf("%c\n", ch);
			sleep(1);
		}
	}

  private:
	std::string data_ = "1234";
	pthread_mutex_t mutex_;
};

class WRResource {
  public:
	WRResource() {
		pthread_rwlock_init(&mutex_, nullptr);
	}
	virtual ~WRResource() {
		pthread_rwlock_destroy(&mutex_);
	}

	void Write(std::size_t index, char ch) {
		Locker<pthread_rwlock_t> lck(mutex_);
		if (0 == lck.Wlock())
			if (index < data_.size()) {
				data_[index] = ch;
			}
	}

	void Print() {
		Locker<pthread_rwlock_t> lck(mutex_);
		if (0 == lck.Rlock())
			for (auto ele : data_) {
				printf("%c\n", ele);
				sleep(1);
			}
	}
  private:
	std::string data_ = "1234";
	pthread_rwlock_t mutex_;
};