# qc15-peilinh2-gzhai5-yikait2

## Structure of the repo
- All required deliverable material, including development, final report, and slides of the presentations are in the deliverable/ folder.
  (Note that when organizing this repo and moving files around, we lost the commit history for MEETING_LOG.)
- All tests are conducted inthe file tests/test.cpp. Feel free to add or comment out tests.
- All data comes from the file data/. Feel free to add more data to the test.
- All outputs are placed in the outputs folder.
- The final presentation video is uploaded to the mediaspace webiste, and here is the link: https://mediaspace.illinois.edu/media/t/1_ndbogxq8.

## How to compile and run?
- to use our current airport/airline data, go ahead and run "make" to compile.
- to use customized data, locate line 51 in main.cpp file and switch the filename "data/airports.dat" and "data/airlines.dat" to data file of your choice. Then, run "make" to compile.
## How to make test?
- to use our current airport/airline data, go ahead and run "make test" to compile our test file.
- to use customized data, locate line 51 in main.cpp file and switch the filename"data/airports.dat" and "data/airlines.dat" to data file of your choice. Then, run "make test" to compile test files.
- After compling, type the command "./test" to run test file.
## About Data Acquisition

- The data we use for this project comes from "openflights.org".
- In paticular, we use the "airport database", and "route database", which gives information about almost all public airports and rouites of flights all over the world.
- The URL of the above mentioned databases are "https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat" for airports, and "https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat" for routes of flights.

- In interpreting the data, if any broken data is observed, such as the latitude and longitude are NOT viable numbers, the corresponding entry will be neglected.

## Final Presentation
- the final presentation video is uploaded to the mediaspace webiste, and here is the link: https://mediaspace.illinois.edu/media/t/1_ndbogxq8.






