/******************************************************************
* File:        ScriptFunction.h
* Description: implement ScriptFunction class and its function factory
*              class. Instance of ScriptFunction is an expression unit
*              has type is function and its behavior is defined in
*              the script, not in C++ part.
* Author:      Vincent Pham
*
* Copyright (c) 2018 VincentPT.
** Distributed under the MIT License (http://opensource.org/licenses/MIT)
**
*
**********************************************************************/

#include "ScriptFunction.h"
#include "ScriptCompiler.h"
#include <array>

namespace ffscript {
	ScriptFunction::ScriptFunction(const std::string& name, const ScriptType& returnType, int registeredParamCount) : Function(name, EXP_UNIT_ID_USER_FUNC, FUNCTION_PRIORITY_USER_FUNCTION, returnType), _registeredParamCount(registeredParamCount)
	{
		params.reserve(registeredParamCount);
	}


	ScriptFunction::~ScriptFunction(){
	}

	int ScriptFunction::pushParam(ExecutableUnitRef pExeUnit) {
		params.push_back(pExeUnit);
		return _registeredParamCount - (int)params.size();
	}

	ExecutableUnitRef ScriptFunction::popParam() {
		ExecutableUnitRef back = params.back();
		params.pop_back();
		return back;
	}
	const ExecutableUnitRef& ScriptFunction::getChild(int index) const {
		return params[index];
	}

	ExecutableUnitRef& ScriptFunction::getChild(int index) {
		return params[index];
	}

	int ScriptFunction::getChildCount() {
		return (int)params.size();
	}

	ScriptFunctionFactory::ScriptFunctionFactory(const char* functionName, ScriptCompiler* scriptCompiler) : FunctionFactory(functionName, scriptCompiler) {

	}
	ScriptFunctionFactory::~ScriptFunctionFactory() {}

	Function* ScriptFunctionFactory::createFunction(const std::string& name, int id) {
		ScriptCompiler* scriptCompiler = this->getCompiler();
		ScriptFunction* scriptFunction = new ScriptFunction(name, this->getReturnType(), this->getParamCount());

		return scriptFunction;
	}
}