#include<linux/bpf.h>
#include<bpf/bpf_helpers.h>

SEC("tracepoint/syscalls/sys_enter_execve")
int handle_exec(void* ctx)
{
    __u64 pid_tpid = bpf_get_current_pid_tgid();
    __u32 PID = pid_tpid & 0xFFFFFFFF;
    __u32 TPID = pid_tpid >> 32;

    bpf_printk("HELLO FROM PID : %u | TPID : %u\n",PID,TPID);

    return 0;
}

char LICENSE[] SEC("license") = "GPL";