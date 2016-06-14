/**
 * @file		interface.hpp
 * @brief		interface headers
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 7
 * @details		COSSB interface headers
 */

#ifndef _COSSB_INTERFACE_HPP_
#define _COSSB_INTERFACE_HPP_

#if defined(__unix__) || defined(__gnu_linux__) || defined(linux) || defined(__linux__)

#include <interface/icomponent.hpp>
#include <interface/iauth.hpp>
#include <interface/iprofile.hpp>
#include <interface/isql.hpp>
#include <interface/ilog.hpp>
#include <interface/icomm.hpp>
#include <interface/iutility.hpp>
#include <interface/iservice.hpp>
#include <base/task.hpp>
#include <base/message.hpp>


#endif

#endif /* _COSSB_INTERFACE_HPP_ */
