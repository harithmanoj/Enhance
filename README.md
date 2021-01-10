## Enhance C++ Libraries ##



![GitHub release (latest by date)](https://img.shields.io/github/v/release/harithmanoj/Enhance?label=stable%20release)
![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/harithmanoj/enhance-develop?include_prereleases&label=develop%20release)
![GitHub](https://img.shields.io/github/license/harithmanoj/Enhance)
![GitHub Release Date](https://img.shields.io/github/release-date/harithmanoj/Enhance?label=Stable%20Release%20Date)
![GitHub (Pre-)Release Date](https://img.shields.io/github/release-date-pre/harithmanoj/enhance-develop?label=develop%20alpha%20release)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/harithmanoj/Enhance/Test)

Develop Release v1.3.2.8.d1 alpha


Enhance C++ Libraries is a collection of multiple `C++` libraries that cater 
to many needs.

Including but not limited to :

* Diagnostics.
* Time and related tracking and synchronisation.
* Date Time manipulation
* Error Tracking.qu
* Version info to be used inside programs.
* Concurrent execution.

The Library requires `C++ standard 17` to compile.

The Library is released under [Apache License](https://github.com/harithmanoj/Enhance/blob/master/License.md)

Source code is Hosted in [GitHub](https://github.com/harithmanoj/Enhance)

Stable Releases can be found [here](https://github.com/harithmanoj/Enhance/releases)

Code Documentation is Hosted by GitHub Pages [here](https://harithmanoj.github.io/Enhance/index.html)

The branch master of Enhance repository contains last stable release code. For latest features, 
bugfixes etc, see develop branch or [enhance-develop](https://github.com/harithmanoj/enhance-develop).

Documentation of Latest bug fixes and features can be found [here](https://harithmanoj.github.io/enhance-develop/index.html)

_______________________________________________________________________________
## Framework
_______________________________________________________________________________

Framework is a library that defines The version of Enhance C++ Library and 
class to store version info.

Exists in `namespace enh`.

### Headers 

`framework.enh.h`

### The Library 

* Class to be used for storing version information.

* Version of the Enhance C++ library


_______________________________________________________________________________
## General
_______________________________________________________________________________

General is a library of functions for general use.

Exists in `namespace enh`.

### Headers 

`general.enh.h`

`ConfinedValue.enh.h`

`numeral_system.enh.h`

`WeightedField.enh.h`

### The Library 

* Check if bits are high in a variable (also constexpr).
* Check if value is within bounds (also constexpr).
* Signum function and inclusive_ration (also constexpr).
* getOrdinalIndicator returns "th", "st", "nd" "rd" according to argument passed.
* signExtend extends the string format of a numeral by prepending '0' s
* ConfinedValue class for storing a value within bounds
* NumericSystem class for storing a value within 0 and an upper limit.
* Class to hold values which has different denominations. (eg money)
 
_______________________________________________________________________________
## Diagnose
_______________________________________________________________________________

Diagnose is a diagnostics library to log to file during sequential code 
execution.

Exists in `namespace debug`, but use Macros for logging easily.

See `logger.enh.h` documentation for usage.

### Headers 

`logger.enh.h`

### The Library 

* Functions that log information to a file unique to each thread
* 5 optimisation levels


_______________________________________________________________________________
## Error Handling
_______________________________________________________________________________

Error Handling Library is a library that contains functions and classes for 
various error handling uses.

Exists in `namespace enh`.

### Headers 

`error_base.enh.h`

### The Library 

* Class to be used for base class for inheriting error management functionality.

* Enumeration to provide 3 possible outcomes (good, error, blocked due to 
previous error) for functions.

_______________________________________________________________________________
## Concurrent
_______________________________________________________________________________

Library for ease of concurrent programming.

Exists in `namespace enh`.

### Headers 

`QueuedProcess.enh.h`

### The Library 

* Class that executes a function by passing messages pushed to a queue.
_______________________________________________________________________________
## Time
_______________________________________________________________________________

Library for time tracking, synchronisation etc. 

Exists in `namespace enh`.

### Header

`timer.enh.h`

`counter.enh.h`

`time_stamp.enh.h`

`date.enh.h`

`date_time.enh.h`

### The Library 

* Tracking time in a sec : min : hr : day manner(representation).

* Tracking time elapsed and providing clients to the class periodical signals.

* Block execution of a thread for a period of time accurately.

* Store and manipulate time.

* Store and manipulate date.

* Store and manipulate date and time simultaneously.

## HOW TO INSTALL 

* Download all required headers and source files, and add them to dependancy 
project.

* Make sure to compile in `C++17`.

### Dependencies

* `VersionInfo.enh.h` depends only on standard c++ headers.
* `general.enh.h` depends only on standard c++ headers.
* `logger.enh.h` depends only on standard c++ headers but requires 
compilation of `logger.cpp`.
* `WeightedField.enh.h` depends only on standard c++ headers.
* `error_base.enh.h` depends on `general.enh.h`, `logger.enh.h`.
* `QueuedProcess.enh.h` depends on `Tristate.enh.h`.
* `counter.enh.h` depends only on standard c++ headers.
* `timer.enh.h` depends only on standard c++ headers.
* `date.enh.h` depends on `general.enh.h`, `numerical_system.enh.h`, 
`ConfinedValue.enh.h`.
* `time_stamp.enh.h` depends on `date.enh.h`, `general.enh.h`, 
`numeral_system.enh.h`, `ConfinedValue.enh.h`.
* `date_time.enh.h` depends on `time_stamp.enh.h`, `date.enh.h`, 
`general.enh.h`, `numerical_system.enh.h`, `ConfinedValue.enh.h`.

### Dependency Graph

   Tristate.enh.h   logger.enh.h      general.enh.h       ConfinedValue.enh.h          VersionInfo.enh.h 
       |             |       |             |                   |
       |             |   logger.cpp        |                   |                       counter.enh.h 
       |             |                     |                   |
       +------+    +-+   +-----------------+---------+  numeral_system.enh            WeightedField.enh.h
       |      |    |     |                           |     |        
       |    ErrorTracker.enh.h                         |     |                             timer.enh.h 
       |                                            date.enh.h
QueuedProcess.enh.h                                     |
                                                 time_stamp.enh.h
                                                        |
                                                  date_time.enh.h

## Contribution


Code contribution is welcome. Refer [Contributing.md]
(https://github.com/harithmanoj/Enhance/blob/master/Contributing.md) 
for ways to contribute.



## AUTHOR

Harith Manoj, <harithpub@gmail.com>

