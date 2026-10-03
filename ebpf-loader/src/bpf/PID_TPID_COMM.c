#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("tracepoint/syscalls/sys_enter_execve")
int handle_exec(void *ctx)
{
    __u64 pid_tgid = bpf_get_current_pid_tgid();

    __u32 pid = pid_tgid & 0xFFFFFFFF;
    __u32 tgid = pid_tgid >> 32;

    char comm[16];

    if (bpf_get_current_comm(comm, sizeof(comm)) != 0)
    {
        bpf_printk("Failed to get comm\n");
        return 0;
    }

    bpf_printk(
        "PID=%u TGID=%u COMM=%s\n",
        pid,
        tgid,
        comm);

    return 0;
}

char LICENSE[] SEC("license") = "GPL";