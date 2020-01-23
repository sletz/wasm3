
## faustwasm3

The **faustwasm3** tool loads a Faust generated wasm module and runs it using the wasm3 interpreter, JACK for the audio, and GTK for the GUI.

`faustwasm3 [-nvoices <num>] [-midi] foo.wasm`

Here are the available options:

- `-nvoices N to start the DSP in polyphonic mode with N voices`
- `-midi to activate MIDI control`

To test, clone the repository, and in the 'faust' folder:

`make && sudo make install `

Then compile a wasm file from a Faust DSP program like:

`faust -lang wasm noise.dsp -o noise.wasm`

And execute it with the wasm3 interpreter:

`faustwasm3 noise.wasm`

Compile a polyphonic aware DSP program like clarinetMIDI.dsp:

`faust -lang wasm clarinetMIDI.dsp -o clarinetMIDI.dsp`

And execute it with the wasm3 interpreter with MIDI and polyphonic activated:

`faustwasm3 -midi -nvoices 8 clarinetMIDI.wasm`

## faustbench-wasm3

The **faustbench-wasm3** tool loads a Faust generated wasm module, runs and benchmark it using the wasm3 interpreter.

`faustbench-wasm3 foo.wasm`

To test, clone the repository, and in the 'faust' folder:

`make && sudo make install `

Then compile a wasm file from a Faust DSP program like:

`faust -lang wasm noise.dsp -o noise.wasm`

And execute it with the wasm3 interpreter:

`faustbench-wasm3 noise.wasm`