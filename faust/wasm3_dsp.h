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

#ifndef __wasm3_dsp__
#define __wasm3_dsp__

#include <assert.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <unistd.h>

#include "faust/dsp/dsp.h"
#include "faust/gui/JSONUIDecoder.h"

#include "../source/m3.h"
#include "../source/m3_env.h"

using namespace std;

#define FATAL(msg, ...) { printf("Fatal: " msg "\n", ##__VA_ARGS__); return; }
#define FATAL_RET(msg, ...) { printf("Fatal: " msg "\n", ##__VA_ARGS__); return nullptr; }
#define FATAL_INT(msg, ...) { printf("Fatal: " msg "\n", ##__VA_ARGS__); return -1; }

struct wasm3_dsp_factory : public dsp_factory {
    
    IM3Environment fEnv;
    IM3Module fModule;
    const uint8_t* fBytes;
    
    JSONUITemplatedDecoder* fDecoder;
    
    //wasm3_module_t* fModule;
    //wasm3_byte_array fModuleNameBytes;
  
    //vector<wasm3_import_func_t*> fFunctionList;
    
    static void print_wasm3_error()
    {
        /*
        int error_len = wasm3_last_error_length();
        char* error_str = (char*)malloc(error_len);
        wasm3_last_error_message(error_str, error_len);
        printf("Error str: `%s`\n", error_str);
        free(error_str);
        */
    }
    
