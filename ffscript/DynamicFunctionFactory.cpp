/******************************************************************
* File:        DynamicFunctionFactory.cpp
* Description: implement DynamicFunctionFactory class.  A factory class
*              that create dynamic parameter function unit from DFunction2
*              function object.
* Author:      Vincent Pham
*
* (C) Copyright 2018, The ffscript project, All rights reserved.
** Distributed under the MIT License (http://opensource.org/licenses/MIT)
**
*
**********************************************************************/

#include "stdafx.h"
#include "DynamicFunctionFactory.h"
#include "ScriptCompiler.h"
//#include "Function.h"

namespace ffscript {
	DynamicFunctionFactory::DynamicFunctionFactory(const char* returnType, DFunction2* nativeFunction, ScriptCompiler* scriptCompiler) :
		FunctionFactory(nullptr, scriptCompiler),
		_returnType(returnType), _nativeFunction(nativeFunction)
	{
		this->setReturnType(ScriptType::parseType(scriptCompiler, _returnType));
	}


	DynamicFunctionFactory::~DynamicFunctionFactory()
	{
	}

	Function* DynamicFunctionFactory::createFunction(const std::string& name, int id) {
		NativeFunction* function = new DynamicParamFunction(name, EXP_UNIT_ID_DYNAMIC_FUNC, FUNCTION_PRIORITY_USER_FUNCTION, getReturnType());
		function->setNative(_nativeFunction);
		return function;
	}
}