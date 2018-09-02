#pragma once
#include "ContextScope.h"

namespace ffscript {
	class FunctionScope;
	class LoopScope :
		public ContextScope
	{
		CommandUnitBuilder* _conditionExpression;
		CommandPointer _conditionCommnand;
	public:
		LoopScope(ContextScope* parent, FunctionScope* functionScope);
		virtual ~LoopScope();

		virtual const wchar_t* parse(const wchar_t* text, const wchar_t* end);
		CommandUnitBuilder* getConditionExpression() const;
		virtual void buildExitScopeCodeCommands(CommandList& commandList) const;
		virtual bool updateCodeForControllerCommands(Program* program);
	};
}