    /*
    // Int: 1 function
    static int _abs(wasm3_instance_context_t* ctx, int val) { return std::abs(val); }
    
    // Float: 14 functions
    static float _acosf(wasm3_instance_context_t* ctx, float val) { return std::acos(val); }
    static float _asinf(wasm3_instance_context_t* ctx, float val) { return std::asin(val); }
    static float _atanf(wasm3_instance_context_t* ctx, float val) { return std::atan(val); }
    static float _atan2f(wasm3_instance_context_t* ctx, float v1, float v2) { return std::atan2(v1, v2); }
    static float _cosf(wasm3_instance_context_t* ctx, float val) { return std::cos(val); }
    static float _expf(wasm3_instance_context_t* ctx, float val) { return std::exp(val); }
    static float _fmodf(wasm3_instance_context_t* ctx, float v1, float v2) { return std::fmod(v1, v2); }
    static float _logf(wasm3_instance_context_t* ctx, float val) { return std::log(val); }
    static float _log10f(wasm3_instance_context_t* ctx, float val) { return std::log10(val); }
    static float _powf(wasm3_instance_context_t* ctx, float v1, float v2) { return std::pow(v1, v2); }
    static float _remainderf(wasm3_instance_context_t* ctx, float v1, float v2) { return std::remainder(v1, v2); }
    static float _roundf(wasm3_instance_context_t* ctx, float val) { return std::round(val); }
    static float _sinf(wasm3_instance_context_t* ctx, float val) { return std::sin(val); }
    static float _tanf(wasm3_instance_context_t* ctx, float val) { return std::tan(val); }
    
    // Hyperbolic: 6 functions
    static float _acoshf(wasm3_instance_context_t* ctx, float val) { return std::acosh(val); }
    static float _asinhf(wasm3_instance_context_t* ctx, float val) { return std::asinh(val); }
    static float _atanhf(wasm3_instance_context_t* ctx, float val) { return std::atanh(val); }
    static float _coshf(wasm3_instance_context_t* ctx, float val) { return std::cosh(val); }
    static float _sinhf(wasm3_instance_context_t* ctx, float val) { return std::sinh(val); }
    static float _tanhf(wasm3_instance_context_t* ctx, float val) { return std::tanh(val); }
    
    // Double: 14 functions
    static double _acos(wasm3_instance_context_t* ctx, double val) { return std::acos(val); }
    static double _asin(wasm3_instance_context_t* ctx, double val) { return std::asin(val); }
    static double _atan(wasm3_instance_context_t* ctx, double val) { return std::atan(val); }
    static double _atan2(wasm3_instance_context_t* ctx, double v1, double v2) { return std::atan2(v1, v2); }
    static double _cos(wasm3_instance_context_t* ctx, double val) { return std::cos(val); }
    static double _exp(wasm3_instance_context_t* ctx, double val) { return std::exp(val); }
    static double _fmod(wasm3_instance_context_t* ctx, double v1, double v2) { return std::fmod(v1, v2); }
    static double _log(wasm3_instance_context_t* ctx, double val) { return std::log(val); }
    static double _log10(wasm3_instance_context_t* ctx, double val) { return std::log10(val); }
    static double _pow(wasm3_instance_context_t* ctx, double v1, double v2) { return std::pow(v1, v2); }
    static double _remainder(wasm3_instance_context_t* ctx, double v1, double v2) { return std::remainder(v1, v2); }
    static double _round(wasm3_instance_context_t* ctx, double val) { return std::round(val); }
    static double _sin(wasm3_instance_context_t* ctx, double val) { return std::sin(val); }
    static double _tan(wasm3_instance_context_t* ctx, double val) { return std::tan(val); }
    
    // Hyperbolic: 6 functions
    static float _acosh(wasm3_instance_context_t* ctx, float val) { return std::acosh(val); }
    static float _asinh(wasm3_instance_context_t* ctx, float val) { return std::asinh(val); }
    static float _atanh(wasm3_instance_context_t* ctx, float val) { return std::atanh(val); }
    static float _cosh(wasm3_instance_context_t* ctx, float val) { return std::cosh(val); }
    static float _sinh(wasm3_instance_context_t* ctx, float val) { return std::sinh(val); }
    static float _tanh(wasm3_instance_context_t* ctx, float val) { return std::tanh(val); }
    
    // Float
    typedef float (*math_unary_float_fun)(wasm3_instance_context_t* ctx, float val);
    typedef float (*math_binary_float_fun)(wasm3_instance_context_t* ctx, float val1, float val2);
    
    // double
    typedef double (*math_unary_double_fun)(wasm3_instance_context_t* ctx, double val);
    typedef double (*math_binary_double_fun)(wasm3_instance_context_t* ctx, double val1, double val2);
    
    typedef int (*math_unary_int_fun)(wasm3_instance_context_t* ctx, int val);

    template <class FUN_TYPE, wasm3_value_tag REAL>
    wasm3_import_t createRealUnary(const char* import_name, FUN_TYPE fun)
    {
        wasm3_value_tag params_sig[] = { REAL };
        wasm3_value_tag returns_sig[] = { REAL };
        
        wasm3_byte_array import_name_bytes;
        import_name_bytes.bytes = (const uint8_t*)import_name;
        import_name_bytes.bytes_len = strlen(import_name);
        
        wasm3_import_func_t* func = wasm3_import_func_new((void (*)(void *))fun, params_sig, 1, returns_sig, 1);
        fFunctionList.push_back(func);
        
        wasm3_import_t func_import;
        func_import.module_name = fModuleNameBytes;
        func_import.import_name = import_name_bytes;
        func_import.tag = wasm3_import_export_kind::WASM_FUNCTION;
        func_import.value.func = func;
        
        return func_import;
    }
    
    template <class FUN_TYPE, wasm3_value_tag REAL>
    wasm3_import_t createRealBinary(const char* import_name, FUN_TYPE fun)
    {
        wasm3_value_tag params_sig[] = { REAL, REAL };
        wasm3_value_tag returns_sig[] = { REAL };
        
        wasm3_byte_array import_name_bytes;
        import_name_bytes.bytes = (const uint8_t*)import_name;
        import_name_bytes.bytes_len = strlen(import_name);
        
        wasm3_import_func_t* func = wasm3_import_func_new((void (*)(void *))fun, params_sig, 2, returns_sig, 1);
        fFunctionList.push_back(func);
        
        wasm3_import_t func_import;
        func_import.module_name = fModuleNameBytes;
        func_import.import_name = import_name_bytes;
        func_import.tag = wasm3_import_export_kind::WASM_FUNCTION;
        func_import.value.func = func;
        
        return func_import;
    }
    
    wasm3_import_t createFloatUnary(const char* import_name, math_unary_float_fun fun)
    {
        return createRealUnary<math_unary_float_fun, wasm3_value_tag::WASM_F32>(import_name, fun);
    }
    wasm3_import_t createDoubleUnary(const char* import_name, math_unary_double_fun fun)
    {
        return createRealUnary<math_unary_double_fun, wasm3_value_tag::WASM_F64>(import_name, fun);
    }
    
    wasm3_import_t createFloatBinary(const char* import_name, math_binary_float_fun fun)
    {
        return createRealBinary<math_binary_float_fun, wasm3_value_tag::WASM_F32>(import_name, fun);
    }
    wasm3_import_t createDoubleBinary(const char* import_name, math_binary_double_fun fun)
    {
        return createRealBinary<math_binary_double_fun, wasm3_value_tag::WASM_F64>(import_name, fun);
    }
    
    wasm3_import_t createIntUnary(const char* import_name, math_unary_int_fun fun)
    {
        wasm3_value_tag params_sig[] = { wasm3_value_tag::WASM_I32 };
        wasm3_value_tag returns_sig[] = { wasm3_value_tag::WASM_I32 };
        
        wasm3_byte_array import_name_bytes;
        import_name_bytes.bytes = (const uint8_t*)import_name;
        import_name_bytes.bytes_len = strlen(import_name);
        
        wasm3_import_func_t* func = wasm3_import_func_new((void (*)(void *))fun, params_sig, 1, returns_sig, 1);
        fFunctionList.push_back(func);
        
        wasm3_import_t func_import;
        func_import.module_name = fModuleNameBytes;
        func_import.import_name = import_name_bytes;
        func_import.tag = wasm3_import_export_kind::WASM_FUNCTION;
        func_import.value.func = func;
        
        return func_import;
    }
    */

