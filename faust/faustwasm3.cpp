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

#include <libgen.h>

/*
#ifndef FAUSTFLOAT
#define FAUSTFLOAT double
#endif
*/

#include "wasm3_dsp.h"

#include "faust/audio/jack-dsp.h"
#include "faust/dsp/poly-dsp.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/gui/httpdUI.h"
#include "faust/gui/GTKUI.h"
#include "faust/gui/FUI.h"
#include "faust/gui/MidiUI.h"
#include "faust/misc.h"

using namespace std;

list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

static bool endWith(const string& str, const string& suffix)
{
    size_t i = str.rfind(suffix);
    return (i != string::npos) && (i == (str.length() - suffix.length()));
}

int main(int argc, char* argv[])
{
    if (argc == 1 || isopt(argv, "-h") || isopt(argv, "-help") || !endWith(argv[argc-1], ".wasm")) {
        cout << "faustwas3 [-nvoices <num>] [-midi] [-ds <factor>] [-us <factor>] [-filter <type>] foo.wasm" << endl;
        cout << "Open the http://127.0.0.1:5510 URL to get an http based control\n";
        exit(EXIT_FAILURE);
    }
    
    char name[256];
    char filename[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    
    dsp* DSP = nullptr;
    MidiUI* midiinterface = nullptr;
    
    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(filename, 255, "%s", basename(argv[argc-1]));
    snprintf(rcfilename, 255, "%s/.%s-%src", home, name, filename);
    
    bool is_midi = isopt(argv, "-midi");
    int nvoices = lopt(argv, "-nvoices", -1);
    int ds = lopt(argv, "-ds", 1);
    int up = lopt(argv, "-us", 1);
    int filter = lopt(argv, "-filter", 1);
    
    wasm3_dsp_factory factory(argv[argc - 1]);
    DSP = factory.createDSPInstance();
    
    if (nvoices > 0) {
        cout << "Starting polyphonic mode 'nvoices' : " << nvoices << endl;
        DSP = new mydsp_poly(DSP, nvoices, true, true);
    }
    
    if (ds != 1) {
        switch (filter) {
            case 1:
                if (ds == 2) DSP = new dsp_down_sampler<LowPass3<Double<45,100>, 2, float>>(DSP);
                else if (ds == 4) DSP = new dsp_down_sampler<LowPass3<Double<45,100>, 4, float>>(DSP);
                else if (ds == 8) DSP = new dsp_down_sampler<LowPass3<Double<45,100>, 8, float>>(DSP);
                else if (ds == 16) DSP = new dsp_down_sampler<LowPass3<Double<45,100>, 16, float>>(DSP);
                else cerr << "Downsampling factor must be a power of two and <= 16\n";
                break;
            case 2:
                if (ds == 2) DSP = new dsp_down_sampler<LowPass4<Double<45,100>, 2, float>>(DSP);
                else if (ds == 4) DSP = new dsp_down_sampler<LowPass4<Double<45,100>, 4, float>>(DSP);
                else if (ds == 8) DSP = new dsp_down_sampler<LowPass4<Double<45,100>, 8, float>>(DSP);
                else if (ds == 16) DSP = new dsp_down_sampler<LowPass4<Double<45,100>, 16, float>>(DSP);
                else cerr << "Downsampling factor must be a power of two and <= 16\n";
                break;
            case 3:
                if (ds == 2) DSP = new dsp_down_sampler<LowPass3e<Double<45,100>, 2, float>>(DSP);
                else if (ds == 4) DSP = new dsp_down_sampler<LowPass3e<Double<45,100>, 4, float>>(DSP);
                else if (ds == 8) DSP = new dsp_down_sampler<LowPass3e<Double<45,100>, 8, float>>(DSP);
                else if (ds == 16) DSP = new dsp_down_sampler<LowPass3e<Double<45,100>, 16, float>>(DSP);
                else cerr << "Downsampling factor must be a power of two and <= 16\n";
                break;
            case 4:
                if (ds == 2) DSP = new dsp_down_sampler<LowPass6e<Double<45,100>, 2, float>>(DSP);
                else if (ds == 4) DSP = new dsp_down_sampler<LowPass6e<Double<45,100>, 4, float>>(DSP);
                else if (ds == 8) DSP = new dsp_down_sampler<LowPass6e<Double<45,100>, 8, float>>(DSP);
                else if (ds == 16) DSP = new dsp_down_sampler<LowPass6e<Double<45,100>, 16, float>>(DSP);
                else cerr << "Downsampling factor must be a power of two and <= 16\n";
                break;
            default:
                cerr << "Incorrect filter type : " << filter << endl;
                break;
        }
    } else if (up != 1) {
        switch (filter) {
            case 1:
                if (up == 2) DSP = new dsp_up_sampler<LowPass3<Double<45,100>, 2, float>>(DSP);
                else if (up == 4) DSP = new dsp_up_sampler<LowPass3<Double<45,100>, 4, float>>(DSP);
                else if (up == 8) DSP = new dsp_up_sampler<LowPass3<Double<45,100>, 8, float>>(DSP);
                else if (up == 16) DSP = new dsp_up_sampler<LowPass3<Double<45,100>, 16, float>>(DSP);
                else cerr << "Upsampling factor must be a power of two and <= 16\n";
                break;
            case 2:
                if (up == 2) DSP = new dsp_up_sampler<LowPass4<Double<45,100>, 2, float>>(DSP);
                else if (up == 4) DSP = new dsp_up_sampler<LowPass4<Double<45,100>, 4, float>>(DSP);
                else if (up == 8) DSP = new dsp_up_sampler<LowPass4<Double<45,100>, 8, float>>(DSP);
                else if (up == 16) DSP = new dsp_up_sampler<LowPass4<Double<45,100>, 16, float>>(DSP);
                else cerr << "Upsampling factor must be a power of two and <= 16\n";
                break;
            case 3:
                if (up == 2) DSP = new dsp_up_sampler<LowPass3e<Double<45,100>, 2, float>>(DSP);
                else if (up == 4) DSP = new dsp_up_sampler<LowPass3e<Double<45,100>, 4, float>>(DSP);
                else if (up == 8) DSP = new dsp_up_sampler<LowPass3e<Double<45,100>, 8, float>>(DSP);
                else if (up == 16) DSP = new dsp_up_sampler<LowPass3e<Double<45,100>, 16, float>>(DSP);
                else cerr << "Upsampling factor must be a power of two and <= 16\n";
                break;
            case 4:
                if (up == 2) DSP = new dsp_up_sampler<LowPass6e<Double<45,100>, 2, float>>(DSP);
                else if (up == 4) DSP = new dsp_up_sampler<LowPass6e<Double<45,100>, 4, float>>(DSP);
                else if (up == 8) DSP = new dsp_up_sampler<LowPass6e<Double<45,100>, 8, float>>(DSP);
                else if (up == 16) DSP = new dsp_up_sampler<LowPass6e<Double<45,100>, 16, float>>(DSP);
                else cerr << "Upsampling factor must be a power of two and <= 16\n";
                break;
            default:
                cerr << "Incorrect filter type : " << filter << endl;
                break;
        }
    }
    
    jackaudio_midi audio;
    if (!audio.init(filename, DSP)) {
        return 0;
    }
    
    if (is_midi) {
        midiinterface = new MidiUI(&audio);
        DSP->buildUserInterface(midiinterface);
        midiinterface->run();
    }
    
    httpdUI httpdinterface(argv[1], DSP->getNumInputs(), DSP->getNumOutputs(), argc, argv);
    DSP->buildUserInterface(&httpdinterface);
    
    GTKUI interface(filename, &argc, &argv);
    DSP->buildUserInterface(&interface);
    
    FUI finterface;
    DSP->buildUserInterface(&finterface);
    
    // State (after UI construction)
    finterface.recallState(rcfilename);
    audio.start();
    
    httpdinterface.run();
    interface.run();
    
    finterface.saveState(rcfilename);
    
    audio.stop();
    
    delete midiinterface;
    delete DSP;
    return 0;
}
