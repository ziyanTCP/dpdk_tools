cmd_mylib/dpdk_init.o = gcc -Wp,-MD,mylib/.dpdk_init.o.d.tmp  -m64 -pthread -I/home/ziyan/test/dpdk//lib/librte_eal/linux/eal/include  -march=native -DRTE_MACHINE_CPUFLAG_SSE -DRTE_MACHINE_CPUFLAG_SSE2 -DRTE_MACHINE_CPUFLAG_SSE3 -DRTE_MACHINE_CPUFLAG_SSSE3 -DRTE_MACHINE_CPUFLAG_SSE4_1 -DRTE_MACHINE_CPUFLAG_SSE4_2 -DRTE_MACHINE_CPUFLAG_AES -DRTE_MACHINE_CPUFLAG_PCLMULQDQ -DRTE_MACHINE_CPUFLAG_AVX  -I/home/ziyan/Dropbox/mylibrary/mynetwork_library/build/include -DRTE_USE_FUNCTION_VERSIONING -I/home/ziyan/test/dpdk//x86_64-native-linuxapp-gcc/include -include /home/ziyan/test/dpdk//x86_64-native-linuxapp-gcc/include/rte_config.h -D_GNU_SOURCE -O3   -O0 -g -o mylib/dpdk_init.o -c /home/ziyan/Dropbox/mylibrary/mynetwork_library/mylib/dpdk_init.c 
