## Enhance C++ Libraries ##

![GitHub release (latest by date)](https://img.shields.io/github/v/release/harithmanoj/Enhance?label=stable%20release)
![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/harithmanoj/Enhance?include_prereleases&label=develop%20release)
![GitHub](https://img.shields.io/github/license/harithmanoj/Enhance)
![GitHub Release Date](https://img.shields.io/github/release-date/harithmanoj/Enhance?label=Stable%20Release%20Date)
![GitHub (Pre-)Release Date](https://img.shields.io/github/release-date-pre/harithmanoj/Enhance?label=develop%20alpha%20release)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/harithmanoj/Enhance/Test)

Develop Release v1.3.2.8.d1 alpha


Enhance C++ Libraries is a collection of multiple `C++` libraries that cater 
to many needs.

Including but not limited to :

* Diagnostics.
* Time and related tracking and synchronisation.
* Date Time manipulation
* Error Tracking.
* Version info to be used inside programs.
* Concurrent execution.

The Library requires `C++ standard 17` to compile.

The Library is released under [Apache License](https://github.com/harithmanoj/Enhance/blob/master/License.md)

Source code is Hosted in [GitHub](https://github.com/harithmanoj/Enhance)

Stable Releases can be found [here](https://github.com/harithmanoj/Enhance/releases)

Code Documentation is Hosted by GitHub Pages [here](https://harithmanoj.github.io/Enhance-cpp-libraries/nav/doc.html)

The branch master of Enhance repository contains last stable release code. For latest features,
bugfixes etc, see develop branch. Documentation for develop branch will not be built untill it 
is released, but documentation will be present as comments in the code itself.

<details>
<summary> <h2> Concurrent </h2> </summary>

Library for ease of concurrent programming.

Exists in `namespace enh`.

### Headers 

`QueuedProcess.enh.h`

### The Library 

* Class to asynchronously handle messages.

</details>

<details>
<summary> <h2> Diagnose </h2> </summary>

Diagnose is a diagnostics library to log to file during sequential code 
execution.

Exists in `namespace debug`, but use Macros for logging easily.

See `logger.enh.h` documentation for usage.

### Headers 

`logger.enh.h`

### The Library 

* Functions that log information to a file unique to each thread
* (E)rror, (W)arning, (I)nfo, (F)atal-(E)rror types of logging.

</details>

<details>
<summary> <h2> Error Handling </h2> </summary>

Error Handling Library is a library that contains functions and classes for 
various error handling uses.

Error tracking functionality and error signaling functionality.

Exists in `namespace enh`.

### Headers 

`ErrorTracker.enh.h`

`Tristate.enh.h`

### The Library 

* Class to be used for base class for inheriting error management functionality.

* Enumeration to provide 3 possible outcomes (good, error, blocked due to 
previous error) for functions.

</details>

<details>
<summary> <h2> Time </h2> </summary>

Library for date-time encapsulation, periodic signaling timer.

Exists in `namespace enh`.

### Header

`timer.enh.h`

`counter.enh.h`

`TimeStamp.enh.h`

`date.enh.h`

`DateTime.enh.h`

### The Library 

* Tracking time in a sec : min : hr : day manner(representation).

* Tracking time elapsed and providing clients to the class periodical signals.

* Block execution of a thread for a period of time accurately.

* Store and manipulate time.

* Store and manipulate date.

* Store and manipulate date and time simultaneously.

</details>

<details>
<summary> <h2> General Utility </h2> </summary>

The library consists of some utility functions, classes, class for versioning 
encapsulation, class for a value confined within dynamic and static limits, 
value which spans different fields of different denominations.

Exists in `namespace enh`.

### Headers 

`general.enh.h`

`ConfinedValue.enh.h`

`LimitedNumber.enh.h`

`WeightedField.enh.h`

`VersionInfo.enh.h`

### The Library 

* Class to be used for storing version information.
* Version of the Enhance C++ library
* Check if bits are high in a variable (also constexpr).
* Check if value is within bounds (also constexpr).
* Signum function and inclusive_ration (also constexpr).
* getOrdinalIndicator returns "th", "st", "nd" "rd" according to argument passed.
* signExtend extends the string format of a numeral by prepending '0' s
* ConfinedValue class for storing a value within bounds
* NumericSystem class for storing a value within 0 and an upper limit.
* Class to hold values which has different denominations. (eg money)
 
</details>

_______________________________________________________________________________

### Dependencies

All headers and source files uses standard c++ headers ( c++17 ).
The library uses exceptions.

#### Generic Utilities

* `general.enh.h` uses only standard c++ headers ( c++17 ).
* `ConfinedValue.enh.h` uses only standard c++ headers ( c++17 ).
* `LimitedNumber.enh.h` uses `ConfinedValue.enh.h` and standard c++ 
headers ( c++17 ).
* `VersionInfo.enh.h` uses only standard c++ headers ( c++17 ).
* `WeightedField.enh.h` uses only standard c++ headers ( c++17 ).

#### Diagnostics

* `logger.enh.h` requires compilation of `logger.cpp` which is compiled with 
c++17 and uses standard c++ headers ( c++17 ).

#### Error Handling 

* `Tristate.enh.h` uses only standard c++ headers ( c++17 ).
* `ErrorTracker.enh.h` uses `Tristate.enh.h`, `logger.enh.h`, `general.enh.h`
and requires compilation of `logger.cpp` and standard c++ headers ( c++17 ).

#### Concurrency

* `QueuedHandler.enh.h` uses `Tristate.enh.h` and standard c++ headers ( c++17 ).

#### Date and Time

* `counter.enh.h` only uses standard c++ headers ( c++17 ).
* `timer.enh.h` only uses standard c++ headers ( c++17 ).
* `date.enh.h` uses `LimitedNumber.enh.h`, `ConfinedValue.enh.h` and 
`general.enh.h` and standard c++ headers ( c++17 ).
* `TimeStamp.enh.h` uses `date.enh.h`, `LimitedNumber.enh.h`, 
`ConfinedValue.enh.h` and `general.enh.h` and standard c++ headers ( c++17 ).
* `DateTime.enh.h` uses `TimeStamp.enh.h`, `date.enh.h`, `LimitedNumber.enh.h`, 
`ConfinedValue.enh.h` and `general.enh.h` and standard c++ headers ( c++17 ).

### Dependency Graph

```
   Tristate.enh.h   logger.enh.h      general.enh.h       ConfinedValue.enh.h          VersionInfo.enh.h 
       |             |       |             |                   |
       |             |   logger.cpp        |                   |                       counter.enh.h 
       |             |                     |                   |
       +------+    +-+   +-----------------+---------+  LimitedNumber.enh            WeightedField.enh.h
       |      |    |     |                           |      |        
       |    ErrorTracker.enh.h                       |      |                             timer.enh.h 
       |                                            date.enh.h
QueuedHandler.enh.h                                     |
                                                 TimeStamp.enh.h
                                                        |
                                                  DateTime.enh.h
```


## HOW TO USE 

* Download required headers and source files (lookup the dependancy list above).
* For header only parts, compile with dependant code using c++17 with 
exceptions turned on.
* For the source files must be compile with c++17 and exceptions turned on.
* Refer Documentation for directions to use each class or functions, or 
MACRO (logging).


## Contribution

Code contribution is welcome. Refer [Contributing.md]
(https://github.com/harithmanoj/Enhance/blob/master/Contributing.md) 
for ways to contribute.



## AUTHOR

Harith Manoj, <harithpub@gmail.com>

