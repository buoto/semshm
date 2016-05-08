#ifndef SHAREDQUEUE_H
#define SHAREDQUEUE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <cstdio>
#include <exception>


class shmerror : public std::exception {
  virtual const char* what() const throw()
  {
    return "Shared memory exception";
  }
};


class semerror : public std::exception {
  virtual const char* what() const throw()
  {
    return "Semaphore exception";
  }
};

union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
															(Linux-specific) */
};


class SharedQueue {
  public:
    /* semaphore indices */
    enum Semaphore {
      mutex,
      size,
      space
    };

    static const int CAPACITY = 10;
    static const int SEM_COUNT = 3;
    static const int IND_COUNT = 3;


    typedef char element;

    SharedQueue(const key_t key, bool is_server);
    ~SharedQueue();

    /* synchronized priority queue interface */
    void push(const element el);
    void push_priority(const element el);
    element pop();

    void print_contents();

  private:
    int shmid, indid;
    char *buf;

    // poiners to buffer indices, not actual elements or adresses
    char *head, *end, *end_priority;
    bool is_server;

    int semsid;

    /* semaphore operations */
    void up(Semaphore sem);
    void down(Semaphore sem);

    /* internal non-synchronized queue methods*/
    void push_(const element el, const bool priority);
    element pop_();

    /* internal utilities */
    void shift_tail();
    static inline char cyclic_inc(const char val) {
      return (val == CAPACITY - 1) ? 0 : val + 1;
    }
    static inline char cyclic_dec(const char val) {
      return (val == 0) ? CAPACITY - 1 : val - 1;
    }

};

#endif
