#pragma once

#include "WB_Render/include/Config.h"

#include "Interface/Render.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

namespace WB
{
    class RENDER_API Render : public IRender
    {
    public:
        /***************************************************************************************************************
         * Constructor & Destructor
        /**************************************************************************************************************/

        Render() = default;
        ~Render() override = default;
    };
}