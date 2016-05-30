#include "shared_queue.h"

SharedQueue::SharedQueue(key_t key, bool is_server) {
  union semun arg;
  this->is_server = is_server;

  // init shared memory
  if( (shmid = shmget(key, CAPACITY, (is_server ? IPC_CREAT : 0) | 0666)) < 0) {
    throw shmerror();
  }
  if( (buf = (char*)shmat(shmid, NULL, 0)) == (char*) -1) {
    throw shmerror();
  }

  // init indexes
  if( ( indid = shmget(key+1, CAPACITY, (is_server ? IPC_CREAT : 0) | 0666)) < 0) {
    throw shmerror();
  }
  if( (head = (char*)shmat(indid, NULL, 0)) == (char*) -1) {
    throw shmerror();
  }
  end = head + 1;
  end_priority = head + 2;



  // init semaphores
  if( (semsid = semget(key+2, SEM_COUNT, (is_server ? IPC_CREAT | 0666 : 0))) < 0) {
    throw semerror();
  }

  // init values
  if(is_server) {

    *head = 0;
    *end = 0;
    *end_priority = 0;

    arg.val = 1;
    if( semctl(semsid, mutex, SETVAL, arg) < 0) {
      throw semerror();
    }
    arg.val = CAPACITY;
    if( semctl(semsid, space, SETVAL, arg) < 0) {
      throw semerror();
    }
  }

}


SharedQueue::~SharedQueue() {
  printf("Queue died\n");
  if(shmdt(buf)) {
    throw shmerror();
  }
  if(shmdt(head)) {
    throw shmerror();
  }
  if(is_server) {
    if( shmctl(shmid, IPC_RMID, NULL) < 0) {
      throw shmerror();
    }
    if( shmctl(indid, IPC_RMID, NULL) < 0) {
      throw shmerror();
    }

    if( semctl(semsid, 0, IPC_RMID, NULL) < 0) {
      throw semerror();
    }
  }
}

void SharedQueue::push(element el) {
  down(space);
  down(mutex);
  push_(el, standard);
  up(mutex);
  up(size);
}

void SharedQueue::push_medium(element el) {
  down(space);
  down(mutex);
  push_(el, medium);
  up(mutex);
  up(size);
}

void SharedQueue::push_priority(element el) {
  down(space);
  down(mutex);
  push_(el, priority);
  up(mutex);
  up(size);
}

SharedQueue::element SharedQueue::pop() {
  down(size);
  down(mutex);
  element result = pop_();
  up(mutex);
  up(space);
  return result;
}

void SharedQueue::push_(const element el, const Priority p) {
  char **pos_index_ptr = &end;
  if(p == priority) {
    shift_tail();
    pos_index_ptr = &end_priority;
  }

  buf[(int)**pos_index_ptr] = el;

  **pos_index_ptr = cyclic_inc(**pos_index_ptr);
}

void SharedQueue::shift_tail() {
  const int priority = cyclic_dec(*end_priority);
  int cur = cyclic_dec(*end);

  while(cur != priority) {
    int next = cyclic_inc(cur);
    buf[next] = buf[cur];
    cur = cyclic_dec(cur);
  }

  *end = cyclic_inc(*end);

}

SharedQueue::element SharedQueue::pop_() {
  element result = buf[(int)*head];
  if(*head == *end_priority) {
    *end_priority = cyclic_inc(*end_priority);
  }
  *head = cyclic_inc(*head);
  return result;
}


void SharedQueue::up(Semaphore sem) {
  sembuf buf;
  buf.sem_num = sem;
  buf.sem_op = 1;
  buf.sem_flg = 0;
  if(semop(semsid, &buf, 1))
    throw semerror();
}

void SharedQueue::down(Semaphore sem) {
  sembuf buf;
  buf.sem_num = sem;
  buf.sem_op = -1;
  buf.sem_flg = 0;
  if(semop(semsid, &buf, 1))
    throw semerror();
}

void SharedQueue::print_contents() {
  printf("%d %d %d\n", *head, *end, *end_priority);
  for(int i = 0; i < CAPACITY; i++) {
    if(i == *head) {
      printf("<%c> ", buf[i]);
    } else if (i == *end) {
      printf("[%c] ", buf[i]);
    } else if (i == *end_priority) {
      printf("{%c} ", buf[i]);
    } else {
     printf("%c ", buf[i]);
    }
  }
  printf("\n");

}


