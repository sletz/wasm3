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

#ifdef __cplusplus
extern "C" {
#endif
    
    static m3ApiRawFunction(m3_wasm3_absf)
    {
        m3ApiReturnType (int32_t)
        m3ApiGetArg(int32_t, val)
        m3ApiReturn(std::abs(val));
        return m3Err_none;
    }

    static m3ApiRawFunction(m3_wasm3_acosf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::acos(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_asinf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::asin(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_atanf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::atan(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_atan2f)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val1)
        m3ApiGetArg(float, val2)
        m3ApiReturn(std::atan2(val1, val2));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_cosf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::cos(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_expf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::exp(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_fmodf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val1)
        m3ApiGetArg(float, val2)
        m3ApiReturn(std::fmod(val1, val2));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_logf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::log(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_log10f)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::log10(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_powf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val1)
        m3ApiGetArg(float, val2)
        m3ApiReturn(std::pow(val1, val2));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_remainderf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val1)
        m3ApiGetArg(float, val2)
        m3ApiReturn(std::remainder(val1, val2));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_roundf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::round(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_sinf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::sin(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_tanf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::tan(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_acoshf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::acosh(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_asinhf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::asinh(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_atanhf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::atanh(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_coshf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::cosh(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_sinhf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::sinh(val));
        return m3Err_none;
    }
    
    static m3ApiRawFunction(m3_wasm3_tanhf)
    {
        m3ApiReturnType (float)
        m3ApiGetArg(float, val)
        m3ApiReturn(std::tanh(val));
        return m3Err_none;
    }
#ifdef __cplusplus
}
#endif

void wasm3_dsp_factory::addFunction(const char* name, const char* type, ModuleFun fun)
{
    if (v_FindFunction(fModule, name)) {
        M3Result result = m3_LinkRawFunction(fModule, "env", name, type, fun);
        if (result) FATAL("addFunction: %s", result);
    }
}

dsp* wasm3_dsp_factory::createDSPInstance()
{
   IM3Runtime instance = m3_NewRuntime(fEnv, 64*1024, NULL);
    if (!instance) FATAL_RET("m3_NewRuntime failed");
    
    M3Result result = m3_LoadModule(instance, fModule);
    if (result) FATAL_RET("m3_LoadModule: %s", result);
    
    uint32_t memorySize;
    char* dsp_memory = (char*)m3_GetMemory(instance, &memorySize, 0);
    
    cout << "memorySize " << memorySize << endl;
    string json = string(dsp_memory);
    
    cout << "JSON " << json << endl;
    if (!fDecoder) fDecoder = createJSONUIDecoder(json);

    addFunction("_abs", "i(i)", &m3_wasm3_absf);
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
    
    return new wasm3_dsp(this, instance, dsp_memory);
}

wasm3_dsp::wasm3_dsp(wasm3_dsp_factory* factory, IM3Runtime instance, char* memory)
:fFactory(factory), fInstance(instance), fMemory(memory)
{
    std::cout << "Libfaust version: " << fFactory->fDecoder->getLibVersion() << std::endl;
    std::cout << "Compilation options: " << fFactory->fDecoder->getCompileOptions() << std::endl;
    
    int ptr_size = sizeof(FAUSTFLOAT*);
    int sample_size = sizeof(FAUSTFLOAT);
    int buffer_size = 4096; // Max
    
    fInputs = new FAUSTFLOAT*[fFactory->fDecoder->getNumInputs()];
    fOutputs = new FAUSTFLOAT*[fFactory->fDecoder->getNumOutputs()];
    
    // DSP is placed first with index 0. Audio buffer start at the end of DSP.
    int audio_heap_ptr = fFactory->fDecoder->getDSPSize();
    
    // Setup pointers offset
    int audio_heap_ptr_inputs = audio_heap_ptr;
    int audio_heap_ptr_outputs = audio_heap_ptr_inputs + (fFactory->fDecoder->getNumInputs() * ptr_size);
    
    // Setup buffer offset
    int audio_heap_inputs = audio_heap_ptr_outputs + (fFactory->fDecoder->getNumOutputs() * ptr_size);
    int audio_heap_outputs = audio_heap_inputs + (fFactory->fDecoder->getNumInputs() * buffer_size * sample_size);
    
    if (fFactory->fDecoder->getNumInputs() > 0) {
        
        fWasmInputs = audio_heap_ptr_inputs;
        int* HEAP32 = reinterpret_cast<int*>(fMemory + audio_heap_ptr_inputs);
        FAUSTFLOAT* HEAPF32 = reinterpret_cast<FAUSTFLOAT*>(fMemory + audio_heap_inputs);
        
        for (int i = 0; i < fFactory->fDecoder->getNumInputs(); i++) {
            // Setup input buffer indexes for wasm side
            HEAP32[i] = audio_heap_inputs + (buffer_size * sample_size * i);
            // Setup input buffer pointers for runtime side
            fInputs[i] = HEAPF32 + (buffer_size * i);
        }
    }
    
    if (fFactory->fDecoder->getNumOutputs() > 0) {
        
        fWasmOutputs = audio_heap_ptr_outputs;
        int* HEAP32 = reinterpret_cast<int*>(fMemory + audio_heap_ptr_outputs);
        FAUSTFLOAT* HEAPF32 = reinterpret_cast<FAUSTFLOAT*>(fMemory + audio_heap_outputs);
        
        for (int i = 0; i < fFactory->fDecoder->getNumOutputs(); i++) {
            // Setup output buffer indexes for wasm side
            HEAP32[i] = audio_heap_outputs + (buffer_size * sample_size * i);
            // Setup output buffer pointers for runtime side
            fOutputs[i] =  HEAPF32 + (buffer_size * i);
        }
    }

    M3Result result = m3_FindFunction(&fCompute, fInstance, "compute");
    if (result) FATAL("m3_FindFunction: %s", result);
}

