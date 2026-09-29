#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("tracepoint/syscalls/sys_enter_execve")
int handle_exec(void *ctx)
{
    bpf_printk("Hello, eBPF!\n");
    return 0;
}

char LICENSE[] SEC("license") = "GPL";