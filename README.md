# Numerical Methods in C

This small academic study verses about numerical methods of integration. There are the famous Runge-Kutta of 4th order and Euler methods implemented in ANSI C code. 

The integration functions are the Lorentz 1963 model.

All code are commented in Brazilian Portuguese. The methods can receive systems of any dimension and some parameter are required to be adjusted inside the code (number of steps, start and end) as well as the equations system. The output must be adjusted in Main() function. 

[Runge Kutta Classical 4th Order (RK4)](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods)

[Euler Method](https://en.wikipedia.org/wiki/Euler_method)

## Instructions

Just download the sources, run

	make

and all code will be compiled. No libs or addtional resources are required. 

Running any of the executables in the commmand line will print the results in the terminal screen. 

The historical.gnu and phase_portrait.gnu employs gnuplot tool to create JPEG images. The former plots the time evolution of each coordinate. The later plots the phase protraits for each dimension.

Calling in the command line
	
	./run.sh executable_name

will call the executable, keep results in a file dots.txt and call gnuplot to create plots from time evolution and phase portraits in the current directory. 


## TODO
	
	Translate comments to English
	Include a print fuction
	


