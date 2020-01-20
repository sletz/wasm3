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

#include "wasm3_dsp.h"
#include "faust/audio/jack-dsp.h"
#include "faust/gui/httpdUI.h"
#include "faust/gui/GTKUI.h"
#include "faust/gui/FUI.h"
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
    if (argc == 1 || isopt(argv, "-h") || isopt(argv, "-help") || !endWith(argv[1], ".wasm")) {
        cout << "faustwas3 foo.wasm" << endl;
        cout << "Open the http://127.0.0.1:5510 URL to get an http based control\n";
        exit(EXIT_FAILURE);
    }
    
    char name[256];
    char filename[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    
    snprintf(name, 255, "%s", basename(argv[0]));
    snprintf(filename, 255, "%s", basename(argv[argc-1]));
    snprintf(rcfilename, 255, "%s/.%s-%src", home, name, filename);
    
    wasm3_dsp_factory factory(argv[1]);
    dsp* DSP = factory.createDSPInstance();
    //delete DSP;
    //DSP = factory.createDSPInstance();
    
    jackaudio audio;
    if (!audio.init(argv[1], DSP)) {
        return 0;
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
    
    delete DSP;
    return 0;
}
