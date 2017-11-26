

#include "libserial.hpp"

libserial::libserial() {
	memset(&_tio, 0, sizeof(_tio));
}

libserial::~libserial() {
	this->close();
}

bool libserial::open(const char* port, int baudrate)
{
	_device = ::open(port, O_RDWR|O_NOCTTY|O_NONBLOCK);

	if(_device==-1)
		return false;

	switch(baudrate)
	{
	case 1200:		_tio.c_cflag = B1200; break;
	case 1800:		_tio.c_cflag = B1800; break;
	case 2400:		_tio.c_cflag = B2400; break;
	case 4800:		_tio.c_cflag = B4800; break;
	case 9600:		_tio.c_cflag = B9600; break;
	case 19200:	_tio.c_cflag = B19200; break;
	case 38400:	_tio.c_cflag = B38400; break;
	case 57600:	_tio.c_cflag = B57600; break;
	case 115200:	_tio.c_cflag = B115200; break;
	}

	_tio.c_cflag |= CS8;
	_tio.c_cflag |= CLOCAL;
	_tio.c_cflag |= CREAD;
	_tio.c_iflag = 0;
	_tio.c_oflag = 0;
	_tio.c_lflag &= ~ICANON; /* Set non-canonical mode */
	_tio.c_cc[VTIME] = 0;
	_tio.c_cc[VMIN] = 0;

	tcflush(_device, TCIFLUSH);
	tcsetattr(_device, TCSANOW, &_tio);

	return true;
}


void libserial::close()
{
	::close(_device);
}


int libserial::write(const char* data, int size)
{
	return ::write(_device, data, size);
}

int libserial::write(const unsigned char* data, int size)
{
	return ::write(_device, data, size);
}


int libserial::read(unsigned char* pdata, int size)
{
	return ::read(_device, pdata, size);
}

bool libserial::is_opened()
{
	if(_device>0)
		return true;
	return false;
}
