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
	_url = get_profile()->get(profile::section::property, "url").asString("https://localhost");
	_key = get_profile()->get(profile::section::property, "key").asString("");
	_file = get_profile()->get(profile::section::property, "file").asString("capture.jpg");

	//set default emotion
	_emotion["anger"] = 0.0;
	_emotion["contempt"] = 0.0;
	_emotion["disgust"] = 0.0;
	_emotion["fear"] = 0.0;
	_emotion["happiness"] = 0.0;
	_emotion["neutral"] = 0.0;
	_emotion["sadness"] = 0.0;
	_emotion["surprise"] = 0.0;

	cossb_log->log(log::loglevel::INFO, fmt::format("MSAPI URL : {}", _url));
	cossb_log->log(log::loglevel::INFO, fmt::format("MSAPI Key : {}", _key));

	return true;
}

bool msapi_face::run()
{
	Py_Initialize();
	if(!Py_IsInitialized())
		return false;

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
				//cossb_log->log(log::loglevel::INFO, fmt::format("Emotion Data : {}", result));

				//process json string
				_api_data = nlohmann::json::parse(result.c_str());
				if(_api_data.find("faceAttributes")!=_api_data.end()){
					_emotion["anger"] = _api_data["faceAttributes"]["emotion"]["anger"];
					_emotion["contempt"] = _api_data["faceAttributes"]["emotion"]["contempt"];
					_emotion["disgust"] = _api_data["faceAttributes"]["emotion"]["disgust"];
					_emotion["fear"] = _api_data["faceAttributes"]["emotion"]["fear"];
					_emotion["happiness"] = _api_data["faceAttributes"]["emotion"]["happiness"];
					_emotion["neutral"] = _api_data["faceAttributes"]["emotion"]["neutral"];
					_emotion["sadness"] = _api_data["faceAttributes"]["emotion"]["sadness"];
					_emotion["surprise"] = _api_data["faceAttributes"]["emotion"]["surprise"];

					//message publish
					cossb::message msg(this, base::msg_type::DATA);
					msg.pack(_emotion);
					cossb_broker->publish("face_emotion", msg);
					cossb_log->log(log::loglevel::INFO, fmt::format("Published {} Emotion Data", _emotion.size()));
				}
				else
					cossb_log->log(log::loglevel::ERROR, "cannot find faceAttributes");
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

	Py_Finalize();

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



