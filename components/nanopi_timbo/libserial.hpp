/**
 * @file		libserial.hpp
 * @brief		serial communication library
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2016. 2. 2
 * @details	serial library for UART component
 */

#ifndef _LIBSERIAL_HPP_
#define _LIBSERIAL_HPP_

#include <sys/types.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

class libserial {
public:
	libserial();
	virtual ~libserial();

	bool open(const char* port, int baudrate);
	void close();

	int write(const char* data, int size);
	int write(const unsigned char* data, int size);
	int read(unsigned char* pdata, int size);

	bool is_opened();

private:
	int _device = -1;
	struct termios _tio;
};

#endif /* _LIBSERIAL_HPP_ */
