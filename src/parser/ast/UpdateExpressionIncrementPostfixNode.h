/*
 * Copyright (c) 2016 Samsung Electronics Co., Ltd
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef UpdateExpressionIncrementPostfixNode_h
#define UpdateExpressionIncrementPostfixNode_h

#include "ExpressionNode.h"

namespace Escargot {

class UpdateExpressionIncrementPostfixNode : public ExpressionNode {
public:
    friend class ScriptParser;

    UpdateExpressionIncrementPostfixNode(Node* argument)
        : ExpressionNode()
    {
        m_argument = (ExpressionNode*)argument;
    }

    virtual ASTNodeType type() { return ASTNodeType::UpdateExpressionIncrementPostfix; }
    virtual void generateExpressionByteCode(ByteCodeBlock* codeBlock, ByteCodeGenerateContext* context)
    {
        m_argument->generateExpressionByteCode(codeBlock, context);
        codeBlock->pushCode(ToNumber(ByteCodeLOC(m_loc.index), context->getLastRegisterIndex()), context, this);
        size_t resultRegisterIndex = context->getLastRegisterIndex();
        size_t tempRegisterIndex = context->getRegister();
        codeBlock->pushCode(Move(ByteCodeLOC(m_loc.index), resultRegisterIndex, tempRegisterIndex), context, this);
        codeBlock->pushCode(Increment(ByteCodeLOC(m_loc.index), tempRegisterIndex), context, this);
        m_argument->generateStoreByteCode(codeBlock, context);
        context->giveUpRegister();
    }

protected:
    ExpressionNode* m_argument;
};
}

#endif
