#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

SYMBOL_CRC(nvidia_p2p_cap_persistent_pages, 0x66079585, "");
SYMBOL_CRC(nvidia_p2p_init_mapping, 0x45bb0ad7, "");
SYMBOL_CRC(nvidia_p2p_destroy_mapping, 0x180f4b6a, "");
SYMBOL_CRC(nvidia_p2p_get_pages, 0x5b3f3e79, "");
SYMBOL_CRC(nvidia_p2p_free_page_table, 0xf42ca687, "");
SYMBOL_CRC(nvidia_p2p_put_pages, 0x642487ac, "");
SYMBOL_CRC(nvidia_p2p_dma_map_pages, 0xcbb2c549, "");
SYMBOL_CRC(nvidia_p2p_dma_unmap_pages, 0xfaa7cb2f, "");
SYMBOL_CRC(nvidia_p2p_free_dma_mapping, 0x9ac50b78, "");
SYMBOL_CRC(nvidia_p2p_register_rsync_driver, 0x63c5db4b, "");
SYMBOL_CRC(nvidia_p2p_unregister_rsync_driver, 0xb5d9f2af, "");
SYMBOL_CRC(nvidia_p2p_get_rsync_registers, 0xa2cb3179, "");
SYMBOL_CRC(nvidia_p2p_put_rsync_registers, 0xc61d489b, "");
SYMBOL_CRC(nvidia_get_rm_ops, 0x193c3c08, "");
SYMBOL_CRC(nv_register_error_cb, 0x11c6c5cc, "");
SYMBOL_CRC(nv_unregister_error_cb, 0x2e6cec6e, "");
SYMBOL_CRC(nvidia_register_module, 0xd5ced146, "");
SYMBOL_CRC(nvidia_unregister_module, 0x1aeb4592, "");
SYMBOL_CRC(nvidia_frontend_add_device, 0x0d4e11f6, "");
SYMBOL_CRC(nvidia_frontend_remove_device, 0x19463f67, "");
SYMBOL_CRC(nvUvmInterfaceRegisterGpu, 0x9190e870, "");
SYMBOL_CRC(nvUvmInterfaceUnregisterGpu, 0xaa9c1109, "");
SYMBOL_CRC(nvUvmInterfaceSessionCreate, 0x4fd65f06, "");
SYMBOL_CRC(nvUvmInterfaceSessionDestroy, 0xc3385e21, "");
SYMBOL_CRC(nvUvmInterfaceDeviceCreate, 0x9bfa3c18, "");
SYMBOL_CRC(nvUvmInterfaceDeviceDestroy, 0x78ba08fc, "");
SYMBOL_CRC(nvUvmInterfaceDupAddressSpace, 0xba548bb9, "");
SYMBOL_CRC(nvUvmInterfaceAddressSpaceCreate, 0xc655f87d, "");
SYMBOL_CRC(nvUvmInterfaceAddressSpaceDestroy, 0xa62da25a, "");
SYMBOL_CRC(nvUvmInterfaceMemoryAllocFB, 0x0bf4e45e, "");
SYMBOL_CRC(nvUvmInterfaceMemoryAllocSys, 0x3e22ffea, "");
SYMBOL_CRC(nvUvmInterfaceGetP2PCaps, 0x0c611df8, "");
SYMBOL_CRC(nvUvmInterfaceGetPmaObject, 0xd3446ca8, "");
SYMBOL_CRC(nvUvmInterfacePmaRegisterEvictionCallbacks, 0x39d420e5, "");
SYMBOL_CRC(nvUvmInterfacePmaUnregisterEvictionCallbacks, 0x30aeb11d, "");
SYMBOL_CRC(nvUvmInterfacePmaAllocPages, 0x08170cee, "");
SYMBOL_CRC(nvUvmInterfacePmaPinPages, 0x3ec90268, "");
SYMBOL_CRC(nvUvmInterfacePmaUnpinPages, 0x2612b964, "");
SYMBOL_CRC(nvUvmInterfaceMemoryFree, 0xd5057c22, "");
SYMBOL_CRC(nvUvmInterfacePmaFreePages, 0xbb22731a, "");
SYMBOL_CRC(nvUvmInterfaceMemoryCpuMap, 0xb83fa4e7, "");
SYMBOL_CRC(nvUvmInterfaceMemoryCpuUnMap, 0x4d7a107f, "");
SYMBOL_CRC(nvUvmInterfaceChannelAllocate, 0x9f1c60c9, "");
SYMBOL_CRC(nvUvmInterfaceChannelDestroy, 0xcd40176d, "");
SYMBOL_CRC(nvUvmInterfaceQueryCaps, 0xb2e108d5, "");
SYMBOL_CRC(nvUvmInterfaceQueryCopyEnginesCaps, 0x7a5a70c8, "");
SYMBOL_CRC(nvUvmInterfaceGetGpuInfo, 0x927c9ab3, "");
SYMBOL_CRC(nvUvmInterfaceServiceDeviceInterruptsRM, 0x19f28917, "");
SYMBOL_CRC(nvUvmInterfaceSetPageDirectory, 0x534759f3, "");
SYMBOL_CRC(nvUvmInterfaceUnsetPageDirectory, 0x4bc0e431, "");
SYMBOL_CRC(nvUvmInterfaceDupAllocation, 0x246cbff7, "");
SYMBOL_CRC(nvUvmInterfaceDupMemory, 0x5d51f2a9, "");
SYMBOL_CRC(nvUvmInterfaceFreeDupedHandle, 0x51f732db, "");
SYMBOL_CRC(nvUvmInterfaceGetFbInfo, 0x79e1c070, "");
SYMBOL_CRC(nvUvmInterfaceGetEccInfo, 0xa452244c, "");
SYMBOL_CRC(nvUvmInterfaceOwnPageFaultIntr, 0xd1600093, "");
SYMBOL_CRC(nvUvmInterfaceInitFaultInfo, 0x5c8382a1, "");
SYMBOL_CRC(nvUvmInterfaceInitAccessCntrInfo, 0xf3928810, "");
SYMBOL_CRC(nvUvmInterfaceEnableAccessCntr, 0xcf560b60, "");
SYMBOL_CRC(nvUvmInterfaceDestroyFaultInfo, 0x52ddc3d5, "");
SYMBOL_CRC(nvUvmInterfaceHasPendingNonReplayableFaults, 0xdac220d4, "");
SYMBOL_CRC(nvUvmInterfaceGetNonReplayableFaults, 0x657fa9f8, "");
SYMBOL_CRC(nvUvmInterfaceDestroyAccessCntrInfo, 0xc808868a, "");
SYMBOL_CRC(nvUvmInterfaceDisableAccessCntr, 0xaf0d91a7, "");
SYMBOL_CRC(nvUvmInterfaceRegisterUvmCallbacks, 0x550cc5f7, "");
SYMBOL_CRC(nvUvmInterfaceDeRegisterUvmOps, 0x84ccfdfb, "");
SYMBOL_CRC(nvUvmInterfaceP2pObjectCreate, 0xf7419bbb, "");
SYMBOL_CRC(nvUvmInterfaceP2pObjectDestroy, 0xce96a1a4, "");
SYMBOL_CRC(nvUvmInterfaceGetExternalAllocPtes, 0xf1fcc453, "");
SYMBOL_CRC(nvUvmInterfaceRetainChannel, 0x81d5d523, "");
SYMBOL_CRC(nvUvmInterfaceBindChannelResources, 0xf82d8f8b, "");
SYMBOL_CRC(nvUvmInterfaceReleaseChannel, 0x43e66ecb, "");
SYMBOL_CRC(nvUvmInterfaceStopChannel, 0x27491fbc, "");
SYMBOL_CRC(nvUvmInterfaceGetChannelResourcePtes, 0xdbbe9dd4, "");
SYMBOL_CRC(nvUvmInterfaceReportNonReplayableFault, 0x69eb8138, "");
SYMBOL_CRC(nvUvmInterfacePagingChannelAllocate, 0x89e0959d, "");
SYMBOL_CRC(nvUvmInterfacePagingChannelDestroy, 0x892a63e7, "");
SYMBOL_CRC(nvUvmInterfacePagingChannelsMap, 0x6fcca1a3, "");
SYMBOL_CRC(nvUvmInterfacePagingChannelsUnmap, 0x36e57696, "");
SYMBOL_CRC(nvUvmInterfacePagingChannelPushStream, 0x942fa6aa, "");

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x735e6a81, "acpi_evaluate_integer" },
	{ 0xc631580a, "console_unlock" },
	{ 0x4dfa8d4b, "mutex_lock" },
	{ 0x1000e51, "schedule" },
	{ 0xee8c61e8, "request_firmware" },
	{ 0x3f49f143, "pci_unregister_driver" },
	{ 0x34db050b, "_raw_spin_lock_irqsave" },
	{ 0xf90a1e85, "__x86_indirect_thunk_r8" },
	{ 0x77c7cfdb, "dma_sync_single_for_cpu" },
	{ 0xe2648af2, "iov_iter_kvec" },
	{ 0x79c176b4, "pci_write_config_byte" },
	{ 0x34cdc727, "pci_find_capability" },
	{ 0xe3f05e13, "__tracepoint_mmap_lock_released" },
	{ 0x63f835ba, "on_each_cpu_cond_mask" },
	{ 0x97f529e8, "pci_clear_master" },
	{ 0xe54d951b, "kmem_cache_free" },
	{ 0x6383b27c, "__x86_indirect_thunk_rdx" },
	{ 0x1e6d26a8, "strstr" },
	{ 0x67c67606, "vm_insert_page" },
	{ 0xad8a4d33, "pci_dev_put" },
	{ 0xdd21bfbc, "pci_read_config_word" },
	{ 0x57bc19d2, "down_write" },
	{ 0x1bf41539, "__mmap_lock_do_trace_acquire_returned" },
	{ 0xdf8c695a, "__ndelay" },
	{ 0x48d3a613, "pci_release_regions" },
	{ 0x349cba85, "strchr" },
	{ 0x9945ef67, "pci_request_regions" },
	{ 0x27bbf221, "disable_irq_nosync" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0xe687d38f, "pci_get_domain_bus_and_slot" },
	{ 0x75871f5e, "acpi_get_next_object" },
	{ 0x9305f8e6, "cpufreq_get" },
	{ 0x3c40223d, "seq_read_iter" },
	{ 0xae04012c, "__vmalloc" },
	{ 0x96ed03d3, "dma_map_resource" },
	{ 0x5a921311, "strncmp" },
	{ 0x25974000, "wait_for_completion" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x53b954a2, "up_read" },
	{ 0xa648e561, "__ubsan_handle_shift_out_of_bounds" },
	{ 0xeceffed5, "dma_ops" },
	{ 0xe837d081, "sg_alloc_table_from_pages_segment" },
	{ 0xa843805a, "get_unused_fd_flags" },
	{ 0x4629334c, "__preempt_count" },
	{ 0xa3f76cb6, "__mmap_lock_do_trace_start_locking" },
	{ 0xa916b694, "strnlen" },
	{ 0xcefb0c9f, "__mutex_init" },
	{ 0xc07351b3, "__SCT__cond_resched" },
	{ 0xb6fde909, "close_fd" },
	{ 0x9493fc86, "node_states" },
	{ 0xf373a649, "address_space_init_once" },
	{ 0xd0719ed5, "proc_remove" },
	{ 0x7f24de73, "jiffies_to_usecs" },
	{ 0xf9c0b663, "strlcat" },
	{ 0x7424bdfe, "proc_create_data" },
	{ 0xe9ffc063, "down_trylock" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0xef1df4de, "param_ops_int" },
	{ 0xcfedd026, "current_task" },
	{ 0x15ba50a6, "jiffies" },
	{ 0x8d48ac06, "pci_bus_type" },
	{ 0x6128b5fc, "__printk_ratelimit" },
	{ 0x81e6b37f, "dmi_get_system_info" },
	{ 0x55385e2e, "__x86_indirect_thunk_r14" },
	{ 0x378599bb, "__put_devmap_managed_page_refs" },
	{ 0xf97ffc26, "pci_set_master" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0x7a905b5b, "vmf_insert_pfn_prot" },
	{ 0x2dbb7368, "dma_set_mask" },
	{ 0x4302d0eb, "free_pages" },
	{ 0x608741b5, "__init_swait_queue_head" },
	{ 0x58f39a87, "__register_chrdev" },
	{ 0xb5b54b34, "_raw_spin_unlock" },
	{ 0x7b4da6ff, "__init_rwsem" },
	{ 0x587f22d7, "devmap_managed_key" },
	{ 0x76f74542, "vmalloc_to_page" },
	{ 0x8d31d9af, "pci_save_state" },
	{ 0x65487097, "__x86_indirect_thunk_rax" },
	{ 0xa0dadd65, "dma_map_sg_attrs" },
	{ 0x69acdf38, "memcpy" },
	{ 0x6b2dc060, "dump_stack" },
	{ 0x7483dc59, "pci_dev_present" },
	{ 0xbbee8ae8, "iterate_fd" },
	{ 0x362f9a8, "__x86_indirect_thunk_r12" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0xc6d09aa9, "release_firmware" },
	{ 0x31549b2a, "__x86_indirect_thunk_r10" },
	{ 0xde80cd09, "ioremap" },
	{ 0x722f17a7, "seq_lseek" },
	{ 0x9e683f75, "__cpu_possible_mask" },
	{ 0xa50a3da7, "_find_next_bit" },
	{ 0xeebb9254, "kernel_read" },
	{ 0x1db7291c, "filp_open" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0xf1e046cc, "panic" },
	{ 0x17e8e8aa, "set_page_dirty_lock" },
	{ 0x955498c3, "dma_buf_put" },
	{ 0x29d1545d, "single_open" },
	{ 0x9e7d6bd0, "__udelay" },
	{ 0x55570d70, "seq_printf" },
	{ 0x412a5f9c, "kthread_stop" },
	{ 0xc814d2b0, "find_vma" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0x296695f, "refcount_warn_saturate" },
	{ 0x8beb4f2b, "__alloc_pages" },
	{ 0x11089ac7, "_ctype" },
	{ 0x3c5d543a, "hrtimer_start_range_ns" },
	{ 0xcd4f2e8e, "dma_unmap_page_attrs" },
	{ 0xe69e2e35, "module_put" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x668b19a1, "down_read" },
	{ 0xa119e553, "dma_sync_single_for_device" },
	{ 0xbcb36fe4, "hugetlb_optimize_vmemmap_key" },
	{ 0x2d0684a9, "hrtimer_init" },
	{ 0xfaaaa1dc, "pci_enable_atomic_ops_to_root" },
	{ 0x365acda7, "set_normalized_timespec64" },
	{ 0x6626afca, "down" },
	{ 0x85df9b6c, "strsep" },
	{ 0x7a357207, "kmem_cache_create" },
	{ 0xfb578fc5, "memset" },
	{ 0x8810754a, "_find_first_bit" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x301674c4, "fd_install" },
	{ 0x37b8b39e, "screen_info" },
	{ 0x37a0cba, "kfree" },
	{ 0xc31db0ce, "is_vmalloc_addr" },
	{ 0xd81e9056, "fget" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x66cca4f9, "__x86_indirect_thunk_rcx" },
	{ 0xcf2a6966, "up" },
	{ 0x46cf10eb, "cachemode2protval" },
	{ 0xa2b5562d, "pci_get_class" },
	{ 0xc086f560, "pcie_capability_read_word" },
	{ 0xfcec0987, "enable_irq" },
	{ 0x8df070e6, "cdev_init" },
	{ 0x5541f017, "filp_close" },
	{ 0x2d4a36f1, "__tracepoint_mmap_lock_start_locking" },
	{ 0x8427cc7b, "_raw_spin_lock_irq" },
	{ 0x1035c7c2, "__release_region" },
	{ 0xff89d035, "i2c_add_adapter" },
	{ 0xab65ed80, "set_memory_uc" },
	{ 0x77358855, "iomem_resource" },
	{ 0x4d9b652b, "rb_erase" },
	{ 0x89940875, "mutex_lock_interruptible" },
	{ 0x56470118, "__warn_printk" },
	{ 0x6a087af, "pin_user_pages" },
	{ 0xdb94d905, "pci_iomap" },
	{ 0x17de3d5, "nr_cpu_ids" },
	{ 0x3684a322, "cdev_add" },
	{ 0xe914e41e, "strcpy" },
	{ 0x170ddf79, "acpi_install_notify_handler" },
	{ 0xf5b00aab, "boot_cpu_data" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x1f224af1, "try_module_get" },
	{ 0x241553eb, "kmem_cache_destroy" },
	{ 0x382881a, "registered_fb" },
	{ 0x9afe1a6d, "set_pages_array_uc" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x7f5b4fe4, "sg_free_table" },
	{ 0x34e02dd9, "pm_vt_switch_unregister" },
	{ 0xc3ff38c2, "down_read_trylock" },
	{ 0xe0112fc4, "__x86_indirect_thunk_r9" },
	{ 0x6b68db21, "pci_iounmap" },
	{ 0xf04841b5, "dma_buf_fd" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x43c7fa, "pci_read_config_byte" },
	{ 0x11d9ce43, "wake_up_process" },
	{ 0xfd93ee35, "ioremap_wc" },
	{ 0x61651be, "strcat" },
	{ 0xa6257a2f, "complete" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0x267f3b6d, "dma_free_attrs" },
	{ 0x2f82173a, "dma_buf_get" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x62fdcc1a, "kthread_create_on_node" },
	{ 0x8596b150, "single_release" },
	{ 0x87b8798d, "sg_next" },
	{ 0x4e8d3c1d, "is_acpi_device_node" },
	{ 0x18f6533d, "__free_pages" },
	{ 0x460b0066, "pci_write_config_word" },
	{ 0x54b1fac6, "__ubsan_handle_load_invalid_value" },
	{ 0x1d9a81d0, "pci_read_config_dword" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x46a4b118, "hrtimer_cancel" },
	{ 0xd35cce70, "_raw_spin_unlock_irqrestore" },
	{ 0xad4458f8, "__tracepoint_mmap_lock_acquire_returned" },
	{ 0x618911fc, "numa_node" },
	{ 0x148653, "vsnprintf" },
	{ 0x17cd2643, "__folio_put" },
	{ 0x531b604e, "__virt_addr_valid" },
	{ 0x4cb6d583, "cdev_del" },
	{ 0xece784c2, "rb_first" },
	{ 0x4d1f894e, "dma_unmap_resource" },
	{ 0x4e080e9a, "dma_alloc_attrs" },
	{ 0xe40c37ea, "down_write_trylock" },
	{ 0xa5526619, "rb_insert_color" },
	{ 0xa7cdcdc3, "pci_enable_msix_range" },
	{ 0xc85d8fc6, "pci_write_config_dword" },
	{ 0xd6eaaea1, "full_name_hash" },
	{ 0x65b0663f, "unmap_mapping_range" },
	{ 0x1edb69d6, "ktime_get_raw_ts64" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x556422b3, "ioremap_cache" },
	{ 0xe2eb28dc, "kmem_cache_alloc" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xd6c7f1fd, "param_ops_charp" },
	{ 0x715a5ed0, "vprintk" },
	{ 0x986816b, "kmalloc_caches" },
	{ 0x47e0a543, "dev_driver_string" },
	{ 0xbb5332e9, "remove_proc_entry" },
	{ 0xc5fe8c6e, "pci_disable_msi" },
	{ 0x4c236f6f, "__x86_indirect_thunk_r15" },
	{ 0x8b8f7c41, "pci_disable_device" },
	{ 0x5a5a2271, "__cpu_online_mask" },
	{ 0x6b15251c, "pcibios_resource_to_bus" },
	{ 0x999e8297, "vfree" },
	{ 0xd680a377, "drm_gem_object_free" },
	{ 0xaafdc258, "strcasecmp" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x984550c7, "follow_pfn" },
	{ 0x41ed3709, "get_random_bytes" },
	{ 0xafec5a0d, "dma_map_page_attrs" },
	{ 0xbdf9a5e3, "dma_unmap_sg_attrs" },
	{ 0x91607d95, "set_memory_wb" },
	{ 0x21ea5251, "__bitmap_weight" },
	{ 0x9166fada, "strncpy" },
	{ 0x449ad0a7, "memcmp" },
	{ 0x4b750f53, "_raw_spin_unlock_irq" },
	{ 0x656444d8, "pci_enable_msi" },
	{ 0x1a79c8e9, "__x86_indirect_thunk_r13" },
	{ 0x284faa6b, "__x86_indirect_thunk_r11" },
	{ 0x44075751, "set_pages_array_wb" },
	{ 0xecd2230c, "pm_vt_switch_required" },
	{ 0xf1969a8e, "__usecs_to_jiffies" },
	{ 0x99a40021, "dma_set_coherent_mask" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x6bd0e573, "down_interruptible" },
	{ 0x2e3bcce2, "wait_for_completion_interruptible" },
	{ 0x6dfdc693, "pv_ops" },
	{ 0x9728df46, "unpin_user_page" },
	{ 0x20285d28, "vga_set_legacy_decoding" },
	{ 0x6c61ce70, "num_registered_fb" },
	{ 0x670ecece, "__x86_indirect_thunk_rbx" },
	{ 0xfaac21fc, "dma_buf_export" },
	{ 0x1800449b, "__pci_register_driver" },
	{ 0x20000329, "simple_strtoul" },
	{ 0x33842dd, "pci_disable_msix" },
	{ 0x56d523f, "pci_stop_and_remove_bus_device" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xa94a09bb, "mem_section" },
	{ 0x1f2c5d54, "seq_read" },
	{ 0xba8fbd64, "_raw_spin_lock" },
	{ 0xce807a25, "up_write" },
	{ 0xe2c17b5d, "__SCT__might_resched" },
	{ 0xfbaaf01e, "console_lock" },
	{ 0x2eed4e60, "i2c_del_adapter" },
	{ 0x1e17a4d2, "kernel_write" },
	{ 0xd38cd261, "__default_kernel_pte_mask" },
	{ 0x9ec6ca96, "ktime_get_real_ts64" },
	{ 0x92997ed8, "_printk" },
	{ 0x9f4f2aa3, "acpi_gbl_FADT" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x108b5973, "proc_mkdir_mode" },
	{ 0x8a35b432, "sme_me_mask" },
	{ 0x5dd9068b, "remap_pfn_range" },
	{ 0x94961283, "vunmap" },
	{ 0x4c9d28b0, "phys_base" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0x754d539c, "strlen" },
	{ 0x7023bea8, "unregister_acpi_notifier" },
	{ 0x2e2b40d2, "strncat" },
	{ 0x7a2af7b4, "cpu_number" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x85bd1608, "__request_region" },
	{ 0x5795b1e5, "pci_enable_device" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0x1f1821ae, "efi" },
	{ 0x56894c7e, "node_data" },
	{ 0x8a186894, "fput" },
	{ 0xc6cbbc89, "capable" },
	{ 0x93d6dd8c, "complete_all" },
	{ 0x9f690459, "kmem_cache_alloc_trace" },
	{ 0x9975dc22, "acpi_get_handle" },
	{ 0x3a2f6702, "sg_alloc_table" },
	{ 0x7dc744cd, "__mmap_lock_do_trace_released" },
	{ 0xec2b8a42, "acpi_walk_namespace" },
	{ 0x48d88a2c, "__SCT__preempt_schedule" },
	{ 0xd92deb6b, "acpi_evaluate_object" },
	{ 0x97934ecf, "del_timer_sync" },
	{ 0x97651e6c, "vmemmap_base" },
	{ 0x6a5cb5ee, "__get_free_pages" },
	{ 0x1c58427f, "acpi_remove_notify_handler" },
	{ 0x27d1f454, "vmap" },
	{ 0x188ea314, "jiffies_to_timespec64" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0xd887b37, "seq_puts" },
	{ 0x973fa82e, "register_acpi_notifier" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xedc03953, "iounmap" },
	{ 0xc0ada9cf, "module_layout" },
};

MODULE_INFO(depends, "drm");

MODULE_ALIAS("pci:v000010DEd*sv*sd*bc03sc00i00*");
MODULE_ALIAS("pci:v000010DEd*sv*sd*bc03sc02i00*");
MODULE_ALIAS("pci:v000010DEd*sv*sd*bc06sc80i00*");

MODULE_INFO(srcversion, "835F086B11797F32CE003BD");
