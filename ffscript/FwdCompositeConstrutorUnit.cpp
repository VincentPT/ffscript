/******************************************************************
* File:        FwdCompositeConstrutorUnit.cpp
* Description: implement FwdConstrutorUnit and
*              FwdCompositeConstrutorUnit classes. These classes
*              contain a constructor unit inside but it also return
*              the reference of the object need to be constructed
*              not the void type like contructor unit do.
* Author:      Vincent Pham
*
* Copyright (c) 2018 VincentPT.
** Distributed under the MIT License (http://opensource.org/licenses/MIT)
**
*
**********************************************************************/

#include "FwdCompositeConstrutorUnit.h"

namespace ffscript {
	FwdConstrutorUnit::FwdConstrutorUnit(const FunctionRef& constructorUnit) :
		_constructorUnit(constructorUnit),
		Function("_create_object_by_ctor", EXP_UNIT_ID_CREATE_OBJECT, FUNCTION_PRIORITY_USER_FUNCTION, "TBD")
	{
	}

	FwdConstrutorUnit::FwdConstrutorUnit(const FunctionRef& constructorUnit, int functionType) :
		_constructorUnit(constructorUnit),
		Function("_create_object_by_ctor", functionType, FUNCTION_PRIORITY_USER_FUNCTION, "TBD")
	{
	}

	FwdConstrutorUnit::~FwdConstrutorUnit()
	{
	}

	int FwdConstrutorUnit::pushParam(ExecutableUnitRef pExeUnit) {
		return _constructorUnit->pushParam(pExeUnit);
	}

	ExecutableUnitRef FwdConstrutorUnit::popParam() {
		return _constructorUnit->popParam();
	}

	const ExecutableUnitRef& FwdConstrutorUnit::getChild(int index) const {
		return _constructorUnit->getChild(index);
	}

	ExecutableUnitRef& FwdConstrutorUnit::getChild(int index) {
		return _constructorUnit->getChild(index);
	}

	int FwdConstrutorUnit::getChildCount() {
		return _constructorUnit->getChildCount();
	}

	FunctionRef& FwdConstrutorUnit::getConstructorUnit() {
		return _constructorUnit;
	}

	///
	///
	///
	FwdCompositeConstrutorUnit::FwdCompositeConstrutorUnit(const FunctionRef& constructorUnit, const std::vector<ScriptTypeRef>& argumentTypes, const ParamCastingList& castingList) :
		_argumentTypes(argumentTypes),
		_castingList(castingList),
		FwdConstrutorUnit(constructorUnit, EXP_UNIT_ID_CREATE_OBJECT_COMPOSITE)
	{
	}


	FwdCompositeConstrutorUnit::~FwdCompositeConstrutorUnit()
	{
	}

	int FwdCompositeConstrutorUnit::pushParam(ExecutableUnitRef pExeUnit) {		
		if (pExeUnit->getType() != EXP_UNIT_ID_DYNAMIC_FUNC) {
			// throw exception here
		}

		auto collector = dynamic_cast<DynamicParamFunction*>(pExeUnit.get());
		auto& params = collector->getParams();

		if ((params.size() + 1) != _argumentTypes.size()) {
			// throw exception here
		}
		if ((params.size() + 1) != _castingList.size()) {
			// throw exception here
		}
		auto jt = _castingList.begin();
		auto ait = _argumentTypes.begin();

		// ignore first argument because it was already supplied inside constructorUnit
		jt++;
		ait++;
		for (auto it = params.begin(); it != params.end(); it++, jt++, ait++) {
			auto& castingInfo = *jt;
			auto& castingFunction = castingInfo.castingFunction;
			if (castingFunction) {
				// set parameter for casting function
				castingFunction->pushParam(*it);
				// set return type for casting function
				castingFunction->setReturnType(*(ait->get()));
				_constructorUnit->pushParam(castingFunction);
			}
			else {
				_constructorUnit->pushParam(*it);
			}
		}

		return 0;
	}
}