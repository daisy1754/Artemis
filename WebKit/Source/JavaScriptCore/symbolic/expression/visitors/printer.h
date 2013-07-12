/*
 * Copyright 2012 Aarhus University
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PRINTER_H
#define PRINTER_H

#include <string>

#include "symbolic/expr.h"

#include "symbolic/expression/visitor.h"


#ifdef ARTEMIS

namespace Symbolic
{

class Printer : public Visitor
{

public:
    Printer();

    void visit(SymbolicInteger* symbolicinteger);
    void visit(ConstantInteger* constantinteger);
    void visit(IntegerBinaryOperation* integerbinaryoperation);
    void visit(IntegerCoercion* integercoercion);
    void visit(SymbolicString* symbolicstring);
    void visit(ConstantString* constantstring);
    void visit(StringBinaryOperation* stringbinaryoperation);
    void visit(StringCoercion* stringcoercion);
    void visit(StringRegexReplace* stringregexreplace);
    void visit(StringReplace* stringreplace);
    void visit(SymbolicBoolean* symbolicboolean);
    void visit(ConstantBoolean* constantboolean);
    void visit(BooleanCoercion* booleancoercion);
    void visit(BooleanBinaryOperation* booleanbinaryoperation);

    inline std::string getResult() const {
        return m_result;
    }

private:
    std::string m_result;

};

}

#endif
#endif // PRINTER_H