#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/netfilter.h>
#include<linux/netfilter_ipv4.h>
#include<linux/ip.h>
#include<linux/inet.h>
#include<linux/skbuff.h>
#include<linux/tcp.h>
#include<linux/udp.h>
#include<linux/time.h>
#include <linux/timer.h>
#include <linux/timex.h>
#include <linux/rtc.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include<linux/string.h>

#include "log.h"
#include "netFilter.h"
#include "netLink.h"

/**
 * 插入模块时调用的函数
 */
static int __init init(void) {
    // 插入模块时
    INFO("insert netFilter module to kernel!\n");

    // 先初始化netLink模块，优先保证与用户态通信
    if (createNetlink() != 0) {
        ERROR("create netLink failed!\n");
        return 1;
    }
    else {
        INFO("create netLink success!\n");
    }

    // 初始化netFilter
    initNetFilter();
    return 0;
}

/**
 * 移除模块时调用的函数
 */
static void __exit fini(void) {
    INFO("remove netfilter module from kernel!\n");
    // 先释放netFilter钩子
    releaseNetFilter();
    // 释放netLink
    deleteNetlink();
}

// 模块入口，插入模块后调用绑定函数
module_init(init);
// 模块出口，插入模块后调用绑定函数
module_exit(fini);