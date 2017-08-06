

#ifndef _COSSB_COMPONENT_MSAPI_FACE_HPP_
#define _COSSB_COMPONENT_MSAPI_FACE_HPP_

#include <interface/icomponent.hpp>
#include <map>
#include <python2.7/Python.h>

using namespace std;

class msapi_face : public interface::icomponent {
public:
	msapi_face();
	virtual ~msapi_face();

	/**
	 * @brief	setup interface function
	 */
	bool setup();

	/**
	 * @brief	run interface function
	 */
	bool run();

	/**
	 * @brief	stop interface function
	 */
	bool stop();

	/**
	 * @brief	request interface function
	 */
	void subscribe(cossb::message* const msg);

private:
	PyObject* _pyFunc = nullptr;
	string _url;
	string _key;
	unsigned char _emotion = 0x00;

};

COMPONENT_EXPORT

#endif /* _COSSB_COMPONENT_MSAPI_FACE_HPP_ */