    wasm3_dsp_factory(const string& filename)
    {
        fDecoder = nullptr;
        
        std::ifstream is(filename, std::ifstream::binary);
        is.seekg(0, is.end);
        int len = is.tellg();
        is.seekg(0, is.beg);
        fBytes = new uint8_t[len];
        is.read((char*)fBytes, len);
        
        fEnv = m3_NewEnvironment();
        if (!fEnv) FATAL("m3_NewEnvironment failed");
        
        M3Result result = m3_ParseModule(fEnv, &fModule, fBytes, len);
        if (result) FATAL("m3_ParseModule: %s", result);
    }
    
    virtual ~wasm3_dsp_factory()
    {
        delete fDecoder;
        m3_FreeModule(fModule);
        m3_FreeEnvironment(fEnv);
        delete[] fBytes;
        
        /*
        wasm3_module_destroy(fModule);
        for (auto& it : fFunctionList) {
            wasm3_import_func_destroy(it);
        }
        */
    }
    
    std::string getName() { return fDecoder->getName(); }
    
    std::string getSHAKey() { return ""; }
    
    std::string getDSPCode() { return ""; }
    
    std::string getCompileOptions() { return fDecoder->getCompileOptions(); }
    
    std::vector<std::string> getLibraryList() { return fDecoder->getLibraryList(); }
    
    std::vector<std::string> getIncludePathnames() { return fDecoder->getIncludePathnames(); }
    
    dsp* createDSPInstance();
    
    void setMemoryManager(dsp_memory_manager* manager) {}
    
    dsp_memory_manager* getMemoryManager() { return nullptr; }
    
};

class wasm3_dsp : public dsp {
    
    private:
    
        wasm3_dsp_factory* fFactory;
    
        IM3Runtime fInstance;
        IM3Function fCompute;
        char* fMemory;
    
        int fWasmInputs;        // Index in wasm memory
        int fWasmOutputs;       // Index in wasm memory
        
        FAUSTFLOAT** fInputs;   // Wasm memory mapped to pointers
        FAUSTFLOAT** fOutputs;  // Wasm memory mapped to pointers
    
