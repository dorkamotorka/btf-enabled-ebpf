package main

//go:generate go run github.com/cilium/ebpf/cmd/bpf2go tpbtf tp_btf.c

import (
	"log"
	"time"
	"github.com/cilium/ebpf/link"
)

func main() {
	// Load the BPF program
	objs := tpbtfObjects{}
	if err := loadTpbtfObjects(&objs, nil); err != nil {
		log.Fatalf("loading objects: %v", err)
	}
	defer objs.Close()

	// Attach the program to the tracepoint
	//tp, err := link.Tracepoint("sched", "sched_process_exec", objs.tpbtfPrograms.TpFunction, nil)
	//if err != nil {
	//	log.Fatalf("attaching tracepoint: %v", err)
	//}
	//defer tp.Close()

	// Attach the BTF-Enabled program to the tracepoint
	tp, err := link.AttachTracing(link.TracingOptions{
		Program: objs.tpbtfPrograms.TpBtfEnabledFunction,
	})
	if err != nil {
		log.Fatalf("attaching tracepoint: %v", err)
	}
	defer tp.Close()

	time.Sleep(30 * time.Second)
}

