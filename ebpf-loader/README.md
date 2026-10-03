sudo ls /sys/kernel/tracing/events/<category>/<event>
sudo cat /sys/kernel/tracing/events/sched/sched_process_fork/format

sudo bpftool btf dump file /sys/kernel/btf/vmlinux format c > src/bpf/vmlinux.h