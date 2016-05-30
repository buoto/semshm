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
    static const int CAPACITY = 100;

    typedef char element;

    SharedQueue(const key_t key, bool is_server=false);
    ~SharedQueue();

    /* synchronized priority queue interface */
    void push(const element el);
    void push_medium(const element el);
    void push_priority(const element el);
    element pop();

    void print_contents();

  private:
    /* semaphore indices */
    enum Semaphore {
      mutex,
      size,
      space
    };

    enum Priority {
      priority,
      medium,
      standard
    };

    static const int SEM_COUNT = 3;
    static const int IND_COUNT = 4;

    int shmid, indid;
    char *buf;

    // poiners to buffer indices, not actual elements or adresses
    char *head, *end, *end_priority, *end_medium;
    bool is_server;

    int semsid;

    /* semaphore operations */
    void up(Semaphore sem);
    void down(Semaphore sem);

    /* internal non-synchronized queue methods*/
    void push_(const element el, const Priority p);
    element pop_();

    /* internal utilities */
    void shift_tail_medium();
    void shift_tail_priority();
    void shift_tail(char **desired_end);
    static inline char cyclic_inc(const char val) {
      return (val == CAPACITY - 1) ? 0 : val + 1;
    }
    static inline char cyclic_dec(const char val) {
      return (val == 0) ? CAPACITY - 1 : val - 1;
    }

};

#endif
