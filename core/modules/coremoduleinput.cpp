/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2021 Pierre-Yves Rollo <dev@pyrollo.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "coremoduleinput.h"
#include "core/coreexceptions.h"
#include "core/coreschema.h"
#include "core/coresamplebuffer.h"

CoreModuleInput::CoreModuleInput(CoreSchema *schema) :
    CoreModule(schema), mSchemaInput(this, 0.0f)
{
    mOutputValue = newOutput("value");
}

CoreModuleInput::~CoreModuleInput()
{
    if (mSchema)
        setName("");
}

void CoreModuleInput::step()
{
    mOutputValue->setValue(mSchemaInput.value());
}

void CoreModuleInput::setName(std::string name)
{
    if (!mSchema)
        throw CoreNoSchemaEx();

    mSchema->setInputName(this, name);
}

