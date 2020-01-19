
## faustwasm3

The **faustwasm3** tool loads a Faust generated wasm model and runs it using the wasm2 interpreter, JACK and GTK.

`faustwasm3 foo.wasm`

To test, clone the repository and in the 'faust' folder:

`make && sudo make install `

Then compile a wasm file from a Faust DSP program like:

`faust -lang noise.dsp -o noise.wasm`

Ane execute it with the wasm3 interpreter:

`faustwasm3 noise.wasm`
