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
#include <fstream>
#include <cmath>
#include <vector>
#include <unistd.h>
#include <stdint.h>

#include "faust/dsp/wasm-dsp-imp.h"

#include "../source/wasm3.h"
#include "../source/m3_env.h"
#include "../source/m3_api_defs.h"

#define FATAL(msg, ...) { printf("Fatal: " msg "\n", ##__VA_ARGS__); return; }
#define FATAL_RET(msg, ...) { printf("Fatal: " msg "\n", ##__VA_ARGS__); return nullptr; }
#define FATAL_INT(msg, ...) { printf("Fatal: " msg "\n", ##__VA_ARGS__); return -1; }

struct wasm3_dsp_factory : public wasm_dsp_factory_imp {
    
    const uint8_t* fBytes;
    int fLen;
    
    wasm3_dsp_factory(const std::string& filename):wasm_dsp_factory_imp()
    {
        std::ifstream is(filename, std::ifstream::binary);
        is.seekg(0, is.end);
        fLen = is.tellg();
        is.seekg(0, is.beg);
        fBytes = new uint8_t[fLen];
        is.read((char*)fBytes, fLen);
    }
    
    virtual ~wasm3_dsp_factory()
    {
        delete[] fBytes;
    }
    
    dsp* createDSPInstance();

};

class wasm3_dsp : public wasm_dsp_imp {
    
    private:
    
        IM3Environment fEnv;
        IM3Module fModule;
        IM3Runtime fInstance;
        IM3Function fCompute;
    
        void addFunction(const char* name, const char* type, M3RawCall fun)
        {
            M3Result result = m3_LinkRawFunction(fModule, "env", name, type, fun);
        }

    public:

        wasm3_dsp(wasm3_dsp_factory* factory);
    
        virtual ~wasm3_dsp()
        {
            m3_FreeRuntime(fInstance); // fModule is deallocated here
            m3_FreeEnvironment(fEnv);
        }
        
        virtual int getNumInputs()
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "getNumInputs");
            if (result) FATAL_INT("m3_FindFunction: %s", result);
  
            const char* i_argv[2] = { "0", NULL };
            result = m3_CallArgv(f, 1, i_argv);

            uint64_t value = *(uint64_t*)(fInstance->stack);
            return value;
        }
        
        virtual int getNumOutputs()
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "getNumOutputs");
            if (result) FATAL_INT("m3_FindFunction: %s", result);
            
            const char* i_argv[2] = { "0", NULL };
            result = m3_CallArgv(f, 1, i_argv);
            
            uint64_t value = *(uint64_t*)(fInstance->stack);
            return value;
        }
    
        virtual int getSampleRate()
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "getSampleRate");
            if (result) FATAL_INT("m3_FindFunction: %s", result);
            
            const char* i_argv[2] = { "0", NULL };
            result = m3_CallArgv(f, 1, i_argv);
            
            uint64_t value = *(uint64_t*)(fInstance->stack);
            return value;
        }
        
        virtual void init(int sample_rate)
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "init");
            if (result) FATAL("m3_FindFunction: %s", result);
            
            const char* i_argv[3] = { "0", std::to_string(sample_rate).c_str(), NULL };
            result = m3_CallArgv(f, 2, i_argv);
        }
        
        virtual void instanceInit(int sample_rate)
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "instanceInit");
            if (result) FATAL("m3_FindFunction: %s", result);
            
            const char* i_argv[3] = { "0", std::to_string(sample_rate).c_str(), NULL };
            result = m3_CallArgv(f, 2, i_argv);
        }
        
        virtual void instanceConstants(int sample_rate)
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "instanceConstants");
            if (result) FATAL("m3_FindFunction: %s", result);
            
            const char* i_argv[3] = { "0", std::to_string(sample_rate).c_str(), NULL };
            result = m3_CallArgv(f, 2, i_argv);
        }
        
        virtual void instanceResetUserInterface()
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "instanceResetUserInterface");
            if (result) FATAL("m3_FindFunction: %s", result);
            
            const char* i_argv[2] = { "0", NULL };
            result = m3_CallArgv(f, 1, i_argv);
        }
        
        virtual void instanceClear()
        {
            IM3Function f;
            M3Result result = m3_FindFunction(&f, fInstance, "instanceClear");
            if (result) FATAL("m3_FindFunction: %s", result);
            
            const char* i_argv[2] = { "0", NULL };
            result = m3_CallArgv(f, 1, i_argv);
        }
       
        virtual wasm3_dsp* clone()
        {
            return new wasm3_dsp(dynamic_cast<wasm3_dsp_factory*>(fFactory));
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            // Copy audio inputs
            for (int i = 0; i < fFactory->fDecoder->getNumInputs(); i++) {
                memcpy(fInputs[i], inputs[i], sizeof(FAUSTFLOAT) * count);
            }
            
            // Call wasm code
            const char* i_argv[5] = { "0", std::to_string(count).c_str(), std::to_string(fWasmInputs).c_str(), std::to_string(fWasmOutputs).c_str(), NULL };
            M3Result result = m3_CallArgv(fCompute, 4, i_argv);
            
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
