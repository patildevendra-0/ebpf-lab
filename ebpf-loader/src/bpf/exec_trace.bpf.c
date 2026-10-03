#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

SEC("tracepoint/sched/sched_process_fork")
int handle_fork(struct trace_event_raw_sched_process_fork *ctx)
{
    __u32 CHILD_PID = ctx->child_pid;

    bpf_printk("CHILD PID : %u\n",CHILD_PID);

    return 0;
}

char LICENSE[] SEC("license") = "GPL";