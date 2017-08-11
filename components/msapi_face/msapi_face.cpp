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
	if(!Py_IsInitialized())
		return false;

	_url = get_profile()->get(profile::section::property, "url").asString("https://localhost");
	_key = get_profile()->get(profile::section::property, "key").asString("");
	_file = get_profile()->get(profile::section::property, "file").asString("capture.jpg");

	cossb_log->log(log::loglevel::INFO, fmt::format("MSAPI URL : {}", _url));
	cossb_log->log(log::loglevel::INFO, fmt::format("MSAPI Key : {}", _key));

	//add path
	PyObject* sysPath = PySys_GetObject((char*)"path");
	PyObject* path = PyString_FromString(".");
	PyList_Insert(sysPath, 0, path);

	//get module
	PyObject* pyName = PyString_FromString("msapi2");
	PyObject* pyModule = PyImport_Import(pyName);

	if(pyModule){
		PyObject* pyFunc = PyObject_GetAttrString(pyModule, "get_emotion");
		 if(pyFunc && PyCallable_Check(pyFunc)){
			 PyObject* pResult = PyObject_CallFunction(pyFunc, "(sss)", _url.c_str(), _key.c_str(), _file.c_str());
			 if(pResult){
				 string result = PyString_AsString(pResult);
				 //process json string
			 }
			 else
				 PyErr_Print();
			 Py_XDECREF(pResult);
		 }
		 else
			 PyErr_Print();
		 Py_XDECREF(pyFunc);
	}
	else
		PyErr_Print();

	Py_XDECREF(sysPath);
	Py_XDECREF(path);
	Py_XDECREF(pyName);
	Py_XDECREF(pyModule);

	return true;
}

bool msapi_face::run()
{
//	PyObject* pArgs = PyTuple_New(3);
//
//	PyTuple_SetItem(pArgs, 0, PyString_FromString(_url.c_str()));
//	PyTuple_SetItem(pArgs, 1, PyString_FromString(_key.c_str()));
//	PyTuple_SetItem(pArgs, 2, PyString_FromString("test.jpg"));
//
//	if(PyCallable_Check(_pyFunc)){
//		PyObject* pResult = PyObject_CallObject(_pyFunc, pArgs);
//		if(pResult!=Py_None){
//			string result = PyString_AsString(pResult);
//			cossb_log->log(log::loglevel::INFO, result);
//		}
//	}
//
//	cossb_log->log(log::loglevel::ERROR, "Cannot call the python function");

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