    public:

        wasm3_dsp(wasm3_dsp_factory* factory, IM3Runtime instance, char* memory);
    
        virtual ~wasm3_dsp()
        {
            m3_FreeRuntime(fInstance);
        }
        
        virtual int getNumInputs()
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "getNumInputs");
            if (result) FATAL_INT("m3_FindFunction: %s", result);
  
            const char* i_argv[2] = { "0", NULL };
            result = m3_CallWithArgs(f, 1, i_argv);

            uint64_t value = *(uint64_t*)(fInstance->stack);
            printf("Result: %lld\n", value);
            return value;
        }
        
        virtual int getNumOutputs()
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "getNumOutputs");
            if (result) FATAL_INT("m3_FindFunction: %s", result);
            
            const char* i_argv[2] = { "0", NULL };
            result = m3_CallWithArgs(f, 1, i_argv);
            
            uint64_t value = *(uint64_t*)(fInstance->stack);
            printf("Result: %lld\n", value);
            return value;
        }
        
        virtual void buildUserInterface(UI* ui_interface)
        {
            fFactory->fDecoder->buildUserInterface(ui_interface, fMemory);
        }
        
        virtual int getSampleRate()
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "getSampleRate");
            if (result) FATAL_INT("m3_FindFunction: %s", result);
            
            const char* i_argv[2] = { "0", NULL };
            result = m3_CallWithArgs(f, 1, i_argv);
            
            uint64_t value = *(uint64_t*)(fInstance->stack);
            printf("Result: %lld\n", value);
            return value;
        }
        
        virtual void init(int sample_rate)
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "init");
            if (result) FATAL("m3_FindFunction: %s", result);
            
            const char* i_argv[3] = { "0", to_string(sample_rate).c_str(), NULL };
            result = m3_CallWithArgs(f, 2, i_argv);
        }
        
        virtual void instanceInit(int sample_rate)
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "instanceInit");
            if (result) FATAL("m3_FindFunction: %s", result);
            
            const char* i_argv[3] = { "0", to_string(sample_rate).c_str(), NULL };
            result = m3_CallWithArgs(f, 2, i_argv);
        }
        
        virtual void instanceConstants(int sample_rate)
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "instanceConstants");
            if (result) FATAL("m3_FindFunction: %s", result);
            
            const char* i_argv[3] = { "0", to_string(sample_rate).c_str(), NULL };
            result = m3_CallWithArgs(f, 2, i_argv);
        }
        
        virtual void instanceResetUserInterface()
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "instanceResetUserInterface");
            if (result) FATAL("m3_FindFunction: %s", result);
            
            const char* i_argv[2] = { "0", NULL };
            result = m3_CallWithArgs(f, 1, i_argv);
        }
        
        virtual void instanceClear()
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "instanceClear");
            if (result) FATAL("m3_FindFunction: %s", result);
            
            const char* i_argv[2] = { "0", NULL };
            result = m3_CallWithArgs(f, 1, i_argv);
        }
       
        virtual dsp* clone()
        {
            assert(false);
            return nullptr;
        }
       
        virtual void metadata(Meta* m)
        {
            fFactory->fDecoder->metadata(m);
        }
        
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            // Copy audio inputs
            for (int i = 0; i < fFactory->fDecoder->getNumInputs(); i++) {
                memcpy(fInputs[i], inputs[i], sizeof(FAUSTFLOAT) * count);
            }
            
            // Call wasm code
            const char* i_argv[5] = { "0", to_string(count).c_str(), to_string(fWasmInputs).c_str(), to_string(fWasmOutputs).c_str(), NULL };
            M3Result result = m3_CallWithArgs(fCompute, 4, i_argv);
            
            // Copy audio outputs
            for (int i = 0; i < fFactory->fDecoder->getNumOutputs(); i++) {
                memcpy(outputs[i], fOutputs[i], sizeof(FAUSTFLOAT) * count);
            }
        }
        
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(count, inputs, outputs);
        }

};

#endif
