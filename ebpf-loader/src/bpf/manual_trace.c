#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

struct trace_event_raw_sched_process_fork {
    unsigned short common_type;          /* 0  */
    unsigned char  common_flags;         /* 2  */
    unsigned char  common_preempt_count; /* 3  */
    int            common_pid;           /* 4  */

    unsigned int   parent_comm_loc;      /* 8  (__data_loc) */
    int            parent_pid;           /* 12 */
    unsigned int   child_comm_loc;       /* 16 (__data_loc) */
    int            child_pid;            /* 20 */
};

SEC("tracepoint/sched/sched_process_fork")
int handle_fork(struct trace_event_raw_sched_process_fork *ctx)
{
    __u32 child_pid = ctx->child_pid;

    bpf_printk("CHILD PID : %u\n", child_pid);

    return 0;
}

char LICENSE[] SEC("license") = "GPL";