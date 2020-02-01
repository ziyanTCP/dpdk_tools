//
// Created by ziyan on 1/13/20.
//

#include "../lib/ip.h"
#include <stdio.h>
#include <inttypes.h>
void test_test_string_to_ip(){
    uint32_t uint32_t_ip= string_to_ip("10.1.1.2");
    printf("[ %"PRIu32" ]\n", uint32_t_ip);
}