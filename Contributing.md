# Contributing

## Reporting Issues

Bug reports are appreciated But please check if the issue has been reported or if it has been resolved in a release later than the one you use.


## Pull Requests

Your pull requests are welcome; however, they may not be accepted for various reasons. 

All branches should merge to the develop branch, only then at time of release 
will it be merged with master.

For typo corrections, open an issue.

## Naming Convention

Use all Capital with underscore seperator for constants and macros.

Use camelCase for variables, functions etc.

Use PascalCase for Types.

Use underscore as prefix for all private class / structure members

Use is / has / can / should etc prefix for boolean variables.

Use i, j, k, index etc for index variables or iterator variables.

## Documentation 

Doxygen documentation will only be built when code is ready to be released.
Doxygen comment blocks must be in /** ... */

### Files


	\file `[filename]`

	\brief  `[description]`

	Created [dd] [MONTH] [yyyy]

	This file is part of project Enhance C++ Libraries.

	Copyright 2020 <name>
	
	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

### pre-processor definitions

* description                          			: \brief description

### namespaces

* description                          			: \brief description 

### functions

* description                          			: \brief  description
* template parameters     	`<h3></h3>` 		: `<code>class ...</code>` : description
* Return		     	`<h3></h3>`     	: description
* Exceptions		     	`<h3></h3>`
* Complexity (Alg)	     	`<h3></h3>`
* average run time	   	`<h3></h3>`
* run time vs input table  	`<h3></h3>` 
* parameters		    				: `<i>[inout]</i>` : desc .  

### Variables

* description                          			: \brief  description

### Classes

* description                          			: \brief  description
* hasErrorHandlers                     			: true / false
* prefered prefix/suffix 
* template parameters      	`<h3></h3> `
* How To Use      			`<h3></h3> `
* Examples					`<h3></h3> `			  

### Structures / Unions

* description                          			: \brief  description
* template parameters      	`<h3></h3>`
* prefered prefix/suffix           

### Enumeration

* description                          			: \brief  description
* Element                              			: `<i>[value]</i>` : desc.. 

### Typedefs

* description                          			: \brief  description


`<h3></h3>` displayed means that, the field must be under a header like so `<h3>[field]</h3>` 

## Example :

A sample documentation:	

sample_doc.enh.h (does not exist)
<code>
	
	/** 
	\file sample_doc.enh.h

	\brief File for demonstrating documentation.

	Created 10 May 2020

	This file is part of project Enhance C++ Libraries.

	Copyright 2020 Harith Manoj <harithpub@gmail.com>
	
	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.


	*/
	
	/**
		\brief Function to add two numbers
		
		<h3>template</h3>
		<code>class arithmetic</code> : The type of numbers to be added, must be arithmetic type.
		
		<h3>Return</h3>
		The sum of the two arguments.
		
	*/
	template< class arithmetic>
	arithmetic add(
		arithmetic lhs /**<i>in</i> : lhs of operation*/,
		arithmetic rhs /**<i>in</i> : lhs of operation*/
	)
	{
		return lhs + rhs;
	}
</code>
