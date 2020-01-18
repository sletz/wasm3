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

dsp* wasm3_dsp_factory::createDSPInstance()
{
    // Env
    const char* module_name = "env";
    
    /*
    fModuleNameBytes.bytes = (const uint8_t*)module_name;
    fModuleNameBytes.bytes_len = strlen(module_name);
    
    wasm3_import_t imports[] = {
        
        // Int
        createIntUnary("_abs", _abs),
        
        // Float
        createFloatUnary("_acosf", _acosf),
        createFloatUnary("_asinf", _asinf),
        createFloatUnary("_atanf", _atanf),
        createFloatBinary("_atan2f", _atan2f),
        createFloatUnary("_cosf", _cosf),
        createFloatUnary("_expf", _expf),
        createFloatBinary("_fmodf", _fmodf),
        createFloatUnary("_logf", _logf),
        createFloatUnary("_log10f", _log10f),
        createFloatBinary("_powf", _powf),
        createFloatBinary("_remainderf", _remainderf),
        createFloatUnary("_roundf", _roundf),
        createFloatUnary("_sinf", _sinf),
        createFloatUnary("_tanf", _tanf),
        
        // Hyperbolic
        createFloatUnary("_acoshf", _acoshf),
        createFloatUnary("_asinhf", _asinhf),
        createFloatUnary("_atanhf", _atanhf),
        createFloatUnary("_coshf", _coshf),
        createFloatUnary("_sinhf", _sinhf),
        createFloatUnary("_tanhf", _tanhf),
        
        // Double
        createDoubleUnary("_acos", _acos),
        createDoubleUnary("_asin", _asin),
        createDoubleUnary("_atan", _atan),
        createDoubleBinary("_atan2", _atan2),
        createDoubleUnary("_cos", _cos),
        createDoubleUnary("_exp", _exp),
        createDoubleBinary("_fmod", _fmod),
        createDoubleUnary("_log", _log),
        createDoubleUnary("_log10", _log10),
        createDoubleBinary("_pow", _pow),
        createDoubleBinary("_remainder", _remainder),
        createDoubleUnary("_round", _round),
        createDoubleUnary("_sin", _sin),
        createDoubleUnary("_tan", _tan),
        
        // Hyperbolic
        createFloatUnary("_acosh", _acosh),
        createFloatUnary("_asinh", _asinh),
        createFloatUnary("_atanh", _atanh),
        createFloatUnary("_cosh", _cosh),
        createFloatUnary("_sinh", _sinh),
        createFloatUnary("_tanh", _tanh),
    };
    
    wasm3_instance_t* instance = nullptr;
    wasm3_result_t instantiate_result = wasm3_module_instantiate(fModule, &instance, imports, 1 + (14 + 6) * 2);
    if (instantiate_result != wasm3_result_t::wasm3_OK) print_wasm3_error();
    
    assert(instantiate_result == wasm3_result_t::wasm3_OK);
    
    // Get all exports.
    wasm3_exports_t* exports = nullptr;
    wasm3_instance_exports(instance, &exports);
    
    // Memory is as index 11
    wasm3_export_t* export1 = wasm3_exports_get(exports, 11);
    wasm3_import_export_kind kind = wasm3_export_kind(export1);
    assert(kind == wasm3_import_export_kind::WASM_MEMORY);
    
    // Cast the export into a memory.
    wasm3_memory_t* memory;
    wasm3_result_t export_to_memory_result = wasm3_export_to_memory(export1, &memory);
    assert(export_to_memory_result == wasm3_result_t::wasm3_OK);
    
    // JSON is located at offset 0 in the memory segment
    char* dsp_memory = (char*)wasm3_memory_data(memory);
    string json = string(dsp_memory);
    
    // Creates fDecoder onde
    if (!fDecoder) fDecoder = createJSONUIDecoder(json);

    wasm3_exports_destroy(exports);
    
    return new wasm3_dsp(this, instance, dsp_memory);
    */
    
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

