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

	//add path
	PyObject *sysPath = PySys_GetObject((char*)"path");
	PyObject *path = PyString_FromString(".");
	PyList_Insert(sysPath, 0, path);

	PyObject* _module = PyImport_ImportModule("msapi2");
	if(_module){

		PyObject* pArgs = PyTuple_New(3);
		PyTuple_SetItem(pArgs, 0, PyString_FromString(_url.c_str()));
		PyTuple_SetItem(pArgs, 1, PyString_FromString(_key.c_str()));
		PyTuple_SetItem(pArgs, 2, PyString_FromString("test.jpg"));

		PyObject* _dict = PyModule_GetDict(_module);
		_pyFunc = PyDict_GetItemString(_dict, "get_emotion");
		if(_pyFunc){
			if(PyCallable_Check(_pyFunc)){
					PyObject* pResult = PyObject_CallObject(_pyFunc, pArgs);
					string result = PyString_AsString(pResult);
					//Py_DECREF(pResult);
					cossb_log->log(log::loglevel::ERROR, "ok");
					//cossb_log->log(log::loglevel::INFO, result);
			}
		}

//		PyObject* _dict = PyModule_GetDict(_module);
//		PyErr_Print();
//		if(!_dict)
//			cossb_log->log(log::loglevel::ERROR, "No dict");
//
//		_pyFunc = PyDict_GetItemString(_dict, "get_emotion");
//
//		PyObject* pArgs = PyTuple_New(3);
//		PyTuple_SetItem(pArgs, 0, PyString_FromString(_url.c_str()));
//		PyTuple_SetItem(pArgs, 1, PyString_FromString(_key.c_str()));
//		PyTuple_SetItem(pArgs, 2, PyString_FromString("test.jpg"));
//
//		if(PyCallable_Check(_pyFunc)){
//				PyObject* pResult = PyObject_CallObject(_pyFunc, pArgs);
//				string result = PyString_AsString(pResult);
//				cossb_log->log(log::loglevel::INFO, result);
//		}
//		else
//			cossb_log->log(log::loglevel::ERROR, "Not Callable");

		//PyObject* _result = PyObject_CallMethod(_module, "get_emotion", "sss", _url.c_str(), _key.c_str(), "test.jpg");
		//string result = PyString_AsString(_result);
		//cossb_log->log(log::loglevel::INFO, result);
		//PyObject* _dict = PyModule_GetDict(_module);
		//_pyFunc = PyDict_GetItemString(_dict, "get_emotion");PyErr_Print();
	}
	else{
		cossb_log->log(log::loglevel::ERROR, "No module to import");
		PyErr_Print();
	}

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



