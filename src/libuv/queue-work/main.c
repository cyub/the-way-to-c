#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <uv.h>

#define FIB_UNTIL 15

uv_loop_t *loop;

long fib_(long t) {
  if (t == 0 || t == 1)
    return 1;
  else
    return fib_(t - 1) + fib_(t - 2);
}

void fib(uv_work_t *req) {
  int n = *(int *)req->data;
  if (random() % 2)
    sleep(1);
  else
    sleep(3);
  long fib = fib_(n);
  fprintf(stderr, "%dth fibonaccis is %lu\n", n, fib);
}

void fib_done(uv_work_t *req, int status) {
  fprintf(stderr, "Done calculating %dth fibonacci\n", *(int *)req->data);
  // free(req); // 非法操作，因为req是main函数的栈上分配的
}

int main() {
  loop = uv_default_loop();
  int data[FIB_UNTIL];
  uv_work_t req[FIB_UNTIL];
  int i;
  for (i = 0; i < FIB_UNTIL; i++) {
    data[i] = i;
    req[i].data = (void *)&data[i];
    uv_queue_work(loop, &req[i], fib, fib_done);
  }

  return uv_run(loop, UV_RUN_DEFAULT);
}