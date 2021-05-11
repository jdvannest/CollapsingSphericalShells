---Set Up---
Enter the command "make" to create the executables "GenerateParamFile" and "Simulation".

Run the executable "GenerateParamFile" to create the text file "params.txt". This is the default parameter file, and can be edited as pleased in order add or edit shells to simulate.

---Run the Simulation---

Run the executable "Simulation" to perform the simulation prescribed in "params.txt". This will write out the data in a text file located in the "outputs/" directory.

The python script "Plot.py" will plot the simulation output in the "Plots/" directory. It takes the required flag "-f <path_to_output_file>" and an option flag "-g", which will compile a gif of the simulation if passed.

**NOTE TO JAMES: This python script uses f-strings, and thus requires python 3. I've not had any issues on my laptop or PC, but on schooner, the default python3 installation throughs an error on this script. I'm not sure why, but hopefully you're using your own installation of python if running this on schooner. Worst case scenario is moving the Plot.py and output text file somewhere else to run (sorry for the inconvenience).