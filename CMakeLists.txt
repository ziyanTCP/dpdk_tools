cmake_minimum_required(VERSION 3.15)
project(mynetwork_library C)

set(CMAKE_C_STANDARD 99)

include_directories(/home/ziyan/song/Dropbox/dpdk/x86_64-native-linuxapp-gcc/include/)
LINK_DIRECTORIES(/home/ziyan/song/Dropbox/dpdk/x86_64-native-linuxapp-gcc/include/)

include_directories(lib/tcp)
LINK_DIRECTORIES(lib/tcp)

add_executable(lib main.c lib/ip.c lib/ip.h test/test_ip.h lib/mac.c lib/mac.h test/test_getchar.h lib/dpdk_init.c lib/dpdk_init.h lib/dpdk_macro.h test/test_dpdk_init.h test/test_minimal_ip_send.h lib/dpdk_utility.c lib/dpdk_utility.h test/test_tailq.h test/queue.h lib/tcp/dpdk_module.c lib/tcp/dpdk_module.h)