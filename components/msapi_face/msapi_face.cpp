/*
 * msapi_face.cpp
 *
 *  Created on: 2017. 7. 22.
 *      Author: hwang
 */

#include "msapi_face.hpp"
#include <cossb.hpp>

using namespace std;

USE_COMPONENT_INTERFACE(msapi_face)

msapi_face::msapi_face()
:cossb::interface::icomponent(COMPONENT(msapi_face)){

}

msapi_face::~msapi_face() {

}

bool msapi_face::setup()
{
	Py_Initialize();

	_url = get_profile()->get(profile::section::property, "url").asString("https://localhost");
	_key = get_profile()->get(profile::section::property, "key").asString("");

	PyObject* _module_string = PyString_FromString((char*)"msapi2");
	PyObject* _module = PyImport_Import(_module_string);
	PyObject* _dict = PyModule_GetDict(_module);
	_pyFunc = PyDict_GetItemString(_dict, "get_emotion");

	return true;
}

bool msapi_face::run()
{
	PyObject* pArgs = PyTuple_New(3);

	PyTuple_SetItem(pArgs, 0, PyString_FromString(_url.c_str()));
	PyTuple_SetItem(pArgs, 1, PyString_FromString(_key.c_str()));
	PyTuple_SetItem(pArgs, 2, PyString_FromString("test.jpg"));

	if(_pyFunc){
		PyObject* pResult = PyObject_CallObject(_pyFunc, pArgs);
		if(pResult!=Py_None){
			string result = PyString_AsString(pResult);
			cossb_log->log(log::loglevel::INFO, result);
		}
	}

	cossb_log->log(log::loglevel::ERROR, "Cannot call the python function");

	return true;
}

bool msapi_face::stop()
{
	Py_Finalize();
	return true;
}

void msapi_face::subscribe(cossb::message* const msg)
{

	switch(msg->get_frame()->type) {
			case cossb::base::msg_type::REQUEST: break;
			case cossb::base::msg_type::DATA: {
				try {
					//cv::Mat image = boost::any_cast<cv::Mat>(*msg->get_data());
					//process

					//after process
//					cossb::message _msg(this, base::msg_type::DATA);
//					_msg.set((unsigned char)0x01);
//					cossb_broker->publish("face_emotion", _msg);

					cossb_log->log(log::loglevel::INFO, "send message to spi");

					}
					catch(const boost::bad_any_cast&){
						cossb_log->log(log::loglevel::ERROR, "Invalid type casting..");
					}
			} break;
			case cossb::base::msg_type::RESPONSE: break;
			case cossb::base::msg_type::EVENT:  break;
			}
}



