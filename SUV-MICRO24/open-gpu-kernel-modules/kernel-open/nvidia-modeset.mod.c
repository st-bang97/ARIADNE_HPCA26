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

SYMBOL_CRC(nvKmsKapiGetFunctionsTable, 0x3395617a, "");

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xc31db0ce, "is_vmalloc_addr" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x9e7d6bd0, "__udelay" },
	{ 0x7b4da6ff, "__init_rwsem" },
	{ 0x82655ff7, "backlight_device_unregister" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x76f74542, "vmalloc_to_page" },
	{ 0xb0e602eb, "memmove" },
	{ 0x656e4a6e, "snprintf" },
	{ 0xa6257a2f, "complete" },
	{ 0xd5ced146, "nvidia_register_module" },
	{ 0x4c236f6f, "__x86_indirect_thunk_r15" },
	{ 0xd81e9056, "fget" },
	{ 0xcf2a6966, "up" },
	{ 0x108b5973, "proc_mkdir_mode" },
	{ 0x69acdf38, "memcpy" },
	{ 0x37a0cba, "kfree" },
	{ 0x722f17a7, "seq_lseek" },
	{ 0x7424bdfe, "proc_create_data" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0x148653, "vsnprintf" },
	{ 0x34db050b, "_raw_spin_lock_irqsave" },
	{ 0x9f690459, "kmem_cache_alloc_trace" },
	{ 0xc3ff38c2, "down_read_trylock" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x11d9ce43, "wake_up_process" },
	{ 0x4482cdb, "__refrigerator" },
	{ 0x284faa6b, "__x86_indirect_thunk_r11" },
	{ 0x65487097, "__x86_indirect_thunk_rax" },
	{ 0x6b2dc060, "dump_stack" },
	{ 0x92997ed8, "_printk" },
	{ 0x193c3c08, "nvidia_get_rm_ops" },
	{ 0x1000e51, "schedule" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x6383b27c, "__x86_indirect_thunk_rdx" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0x8a186894, "fput" },
	{ 0x57bc19d2, "down_write" },
	{ 0xce807a25, "up_write" },
	{ 0x55385e2e, "__x86_indirect_thunk_r14" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0x6626afca, "down" },
	{ 0x670ecece, "__x86_indirect_thunk_rbx" },
	{ 0x9166fada, "strncpy" },
	{ 0x1a79c8e9, "__x86_indirect_thunk_r13" },
	{ 0x9ec6ca96, "ktime_get_real_ts64" },
	{ 0x449ad0a7, "memcmp" },
	{ 0x412a5f9c, "kthread_stop" },
	{ 0x2ee4a2fb, "freezing_slow_path" },
	{ 0xcfedd026, "current_task" },
	{ 0xd35cce70, "_raw_spin_unlock_irqrestore" },
	{ 0xfb578fc5, "memset" },
	{ 0x31549b2a, "__x86_indirect_thunk_r10" },
	{ 0x97934ecf, "del_timer_sync" },
	{ 0x25974000, "wait_for_completion" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x1aeb4592, "nvidia_unregister_module" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0xd0719ed5, "proc_remove" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x15ba50a6, "jiffies" },
	{ 0x62fdcc1a, "kthread_create_on_node" },
	{ 0x1f2c5d54, "seq_read" },
	{ 0x4629334c, "__preempt_count" },
	{ 0x999e8297, "vfree" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0xb3b378e, "param_ops_bool" },
	{ 0x66cca4f9, "__x86_indirect_thunk_rcx" },
	{ 0x56470118, "__warn_printk" },
	{ 0x6bd0e573, "down_interruptible" },
	{ 0xe0112fc4, "__x86_indirect_thunk_r9" },
	{ 0x2e32f96d, "backlight_device_register" },
	{ 0x7ab88a45, "system_freezing_cnt" },
	{ 0xc07351b3, "__SCT__cond_resched" },
	{ 0xd887b37, "seq_puts" },
	{ 0x8596b150, "single_release" },
	{ 0x362f9a8, "__x86_indirect_thunk_r12" },
	{ 0x54b1fac6, "__ubsan_handle_load_invalid_value" },
	{ 0x754d539c, "strlen" },
	{ 0xef1df4de, "param_ops_int" },
	{ 0x29d1545d, "single_open" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x53b954a2, "up_read" },
	{ 0xf90a1e85, "__x86_indirect_thunk_r8" },
	{ 0xf9a482f9, "msleep" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0xe2c17b5d, "__SCT__might_resched" },
	{ 0x986816b, "kmalloc_caches" },
	{ 0xc0ada9cf, "module_layout" },
};

MODULE_INFO(depends, "nvidia");


MODULE_INFO(srcversion, "74789EE834A60AEF958568D");
