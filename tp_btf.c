//go:build ignore
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

char _license[] SEC("license") = "GPL";

// Output of: cat /sys/kernel/tracing/events/sched/sched_process_exec/format 
//name: sched_process_exec
//ID: 323
//format:
//	field:unsigned short common_type;	offset:0;	size:2;	signed:0;
//	field:unsigned char common_flags;	offset:2;	size:1;	signed:0;
//	field:unsigned char common_preempt_count;	offset:3;	size:1;	signed:0;
//	field:int common_pid;	offset:4;	size:4;	signed:1;
//
//	field:__data_loc char[] filename;	offset:8;	size:4;	signed:0;
//	field:pid_t pid;	offset:12;	size:4;	signed:1;
//	field:pid_t old_pid;	offset:16;	size:4;	signed:1;
//
//print fmt: "filename=%s pid=%d old_pid=%d", __get_str(filename), REC->pid, REC->old_pid
struct my_struct_sched_process_exec {
    unsigned short common_type;
    unsigned char common_flags;
    unsigned char common_preempt_count;
    int common_pid;

    long syscall_nr;
    void *filename_ptr;
    long argv_ptr;
    long envp_ptr;
};

SEC("tracepoint/sched/sched_process_exec")
int tp_function(struct my_struct_sched_process_exec *ctx) {
   bpf_printk("tracepoint called");
   return 0;
}

// trace_event_raw_sched_process_exec is defined in vmlinux.h
SEC("tp_btf/sched_process_exec")
int tp_btf_enabled_function(struct trace_event_raw_sched_process_exec *ctx) {
   bpf_printk("BTF-Enabled tracepoint called");
   return 0;
}
