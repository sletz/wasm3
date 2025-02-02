/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#include "wasm3_dsp.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
    
    // Integer
    static m3ApiRawFunction(m3_wasm3_abs)
    {
        m3ApiReturnType (int32_t)
        m3ApiGetArg(int32_t, val)
        m3ApiReturn(std::abs(val));
        m3ApiSuccess();
    }

    // Float versions
    static m3ApiRawFunction(m3_wasm3_acosf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::acos(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_asinf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::asin(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_atanf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::atan(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_atan2f)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val1)
        m3ApiGetArg(float, val2)
        m3ApiReturn(std::atan2(val1, val2));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_cosf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::cos(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_expf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::exp(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_fmodf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val1)
        m3ApiGetArg(float, val2)
        m3ApiReturn(std::fmod(val1, val2));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_logf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::log(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_log10f)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::log10(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_powf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val1)
        m3ApiGetArg(float, val2)
        m3ApiReturn(std::pow(val1, val2));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_remainderf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val1)
        m3ApiGetArg(float, val2)
        m3ApiReturn(std::remainder(val1, val2));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_roundf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::round(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_sinf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::sin(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_tanf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::tan(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_acoshf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::acosh(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_asinhf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::asinh(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_atanhf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::atanh(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_coshf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::cosh(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_sinhf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::sinh(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_tanhf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::tanh(val));
        m3ApiSuccess();
    }
    
    // Double versions
    static m3ApiRawFunction(m3_wasm3_acos)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::acos(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_asin)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::asin(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_atan)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::atan(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_atan2)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val1)
        m3ApiGetArg(double, val2)
        m3ApiReturn(std::atan2(val1, val2));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_cos)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::cos(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_exp)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::exp(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_fmod)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val1)
        m3ApiGetArg(double, val2)
        m3ApiReturn(std::fmod(val1, val2));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_log)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::log(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_log10)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::log10(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_pow)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val1)
        m3ApiGetArg(double, val2)
        m3ApiReturn(std::pow(val1, val2));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_remainder)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val1)
        m3ApiGetArg(double, val2)
        m3ApiReturn(std::remainder(val1, val2));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_round)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::round(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_sin)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::sin(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_tan)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::tan(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_acosh)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::acosh(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_asinh)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::asinh(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_atanh)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::atanh(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_cosh)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::cosh(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_sinh)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::sinh(val));
        m3ApiSuccess();
    }
    
    static m3ApiRawFunction(m3_wasm3_tanh)
    {
        m3ApiReturnType (double)
        m3ApiGetArg(double, val)
        m3ApiReturn(std::tanh(val));
        m3ApiSuccess();
    }
    
#ifdef __cplusplus
}
#endif

dsp* wasm3_dsp_factory::createDSPInstance()
{
    return new wasm3_dsp(this);
}

wasm3_dsp::wasm3_dsp(wasm3_dsp_factory* factory):wasm_dsp_imp(factory)
{
    fEnv = m3_NewEnvironment();
    if (!fEnv) FATAL("m3_NewEnvironment failed");
    
    M3Result result = m3_ParseModule(fEnv, &fModule, factory->fBytes, factory->fLen);
    if (result) FATAL("m3_ParseModule: %s", result);
    
    fInstance = m3_NewRuntime(fEnv, 64*1024, NULL);
    if (!fInstance) FATAL("m3_NewRuntime failed");
    
    result = m3_LoadModule(fInstance, fModule);
    if (result) FATAL("m3_LoadModule: %s", result);
    
    uint32_t memorySize;
    fMemory = (char*)m3_GetMemory(fInstance, &memorySize, 0);
    
    initDecoder();
    
    if (fFactory->fDecoder->hasCompileOption("-double")) {
        addFunction("_abs", "i(i)", &m3_wasm3_abs);
        addFunction("_acos", "F(F)", &m3_wasm3_acos);
        addFunction("_asin", "F(F)", &m3_wasm3_asin);
        addFunction("_atan", "F(F)", &m3_wasm3_atan);
        addFunction("_atan2", "F(FF)", &m3_wasm3_atan2);
        addFunction("_cos", "F(F)", &m3_wasm3_cos);
        addFunction("_exp", "F(F)", &m3_wasm3_exp);
        addFunction("_fmod", "F(FF)", &m3_wasm3_fmod);
        addFunction("_log", "F(F)", &m3_wasm3_log);
        addFunction("_log10", "F(F)", &m3_wasm3_log10);
        addFunction("_pow", "F(FF)", &m3_wasm3_pow);
        addFunction("_remainder", "F(FF)", &m3_wasm3_remainder);
        addFunction("_round", "F(F)", &m3_wasm3_round);
        addFunction("_sin", "F(F)", &m3_wasm3_sin);
        addFunction("_tan", "F(F)", &m3_wasm3_tan);
        addFunction("_acosh", "F(F)", &m3_wasm3_acosh);
        addFunction("_asinh", "F(F)", &m3_wasm3_asinh);
        addFunction("_atanh", "F(F)", &m3_wasm3_atanh);
        addFunction("_cosh", "F(F)", &m3_wasm3_cosh);
        addFunction("_sinh", "F(F)", &m3_wasm3_sinh);
        addFunction("_tanh", "F(F)", &m3_wasm3_tanh);
    } else {
        addFunction("_abs", "i(i)", &m3_wasm3_abs);
        addFunction("_acosf", "f(f)", &m3_wasm3_acosf);
        addFunction("_asinf", "f(f)", &m3_wasm3_asinf);
        addFunction("_atanf", "f(f)", &m3_wasm3_atanf);
        addFunction("_atan2f", "f(ff)", &m3_wasm3_atan2f);
        addFunction("_cosf", "f(f)", &m3_wasm3_cosf);
        addFunction("_expf", "f(f)", &m3_wasm3_expf);
        addFunction("_fmodf", "f(ff)", &m3_wasm3_fmodf);
        addFunction("_logf", "f(f)", &m3_wasm3_logf);
        addFunction("_log10f", "f(f)", &m3_wasm3_log10f);
        addFunction("_powf", "f(ff)", &m3_wasm3_powf);
        addFunction("_remainderf", "f(ff)", &m3_wasm3_remainderf);
        addFunction("_roundf", "f(f)", &m3_wasm3_roundf);
        addFunction("_sinf", "f(f)", &m3_wasm3_sinf);
        addFunction("_tanf", "f(f)", &m3_wasm3_tanf);
        addFunction("_acoshf", "f(f)", &m3_wasm3_acoshf);
        addFunction("_asinhf", "f(f)", &m3_wasm3_asinhf);
        addFunction("_atanhf", "f(f)", &m3_wasm3_atanhf);
        addFunction("_coshf", "f(f)", &m3_wasm3_coshf);
        addFunction("_sinhf", "f(f)", &m3_wasm3_sinhf);
        addFunction("_tanhf", "f(f)", &m3_wasm3_tanhf);
    }
    
    result = m3_FindFunction(&fCompute, fInstance, "compute");
    if (result) FATAL("m3_FindFunction: %s", result);
}
