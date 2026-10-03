#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("tracepoint/sched/sched_process_fork")
int handle_fork(void *ctx)
{

    bpf_printk("FORK_EVENT...\n");

    return 0;
}

char LICENSE[] SEC("license") = "GPL";  