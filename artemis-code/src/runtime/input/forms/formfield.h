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
#ifndef FORMFIELD_H
#define FORMFIELD_H

#include <QSet>
#include <QString>
#include <QSharedPointer>

#include "formfieldtypes.h"
#include "runtime/input/events/domelementdescriptor.h"

namespace artemis
{

class FormField
{

public:
    FormField(FormFieldTypes fieldType, DOMElementDescriptorConstPtr domElement, QSet<QString> inputOptions);
    FormField(FormFieldTypes fieldType, DOMElementDescriptorConstPtr domElement);

    inline const DOMElementDescriptorConstPtr getDomElement() const {
        return mElementDescriptor;
    }

    FormFieldTypes getType() const;
    QSet<QString> getInputOptions() const;

    QDebug friend operator<<(QDebug dbg, const FormField& f);

private:
    DOMElementDescriptorConstPtr mElementDescriptor;
    const FormFieldTypes mFieldType;
    QSet<QString> mDefaultInputs;

};

typedef QSharedPointer<FormField> FormFieldPtr;
typedef QSharedPointer<const FormField> FormFieldConstPtr;

}

#endif // FORMFIELD_H