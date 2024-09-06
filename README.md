# BTF Enabled Tracepoint

This is an example of a BTF-Enabled Program, which means the eBPF verifier in your running kernel is aware of the type information associated with the input arguments passed into the eBPF program.

The section `tp_btf/` indicates that this is a BTF-enabled eBPF program.

I utilize Golang alongside the ebpf-go package.

## How to Run

First build and run the eBPF program:
```
go generate
go build
sudo ./tp_btf
```

Now let's verify it works as expected by inspecting eBPF logs using `sudo cat /sys/kernel/debug/tracing/trace_pipe` to verify eBPF is indeed attached and triggering as expected.
