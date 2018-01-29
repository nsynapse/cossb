################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../util/lwan/src/lib/base64.c \
../util/lwan/src/lib/hash.c \
../util/lwan/src/lib/int-to-str.c \
../util/lwan/src/lib/list.c \
../util/lwan/src/lib/lwan-array.c \
../util/lwan/src/lib/lwan-cache.c \
../util/lwan/src/lib/lwan-config.c \
../util/lwan/src/lib/lwan-coro.c \
../util/lwan/src/lib/lwan-http-authorize.c \
../util/lwan/src/lib/lwan-io-wrappers.c \
../util/lwan/src/lib/lwan-job.c \
../util/lwan/src/lib/lwan-lua.c \
../util/lwan/src/lib/lwan-mod-lua.c \
../util/lwan/src/lib/lwan-mod-redirect.c \
../util/lwan/src/lib/lwan-mod-response.c \
../util/lwan/src/lib/lwan-mod-rewrite.c \
../util/lwan/src/lib/lwan-mod-serve-files.c \
../util/lwan/src/lib/lwan-request.c \
../util/lwan/src/lib/lwan-response.c \
../util/lwan/src/lib/lwan-socket.c \
../util/lwan/src/lib/lwan-status.c \
../util/lwan/src/lib/lwan-straitjacket.c \
../util/lwan/src/lib/lwan-tables.c \
../util/lwan/src/lib/lwan-template.c \
../util/lwan/src/lib/lwan-thread.c \
../util/lwan/src/lib/lwan-time.c \
../util/lwan/src/lib/lwan-trie.c \
../util/lwan/src/lib/lwan.c \
../util/lwan/src/lib/missing.c \
../util/lwan/src/lib/murmur3.c \
../util/lwan/src/lib/patterns.c \
../util/lwan/src/lib/realpathat.c \
../util/lwan/src/lib/sd-daemon.c \
../util/lwan/src/lib/strbuf.c 

OBJS += \
./util/lwan/src/lib/base64.o \
./util/lwan/src/lib/hash.o \
./util/lwan/src/lib/int-to-str.o \
./util/lwan/src/lib/list.o \
./util/lwan/src/lib/lwan-array.o \
./util/lwan/src/lib/lwan-cache.o \
./util/lwan/src/lib/lwan-config.o \
./util/lwan/src/lib/lwan-coro.o \
./util/lwan/src/lib/lwan-http-authorize.o \
./util/lwan/src/lib/lwan-io-wrappers.o \
./util/lwan/src/lib/lwan-job.o \
./util/lwan/src/lib/lwan-lua.o \
./util/lwan/src/lib/lwan-mod-lua.o \
./util/lwan/src/lib/lwan-mod-redirect.o \
./util/lwan/src/lib/lwan-mod-response.o \
./util/lwan/src/lib/lwan-mod-rewrite.o \
./util/lwan/src/lib/lwan-mod-serve-files.o \
./util/lwan/src/lib/lwan-request.o \
./util/lwan/src/lib/lwan-response.o \
./util/lwan/src/lib/lwan-socket.o \
./util/lwan/src/lib/lwan-status.o \
./util/lwan/src/lib/lwan-straitjacket.o \
./util/lwan/src/lib/lwan-tables.o \
./util/lwan/src/lib/lwan-template.o \
./util/lwan/src/lib/lwan-thread.o \
./util/lwan/src/lib/lwan-time.o \
./util/lwan/src/lib/lwan-trie.o \
./util/lwan/src/lib/lwan.o \
./util/lwan/src/lib/missing.o \
./util/lwan/src/lib/murmur3.o \
./util/lwan/src/lib/patterns.o \
./util/lwan/src/lib/realpathat.o \
./util/lwan/src/lib/sd-daemon.o \
./util/lwan/src/lib/strbuf.o 

C_DEPS += \
./util/lwan/src/lib/base64.d \
./util/lwan/src/lib/hash.d \
./util/lwan/src/lib/int-to-str.d \
./util/lwan/src/lib/list.d \
./util/lwan/src/lib/lwan-array.d \
./util/lwan/src/lib/lwan-cache.d \
./util/lwan/src/lib/lwan-config.d \
./util/lwan/src/lib/lwan-coro.d \
./util/lwan/src/lib/lwan-http-authorize.d \
./util/lwan/src/lib/lwan-io-wrappers.d \
./util/lwan/src/lib/lwan-job.d \
./util/lwan/src/lib/lwan-lua.d \
./util/lwan/src/lib/lwan-mod-lua.d \
./util/lwan/src/lib/lwan-mod-redirect.d \
./util/lwan/src/lib/lwan-mod-response.d \
./util/lwan/src/lib/lwan-mod-rewrite.d \
./util/lwan/src/lib/lwan-mod-serve-files.d \
./util/lwan/src/lib/lwan-request.d \
./util/lwan/src/lib/lwan-response.d \
./util/lwan/src/lib/lwan-socket.d \
./util/lwan/src/lib/lwan-status.d \
./util/lwan/src/lib/lwan-straitjacket.d \
./util/lwan/src/lib/lwan-tables.d \
./util/lwan/src/lib/lwan-template.d \
./util/lwan/src/lib/lwan-thread.d \
./util/lwan/src/lib/lwan-time.d \
./util/lwan/src/lib/lwan-trie.d \
./util/lwan/src/lib/lwan.d \
./util/lwan/src/lib/missing.d \
./util/lwan/src/lib/murmur3.d \
./util/lwan/src/lib/patterns.d \
./util/lwan/src/lib/realpathat.d \
./util/lwan/src/lib/sd-daemon.d \
./util/lwan/src/lib/strbuf.d 


# Each subdirectory must supply rules for building sources it contributes
util/lwan/src/lib/%.o: ../util/lwan/src/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


